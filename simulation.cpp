#include "simulation.h"

//static function
static instruction_t getInstruction(const creature_t &creature)
{
	return creature.species->program[creature.programID-1];
}

static creature_t *getCreature(const grid_t &grid, point_t location)
{
	return grid.squares[location.r][location.c];
}

static point_t adjacentPoint(point_t pt, direction_t dir)
{
	if(directName[dir]=="north")
		pt.r=pt.r-1;
	else if(directName[dir]=="south")
		pt.r=pt.r+1;
	else if(directName[dir]=="west")
		pt.c=pt.c-1;
	else if(directName[dir]=="east")
		pt.c=pt.c+1;
	return pt;
}

static direction_t leftFrom(direction_t dir)
{
	if(directName[dir]=="north")
		dir=WEST;
	else if(directName[dir]=="south")
		dir=EAST;
	else if(directName[dir]=="west")
		dir=SOUTH;
	else if(directName[dir]=="east")
		dir=NORTH;
	return dir;
}

static direction_t rightFrom(direction_t dir)
{
	if(directName[dir]=="north")
		dir=EAST;
	else if(directName[dir]=="south")
		dir=WEST;
	else if(directName[dir]=="west")
		dir=NORTH;
	else if(directName[dir]=="east")
		dir=SOUTH;
	return dir;
}

static bool ifempty(point_t p,const grid_t &grid)
{
	if(p.r<0||p.r>=(int)grid.height||p.c<0||p.c>=(int)grid.width)
		return 0;
	else if(grid.squares[p.r][p.c])
		return 0;
	else
		return 1;
}

static bool ifwall(point_t p,const grid_t &grid)
{
	if(p.r<0||p.r>=(int)grid.height||p.c<0||p.c>=(int)grid.width)
		return 1;
	else
		return 0;
}

static bool ifenemy(point_t p,const grid_t &grid, const creature_t &creature)
{
	if(p.r<0||p.r>=(int)grid.height||p.c<0||p.c>=(int)grid.width)
		return 0;
	else if(grid.squares[p.r][p.c])
		return creature.species->name!=getCreature(grid,p)->species->name;
	else
		return 0;
}

static bool ifsame(point_t p,const grid_t &grid, const creature_t &creature)
{
	if(p.r<0||p.r>=(int)grid.height||p.c<0||p.c>=(int)grid.width)
		return 0;
	else if(grid.squares[p.r][p.c])
		return creature.species->name==getCreature(grid,p)->species->name;
	else
		return 0;
}

static void updateID(creature_t &creature, unsigned int s)
{
	if(s==0&&((creature.programID+1)<=creature.species->programSize))
		creature.programID++;
	else if(s==0&&((creature.programID+1)>creature.species->programSize))
		creature.programID=1;
	else
		creature.programID=s;

}

static void runInstruction(creature_t &creature, grid_t &grid)
{
	point_t p1=adjacentPoint(creature.location, creature.direction);
	unsigned int s=0;
	if(opName[getInstruction(creature).op]=="hop"&&ifempty(p1,grid))
	{
		grid.squares[p1.r][p1.c]=&creature;
		grid.squares[creature.location.r][creature.location.c]=NULL;
		creature.location=p1;
	}
	else if(opName[getInstruction(creature).op]=="right")
	{
		direction_t dir=rightFrom(creature.direction);
		creature.direction=dir;
	}
	else if(opName[getInstruction(creature).op]=="left")
	{
		direction_t dir=leftFrom(creature.direction);
		creature.direction=dir;
	}
	else if(opName[getInstruction(creature).op]=="go")
	{
		s=getInstruction(creature).address;
	}
	else if(opName[getInstruction(creature).op]=="ifwall"&&ifwall(p1,grid))
	{
		s=getInstruction(creature).address;
	}
	else if(opName[getInstruction(creature).op]=="ifsame"&&ifsame(p1,grid,creature))
	{
		s=getInstruction(creature).address;
	}
	else if(opName[getInstruction(creature).op]=="ifempty"&&ifempty(p1,grid))
	{
		s=getInstruction(creature).address;
	}
	else if(opName[getInstruction(creature).op]=="ifenemy"&&ifenemy(p1,grid,creature))
	{
		s=getInstruction(creature).address;
	}
	else if(opName[getInstruction(creature).op]=="infect"&&ifenemy(p1,grid,creature))
	{
		getCreature(grid,p1)->species=creature.species;
		getCreature(grid,p1)->programID=1;
	}
	else{}
	updateID(creature,s);
	
}


// initialization, simulation and print function
bool initWorld(world_t &world, const string &speciesFile,const string &creaturesFile)
{	
	//Open the file
	ifstream infile1;//species-summary file
	ifstream infile2;//world file
	ifstream infile3;// species specification file
	infile1.open(speciesFile);
	infile2.open(creaturesFile);
	istringstream strr;// the string stream
	if(!infile1)
	{
		cout<<"Error: Cannot open file "<<speciesFile<<"!"<<endl;
		return 0;
	}
	if(!infile2)
	{
		cout<<"Error: Cannot open file "<<creaturesFile<<"!"<<endl;
		return 0;
	}


	//initialise the species
	string s;//directory
	string s1;//file name
	string s2;//the total path
	string s3;//the instruction line;
	string s4;//the instruction name
	unsigned int s5;// the address number of the instruction
	unsigned int i=0;//the index of species
	getline(infile1,s);
	for(unsigned int i=0;i<MAXHEIGHT;i++)
	for(unsigned int j=0;j<MAXWIDTH;j++)
		world.grid.squares[i][j]=NULL;
	while(getline(infile1,s1))
	{
		if(s1.size()==0)
			 break;
		world.species[i].name=s1;
		s2=s+'/'+s1;
		infile3.open(s2.c_str());
		if(!infile3)
		{
			cout<<"Error: Cannot open file "<<s2<<"!"<<endl;
			return 0;
		}
		if(i>=MAXSPECIES)
		{
			cout<<"Error: Too many species!"<<endl;
			cout<<"Maximal number of species is "<<MAXSPECIES<<"."<<endl;
			return 0;
		}
		unsigned int j=0;// index of instruction
		while(getline(infile3,s3))
		{
			if(s3.size()==0)
				break;
			strr.clear();//rebind the string
			strr.str(s3);
			strr>>s4;
			if(j>=MAXPROGRAM)
			{
				cout<<"Error: Too many instructions for species "<<s1<<"!"<<endl;
				cout<<"Maximal number of instructions is "<<MAXPROGRAM<<"."<<endl;
				return 0;
			}
		    if(s4==opName[HOP])
			{
				world.species[i].program[j].op=HOP;
				world.species[i].program[j].address=0;
			}
			else if(s4==opName[LEFT])
			{
				world.species[i].program[j].op=LEFT;
				world.species[i].program[j].address=0;
			}
			else if(s4==opName[RIGHT])
			{
				world.species[i].program[j].op=RIGHT;
				world.species[i].program[j].address=0;
			}
			else if(s4==opName[INFECT])
			{
				world.species[i].program[j].op=INFECT;
				world.species[i].program[j].address=0;
			}
			else 
			{
				strr>>s5;
				world.species[i].program[j].address=s5;
				if(s4==opName[IFEMPTY])
					world.species[i].program[j].op=IFEMPTY;
				else if(s4==opName[IFENEMY])
					world.species[i].program[j].op=IFENEMY;
				else if(s4==opName[IFSAME])
					world.species[i].program[j].op=IFSAME;
				else if(s4==opName[IFWALL])
					world.species[i].program[j].op=IFWALL;
				else if(s4==opName[GO])
					world.species[i].program[j].op=GO;
				else{
					cout<<"Error: Instruction "<<s4<<" is not recognized!"<<endl;
					return 0;
				}
				
			}
			j=j+1;
			
		}
		world.species[i].programSize=j;
		i=i+1;
		infile3.close();
	}
	world.numSpecies=i;


	//intialise the grid and creature
	unsigned int height;// the height of the grid
	unsigned int width;// the width of the grid
	string creature;//the name of the creature
	string direction;//the direction of the creature
	int row; // the row of the creature's location
	int column;// the column of the creature's location
	infile2>>height>>width;
	if(height>MAXHEIGHT||height<1)
	{
		cout<<"Error: The grid height is illegal!"<<endl;
		return 0;
	}
	if(width>MAXWIDTH||width<1)
	{
		cout<<"Error: The grid width is illegal!"<<endl;
		return 0;
	}
	world.grid.height=height;
	world.grid.width=width;
	i=0;// the index of creature
	infile2.get();
	while(getline(infile2,s3))
	{
		if(s3.size()==0)
			break;
		strr.clear();
		strr.str(s3);
		strr>>creature;
		strr>>direction;
		strr>>row;
	        strr>>column;
		if(i>=MAXCREATURES)
		{
			cout<<"Error: Too many creatures!"<<endl;
			cout<<"Maximal number of creatures is "<<MAXCREATURES<<"."<<endl;
			return 0;
		}
		
		if(world.grid.squares[row][column])
		{
			cout<<"Error: Creature ("<<creature<<" "<<direction<<" "<<row<<" "<<column
			<<") overlaps with creature ("<<world.grid.squares[row][column]->species->name<<" "
			<<directName[world.grid.squares[row][column]->direction]<<" "<<row<<" "<<column<<")!"<<endl;
			return 0;
		}
		else
			world.grid.squares[row][column]=&world.creatures[i];
		if(row<0||row>=(int)world.grid.height||column<0||column>=(int)world.grid.width)
		{
			cout<<"Error: Creature ("<<creature<<" "<<direction<<" "<<row<<" "<<column
			<<") is out of bound!"<<endl;
			cout<<"The grid size is "<<world.grid.height<<"-by-"<<world.grid.width<<"."<<endl;
			return 0;
		}
		world.creatures[i].location={row,column};
		world.creatures[i].programID=1;
		if(direction==directName[EAST])
			world.creatures[i].direction=EAST;
		else if(direction==directName[SOUTH])
			world.creatures[i].direction=SOUTH;
		else if(direction==directName[WEST])
			world.creatures[i].direction=WEST;
		else if(direction==directName[NORTH]) 
			world.creatures[i].direction=NORTH;
		else
		{
			cout<<"Error: Direction "<<direction<<" is not recognized!"<<endl;
			return 0;
		}
		int flag=0;
		for(unsigned int j=0;j<world.numSpecies;j++)
		{
			if(creature==world.species[j].name)
			{
				world.creatures[i].species=&world.species[j];
				flag=1;
				break;
				
			}
		}
		if(flag==0)
		{
			cout<<"Error: Species "<<creature<<" not found!"<<endl;
			return 0;
		}
		i=i+1;
	}
	world.numCreatures=i;

	
	return 1;
}


void simulateCreature(creature_t &creature, grid_t &grid, bool verbose)
{
	
      if(verbose==1)
      {	
	cout<<"Creature "<<"("<<creature.species->name<<" "<<directName[creature.direction]
            <<" "<<creature.location.r<<" "<<creature.location.c<<") takes action:"<<endl;
	for(unsigned int i=0;i<MAXPROGRAM;i++)
	{
		if(opName[getInstruction(creature).op]=="hop"||opName[getInstruction(creature).op]=="left"||opName[getInstruction(creature).op]=="right"||
		opName[getInstruction(creature).op]=="infect")
		{
			cout<<"Instruction "<<creature.programID<<": "<<opName[getInstruction(creature).op]<<endl;
			runInstruction(creature,grid);
			break;
		}
		else
		{
			cout<<"Instruction "<<creature.programID<<": "<<opName[getInstruction(creature).op]<<" "<<
                        getInstruction(creature).address<<endl;
			runInstruction(creature,grid);
		}
	}
	printGrid(grid);
      }
      else
      {
	for(unsigned int i=0;i<MAXPROGRAM;i++)
	{
		if(opName[getInstruction(creature).op]=="hop"||opName[getInstruction(creature).op]=="left"
                  ||opName[getInstruction(creature).op]=="right"||opName[getInstruction(creature).op]=="infect")
		{
			cout<<"Creature "<<"("<<creature.species->name<<" "<<directName[creature.direction]
            <<" "<<creature.location.r<<" "<<creature.location.c<<") takes action: "<<opName[getInstruction(creature).op]<<endl;
			runInstruction(creature,grid);
			break;
		}
		else
		{
			runInstruction(creature,grid);
		}
	}	
      }
	
}


void printGrid(const grid_t &grid)
{
	for(unsigned int i=0;i<grid.height;i++)
	{
		for(unsigned j=0;j<grid.width;j++)
		{
			if(grid.squares[i][j])
				cout<<grid.squares[i][j]->species->name[0]<<grid.squares[i][j]->species->name[1]<<'_'
				<<directShortName[grid.squares[i][j]->direction]<<" ";
			else
				cout<<setw(5)<<right<<setfill('_')<<" ";
		}
		cout<<endl;
	}
}








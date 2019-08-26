#include <iostream>
#include <string>
#include "world_type.h"
#include "simulation.h"
using namespace std;

int main(int argc, char* argv[])
{
	//checking and initialization
	if(argc<3)
	{
		cout<<"Error: Missing arguments!"<<endl;
		cout<<"Usage: ./p3 <species-summary> <world-file> <rounds> [v|verbose]"<<endl;
		return 0;
	}
	
	int round=atoi(argv[3]);
	bool verbose;
	string s="verbose";
	string s1="v";
	if(argc<5)
		verbose=0;
	else if(~s.compare(argv[4])||~s.compare(argv[4]))
		verbose=1;
	else
		verbose=0;
	if(round<0)
	{
		cout<<"Error: Number of simulation rounds is negative!"<<endl;
		return 0;
	}
	world_t world;
	if(!initWorld(world,argv[1],argv[2]))
		return 0;


	//Simulation
	cout<<"Initial state"<<endl;
	printGrid(world.grid);
	for(int i=0;i<round;i++)
	{
		cout<<"Round "<<i+1<<endl;
		for(unsigned int j=0;j<world.numCreatures;j++)
			simulateCreature(world.creatures[j], world.grid, verbose);
		if(verbose==0)		
			printGrid(world.grid);
	}
	
	return 0;
}

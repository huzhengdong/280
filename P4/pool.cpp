#include "pool.h"
using namespace std;

Pool::Pool(){
	for(int i=0;i<NP;i++){
		if(i==0)
		{
			Piece p(SHORT,BEIGE,CIRCLE,HOLLOW);
			pieces[i]=p;
		}	
		else if(i==1)
		{
			Piece p(SHORT,BEIGE,CIRCLE,SOLID);
			pieces[i]=p;
		}
		else if(i==2)
		{
			Piece p(SHORT,BEIGE,SQUARE,HOLLOW);
			pieces[i]=p;
		}
		else if(i==3)
		{
			Piece p(SHORT,BEIGE,SQUARE,SOLID);
			pieces[i]=p;
		}
		else if(i==4)
		{
			Piece p(SHORT,SEPIA,CIRCLE,HOLLOW);
			pieces[i]=p;
		}
		else if(i==5)
		{
			Piece p(SHORT,SEPIA,CIRCLE,SOLID);
			pieces[i]=p;
		}
		else if(i==6)
		{
			Piece p(SHORT,SEPIA,SQUARE,HOLLOW);
			pieces[i]=p;
		}
		else if(i==7)
		{
			Piece p(SHORT,SEPIA,SQUARE,SOLID);
			pieces[i]=p;
		}
		else if(i==8)
		{
			Piece p(TALL,BEIGE,CIRCLE,HOLLOW);
			pieces[i]=p;
		}
		else if(i==9)
		{
			Piece p(TALL,BEIGE,CIRCLE,SOLID);
			pieces[i]=p;
		}
		else if(i==10)
		{
			Piece p(TALL,BEIGE,SQUARE,HOLLOW);
			pieces[i]=p;
		}
		else if(i==11)
		{
			Piece p(TALL,BEIGE,SQUARE,SOLID);
			pieces[i]=p;
		}	
		else if(i==12)
		{
			Piece p(TALL,SEPIA,CIRCLE,HOLLOW);
			pieces[i]=p;
		}
		else if(i==13)
		{
			Piece p(TALL,SEPIA,CIRCLE,SOLID);
			pieces[i]=p;
		}
		else if(i==14)
		{
			Piece p(TALL,SEPIA,SQUARE,HOLLOW);
			pieces[i]=p;
		}
		else 
		{
			Piece p(TALL,SEPIA,SQUARE,SOLID);
			pieces[i]=p;
		}
	}
}

Piece & Pool::getUnusedPiece(int index){
	if(pieces[index].isUsed())
		throw UsedPieceException(pieces[index]);
	else
		return pieces[index];
}
Piece & Pool::getUnusedPiece(Height h, Color c, Shape s, Top t){
	int index=0;
	if(t==SOLID) index+=1;
	if(s==SQUARE) index+=2;
	if(c==SEPIA) index+=4;
	if(h==TALL) index+=8;
	return getUnusedPiece(index);
}

Piece & Pool::getUnusedPiece(const std::string &in){
	int index=0;
	if(in.substr(0,1)=="T") index+=8;
	if(in.substr(1,1)=="E") index+=4;
	if(in.substr(2,1)=="Q") index+=2;
	if(in.substr(3,1)=="O") index+=1;
	return getUnusedPiece(index);
}

std::string Pool::toString() const{
	int a=0;
	for(int i=0;i<NP;i++)
	{
		if(pieces[i].isUsed()==0)
			a++;
	}
	
	if(a==0)
		return "";
	else{
		ostringstream p;
		p<<"Available:"<<endl;
		for(int i=0; i<16;i++)
		{
			if(pieces[i].isUsed()==0)
			p<<pieces[i].toString().substr(0,2)<<" ";
		}
		p<<endl;
		for(int j=0; j<16;j++)
		{
			if(pieces[j].isUsed()==0)
			p<<pieces[j].toString().substr(2,2)<<" ";
		}
		p<<endl;
		return p.str();
	}		
}






#include "board.h"
#include <iomanip>
#include <iostream>
using namespace std;

Board::Board(){
	Vaxis v[]={A, B, C, D};
	Haxis h[]={H1, H2, H3, H4};
	for(int m=0;m<N;m++)
		for(int n=0;n<N;n++)
			grid[m][n]=Square(v[m],h[n]);
}

Square & Board::getSquare(Vaxis v, Haxis h)
{
	return grid[v][h];
}

Square & Board::getEmptySquare(Vaxis v, Haxis h)
{
	if(grid[v][h].isEmpty())
		return grid[v][h];
	else 
		throw SquareException(grid[v][h] ,"not empty");
}

Square & Board::getEmptySquare(const std::string &s)
{
	Vaxis v;
	Haxis h;
	if(s.substr(0,1)=="A")
		v=A;
	else if(s.substr(0,1)=="B")
		v=B;
	else if(s.substr(0,1)=="C")
		v=C;
	else
		v=D;

	if(s.substr(1,1)=="1")
		h=H1;
	else if(s.substr(1,1)=="2")
		h=H2;
	else if(s.substr(1,1)=="3")
		h=H3;
	else
		h=H4;
	return getEmptySquare(v,h);
}
void Board::place(Piece &p, Square &sq)
{
	sq.setPiece(&p);
	p.setUsed(true);
}


bool Board::isWinning(const Piece &p, const Square &sq)
{
	Vaxis v=sq.getV();
	Haxis h=sq.getH();
	bool win[3]={true,true,true};
	for(int i=0;i<N;i++)
	{
		if(h!=i)
		{	
			if(grid[v][i].isEmpty())
			{	
				win[0]=0;
			}
		}
		if(v!=i)
		{
			if(grid[i][h].isEmpty())
			{
				win[1]=0;	
			}
		}
		
	}
	if(sq.isOnFirstDiagonal())
	{
		for(int i=0;i<N;i++)
		{
			if(v!=i)
			if(grid[i][i].isEmpty())
				win[2]=0;
			
		}
	}
	else if(sq.isOnSecondDiagonal())
	{
		for(int i=0;i<N;i++)
		{
			if(v!=i)
			if(grid[i][3-i].isEmpty())
				win[2]=0;
			
		}
	}
	else
		win[2]=0;
	if(win[0])
	{
		bool hh=1; bool c=1; bool s=1; bool t=1;
		for(int i=0;i<N;i++)
		{
			if(h!=i)
			{
				if(!grid[v][i].getPiece().compareHeight(p))
					hh=0;
				if(!grid[v][i].getPiece().compareColor(p))
					c=0;
				if(!grid[v][i].getPiece().compareShape(p))
					s=0;
				if(!grid[v][i].getPiece().compareTop(p))
					t=0;
			}
		} 
		win[0]=hh||c||s||t;
	}
	if(win[1])
	{
		bool hh=1; bool c=1; bool s=1; bool t=1;
		for(int i=0;i<N;i++)
		{
			if(v!=i)
			{
				if(!grid[i][h].getPiece().compareHeight(p))
					hh=0;
				if(!grid[i][h].getPiece().compareColor(p))
					c=0;
				if(!grid[i][h].getPiece().compareShape(p))
					s=0;
				if(!grid[i][h].getPiece().compareTop(p))
					t=0;
			}
		} 
		win[1]=hh||c||s||t;
	}
	if(win[2])
	{
		if(sq.isOnFirstDiagonal())
		{
			bool hh=1; bool c=1; bool s=1; bool t=1;
			for(int i=0;i<N;i++)
			{
				if(v!=i)
				{
					
					if(!grid[i][i].getPiece().compareHeight(p))
						hh=0;
					if(!grid[i][i].getPiece().compareColor(p))
						c=0;
					if(!grid[i][i].getPiece().compareShape(p))
						s=0;
					if(!grid[i][i].getPiece().compareTop(p))
						t=0;
				}
				
			
			}
			win[2]=hh||c||s||t;

		}
		else 
		{
			bool hh=1; bool c=1; bool s=1; bool t=1;
			for(int i=0;i<N;i++)
			{
				
				if(v!=i)
				{
				
					if(!grid[i][3-i].getPiece().compareHeight(p))
						hh=0;
					if(!grid[i][3-i].getPiece().compareColor(p))
						c=0;
					if(!grid[i][3-i].getPiece().compareShape(p))
						s=0;
					if(!grid[i][3-i].getPiece().compareTop(p))
						t=0;
				}
			
			}
			win[2]=hh||c||s||t;
		}	
	}

	return win[0]||win[1]||win[2];
}


std::string Board::toString() const
{
	ostringstream m;
	m<<" "<<setw(5)<<right<<setfill(' ')<<"1"
	<<setw(5)<<right<<setfill(' ')<<"2"
	<<setw(5)<<right<<setfill(' ')<<"3"
	<<setw(5)<<right<<setfill(' ')<<"4"
	<<endl;
	char vex[]={'a','b','c','d'};
	for(int i=0; i<N; i++)
	{
		m<<"   +----+----+----+----+"<<endl;
		m<<" "<<vex[i]<<" |";
		for(int j=0; j<N;j++)
		{
			if(grid[i][j].isEmpty())
				m<<setw(5)<<right<<setfill(' ')<<"|";
			else
				m<<" "<<grid[i][j].getPiece().toString().substr(0,2)<<" |";
		}
		m<<endl;
		m<<"   |";
		for(int j=0; j<N;j++)
		{
			if(grid[i][j].isEmpty())
				m<<setw(5)<<right<<setfill(' ')<<"|";
			else
				m<<" "<<grid[i][j].getPiece().toString().substr(2,2)<<" |";
		}
		m<<endl;	
	}
	m<<"   +----+----+----+----+"<<endl;
	return m.str();
}

#include "player.h"
#include <iostream>
#include <cstdlib>

using namespace std;

static  Vaxis v[]={A, B, C, D};
static  Haxis h[]={H1, H2, H3, H4};
static string index[]={"SBCH", "SBCO","SBQH","SBQO",
			"SECH","SECO","SEQH","SEQO",
			"TBCH","TBCO","TBQH","TBQO",
			"TECH","TECO","TEQH","TEQO"};

class HumanPlayer:public Player
{
public:
	HumanPlayer(Board *board= nullptr, Pool *pool= nullptr): Player(board,pool){}
	Piece & selectPiece ();
   	Square & selectSquare(const Piece &p);
};

class MyopicPlayer:public Player
{
public:	
	MyopicPlayer(Board *board= nullptr, Pool *pool= nullptr): Player(board,pool){}
	Piece & selectPiece ();
   	Square & selectSquare(const Piece &p);
};

Piece & HumanPlayer::selectPiece()
{
	string s;
	int flag=0;
	while(flag==0)
	{
		cout<<"Enter a piece:";
		s.clear();
		cin>>s;
				try{
					if(s.size()==4){
						if((s.substr(0,1)=="S"||s.substr(0,1)=="T")&&(s.substr(1,1)=="B"||s.substr(1,1)=="E")
						   &&(s.substr(2,1)=="C"||s.substr(2,1)=="Q")&&(s.substr(3,1)=="H"||s.substr(3,1)=="O"))
						{
								this->pool->getUnusedPiece(s);
								flag=1;
						}
						else
							throw InvalidInputException(s);
					} else
						throw InvalidInputException(s);
				}
				catch(UsedPieceException &m)
				{
					cout<<m.what()<<endl;
				}
				catch(InvalidInputException &m) {
					cout << m.what() << endl;
				}
	}
	return pool->getUnusedPiece(s);
}





Square & HumanPlayer::selectSquare(const Piece &p){
	int flag=0;
	string s;
	while(flag==0)
	{
		cout<<"Enter a position:";
		s.clear();
		cin>>s;
		try{
			if((s.substr(0,1)=="A"||s.substr(0,1)=="B"||s.substr(0,1)=="C"||s.substr(0,1)=="D")
			   &&(s.substr(1,1)=="1"||s.substr(1,1)=="2"||s.substr(1,1)=="3"||s.substr(1,1)=="4"))
			{
				board->getEmptySquare(s);
				flag=1;
			}
			else
				throw InvalidInputException(s);

		}
		catch(SquareException &j)
		{
			cout<<j.what()<<endl;
		}
		catch(InvalidInputException &i)
		{
			cout<<i.what()<<endl;
		}
	}

	return board->getEmptySquare(s);
}


Piece & MyopicPlayer::selectPiece()
{
	int bad[NP]={0};
	int good=0;
	int badd=0;
	int target=1;
	for(int i=0;i<NP;i++)
	{
		try{
			pool->getUnusedPiece(index[i]);
		}
		catch(UsedPieceException &m)
		{
			bad[i]=-1;
		}
	}
	for(int i=0;i<NP;i++) {
		if (bad[i] != -1) {
			for (int m = 0; m < N; m++){
				for (int n = 0; n < N; n++) {
					try {
						board->getEmptySquare(v[m], h[n]);
						if (board->isWinning(pool->getUnusedPiece(index[i]), board->getEmptySquare(v[m], h[n]))) {
							bad[i] = 1;
						}
					}
					catch(SquareException & u)
					{}
					}
				}
		}
	}
	for(int i=0;i<NP;i++)
	{
		if(bad[i]==0)
			good++;
		if(bad[i]==1)
			badd++;
	}
	if(good==0)
	{
		int r1=rand()%badd+1;
		int r2=0;
		for(target=0;target<NP;target++)
		{
			
			if(bad[target]==1)
			{
				r2++;
				if(r1==r2)
					break;
			}
		}
	}
	else
	{
		int r1=rand()%good+1;
		int r2=0;
		for(target=0;target<NP;target++)
		{
			
			if(bad[target]==0)
			{
				r2++;
				if(r1==r2)
					break;
			}
		}
	}
	     return  pool->getUnusedPiece(index[target]);
}

Square & MyopicPlayer::selectSquare(const Piece &p)
{
	int em=0;
	for(int m=0;m<N;m++)
	for(int n=0;n<N;n++)
	{
		try{
			board->getEmptySquare(v[m], h[n]);
			if(board->isWinning(p, board->getEmptySquare(v[m], h[n])))
			{
				return board->getEmptySquare(v[m], h[n]);
			}
			em++;
		}
		catch(SquareException &s){}
	}
	int r1=rand()%em+1;
	int r2=0;
	int m=0; int n=0;
	for(m=0;m<N;m++)
	for(n=0;n<N;n++)
	{
		try{
			board->getEmptySquare(v[m], h[n]);
			r2++;
			if(r1==r2)
				return board->getEmptySquare(v[m], h[n]);

		}
		catch(SquareException &s){}
	}
	return board->getEmptySquare(v[m], h[n]);
}


static HumanPlayer h0(nullptr, nullptr);
static MyopicPlayer m0(nullptr, nullptr);
Player *getHumanPlayer(Board *b, Pool *p)
{
	HumanPlayer h1(b,p);
	h0=h1;
	return &h0;
}
Player *getMyopicPlayer(Board *b, Pool *p, unsigned int s)
{
	srand(s);
	MyopicPlayer m1(b,p);
	m0=m1;
	return &m0;
}



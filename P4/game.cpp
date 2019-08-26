#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <string>
#include "piece.h"
#include "quarto.h"
#include "piece.h"
#include "exceptions.h"
#include "board.h"
#include "player.h"
using namespace std;

int main(int argc, char* argv[])
{
	Board b;
	Pool  p;
	string type="h";
	unsigned int s;
	Player *play[2];
	for(int i=0;i<2;i++)
	{
		if(strcmp(argv[i+1],type.c_str())==0)
			play[i]=getHumanPlayer(&b,&p);	
		else
		{	s=(unsigned int)atoi(argv[3]);
			play[i]=getMyopicPlayer(&b,&p,s);
		}
	}
	int win=0;
	int draw=0;
	int i=1;
	int j=2;
	int step=0;
	Piece *ppp;
	Square *sss;
	cout << b.toString() << endl;
	cout << p.toString() << endl;
	while(win==0&&draw==0) {
		cout << "Player " << i << "'s turn to select a piece:" << endl;
		ppp=&play[i - 1]->selectPiece();
		cout << ppp->toString() << " selected.\n" << endl;
		cout << "Player " << j << "'s turn to select a square:" << endl;
		sss=&play[j - 1]->selectSquare(*ppp);
		cout << sss->toString() << " selected." << endl;
		cout<<endl;
		b.place(*ppp,*sss);
		cout << b.toString() << endl;
		cout << p.toString() << endl;
		if (b.isWinning(*ppp,*sss)) {
			cout << "Player " << j << " has won!" << endl;
			win = 1;
		}
		else if (step == NP - 1) {
			cout << "It is a draw." << endl;
			draw=1;
		}
		else {
			step++;
			if (i == 1) {
				i = 2;
				j = 1;
			} else {
				i = 1;
				j = 2;
			}

		}
	}
	return 0;
}




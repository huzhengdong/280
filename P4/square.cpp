#include "square.h"
using namespace std;

Square::Square(Vaxis v, Haxis h)
{
	this->v=v;
	this->h=h;
	this->p= nullptr;
}

Vaxis Square::getV() const
{
	return v;
}
void Square::setV(Vaxis v)
{
	this->v=v;
}
Haxis Square::getH() const
{
	return h;
}
void Square::setH(Haxis h){
	this->h=h;
}
const Piece & Square::getPiece() const
{
	if(p)
		return *p;
	else
		throw SquareException(*this, "empty");
}
  
void Square::setPiece(const Piece *p)
{
	this->p=p;
}

bool Square::isEmpty() const
{
	return !p;
}
 
bool Square::isOnFirstDiagonal() const
{
	return ((v==A&&h==H1)||(v==B&&h==H2)||(v==C&&h==H3)||(v==D&&h==H4));
}

bool Square::isOnSecondDiagonal() const
{
	return ((v==A&&h==H4)||(v==B&&h==H3)||(v==C&&h==H2)||(v==D&&h==H1));
}
std::string Square:: toString() const{
	ostringstream s;
	char a[]={'A','B','C','D'};
	char b[]={'1','2','3','4'};
	s<<a[v]<<b[h];
	return s.str();
}
   

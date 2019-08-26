#include "piece.h"
using namespace std;

Piece::Piece(Height h, Color c, Shape s, Top t){
	this->h=h;
	this->c=c;
	this->s=s;
	this->t=t;
	this->used= false;
}

bool Piece::compareHeight(const Piece &p) const{
	return this->h==p.h;
}

bool Piece::compareColor(const Piece &p) const{
	return this->c==p.c;
}

bool Piece::compareShape(const Piece &p) const{
	return this->s==p.s;
}
  
bool Piece::compareTop(const Piece &p) const{
	return this->t==p.t;
}

bool Piece::isUsed() const{
	return used;
}

void Piece::setUsed(bool u){
	used=u;
}
std::string Piece::toString() const{
	ostringstream m;
	m<<HCODE[h]<<CCODE[c]<<SCODE[s]<<TCODE[t];
	return m.str();
}
   


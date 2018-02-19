#include "Piece.h"

Piece::Piece(int r, int c, int color) 
{
	this->r = r;
	this->c = c;
	this->color = color;
	king = false;
}
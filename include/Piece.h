#ifndef PIECE_H_
#define PIECE_H_

static const int WHITE = 3;
static const int BLACK = 2;

class Piece
{
public:
	Piece():r(0), c(0), color(1), king(false) {};
	Piece(int r, int c, int color);
	~Piece() {};

	int r;
	int c;
	int color;
	bool king;
private:
};

#endif
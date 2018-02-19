#ifndef BOARD_H_
#define BOARD_H_

#include "Piece.h"
#include <vector>
#include <memory>

static const int INVALID_MOVE = -1;
static const int VALID_MOVE = 0;
static const int REMOVED_PIECE = 1;

class Board 
{
public:
	Board();
	~Board() {};

	bool isGameOver();
	bool hasValidMoves(int color);
	bool hasValidMoves(int color, int r, int c);
	bool hasValidMoves(std::shared_ptr<Piece> p);
	bool hasValidJumps(int color, int r, int c);
	bool hasValidJumps(std::shared_ptr<Piece> p);
	std::shared_ptr<Piece> pieceAt(int r, int c);
	int move(int color, int r, int c, int nr, int nc);
	void removePiece(int r, int c);
	void print();

private:
	//color = 1 == white
	std::vector<std::shared_ptr<Piece>> pieces;
};

#endif //BOARD_H_
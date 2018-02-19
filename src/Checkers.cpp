#include <iostream>
#include "Board.h"

int main() 
{
	std::cout << "Checkers app" << std::endl;
	int result = 0;
	Board b;
	int color = BLACK;

	while (result == VALID_MOVE 
		|| result == INVALID_MOVE
		|| result == REMOVED_PIECE)
	{
		if (!b.hasValidMoves(color)) 
		{
			std::cout << (color == BLACK ? "Black " : "White ");
			std::cout << "has no valid moves. " << std::endl;
	  		color = color == BLACK ? WHITE : BLACK;
	  		result = VALID_MOVE;
	  		continue;
		}
		b.print();

		std::cout << "It is " << (color == BLACK ? " Black's " : " White's ");
		std::cout << "turn. " << std::endl;

		int r, c, nr, nc;

		if (result != REMOVED_PIECE) 
		{
		  	std::cout << "Enter piece's row: ";
		  	std::cin >> r;
		  	std::cout << "Enter piece's col: ";
		  	std::cin >> c;
		}
	  	std::cout << "Enter piece's new row: ";
	  	std::cin >> nr;
	  	std::cout << "Enter piece's new col: ";
	  	std::cin >> nc;
	  	int lastResult = result;
	  	std::cout << "Moving " << r << " " << c << " to " << nr << " " << nc << std::endl;
	  	result = b.move(color, r,c,nr,nc);
	  	if (lastResult == REMOVED_PIECE && result == INVALID_MOVE)
	  	{
	  		result = lastResult;
	  	}

	  	if (result == VALID_MOVE)
	  		color = color == BLACK ? WHITE : BLACK;
	  	else if (result == color)
	  	{
	  		std::cout << "Congratulations, " <<  (color == BLACK ? "Black" : "White");
	  		std::cout << " wins!" << std::endl;
	  	}
	  	else if (result == REMOVED_PIECE) {
	  		r = nr;
	  		c = nc;
	  		result = b.hasValidJumps(color, r, c) ? REMOVED_PIECE : VALID_MOVE; 
	  	}
	  	else 
	  	{
	  		std::cout << "Invalid Move!" << std::endl;
	  	}
	}
}
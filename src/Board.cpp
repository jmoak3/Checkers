#include "Board.h"
#include <string>
#include <iostream>     
#include <stdlib.h> 

Board::Board() 
{
	std::cout << "Initializing Board." << std::endl;
	for (int i=0;i<3;++i) 
	{
		int startingJ = i==1 ? 1 : 0;
		for (int j=startingJ;j<8;j+=2) 
		{
			auto piece_ptr = std::make_shared<Piece>(i,j,BLACK);
			pieces.push_back(piece_ptr);
		}
	}

	for (int i=5;i<8;++i) 
	{
		int startingJ = i==6 ? 0 : 1;
		for (int j=startingJ;j<8;j+=2) 
		{
			auto piece_ptr = std::make_shared<Piece>(i,j,WHITE);
			pieces.push_back(piece_ptr);
		}
	}
	std::cout << "Board init complete." << std::endl;
}

bool Board::isGameOver()
{
	int blackCount = 0;
	int whiteCount = 0;
	for(auto p : pieces) 
	{
		if (p->color == BLACK) 
			blackCount++;
		else
			whiteCount++;
	}
	if (blackCount == 0 || whiteCount == 0) 
		return true;
	else
		return false;
}

bool Board::hasValidMoves(int color)
{
	for(auto p : pieces) 
	{
		if (p->color == color)
		{
			if (hasValidMoves(p))
				return true;
		} 
	}
	return false;
}

bool Board::hasValidMoves(int color, int r, int c)
{
	for(auto p : pieces) 
	{
		if (p->color == color && p->r == r && p->c == c)
		{
			return hasValidMoves(p);
		} 
	}
	return false;
}

bool Board::hasValidMoves(std::shared_ptr<Piece> p)
{
	int dirs[2][2] = {{1,1}, {1,-1}};
	int sign = p->color == BLACK ? 1 : -1;
	for (int i=0;i<2;++i)
	{
		int nr = sign*dirs[i][0] + p->r; 
		int nc = sign*dirs[i][1] + p->c;
		if (pieceAt(nr, nc) == NULL && (nr < 8 || nr > -1))
			return true;
	}
	if (p->king)
	{
		sign = -1*sign;
		//flip direction and try again
		for (int i=0;i<2;++i)
		{
			int nr = sign*dirs[i][0] + p->r; 
			int nc = sign*dirs[i][1] + p->c;
			if (pieceAt(nr, nc) == NULL && (nr < 8 || nr > -1))
				return true;
		}
	}
	return false;
}

bool Board::hasValidJumps(int color, int r, int c)
{
	for(auto p : pieces) 
	{
		if (p->color == color && p->r == r && p->c == c)
		{
			return hasValidJumps(p);
		} 
	}
	return false;
}

bool Board::hasValidJumps(std::shared_ptr<Piece> p)
{
	int dirs[2][2] = {{2,2}, {2,-2}};
	int sign = p->color == BLACK ? 1 : -1;
	for (int i=0;i<2;++i)
	{
		for (int i=0;i<2;++i)
		{
			int nr = sign*dirs[i][0] + p->r; 
			int nc = sign*dirs[i][1] + p->c;
			if (pieceAt(nr, nc) == NULL && (nr < 8 || nr > -1))
			{
				//Find the other piece.
				int jumpedr = ((nr-p->r)/2)+p->r;
				int jumpedc = ((nc-p->c)/2)+p->c;
				std::shared_ptr<Piece> j = pieceAt(jumpedr, jumpedc);
				if (j != NULL && j->color != p->color) 
				{
					return true;
				}
			}
		}
	}
	if (p->king)
	{
		sign = -1*sign;
		//flip direction and try again
		for (int i=0;i<2;++i)
		{
			int nr = sign*dirs[i][0] + p->r; 
			int nc = sign*dirs[i][1] + p->c;
			if (pieceAt(nr, nc) == NULL && (nr < 8 || nr > -1))
			{
				//Find the other piece.
				int jumpedr = ((nr-p->r)/2)+p->r;
				int jumpedc = ((nc-p->c)/2)+p->c;
				std::shared_ptr<Piece> j = pieceAt(jumpedr, jumpedc);
				if (j != NULL && j->color != p->color) 
				{
					return true;
				}
			}
		}
	}
	return false;
}

std::shared_ptr<Piece> Board::pieceAt(int r, int c) 
{
	for(auto p : pieces) 
	{
		if (p->r == r && p->c == c) 
		{
			return p;
		}
	}
	return NULL;
}

int Board::move(int color, int r, int c, int nr, int nc) 
{
	std::shared_ptr<Piece> p = pieceAt(r, c);
	if (p != NULL && p->color == color) 
	{
		bool removedPiece = false;
		//is the attempted square taken
		//is the attempted square valid
		//make sure we're going 'forward'.
		if ( (pieceAt(nr, nc) != NULL) 
		  || (nr > 7 || nr < 0)
		  || (color == BLACK && !p->king && nr <= r)
	      || (color == WHITE && !p->king && nr >= r) )
			return INVALID_MOVE;

		//Are we jumping over someone?
		if (abs(nr-r) == 2 && abs(nc-c) == 2) //yes
		{
			//Find the other piece.
			int jumpedr = ((nr-r)/2)+r;
			int jumpedc = ((nc-c)/2)+c;
			std::shared_ptr<Piece> j = pieceAt(jumpedr, jumpedc);
			if (j != NULL && j->color != color) 
			{
				removePiece(jumpedr, jumpedc);
				p->r = nr;
				p->c = nc;
				removedPiece = true;
			}
			else 
			{
				return INVALID_MOVE;
			}
		}
		else if (abs(nr-r) == 1 && abs(nc-c) == 1)//no
		{
			p->r = nr;
			p->c = nc;
			if (nr == 0 || nr == 7) 
				p->king = true;
		}
		else 
		{
			return INVALID_MOVE;
		}

		if (isGameOver()) 
		{
			return color;
		}
		else
		{
			if (removedPiece) 
				return REMOVED_PIECE;
			else 
				return VALID_MOVE;
		}
	}
	return INVALID_MOVE;
}

void Board::removePiece(int r, int c) 
{
	for (std::vector<std::shared_ptr<Piece>>::iterator it = pieces.begin();
		 it!=pieces.end();
		 ++it)
	{
		if ((*it)->r == r && (*it)->c == c)
		{
			pieces.erase(it);
			break;
		}
	}
}

void Board::print() 
{
	std::string s = "";
	s+=" ";
	for (int i=0;i<8;++i) 
		s+=std::to_string(i);
	s+="\n";
	for (int i=0;i<8;++i) 
	{
		s+=std::to_string(i);
		for (int j=0;j<8;++j) 
		{
			std::shared_ptr<Piece> p = pieceAt(i, j);
			if (p != NULL) 
			{
				if (p->color == BLACK) 
				{
					s+= "x";
				}
				else
				{
					s+="o";
				}
			}
			else 
			{
				s+="-";
			}
		}
		s+="\n";
	}
	std::cout << s << std::endl;
}
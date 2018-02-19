#include <iostream>

int main() 
{
	std::cout << "Checkers app" << std::endl;
	int result = 0;
	Board b;
	int color = BLACK;

	while (result <=0)
	{
		std::cout << "It is " << color == BLACK ? " Black's " : " White's ";
		std::cout << "turn. " << std::endl;

		int r, c, nr, nc;

	  	std::cout << "Enter piece's row: ";
	  	std::cin >> r;
	  	std::cout << "Enter piece's col: ";
	  	std::cin >> c;
	  	std::cout << "Enter piece's new row: ";
	  	std::cin >> nr;
	  	std::cout << "Enter piece's new col: ";
	  	std::cin >> nc;

	  	std::cout << "Moving " << r << " " << c << " to " << nr << " " << nc << std:endl;
	  	result = b.move(color, r,c,nr,nc);
	  	if (result == 0)
	  		color = color == BLACK ? WHITE : BLACK;
	  	if (result == color)
	  	{
	  		std::cout << "Congratulations, " <<  color == BLACK ? "Black" : "White";
	  		std::cout << " wins!" << std::endl;
	  	}
	}
}
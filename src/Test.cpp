#include <iostream>
#include "Board.h"

int main() 
{
	std::cout << "Test app" << std::endl;
	Board b;
	b.print();
	std::cout << "result of move: " << b.move(BLACK, 2, 0, 3, 1) << std::endl;
	std::cout << "result of move: " << b.move(WHITE, 5, 1, 4, 2) << std::endl;
	std::cout << "result of move: " << b.move(BLACK, 2, 2, 3, 3) << std::endl;
	b.print();
	std::cout << "result of move: " << b.move(WHITE, 4, 2, 2, 0) << std::endl;
	if (b.hasValidJumps(WHITE, 2,0)) 
	{
		std::cout << "Valid jumps remaining!" << std::endl;
	}
	else 
	{
		std::cout << "No jumps remaining!" << std::endl;
	}
	b.print();
	std::cout << "result of move: " << b.move(BLACK, 1, 1, 2, 2) << std::endl;
	std::cout << "result of move: " << b.move(WHITE, 2, 0, 1, 1) << std::endl;
	b.print();
	std::cout << "result of move: " << b.move(BLACK, 0, 2, 2, 0) << std::endl;
	if (b.hasValidJumps(BLACK, 2,0)) 
	{
		std::cout << "Valid jumps remaining!" << std::endl;
	}
	else 
	{
		std::cout << "No jumps remaining!" << std::endl;
	}
	b.print();
	std::cout << "result of move: " << b.move(WHITE, 5, 3, 4, 2) << std::endl;
	std::cout << "result of move: " << b.move(BLACK, 3, 3, 4, 4) << std::endl;
	b.print();
	std::cout << "result of move: " << b.move(WHITE, 5, 5, 3, 3) << std::endl;
	std::cout << "result of move: " << b.move(WHITE, 3, 3, 1, 1) << std::endl;
	std::cout << "result of move: " << b.move(BLACK, 0, 0, 2, 2) << std::endl;
	std::cout << "result of move: " << b.move(WHITE, 5, 7, 4, 6) << std::endl;
	b.print();
	std::cout << "result of move: " << b.move(BLACK, 2, 6, 3, 7) << std::endl;
	std::cout << "result of move: " << b.move(WHITE, 6, 6, 5, 5) << std::endl;
	b.print();
	return 0;
}
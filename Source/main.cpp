#include "GameOfLife.h"
#include <iostream>
int main()
{
	cout << "Beginning initialization." << endl;
	GameOfLife *game = new GameOfLife("input.txt", "output.txt");
	if (game->readInputFile())
	{
		cout << "Initialization complete. Evaluating game board." << endl;
		game->evaluateBoard();
		cout << "Writing evolved board to file..." << endl;
		game->writeOutputFile();
	}
	
	delete game;
	
	cout << "Press any key to continue." << endl;
	cin.get();
}
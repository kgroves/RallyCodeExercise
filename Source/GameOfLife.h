#pragma once
#include <string>
using namespace std;

class GameOfLife
{
	public:
		GameOfLife(string inPath, string outPath);
		~GameOfLife();
		
		void evaluateBoard();
		bool readInputFile();
		void writeOutputFile();
		enum State 
		{
			DEAD,
			ALIVE
		};

	private:
		string mInPath;
		string mOutPath;
		int mRows;
		int mColumns;
		int mNumLiveNeighbors;
		int **mInputBoard;
		int **mOutputBoard;

		void countRowsAndColumns();
		int determineFate(int row, int column);
		void initializeBoards();
};
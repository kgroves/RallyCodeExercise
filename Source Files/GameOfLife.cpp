#include "GameOfLife.h"
#include <iostream>
#include <fstream>


GameOfLife::GameOfLife(string inPath, string outPath)
{
	mInPath = inPath;
	mOutPath = outPath;
	countRowsAndColumns();
	initializeBoards();
}

GameOfLife::~GameOfLife()
{
	for (int i = 0; i < mRows; ++i)
	{
		delete[] mInputBoard[i];
	}
	delete[] mInputBoard;

	for (int j = 0; j < mRows; ++j)
	{
		delete[] mOutputBoard[j];
	}
	delete[] mOutputBoard;
}

void GameOfLife::countRowsAndColumns()
{
	ifstream inputFile;
	inputFile.open(mInPath);
	if (!inputFile)
	{
		cout << "Error opening file. Unable to count rows & columns.\n";
	}
	else
	{
		string in;
		while (!inputFile.eof())
		{
			getline(inputFile, in);
			++mRows;
		}
		for (unsigned i = 0; i < in.length(); ++i)
		{
			if (in[i] != ' ')
			{
				++mColumns;
			}
		}
	}
}

bool GameOfLife::readInputFile()
{
	ifstream inputFile;
	inputFile.open(mInPath);
	
	if (!inputFile)
	{
		cout << "Error opening file. Unable to initialize input array." << endl;
		return false;
	}
	else
	{
		while (!inputFile.eof())
		{
			for (int i = 0; i < mRows; ++i)
			{
				for (int j = 0; j < mColumns; ++j)
				{
					inputFile >> mInputBoard[i][j];
				}
			}
		}
		inputFile.close();
		cout << "Finished reading input file." << endl;
		return true;
	}
}

void GameOfLife::writeOutputFile()
{
	ofstream outFile;
	outFile.open(mOutPath);
	
	for (int i = 0; i < mRows; ++i)
	{
		for (int j = 0; j < mColumns; ++j)
		{
			outFile << mOutputBoard[i][j];
			outFile << " ";
		}
		outFile << "\n";
	}
	outFile.close();
}

void GameOfLife::evaluateBoard()
{
	for (int i = 0; i < mRows; ++i)
	{
		for (int j = 0; j < mColumns; ++j)
		{
			mNumLiveNeighbors = 0;
			if (i < (mRows - 1))
			{
				if (mInputBoard[i + 1][j] == ALIVE)
				{
					++mNumLiveNeighbors;
				}
				if (j < (mColumns - 1))
				{
					if (mInputBoard[i + 1][j + 1] == ALIVE)
					{
						++mNumLiveNeighbors;
					}
					if (i > 0 && (mInputBoard[i - 1][j + 1] == ALIVE))
					{
						++mNumLiveNeighbors;
					}
				}
				if (j > 0)
				{
					if (mInputBoard[i + 1][j - 1] == ALIVE)
					{
						++mNumLiveNeighbors;
					}
					if (i > 0 && mInputBoard[i - 1][j - 1] == ALIVE)
					{
						++mNumLiveNeighbors;
					}
				}
			}

			if (i > 0 && mInputBoard[i - 1][j] == ALIVE)
			{
				++mNumLiveNeighbors;
			}
			if (i > 0 && mInputBoard[i][j - 1] == ALIVE)
			{
				++mNumLiveNeighbors;
			}
			if (j < (mColumns - 1) && mInputBoard[i][j + 1] == ALIVE)
			{
				++mNumLiveNeighbors;
			}
			
			mOutputBoard[i][j] = determineFate(i,j);
		}
	}
}

int GameOfLife::determineFate(int row, int column)
{
	if (mInputBoard[row][column] == DEAD)
	{
		// Reproduction
		if (mNumLiveNeighbors == 3)
		{
			return ALIVE;
		}
		else
		{
			return DEAD;
		}
	}
	else
	{
		// Over- or under-population
		if (mNumLiveNeighbors < 2 || mNumLiveNeighbors > 3)
		{
			return DEAD;
		}
		else 
		{
			// Survival
			return ALIVE; 
		}
	}
}

void GameOfLife::initializeBoards()
{
	mInputBoard = new int*[mRows];
	for (int i = 0; i < mRows; ++i)
	{
		mInputBoard[i] = new int[mColumns];
	}

	mOutputBoard = new int*[mRows];
	for (int j = 0; j < mRows; ++j)
	{
		mOutputBoard[j] = new int[mColumns];
	}
}
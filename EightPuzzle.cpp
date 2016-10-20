#include "EightPuzzle.h"


EightPuzzle::EightPuzzle() : Column(0), currentPath(0), iRow(0), Row(0), tempNum(0)
{
	//Creates the goal state
	Goal[0][0] = 1;
	Goal[0][1] = 2;
	Goal[0][2] = 3;
	Goal[1][2] = 4;
	Goal[2][2] = 5;
	Goal[2][1] = 6;
	Goal[2][0] = 7;
	Goal[1][0] = 8;
	Goal[1][1] = 0;

	initalPuzzle = new Path;
}


EightPuzzle::~EightPuzzle()
{
}


bool EightPuzzle::isGoal(Path* currentPuzzle)
{
	//Checks to see if the current path is at the goal state
	for (int Row = 0; Row < 3; Row++)
	{
		for (int Column = 0; Column < 3; Column++)
		{
			if (currentPuzzle->Puzzle[Row][Column] != Goal[Row][Column])
			{
				return false;
			}
		}
	}

	return true;
}


void EightPuzzle::FillInital(int Column0, int Column1, int Column2)
{
	//Reads in the values from the file and creates my inital state
	initalPuzzle->Puzzle[iRow][0] = Column0;
	initalPuzzle->Puzzle[iRow][1] = Column1;
	initalPuzzle->Puzzle[iRow][2] = Column2;
	iRow++;
}


void EightPuzzle::FindCurrentPath()
{
	//Finds the cheapest current path from the list of paths
	for (int i = 0; i < Paths.size(); i++)
	{
		if ((Paths.at(currentPath)->totalWeight + Paths.at(currentPath)->Hammington) > (Paths.at(i)->totalWeight + Paths.at(i)->Hammington))
		{
			currentPath = i;
		}
	}
}


void EightPuzzle::FindZero(Path* currentPuzzle)
{
	//Finds the location of the zero in the puzzle
	for (int Row = 0; Row < 3; Row++)
	{
		for (int Column = 0; Column < 3; Column++)
		{
			if (currentPuzzle->Puzzle[Row][Column] == 0)
			{
				this->Row = Row;
				this->Column = Column;
			}
		}
	}
}


void EightPuzzle::Hammington(Path* currentPuzzle)
{
	//Sets the hammington value for the puzzle to be used during finding least cost
	for (int Row = 0; Row < 3; Row++)
	{
		for (int Column = 0; Column < 3; Column++)
		{
			if (currentPuzzle->Puzzle[Row][Column] != Goal[Row][Column])
			{
				currentPuzzle->Hammington++;
			}
		}
	}
}


void EightPuzzle::PrintSoln(Path* currentPuzzle) const
{
	//Prints the answer
	if (currentPuzzle->totalWeight == 0)
	{
		std::cout << "The inital state is the goal state!";
	}
	else
	{
		std::cout << "The shortest path cost = " << currentPuzzle->totalWeight << std::endl;
	}
}


void EightPuzzle::ShiftDown(Path* currentPuzzle)
{
	//Creates a new path and initalize it from the current path
	newPuzzle = new Path;
	for (int Row = 0; Row < 3; Row++)
	{
		for (int Column = 0; Column < 3; Column++)
		{
			newPuzzle->Puzzle[Row][Column] = currentPuzzle->Puzzle[Row][Column];
		}
	}

	//Finds the zero for the puzzle, shifts the 0 down, adjust the total cost 
	//and finds the hammington value
	FindZero(newPuzzle);
	tempNum = newPuzzle->Puzzle[Row + 1][Column];
	newPuzzle->Puzzle[Row + 1][Column] = 0;
	newPuzzle->Puzzle[Row][Column] = tempNum;
	newPuzzle->totalWeight = currentPuzzle->totalWeight;
	newPuzzle->totalWeight += tempNum;
	Hammington(newPuzzle);
	Paths.push_back(newPuzzle);
}


void EightPuzzle::ShiftLeft(Path* currentPuzzle)
{
	//Creates a new path and initalize it from the current path
	newPuzzle = new Path;
	for (int Row = 0; Row < 3; Row++)
	{
		for (int Column = 0; Column < 3; Column++)
		{
			newPuzzle->Puzzle[Row][Column] = currentPuzzle->Puzzle[Row][Column];
		}
	}

	//Finds the zero for the puzzle, shifts the 0 left, adjust the total cost 
	//and finds the hammington value
	FindZero(newPuzzle);
	tempNum = newPuzzle->Puzzle[Row][Column - 1];
	newPuzzle->Puzzle[Row][Column - 1] = 0;
	newPuzzle->Puzzle[Row][Column] = tempNum;
	newPuzzle->totalWeight = currentPuzzle->totalWeight;
	newPuzzle->totalWeight += tempNum;
	Hammington(newPuzzle);
	Paths.push_back(newPuzzle);
}


void EightPuzzle::ShiftRight(Path* currentPuzzle)
{
	//Creates a new path and initalize it from the current path
	newPuzzle = new Path;
	for (int Row = 0; Row < 3; Row++)
	{
		for (int Column = 0; Column < 3; Column++)
		{
			newPuzzle->Puzzle[Row][Column] = currentPuzzle->Puzzle[Row][Column];
		}
	}

	//Finds the zero for the puzzle, shifts the 0 right, adjust the total cost 
	//and finds the hammington value
	FindZero(newPuzzle);
	tempNum = newPuzzle->Puzzle[Row][Column + 1];
	newPuzzle->Puzzle[Row][Column + 1] = 0;
	newPuzzle->Puzzle[Row][Column] = tempNum;
	newPuzzle->totalWeight = currentPuzzle->totalWeight;
	newPuzzle->totalWeight += tempNum;
	Hammington(newPuzzle);
	Paths.push_back(newPuzzle);
}


void EightPuzzle::ShiftUp(Path* currentPuzzle)
{
	//Creates a new path and initalize it from the current path
	newPuzzle = new Path;
	for (int Row = 0; Row < 3; Row++)
	{
		for (int Column = 0; Column < 3; Column++)
		{
			newPuzzle->Puzzle[Row][Column] = currentPuzzle->Puzzle[Row][Column];
		}
	}

	//Finds the zero for the puzzle, shifts the 0 up, adjust the total cost 
	//and finds the hammington value
	FindZero(newPuzzle);
	tempNum = newPuzzle->Puzzle[Row - 1][Column];
	newPuzzle->Puzzle[Row - 1][Column] = 0;
	newPuzzle->Puzzle[Row][Column] = tempNum;
	newPuzzle->totalWeight = currentPuzzle->totalWeight;
	newPuzzle->totalWeight += tempNum;
	Hammington(newPuzzle);
	Paths.push_back(newPuzzle);
}


void EightPuzzle::SolvePuzzle()
{
	//Checks to see if inital state is goal state
	if (isGoal(initalPuzzle))
	{
		PrintSoln(initalPuzzle);
		return;
	}

	//Creates the first set of possible paths based on the inital state
	FindZero(initalPuzzle);
	if (Row == 0 && Column == 0)
	{
		ShiftRight(initalPuzzle);
		ShiftDown(initalPuzzle);
	}
	else if (Row == 0 && Column == 1)
	{
		ShiftLeft(initalPuzzle);
		ShiftRight(initalPuzzle);
		ShiftDown(initalPuzzle);
	}
	else if (Row == 0 && Column == 2)
	{
		ShiftLeft(initalPuzzle);
		ShiftDown(initalPuzzle);
	}
	else if (Row == 1 && Column == 0)
	{
		ShiftUp(initalPuzzle);
		ShiftRight(initalPuzzle);
		ShiftDown(initalPuzzle);
	}
	else if (Row == 1 && Column == 1)
	{
		ShiftUp(initalPuzzle);
		ShiftLeft(initalPuzzle);
		ShiftRight(initalPuzzle);
		ShiftDown(initalPuzzle);
	}
	else if (Row == 1 && Column == 2)
	{
		ShiftUp(initalPuzzle);
		ShiftLeft(initalPuzzle);
		ShiftDown(initalPuzzle);
	}
	else if (Row == 2 && Column == 0)
	{
		ShiftUp(initalPuzzle);
		ShiftRight(initalPuzzle);
	}
	else if (Row == 2 && Column == 1)
	{
		ShiftUp(initalPuzzle);
		ShiftLeft(initalPuzzle);
		ShiftRight(initalPuzzle);
	}
	else if (Row == 2 && Column == 2)
	{
		ShiftUp(initalPuzzle);
		ShiftLeft(initalPuzzle);
	}
	
	//Finds the current cheapest path
	FindCurrentPath();
	
	//First check to see if the current path is the goal state. If not then we create children based
	//on the current path by finding the zero, creating the chiildren, deleteing the current path, and
	//finding the newest cheapest path
	while (!isGoal(Paths.at(currentPath)))
	{
		FindZero(Paths.at(currentPath));
		if (Row == 0 && Column == 0)
		{
			ShiftRight(Paths.at(currentPath));
			ShiftDown(Paths.at(currentPath));
			Paths.erase(Paths.begin() + currentPath);
		}
		else if (Row == 0 && Column == 1)
		{
			ShiftLeft(Paths.at(currentPath));
			ShiftRight(Paths.at(currentPath));
			ShiftDown(Paths.at(currentPath));
			Paths.erase(Paths.begin() + currentPath);
		}
		else if (Row == 0 && Column == 2)
		{
			ShiftLeft(Paths.at(currentPath));
			ShiftDown(Paths.at(currentPath));
			Paths.erase(Paths.begin() + currentPath);
		}
		else if (Row == 1 && Column == 0)
		{
			ShiftUp(Paths.at(currentPath));
			ShiftRight(Paths.at(currentPath));
			ShiftDown(Paths.at(currentPath));
			Paths.erase(Paths.begin() + currentPath);
		}
		else if (Row == 1 && Column == 1)
		{
			ShiftUp(Paths.at(currentPath));
			ShiftLeft(Paths.at(currentPath));
			ShiftRight(Paths.at(currentPath));
			ShiftDown(Paths.at(currentPath));
			Paths.erase(Paths.begin() + currentPath);
		}
		else if (Row == 1 && Column == 2)
		{
			ShiftUp(Paths.at(currentPath));
			ShiftLeft(Paths.at(currentPath));
			ShiftDown(Paths.at(currentPath));
			Paths.erase(Paths.begin() + currentPath);
		}
		else if (Row == 2 && Column == 0)
		{
			ShiftUp(Paths.at(currentPath));
			ShiftRight(Paths.at(currentPath));
			Paths.erase(Paths.begin() + currentPath);
		}
		else if (Row == 2 && Column == 1)
		{
			ShiftUp(Paths.at(currentPath));
			ShiftLeft(Paths.at(currentPath));
			ShiftRight(Paths.at(currentPath));
			Paths.erase(Paths.begin() + currentPath);
		}
		else if (Row == 2 && Column == 2)
		{
			ShiftUp(Paths.at(currentPath));
			ShiftLeft(Paths.at(currentPath));
			Paths.erase(Paths.begin() + currentPath);
		}

		FindCurrentPath();
	}

	PrintSoln(Paths.at(currentPath));
}
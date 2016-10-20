#ifndef EIGHTPUZZLE
#define EIGHTPUZZLE
#include "Path.h"
#include <iostream>
#include <vector>
#pragma once
class EightPuzzle
{
public:
	EightPuzzle(); //Default constructor
	~EightPuzzle(); //Default desctrutor
	bool isGoal(Path* currentPuzzle); //Checks to see if the current path is the goal
	void FillInital(int Column0, int Column1, int Column2); //Fills in my inital state
	void FindCurrentPath(); //Finds the cheapest path currently
	void FindZero(Path* currentPuzzle); //Finds the zero in the puzzle to slide
	void Hammington(Path* currentPuzzle); //Calculates the hammington value for my puzzles
	void PrintSoln(Path* currentPuzzle) const; //Prints the answer
	void ShiftDown(Path* currentPuzzle); //Shifts the piece down
	void ShiftLeft(Path* currentPuzzle); //Shifts the piece left
	void ShiftRight(Path* currentPuzzle); //Shifts the piece right
	void ShiftUp(Path* currentPuzzle); //Shifts the piece up
	void SolvePuzzle(); //Solves the puzzle
private:
	int Column; //Holds the column of the zero
	int currentPath; //Is the current path I am exploring
	int Goal[3][3]; //Holds the goal state
	int iRow; //Helps for inputing the inital state
	int Row; //Holds the row of the zero
	int tempNum; //Holds the number for shifting
	Path* initalPuzzle; //Inital state
	Path* newPuzzle; //Used to create more paths
	std::vector<Path*> Paths; //Holds all possible paths
};
#endif


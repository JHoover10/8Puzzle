#include "EightPuzzle.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
int main(){
	int Column0, Column1, Column2;
	EightPuzzle newPuzzle;
	ifstream myFile;

	//Opens the file
	myFile.open("C:/Users/Jeffrey/Dropbox/My Programs/input.txt", ios::in);

	//Inputs the data from my file into my object
	do
	{
		myFile >> Column0 >> Column1 >> Column2;

		newPuzzle.FillInital(Column0, Column1, Column2);
	} while (!myFile.eof());

	//Solves the puzzle
	newPuzzle.SolvePuzzle();

	system("pause");
}
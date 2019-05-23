//Created By Micha³ Krawczyk on 23.05.2019
#pragma once

#include <Windows.h>

#include "Arena.h"
#include "Position.h"
#include "Misc.h"


typedef std::vector<Position> vecPosition;
typedef std::vector<std::vector <bool>> vec2Dbool;


class Naive
{
public:
	Naive(mapStrBool &dictionary,int ndirections);
	~Naive();
	void solveNaive(vec2Dchar &arena);
	void printWordsFound();
	void printWordsNotFound();
private:
	mapStrBool wordsUsed;
	bool wordFinder(std::string & word, vec2Dchar & arena,int ndirections);
	std::vector<Position> wordsFoundPosition;
	void printSolution(vec2Dchar &arena); 
	int ndirections;
};



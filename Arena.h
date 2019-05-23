//Created By Micha³ Krawczyk on 23.05.2019
#pragma once

#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include <cstdlib>

#include "Misc.h"

typedef std::map<std::string, bool> mapStrBool;
typedef std::vector<std::vector <char>> vec2Dchar;

enum DIRECTION
{
	LEFTRIGHT = 0,
	UPDOWN = 1,
};

namespace ArenaConsts
{
	const int directionsAvailable = 2; // number of declared in enum DIRECTION values
}

class Arena
{
public:
	Arena(int ndirections);
	~Arena();
	void makeArena(vec2Dchar &arena, int columns, int rows);
	bool findWord(mapStrBool &dictionary,std::string word);
	void usedWords(mapStrBool &dictionary);
	void printArena(vec2Dchar &arena);
	void fullfillArena(vec2Dchar &arena, mapStrBool &dictionary,int nwords);
	int getnDirections(); 
private:
	bool generated;
	bool isEmpty;
	bool addWord(vec2Dchar &arena, std::string &word, DIRECTION dir, int column, int row);
	bool wordFit(vec2Dchar &arena, std::string &word, int column, int row, DIRECTION dir);
	int ndirections;
};

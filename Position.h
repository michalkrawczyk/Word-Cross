//Created By Micha³ Krawczyk on 23.05.2019
#pragma once

#include "Arena.h"


class Position {
public:
	Position(std::string &word, int row, int column, DIRECTION dir);
	std::string getWord();
	int getRow();
	int getColumn();
	DIRECTION getDirection();
	void printPosition();
private:
	std::string word;
	int row;
	int column;
	DIRECTION dir;
};
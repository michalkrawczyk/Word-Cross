#include "pch.h"
#include "Position.h"


Position::Position(std::string &word, int row, int column, DIRECTION dir)
{
	this->word = word;
	this->row = row;
	this->column = column;
	this->dir = dir;
	// zabezpieczenie przed nieprawid³ow¹ pozycj¹
}

std::string Position::getWord()
{
	return this->word;
}

int Position::getRow()
{
	return this->row;
}

int Position::getColumn()
{
	return this->column;
}

DIRECTION Position::getDirection()
{
	return this->dir;
}

void Position::printPosition()
{
	std::cout << word << "- Row:" << this->row << ", Column:" << this->column << std::endl;
	switch (this->dir)
	{
		case UPDOWN:
		{
			std::cout << "Direction: Down" << std::endl;
			break;
		}
		case LEFTRIGHT:
		{
			std::cout << "Direction: Right" << std::endl;
			break;
		}
	}
	
}

//Considering to store also color for color mixing
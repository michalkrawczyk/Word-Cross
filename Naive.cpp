//Created By Micha³ Krawczyk on 23.05.2019
#include "pch.h"
#include "Naive.h"





Naive::Naive(mapStrBool &dictionary, int ndirections)
{
	if (ndirections <= ArenaConsts::directionsAvailable && ndirections != 0)
	{
		this->ndirections = ndirections;
	}
	else
	{
		throw std::runtime_error("Nieprawidlowa liczba kierunkow");
	}
	for (auto &it : dictionary)
	{
		if (it.second)
		{
			this->wordsUsed[it.first] = false;
		}
	}
	if (this->wordsUsed.empty())
	{
		throw std::runtime_error("Solver nie wczytal zadnych slow");
	}
}


Naive::~Naive()
{
}

void Naive::solveNaive(vec2Dchar & arena)
{
	if (!this->wordsUsed.empty())
	{
		std::cout << "Proboje znalezc slowa metoda naiwna..." << std::endl;
		for (auto it : this->wordsUsed)
		{
			std::string temp = it.first;
			std::cout << "Szukam slowa:" << temp << std::endl;
			this->wordFinder(temp, arena, this->ndirections);
			
		}
		std::cout << "Wyswietlam tabele z rozwiazaniem..." << std::endl;
		this->printSolution(arena);
	}
	else
	{
		std::cout << "Nie ma slow do znalezienia" << std::endl;
	}
}

void Naive::printWordsFound()
{
	std::cout << std::endl;
	std::cout << "Words Already Found:" << std::endl;
	for (auto &it : this->wordsUsed)
	{
		if (it.second)
		{
			std::cout << it.first << std::endl;
		}
	}
}

void Naive::printWordsNotFound()
{
	std::cout << std::endl;
	std::cout << "Words Left to Find" << std::endl;
	for (auto &it : this->wordsUsed)
	{
		if (!it.second)
		{
			std::cout << it.first << std::endl;
		}
	}
}

bool Naive::wordFinder(std::string & word, vec2Dchar & arena, int ndirections)
{
	
	int height = arena.size();
	int width = arena[0].size();
	int checkDirection;
	bool test;
	for (int row = 0; row < height; row++)
	{
		for (int column = 0; column < width; column++)
		{
			checkDirection = 0;
			while (checkDirection <= (int) ndirections)
			{
				switch (checkDirection)
				{
					case LEFTRIGHT:
					{
						test = true;
						for (int i = 0; i < (int) word.length(); i++)
						{
							if ( (column + i) >= width || word[i] != arena[row][column + i])
							{
								test = false;
								break;
							}

						}
						if (test)
						{
							Position found(word, row, column, LEFTRIGHT);
							wordsFoundPosition.push_back(found);
							wordsUsed[word] = true; //
							return true;
						}
						break;
					
					}
					case UPDOWN:
					{
						test = true;
						for (int i = 0; i < (int) word.length(); i++)
						{
							if ( (row + i) >= height || word[i] != arena[row + i][column] )
							{
								test = false;
								break;
							}
						}
						if (test)
						{
							Position found(word, row, column, UPDOWN);
							wordsFoundPosition.push_back(found);
							wordsUsed[word] = true; //
							return true;
						}
						break;
					}
					default:
					{
						break;
					}
				}
				checkDirection++;
			}
		}
	}
	return false;
}

void Naive::printSolution(vec2Dchar & arena)
{

	int height = arena.size();
	int width = arena[0].size();
	vec2Dbool coloredWords;
	
	coloredWords.resize(height, std::vector<bool>(width,false));

	for (auto &it : this->wordsFoundPosition)
	{
		switch (it.getDirection())
		{
			case LEFTRIGHT:
			{
				for (int i = 0; i < (int) it.getWord().length();i++)
				{
					coloredWords[it.getRow()][it.getColumn() + i] = true;
				}
				break;
			}
			case UPDOWN:
			{
				for (int i = 0; i < (int) it.getWord().length(); i++)
				{
					coloredWords[it.getRow()+i][it.getColumn()] = true;
				}
				break;
			}
			default:
			{
				break;
			}
		}
	}

	//prints Arena with colored found words
	for (int i = 0; i < (int) arena[0].size(); i++)
	{
		std::cout << " " << i + 1; //ASCII ART - Prints column numbers
	}
	std::cout << std::endl;

	for (int i = 0; i < (int) arena.size(); i++)
	{
		for (int j = 0; j < (int) arena[i].size() * 2 + 1; j++)
		{
			std::cout << '-'; //ASCII ART
		}
		std::cout << std::endl;
		std::cout << "|"; //ASCII ART


		for (int j = 0; j < (int) arena[i].size(); j++)
		{
			
			if (coloredWords[i][j])
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARKYELLOW);
			}
			std::cout << arena[i][j];
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
			std::cout << "|"; //ASCII ART
		}
		std::cout << " " << i + 1; //ASCII ART - Prints row numbers

		std::cout << std::endl;
	}
	for (int j = 0; j < (int) arena[0].size() * 2 + 1; j++)
	{
		std::cout << '-'; //ASCII ART
	}

}

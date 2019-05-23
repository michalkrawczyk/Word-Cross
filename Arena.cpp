//Created By Micha� Krawczyk on 23.05.2019
#include "pch.h"
#include "Arena.h"


Arena::Arena(int ndirections)
{
	if (ndirections <= ArenaConsts::directionsAvailable && ndirections > 0)
	{
		this->ndirections = ndirections;
	}
	else
	{
		throw std::invalid_argument("Nieprawidlowa liczba kierunkow");
	}
	this->generated = false;
	this->isEmpty = true;
}


Arena::~Arena()
{
}


void Arena::makeArena(vec2Dchar &arena, int columns, int rows)
{
	//generates empty Arena
	arena.clear();

	if (columns <= 0 || rows <= 0) //alternative to unsigned values ,due to comparison operations - avoiding unexpected situations
	{
		std::invalid_argument("Niedozwolone rozmiary Planszy");
	}

	int width = columns;
	int height = rows;

	arena.resize(height, std::vector<char>(width));

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
				arena[i][j] = '*';
		}
	}
	
	this->generated = true;

}

bool Arena::findWord(mapStrBool &dictionary, std::string word)
{
	//check if given word is used in Arena

	//	Mo�e u�y� w Mainie?

	word = formatPolish(word); 
	std::cout << word << std::endl;
	if (!isEmpty)
	{
		auto it = dictionary.find(word);
		if (it != dictionary.end() && it->second==true)
		{
			return true;
		}

	}
	else
	{
		std::cout << "Plansza jest pusta" << std::endl;
	}
	return false;
}

void Arena::usedWords(mapStrBool &dictionary)
{
	//wyswietla liste uzytych slow
	int total = 0;
	if (!isEmpty)
	{
		std::cout << "____________________________" << std::endl; //ASCII ART
		std::cout << "Uzyte slowa:" << std::endl;
		for (auto &it : dictionary)
		{
			if (it.second == true)
			{
				total++;
				std::cout << it.first << std::endl;
			}
		}
		std::cout << std::endl;
		std::cout << "Liczba uzytych slow: " << total << std::endl;
		std::cout << "___________________________" << std::endl; //ASCII ART
	}
	else
	{
		std::cout << "Niewygenerowana Plansza lub Plansza nie jest wypelniona" << std::endl;
	}
}

bool Arena::addWord(vec2Dchar &arena, std::string &word, DIRECTION dir, int column, int row)
{
	//writes word into Arena
	if (!wordFit(arena, word, column, row, dir))
	{
		return false;
	}
	if (generated)
	{
		switch (dir)
		{
			case LEFTRIGHT:
			{
				for (int i = 0; i < (int)word.length(); i++)  
				{
					arena[row][column + i] = word[i];
				}
				break;
			}
			case UPDOWN:
			{
				for (auto i = 0; i < (int)word.length(); i++) 
				{
					arena[row+i][column] = word[i];
				}
				break;
			}
			default:
			{
				return false;
				break;
			}
		}
		return true;
	}
	else
	{
		std::cout << "Niewygenerowana Plansza " << std::endl;
		return false;
	}
}

void Arena::printArena(vec2Dchar & arena)
{
	//prints Arena on console
	if (generated)
	{
		for (int i = 0; i < (int) arena[0].size(); i++)
		{
			std::cout << " " << i + 1; //ASCII ART - prints column number
		}
		std::cout << std::endl;

		for (int i = 0; i < (int) arena.size(); i++)
		{
			for (int j = 0; j < (int) arena[i].size()*2+1; j++)
			{
				std::cout << '-'; //ASCII ART
			}
			std::cout << std::endl;
			std::cout << "|"; //ASCII ART
			for (int j = 0; j < (int) arena[i].size(); j++)
			{
				std::cout << arena[i][j];
				std::cout << "|"; //ASCII ART
			}
				std::cout << " " << i  + 1; //ASCII ART - prints row number
				
			std::cout << std::endl; 
		}
		for (int j = 0; j < (int) arena[0].size() * 2+1; j++)
		{
			std::cout << '-'; //ASCII ART
		}
		std::cout << std::endl;
	}
	else
	{
		std::cout << "Wygeneruj najpierw plansze" << std::endl;
	}
}

void Arena::fullfillArena(vec2Dchar & arena, mapStrBool & dictionary, int nwords)
{
	//wypelnia plansze slowami i przypadkowymi znakami
	if (generated)
	{
		
		int height = arena.size();
		int width = arena[0].size();
		srand(time(NULL));
		std::string word;
		for (int i = 0; i < nwords; i++)
		{
			DIRECTION dir = static_cast <DIRECTION>(rand() % this->ndirections);

			mapStrBool::iterator mapIt;
			
			//losowanie dopoki nie znajdzie pasujacego wyrazu
			//dodatkowe ograniczenie czasowe - je�li nie zmie�ci si� w 100 losowaniach na 1 wyraz to idzie exception
			int controlValue = 0;
			int x, y;

			do
			{
				mapIt = dictionary.begin();
				std::advance(mapIt, rand() % dictionary.size());
				word = mapIt->first;
				

				controlValue++;
				if (controlValue >= 100)
				{
					throw std::runtime_error("Przekroczono dozwolona liczbe losowan dla pojedynczego wyrazu");
				}

				x = rand() % width;
				y = rand() % height;

			} while (!(mapIt->second == false && addWord(arena, word, dir, x, y)));

			mapIt->second = true;
		}
		for (int i = 0; i < (int) arena.size(); i++)
		{
			for (int j = 0; j < (int) arena[i].size(); j++)
			{
				if (arena[i][j] == '*')
				{
					arena[i][j] = char(97 + rand() % 25);
					//fullfils arena with random characters
				}
			}
		}
		isEmpty = false;
	}
	else
	{
		std::cout << "Niewygenerowana Plansza lub Plansza nie jest wypelniona" << std::endl;
	}
}

int Arena::getnDirections()
{
	return this->ndirections;
}



bool Arena::wordFit(vec2Dchar & arena, std::string & word, int column, int row, DIRECTION dir)
{
	//sprawdza czy slowo pasuje
	int height = arena.size() ;
	int width = arena[0].size();
	int wordlen = word.length();

	if (column < width && row < height) 
	{
		switch (dir)
		{
			case LEFTRIGHT:
			{
				if ((column + wordlen) <= width)
				{
					for (int i=0;i<wordlen;i++)
					{
						//sprawdza czy w tym miejscu jest litera i czy jest puste
						if (arena[row][column + i] != '*' && arena[row][column] != word[i])
						{
							return false;
						}
					}
					return true;
				}
				
				return false;
				break;
			}
			case UPDOWN:
			{
				if ((row + wordlen) <= height)
				{
					for (int i = 0; i < wordlen; i++)
					{
						if (arena[row + i ][column] != '*' && arena[row + i][column] != word[i])
						{
							return false;
						}
					}
					return true;
				}
				
				return false;
				break;
			}
			default:
			{
				return false;
				break;
			}
		}
	}
	return false;
}


//cast to int in for loops made just to delete warnings with comparison between 2 different types
// Still considering limit rows and columns to max console size
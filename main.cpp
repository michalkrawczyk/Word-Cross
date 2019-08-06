//Created By Michał Krawczyk on 23.05.2019

#include "pch.h"
#include <iostream>
#include <fstream>
#include <conio.h>


#include "Naive.h"
#include "Configuration.h"


#define DICTIONARY_FILE "słowa.txt"


mapStrBool dictionary;
vec2Dchar arena;

enum CHOICE
{
	NONE = -1,
	EXIT = 0,
	CONFIG = 1,
	NEW_ARENA = 2,
	PRINT_ARENA = 3,
	PLAY_NAIVE = 4,
};

void loadData();
void resetDictionary();
void printMenu();

int main()
{
	try {
		loadData();
		Configuration loadConfig;
		
		bool arenaCreated = false; 
		Arena game(loadConfig.getNDirections());

		int choice = CHOICE::NONE;
		printMenu();		

		while (choice == CHOICE::NONE)
		{
			
			std::cin >> choice;
			std::cout << "Wybrano:" << choice << std::endl;

			switch (choice)
			{
				case CHOICE::EXIT:
				{
					break;
				}

				case CHOICE::CONFIG:
				{
					loadConfig.showSettings();
					
					choice = CHOICE::NONE;
					break;
				}

				case CHOICE::NEW_ARENA:
				{
					if (arenaCreated)
					{
						resetDictionary();
					}

					std::cout << "Generuje Nowa Plansze" << std::endl;
					game.makeArena(arena, loadConfig.getNColumns(), loadConfig.getNRows());
					game.fullfillArena(arena, dictionary, loadConfig.getNWords());
					
					std::cout << "Pomyslnie Wygenerowano Nowa Plansze " << std::endl;
					arenaCreated = true;

					choice = CHOICE::NONE;
					break;
				}

				case CHOICE::PRINT_ARENA:
				{
					if (arenaCreated)
					{
						game.printArena(arena);
						game.usedWords(dictionary); 
					}
					else
					{
						std::cout<<"Najpierw Nalezy Wygenerowac Plansze (Opcja nr.2)" << std::endl;
					}

					choice = CHOICE::NONE;
					break;
				}

				case CHOICE::PLAY_NAIVE:
				{
					if (arenaCreated)
					{
						Naive play(dictionary, loadConfig.getNDirections());
						play.solveNaive(arena);
						play.printWordsFound();
					}
					else
					{
						std::cout << "Najpierw Nalezy Wygenerowac Plansze (Opcja nr.2)" << std::endl;
					}
					
					choice = CHOICE::NONE;
					break;
				}

				default:
				{
					std::cout << "Nieprawidlowa opcja - Sproboj ponownie" << std::endl;
					std::cout << std::endl;
					printMenu();
					
					choice = CHOICE::NONE;
					break;
				}
			}
		}
				
	}
	catch (std::exception& e)
	{
		std::cout << std::endl;
		std::cout << "Blad: " << e.what() << std::endl;
		std::cout << "Nacisnij dowolny klawisz ,aby zakonczyc..." << std::endl;
		_getch();
	}
}

void loadData()
{
	std::ifstream input(DICTIONARY_FILE);
	#ifdef DEBUG
		std::cout << "Wczytuje dane..";
	#endif // DEBUG
	if (input.is_open() && input.good())
	{
		std::string word;
		std::getline(input, word); // to get rid of first line

		while (!input.eof())
		{
			std::getline(input, word);
			dictionary[formatPolish(word)] = false;
		}
		
		input.close();
	#ifdef DEBUG
		std::cout << ". - Zrobione" << std::endl;
	#endif // DEBUG 		
	}

	else
	{
		throw std::runtime_error("Nie udalo sie wczytac pliku z danymi wejsciowymi");
	}
	
}

void resetDictionary()
{
	if (!dictionary.empty())
	{
		for (auto &it : dictionary)
		{
			it.second = false; 
		}
	}
	else
	{
		std::cout << "Slownik jest pusty - Ponowne wczytanie danych" << std::endl;
		loadData();
	}
		
}

void printMenu()
{
	std::cout << std::endl;
	std::cout << "Wybierz opcje , poprzez wpisanie odpowiedniej liczby " << std::endl;
	std::cout << "Po wybraniu opcji , potwierdz ja za pomoca klawisza ENTER" << std::endl;
	std::cout << "Lista Opcji:" << std::endl;
	std::cout << "0 - Wyjscie z programu" << std::endl;
	std::cout << "1 - Pokaz Ustawienia" << std::endl;
	std::cout << "2 - Generuj Plansze" << std::endl;
	std::cout << "3 - Pokaz Plansze" << std::endl;
	std::cout << "4 - Rozwiaz metoda naiwna" << std::endl;
}

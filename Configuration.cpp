//Created By Micha³ Krawczyk on 23.05.2019
#include "pch.h"
#include "Configuration.h"


Configuration::Configuration()
{
	this->loadConfigFromFile();
}

void Configuration::showSettings()
{
	std::cout << "Obecne Ustawienia:" << std::endl;
	std::cout << " Liczba Wierszy:" << this->nRows << std::endl;
	std::cout << " Liczba Kolumn:" << this->nColumns << std::endl;
	std::cout << " Liczba Dozwolonych Kierunkow:" << this->nDirections << std::endl;
	std::cout << " Liczba Uzytych Slow:" << this->nWords << std::endl;
	std::cout << std::endl;
}

int Configuration::getNDirections()
{
	return this->nDirections;
}

int Configuration::getNRows()
{
	return this->nRows;
}

int Configuration::getNColumns()
{
	return this->nColumns;
}

int Configuration::getNWords()
{
	return this->nWords;
}

void Configuration::loadConfigFromFile()
{
	#ifdef DEBUG
	std::cout << "Wczytuje ustawienia.";
	#endif // DEBUG

	
	std::ifstream config(CONFIGURATION_FILE);
	if (config.is_open() && config.good())
	{
		int nRows;
		int nColumns;
		int nDirections;
		int nWords;

		config >> nRows;
		config >> nColumns;
		config >> nDirections;
		config >> nWords;

		this->nRows = nRows;
		this->nColumns = nColumns;
		this->nDirections = nDirections;
		this->nWords = nWords;

		config.close();
	}
	else
	{
		throw std::runtime_error("Nie udalo sie wczytac pliku konfiguracyjnego");
	}
	#ifdef DEBUG
		std::cout << ". - Zrobione" << std::endl;
	#endif // DEBUG
}

//Considering: using stringstream to read data


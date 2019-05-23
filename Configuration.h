//Created By Micha³ Krawczyk on 23.05.2019
#pragma once

#include <iostream>
#include <fstream>

#define CONFIGURATION_FILE "config.txt"

class Configuration
{
public:
	Configuration();
	void showSettings();
	int getNDirections();
	int getNRows(); 
	int getNColumns();
	int getNWords();
private:
	int nDirections;
	int nRows; 
	int nColumns;
	int nWords;
	void loadConfigFromFile();
};


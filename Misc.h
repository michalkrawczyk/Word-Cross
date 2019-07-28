//Created By Micha³ Krawczyk on 23.05.2019
#pragma once

#include <string>


enum COLOR //kolory konsoli do wypisywania
{
	BLACK = 0, 
	DARKBLUE = 1,
	DARKGREEN = 2,
	DARKAZURE = 3,
	DARKRED = 4,
	PURPLE = 5,
	DARKYELLOW = 6,
	WHITE = 7,
	GREY = 8,
};


std::string formatPolish(std::string word);

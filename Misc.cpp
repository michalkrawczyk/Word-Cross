//Created By Micha³ Krawczyk on 23.05.2019
#include "pch.h"
#include "Misc.h"


std::string formatPolish(std::string word)
{
	/*Polish characters can cause some errors (Made from differences , between compiler and system interpretation)
	So I've decided to write my own method 
	Made by analyzing how they're are stored
	*/
	std::string temp;
	int ctrl[2];

	for (int i = 0; i < (int)word.length(); i++)
	{
		ctrl[0] = int(word[i]);
		if (ctrl[0] < 0)
		{
			ctrl[1] = int(word[++i]);
			if (ctrl[0] == -60 && ctrl[1] == -123) // ¹
				temp += char(165);
			else if (ctrl[0] == -60 && ctrl[1] == -103) //ê
				temp += char(169);
			else if (ctrl[0] == -60 && ctrl[1] == -121) //æ
				temp += char(134);
			else if (ctrl[0] == -59 && ctrl[1] == -126) //³
				temp += char(136);
			else if (ctrl[0] == -61 && ctrl[1] == -77) //ó
				temp += char(162);
			else if (ctrl[0] == -59 && ctrl[1] == -68) //¿
				temp += char(190);
			else if (ctrl[0] == -59 && ctrl[1] == -70) //Ÿ
				temp += char(171);
			else if (ctrl[0] == -59 && ctrl[1] == -101) //œ
				temp += char(152);
			else if (ctrl[0] == -59 && ctrl[1] == -124) //ñ
				temp += char(228);
			else
			{
				temp += word[i - 1];
				temp += word[i];
			}
		}
		else
		{
			temp += word[i];
		}
	}
	return temp;
}
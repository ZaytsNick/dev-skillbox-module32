// Task_1.cpp: определяет точку входа для приложения.
//

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
#include "nlohmann/json.hpp"
struct MainCharacter
{
	std::string nameCharacter;
	std::string nameActor;
};
struct Film
{
	std::string name;
	std::string country;
	std::tm date;
	std::string studio;
	std::string	writtenBy;
	std::string	director;
	std::string	producer;
	//std::vector<MainCharacter>mainCharacters;	
};
Film addFilm()
{
	Film temp;
	temp.name = "Swiss Army Man";
	temp.country="USA";
	temp.date.tm_year=2016;//2016
	temp.studio="Blackbird Films";
	temp.writtenBy = "Daniel Scheinert";
	temp.director = "Daniel Kwan";
	temp.producer = "Miranda Bailey";
	/*MainCharacter tempCharacter("Manny", "Daniel Radcliffe");
	temp.mainCharacters.push_back(tempCharacter);
	tempCharacter.nameCharacter = "Hank";
	tempCharacter.nameActor= "Paul Dano";
	temp.mainCharacters.push_back(tempCharacter);	*/
	return temp;
}
int main()
{
	Film film1;
	film1 = addFilm();
	std::ofstream file("film.json");
	std::cout << film1.name;
	nlohmann::json dict = 	{
		{ "name",		film1.name},
		{ "country",	film1.country},
		{ "date",		film1.date.tm_year },
		{ "studio",		film1.studio },
		{ "writtenBy",	film1.writtenBy },
		{ "director",	film1.director },
		{ "producer",	film1.producer }
		//std::vector<MainCharacter>mainCharacters;
	};
	file << dict;
	file.close();
	return 0;
}

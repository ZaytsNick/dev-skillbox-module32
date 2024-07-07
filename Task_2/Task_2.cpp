// Task_2.cpp: определяет точку входа для приложения.
//

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
#include <sstream>
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
	std::vector<MainCharacter>mainCharacters;
};
void addFilm(Film(&films)[], size_t count)
{
	for(int i=0;i< count;i++)
	{
		Film temp;
		films[i].name = "Swiss Army Man PART "+std::to_string(i+1);
		films[i].country = "USA";
		films[i].date.tm_year = 2016+i*2;//2016
		films[i].studio = "Blackbird Films";
		films[i].writtenBy = "Daniel Scheinert";
		films[i].director = "Daniel Kwan";
		films[i].producer = "Miranda Bailey";
		MainCharacter tempCharacter(std::to_string(i + 1) + "Manny", std::to_string(i + 1)+"Daniel " + std::to_string(i + 1) + "Radcliffe");
		films[i].mainCharacters.push_back(tempCharacter);
		tempCharacter.nameCharacter = "Hank";
		tempCharacter.nameActor = std::to_string(i + 1) + "Paul "+ std::to_string(i + 1) + "Dano";
		films[i].mainCharacters.push_back(tempCharacter);
	}
}
void recordFilm(Film (&films)[],size_t count)
{
	std::ofstream file("film.json", std::ios::app);
	nlohmann::json allFilms;
	for(int i=0;i< count; i++)
	{
		//std::cout << films[i].name << " " << films[i].mainCharacters.size();
		nlohmann::json dict = {
			{ "country",	films[i].country},
			{ "date",		films[i].date.tm_year },
			{ "studio",		films[i].studio },
			{ "writtenBy",	films[i].writtenBy },
			{ "director",	films[i].director },
			{ "producer",	films[i].producer }
		};
		for (const auto& character : films[i].mainCharacters) {
			dict["mainCharacters"].push_back({
				{ "nameActor", character.nameActor },
				{ "nameCharacter", character.nameCharacter }
				});
		}		

		allFilms[films[i].name] = dict;
		
	}
	if (file.is_open()) {
		file << allFilms.dump(4) << std::endl;
		file.close();
	}
}
void readFilm(Film(&films)[], size_t count, nlohmann::json& allFilms)
{
	int i = 0;
	for (auto it = allFilms.begin(); it != allFilms.end(); ++it) {
		//Film film;
		films[i].name = it.key();
		films[i].country = it.value()["country"];
		films[i].date.tm_year = it.value()["date"];
		films[i].studio = it.value()["studio"];
		films[i].writtenBy = it.value()["writtenBy"];
		films[i].director = it.value()["director"];
		films[i].producer = it.value()["producer"];

		for (const auto& charJson : it.value()["mainCharacters"]) {
			MainCharacter character;
			character.nameActor = charJson["nameActor"];
			character.nameCharacter = charJson["nameCharacter"];
			films[i].mainCharacters.push_back(character);
		}
		i++;
	}
}
bool comparison(std::string search, std::string word)
{
	bool tmp(true);
	if (search.size() == word.size()) {
		for (int k = 0; tmp && k < search.size(); k++) {
			if (search[k] != word[k]) {
				tmp = false;
				break;
			}
		}
	}
	else return false;
	return tmp;
}
void searchFilm(Film(&films)[], size_t count)
{
	std::cout << "Enter name or surname actor: ";
	std::string search;
	std::cin >> search;
	for (int i = 0; i < count; i++)	{
		for (int j = 0; j < films[i].mainCharacters.size();j++){
			std::istringstream actor(films[i].mainCharacters[j].nameActor);
			std::string name, surname;
			actor >> name >> surname;
			if(comparison(search, name)) {
				std::cout << films[i].name << std::endl;
				return;
			}
			else if (comparison(search, surname)) {
				std::cout << films[i].name << std::endl;
				return;
			}
		}
	}
	std::cout<<"There are no films with such an actor" << std::endl;
}
int main()
{
	Film films[5];
	size_t count = std::size(films);
	std::ifstream file("film.json");

	nlohmann::json allFilms;
	if (!file.is_open()) {
		std::cerr << "Failed to open file" << std::endl;
		addFilm(films, count);
		recordFilm(films, count);
	}else
	{
		file >> allFilms;
		file.close();
	}
	readFilm(films, count, allFilms);
	searchFilm(films, count);
	return 0;
}

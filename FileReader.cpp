#include "FileReader.h"

#include <fstream>
#include <string>

#include "Resources.h"

FileReader::FileReader(std::string filename) 
	: filename(filename) 
{
	updateValues();
}


bool FileReader::updateValues()
{
	std::fstream file;
	file.open(filename, std::ios::in);
	if (!file.is_open())
	{
		std::cout << "Can't open the file!" << std::endl;
		return false;
	}

	while (!file.eof())
	{
		std::string value;
		file >> value;

		if (value == "cell_rows") file >> CELL_HEIGHT_AMOUNT;
		if (value == "cell_cols") file >> CELL_WIDTH_AMOUNT;
		if (value == "colors") file >> MAX_GROUPS;
		if (value == "range") file >> RANGE;
		if (value == "random_R_tries") file >> RANDOM_R_TRIES;
		if (value == "speed") file >> game_speed;
		if (value == "k") file >> k;
		if (value == "monte_carlo_groups") file >> monte_carlo_groups;
	}

	std::cout << "cell rows: " << CELL_HEIGHT_AMOUNT << std::endl;
	std::cout << "cell cols: " << CELL_WIDTH_AMOUNT << std::endl;
	std::cout << "colors: " << MAX_GROUPS << std::endl;
	std::cout << "range: " << RANGE << std::endl;
	std::cout << "random_R_tries: " << RANDOM_R_TRIES << std::endl;
	std::cout << "speed: " << game_speed << std::endl;
	std::cout << "k: " << k << std::endl;
	std::cout << "monte_carlo_groups: " << monte_carlo_groups << std::endl;

	return true;

}
#pragma once
#include <iostream>

class FileReader
{
public:
	FileReader(std::string filename);

	bool updateValues();

private:
	std::string filename;
};
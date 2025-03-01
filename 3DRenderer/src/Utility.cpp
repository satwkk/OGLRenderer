#include "Utility.h"
#include <iostream>
#include <filesystem>
#include <fstream>

std::string Utility::ReadFile(const std::string& filePath)
{
	std::filesystem::path file(filePath);
	std::ifstream inputStream(filePath);
	std::string contents{};

	std::string src{};
	while (std::getline(inputStream, src))
	{
		contents.append(src+'\n');
	}
	return contents;
}
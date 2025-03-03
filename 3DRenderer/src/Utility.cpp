#include "Utility.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <assert.h>

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

std::string Utility::GetFileNameFromPath(const std::string& filePath)
{
	std::filesystem::path file(filePath);
	assert(file.has_filename());
	auto fileName = file.filename();
	auto fileStr = fileName.string();
	return fileStr.substr(0, fileStr.find_first_of('.'));
}

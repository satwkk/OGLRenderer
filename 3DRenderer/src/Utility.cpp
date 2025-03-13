#include "Utility.h"
#include <iostream>
#include <filesystem>
#include <fstream>

std::string CUtility::ReadFile(const std::string& filePath)
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

std::string CUtility::GetFileNameFromPath(const std::string& filePath)
{
	std::filesystem::path file(filePath);
	ASSERT(file.has_filename());
	auto fileName = file.filename();
	auto fileStr = fileName.string();
	return fileStr.substr(0, fileStr.find_first_of('.'));
}

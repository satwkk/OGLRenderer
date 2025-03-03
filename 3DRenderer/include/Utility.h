#pragma once

#include <string>

class Utility
{
public:
	static std::string ReadFile(const std::string& filePath);
	static std::string GetFileNameFromPath(const std::string& filePath);
};
#pragma once

#include <string>
#include "Logger.h"

#define ASSERT(x) \
if (!(x)) { \
	verr << #x << " failed" << __FILE__ << ":" << __LINE__ << nl; \
	_CrtDbgBreak();\
}

class Utility
{
public:
	static std::string ReadFile(const std::string& filePath);
	static std::string GetFileNameFromPath(const std::string& filePath);
};
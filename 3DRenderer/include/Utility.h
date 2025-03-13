#pragma once

#include <string>
#include "Logger.h"

#define COPY_CONSTRUCT(className) \
	className(const className& other) noexcept; \
	className& operator=(const className& other) noexcept;\

#define MOVE_CONSTRUCT(className) \
	className(className&& other) noexcept;\
	className& operator=(className&& other) noexcept;\

#define ASSERT(x) \
if (!(x)) { \
	verr << #x << " failed" << __FILE__ << ":" << __LINE__ << nl; \
	_CrtDbgBreak();\
}

class CUtility
{
public:
	static std::string ReadFile(const std::string& filePath);
	static std::string GetFileNameFromPath(const std::string& filePath);
};
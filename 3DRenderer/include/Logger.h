#pragma once

#include <ostream>
#include <string>
#include <iostream>


class Logger
{
public:
	Logger(std::ostream& outputStream, const std::string& prefix) :
		m_Stream(outputStream), m_Prefix(prefix)
	{
	}

	std::ostream& operator<<(const std::string& msg)
	{
		m_Stream << "[" << m_Prefix << "]" << ": " << msg;
		return m_Stream;
	}

private:
	std::string m_Prefix;
	std::ostream& m_Stream;
};

Logger err(std::cerr, "ERROR");
Logger log(std::cout, "LOG");
Logger warn(std::cout, "WARN");
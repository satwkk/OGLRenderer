#pragma once

#include <ostream>
#include <string>
#include <iostream>


class CLogger
{
public:
	CLogger(std::ostream& outputStream, const std::string& prefix) :
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

static CLogger verr(std::cerr, "ERROR");
static CLogger vlog(std::cout, "LOG");
static CLogger vwarn(std::cout, "WARN");

#define nl std::endl;
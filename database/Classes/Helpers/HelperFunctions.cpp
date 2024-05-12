#include "HelperFunctions.h"

#include <sstream>

StringVector splitString(const String& str, char delimiter)
{
	StringVector tokens;
	std::stringstream ss(str);
	String token;

	while (std::getline(ss, token, delimiter))
	{
		tokens.push_back(token);
	}

	return tokens;
}
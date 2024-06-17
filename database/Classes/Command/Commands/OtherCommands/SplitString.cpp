#include "SplitString.h"

#include <sstream>

std::vector<String> SplitString::execute(const String& str, char delimiter)
{
	std::vector<String> tokens;
	std::stringstream ss(str);
	String token;

	while (std::getline(ss, token, delimiter))
	{
		tokens.push_back(token);
	}

	return tokens;
}

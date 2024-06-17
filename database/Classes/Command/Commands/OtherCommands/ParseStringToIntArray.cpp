#include "ParseStringToIntArray.h"

#include "SplitString.h"

std::vector<int> ParseStringToIntArray::execute(const String& string, char delimiter)
{
	std::vector<String> tokens = SplitString::execute(string, delimiter);
	std::vector<int> res(tokens.size());

	for (size_t i = 0; i < tokens.size(); i++) {
		res[i] = std::stoi(tokens[i]);
	}

	return res;
}

#pragma once

#include <vector>
#include <string>
using String = std::string;

class ParseStringToIntArray {
public:
	static std::vector<int> execute(const String& string, char delimiter);
};

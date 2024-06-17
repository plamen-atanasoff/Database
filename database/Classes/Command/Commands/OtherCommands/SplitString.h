#pragma once

#include <vector>
#include <string>
using String = std::string;

class SplitString {
public:
	static std::vector<String> execute(const String& str, char delimiter);
};

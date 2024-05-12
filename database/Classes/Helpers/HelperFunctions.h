#pragma once

#include <string>
#include <vector>

using String = std::string;
using StringVector = std::vector<std::string>;

StringVector splitString(const String& str, char delimiter);

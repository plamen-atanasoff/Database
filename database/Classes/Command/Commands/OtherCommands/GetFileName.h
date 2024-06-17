#pragma once

#include <string>
#include <vector>
#include "../../../Database.h"
using String = std::string;

class GetFileName {
public:
	static const String& execute(const String& tableName, const std::vector<StringPair>& tables);
};
#pragma once

#include <vector>
#include <string>
#include "../../../Database.h"

using String = std::string;

class ReadTablesInfo {
public:
	static void execute(const String& fileName, std::vector<StringPair>* tablesInfo);
};
#pragma once

#include "../../../Database.h"

class WriteTableInfo {
public:
	static void execute(const StringPair& tableInfo, const String& tablesFileName, size_t tablesCount);
};

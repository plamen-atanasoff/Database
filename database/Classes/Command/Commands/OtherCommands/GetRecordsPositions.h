#pragma once

#include <vector>
#include "../../../Column/Column.h"

class GetRecordsPositions {
public:
	static std::vector<size_t> execute(const Column* col, const String& value);
};
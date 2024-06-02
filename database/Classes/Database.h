#pragma once

#include <vector>

#include "Table/Table.h"

struct StringPair {
	static constexpr int MAX_SIZE_STRING = 33;
	char tableName[MAX_SIZE_STRING]{};
	char fileName[MAX_SIZE_STRING]{};

	StringPair() = default;

	StringPair(const char* tableName, const char* fileName) {
		strcpy_s(this->tableName, MAX_SIZE_STRING, tableName);
		strcpy_s(this->fileName, MAX_SIZE_STRING, fileName);
	}
};

class Database
{
public:
	std::vector<StringPair>& getTablesInfo();
	Table& getTable();
private:
	std::vector<StringPair> tablesInfo;
	Table table;
};


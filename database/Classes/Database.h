#pragma once

#include <vector>

#include "Table/Table.h"

struct StringPair {
	static constexpr int MAX_SIZE_STRING = 33;
	char tableName[MAX_SIZE_STRING]{};
	char fileName[MAX_SIZE_STRING]{};

	StringPair() = default;

	StringPair(const char* tableName, const char* fileName) {
		validate(tableName, TABLE_NAME);
		validate(tableName, FILE_NAME);

		strcpy_s(this->tableName, MAX_SIZE_STRING, tableName);
		strcpy_s(this->fileName, MAX_SIZE_STRING, fileName);
	}

private:
	void validate(const char* str, const char* fieldName) {
		if (str == nullptr || strlen(str) == 0) {
			throw std::invalid_argument(String(fieldName) + " cannot be empty");
		}

		if (std::strlen(str) >= MAX_SIZE_STRING) {
			throw std::invalid_argument(String(fieldName) + " length must be less than " + std::to_string(MAX_SIZE_STRING));
		}
	}

	static constexpr const char* TABLE_NAME = "tableName";
	static constexpr const char* FILE_NAME = "fileName";
};

class Database
{
public:
	std::vector<StringPair>& getTablesInfo();
	Table& getTable();
	const char* getTablesInfoFileName() const;
private:
	std::vector<StringPair> tablesInfo;
	Table table;

	static constexpr const char* TABLES_FILE = "tables.dat";
};


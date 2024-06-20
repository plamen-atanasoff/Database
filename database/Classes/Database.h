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
			throw std::invalid_argument(String(fieldName) + IS_EMPTY_MESSAGE);
		}

		if (std::strlen(str) >= MAX_SIZE_STRING) {
			throw std::invalid_argument(String(fieldName) + IS_TOO_LONG_MESSAGE + std::to_string(MAX_SIZE_STRING));
		}
	}

	static constexpr const char* TABLE_NAME = "tableName";
	static constexpr const char* FILE_NAME = "fileName";
	static constexpr const char* IS_EMPTY_MESSAGE = " cannot be empty";
	static constexpr const char* IS_TOO_LONG_MESSAGE = " length must be less than ";
};

class Database
{
public:
	Database(const String& tablesInfoFilePath);
	std::vector<StringPair>& getTablesInfo();
	Table& getTable();
	const String& getTablesInfoFileName() const;
private:
	std::vector<StringPair> tablesInfo;
	Table table;
	String tablesInfoFilePath;

	static constexpr const char* FILE_COULD_NOT_BE_OPENED_MESSAGE = "file could not be opened";
};


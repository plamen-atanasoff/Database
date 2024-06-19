#include "Database.h"

Database::Database(const String& tablesInfoFilePath) : tablesInfoFilePath(tablesInfoFilePath) {
	std::fstream file(tablesInfoFilePath, std::ios::in | std::ios::out | std::ios::binary);
	if (!file.is_open()) {
		file.open(tablesInfoFilePath, std::ios::out | std::ios::binary);
		file.close();

		file.open(tablesInfoFilePath, std::ios::in | std::ios::out | std::ios::binary);
		if (!file.is_open()) {
			throw std::exception("file could not be opened");
		}
	}
}

std::vector<StringPair>& Database::getTablesInfo()
{
    return tablesInfo;
}

Table& Database::getTable()
{
    return table;
}

const String& Database::getTablesInfoFileName() const
{
    return tablesInfoFilePath;
}

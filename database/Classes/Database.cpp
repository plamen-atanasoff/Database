#include "Database.h"

Database::Database(const String& tablesInfoFilePath) : tablesInfoFilePath(tablesInfoFilePath) {}

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

#include "Database.h"

std::vector<StringPair>& Database::getTablesInfo()
{
    return tablesInfo;
}

Table& Database::getTable()
{
    return table;
}

const char* Database::getTablesInfoFileName() const
{
    return TABLES_FILE;
}

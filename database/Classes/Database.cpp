#include "Database.h"

std::vector<StringPair>& Database::getTablesInfo()
{
    return tablesInfo;
}

Table& Database::getTable()
{
    return table;
}

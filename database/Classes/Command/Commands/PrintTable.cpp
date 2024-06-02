#include "PrintTable.h"

PrintTable::PrintTable(Table* table) : table(table) {}

void PrintTable::execute() const
{
	table->printTable();
}

PrintTableCreator::PrintTableCreator() : CommandCreator(CommandType::PRINT_TABLE) {}

Command* PrintTableCreator::create(const std::vector<String>& args, Database& database) const
{
	return new PrintTable(&database.getTable());
}

static PrintTableCreator __;
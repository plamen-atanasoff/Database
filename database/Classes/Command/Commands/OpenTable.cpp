#include "OpenTable.h"

#include "ReadIntoTable.h"
#include "OtherCommands/GetFileName.h"

OpenTable::OpenTable(const String& tableName, const std::vector<StringPair>& tables, Table* table) 
	: tableName(tableName), tables(tables), table(table) {}

void OpenTable::execute() const
{
	const String& fileName = GetFileName::execute(tableName, tables);
	if (fileName == "") {
		throw std::exception("table not found");
	}

	ReadIntoTable command(fileName, table);
	command.execute();
}

Command* OpenTable::clone() const
{
	return new OpenTable(*this);
}

OpenTableCreator::OpenTableCreator() : CommandCreator(CommandType::OPEN_TABLE) {}

Command* OpenTableCreator::create(const std::vector<String>& args, Database& database) const
{
	if (args.size() != 1) {
		throw std::exception("invalid arguments count");
	}

	return new OpenTable(args[0], database.getTablesInfo(), &database.getTable());
}

static OpenTableCreator __;

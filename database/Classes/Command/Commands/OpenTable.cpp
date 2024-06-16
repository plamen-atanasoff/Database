#include "OpenTable.h"

#include "ReadIntoTable.h"

OpenTable::OpenTable(const String& tableName, const std::vector<StringPair>& tables, Table* table) 
	: tableName(tableName), tables(tables), table(table) {}

void OpenTable::execute() const
{
	String fileName = getFileName();
	if (fileName == "") {
		throw std::exception("table not found");
	}

	// ask to save current table?

	ReadIntoTable command(fileName, table);
	command.execute();
}

String OpenTable::getFileName() const
{
	size_t n = tables.size();
	for (size_t i = 0; i < n; i++) {
		if (tableName == tables[i].tableName) {
			return tables[i].fileName;
		}
	}

	return "";
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

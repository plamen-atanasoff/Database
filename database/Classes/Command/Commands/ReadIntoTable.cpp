#include "ReadIntoTable.h"

#include <fstream>

ReadIntoTable::ReadIntoTable(const String& fileName, Table* table) : fileName(fileName), table(table) {}

void ReadIntoTable::execute() const
{
	// ask to save the current table

	std::ifstream ifile(fileName, std::ios::binary);
	if (!ifile.is_open()) {
		throw std::exception("file could not be opened");
	}
	table->readFromFile(ifile);

	ifile.close();
}

ReadIntoTableCreator::ReadIntoTableCreator() : CommandCreator(CommandType::READ_TABLE) {}

Command* ReadIntoTableCreator::create(const std::vector<String>& args, Database& database) const
{
	return new ReadIntoTable(args[0], &database.getTable());
}

static ReadIntoTableCreator __;
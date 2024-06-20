#include "ReadIntoTable.h"

#include <fstream>

ReadIntoTable::ReadIntoTable(const String& fileName, Table* table) : fileName(fileName), table(table) {}

void ReadIntoTable::execute() const
{
	std::ifstream ifile(fileName, std::ios::binary);
	if (!ifile.is_open()) {
		throw std::exception("file could not be opened");
	}
	table->readFromFile(ifile);

	ifile.close();
}

Command* ReadIntoTable::clone() const
{
	return new ReadIntoTable(*this);
}

ReadIntoTableCreator::ReadIntoTableCreator() : CommandCreator(CommandType::READ_TABLE) {}

Command* ReadIntoTableCreator::create(const std::vector<String>& args, Database& database) const
{
	if (args.size() != 1) {
		throw std::exception("invalid arguments count");
	}

	return new ReadIntoTable(args[0], &database.getTable());
}

static ReadIntoTableCreator __;

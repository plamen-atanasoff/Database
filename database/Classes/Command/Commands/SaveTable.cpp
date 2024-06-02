#include "SaveTable.h"

SaveTable::SaveTable(const String& fileName, Table* table) : fileName(fileName), table(table) {}

void SaveTable::execute() const
{
	std::ofstream ofile(fileName, std::ios::binary);
	if (!ofile.is_open()) {
		throw std::exception("file could not be opened");
	}
	table->writeToFile(ofile);

	ofile.close();
}

SaveTableCreator::SaveTableCreator() : CommandCreator(CommandType::SAVE_TABLE) {}

Command* SaveTableCreator::create(const std::vector<String>& args, Database& database) const
{
	if (args.size() != 1) {
		throw std::exception("invalid arguments count");
	}

	return new SaveTable(args[0], &database.getTable());
}

static SaveTableCreator __;
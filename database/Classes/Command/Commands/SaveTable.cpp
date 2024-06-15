#include "SaveTable.h"

SaveTable::SaveTable(const std::vector<StringPair>& tables, const Table* table) : tables(tables), table(table) {}

void SaveTable::execute() const
{
	String fileName = getFileName();
	if (fileName == "") {
		throw std::exception("table does not exist in database");
	}

	std::ofstream ofile(fileName, std::ios::binary);
	if (!ofile.is_open()) {
		throw std::exception("file could not be opened");
	}
	table->writeToFile(ofile);

	ofile.close();
}

String SaveTable::getFileName() const
{
	size_t n = tables.size();
	for (size_t i = 0; i < n; i++) {
		if (table->getName() == tables[i].tableName) {
			return tables[i].fileName;
		}
	}

	return "";
}

SaveTableCreator::SaveTableCreator() : CommandCreator(CommandType::SAVE_TABLE) {}

Command* SaveTableCreator::create(const std::vector<String>& args, Database& database) const
{
	if (args.size() != 0) {
		throw std::exception("invalid arguments count");
	}

	return new SaveTable(database.getTablesInfo(), &database.getTable());
}

static SaveTableCreator __;
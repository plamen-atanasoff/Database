#include "ImportTable.h"

#include "OtherCommands/WriteTableInfo.h"

ImportTable::ImportTable(const String& fileName, std::vector<StringPair>& tables, Table* table, const String& tablesFileName)
	: fileName(fileName), tables(tables), table(table), tablesFileName(tablesFileName) {}

void ImportTable::execute() const
{
	if (fileNameExists()) {
		throw std::exception("table already exists");
	}

	std::ifstream ifile(fileName, std::ios::binary | std::ios::in);
	if (!ifile.is_open()) {
		throw std::exception("file could not be opened");
	}

	Table* tableTemp = new Table();
	tableTemp->readFromFile(ifile);

	StringPair temp(tableTemp->getName(), fileName.c_str());
	WriteTableInfo::execute(temp, tablesFileName, tables.size());

	tables.push_back(temp);

	delete tableTemp;
	ifile.close();
}

Command* ImportTable::clone() const
{
	return new ImportTable(*this);
}

bool ImportTable::fileNameExists() const
{
	size_t n = tables.size();
	for (size_t i = 0; i < n; i++) {
		if (fileName == tables[i].fileName) {
			return true;
		}
	}

	return false;
}

ImportTableCreator::ImportTableCreator() : CommandCreator(CommandType::IMPORT_TABLE) {}

Command* ImportTableCreator::create(const std::vector<String>& args, Database& database) const
{
	if (args.size() != 1) {
		throw std::exception("invalid arguments count");
	}

	return new ImportTable(args[0], database.getTablesInfo(), &database.getTable(), database.getTablesInfoFileName());
}

static ImportTableCreator __;

#pragma once

#include "Helpers/Command.h"

#include <string>
#include <vector>

#include "Table/Table.h"

using StringVector = std::vector<std::string>;

struct StringPair {
	static constexpr int MAX_SIZE_STRING = 33;
	char tableName[MAX_SIZE_STRING]{};
	char fileName[MAX_SIZE_STRING]{};
};

class Controller
{
public:
	Controller();

	void execute(const Command& command);
private:
	std::vector<StringPair> tablesInfo;
	Table table;

	static constexpr const char* TABLES_FILE = "tables.dat"; //.dat or .txt for the tablesInfo file?

	void createTable(const std::vector<std::string>& args);
	void addColumn(const std::string& name, ColumnType type);
	void readTables();
	void printTableNames() const;
};

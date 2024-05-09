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

	void printTableNames() const;
	void createTable(const std::vector<std::string>& args);
	void addColumn(const std::vector<std::string>& args);
	void addRecord(const std::vector<std::string>& args);
	void saveTable() const;
	void readTable(const std::vector<std::string>& args);
	void deleteRecords(const std::vector<std::string>& args);

	void readTables();

	bool tableExists() const;
	const std::string getTableFileName() const;
};

#pragma once

#include "Helpers/Command.h"

#include <string>
#include <vector>

#include "Table/Table.h"

using String = std::string;
using StringVector = std::vector<std::string>;

struct StringPair {
	static constexpr int MAX_SIZE_STRING = 33;
	char tableName[MAX_SIZE_STRING]{};
	char fileName[MAX_SIZE_STRING]{};

	StringPair() = default;

	StringPair(const char* tableName, const char* fileName) {
		strcpy_s(this->tableName, MAX_SIZE_STRING, tableName);
		strcpy_s(this->fileName, MAX_SIZE_STRING, fileName);
	}
};

class Controller
{
public:
	Controller();

	void execute(const Command& command);
private:
	std::vector<StringPair> tablesInfo;
	Table table;

	static constexpr const char* TABLES_FILE = "tables.dat";

	void printTableNames() const;
	void createTable(const std::vector<String>& args);
	void addColumn(const std::vector<String>& args);
	void addRecord(const std::vector<String>& args);
	void saveTable() const;
	void readTable(const std::vector<String>& args);
	void deleteRecords(const std::vector<String>& args);
	void printTable() const;
	void importTable(const std::vector<String>& args);
	void openTable(const std::vector<String>& args);
	void describeColumns() const;
	void exportTable(const std::vector<String>& args) const;
	void updateRecords(const std::vector<String>& args);
	void selectRecords(const std::vector<String>& args) const;

	void readTables();
	void writeTable(const StringPair& sp) const;

	bool tableExists(const char* tableName) const;
	const String getTableFileName(const char* tableName) const;
};

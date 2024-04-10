#pragma once

#include "Helpers/Command.h"

#include <string>
#include <vector>

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
	std::vector<StringPair> tables;

	static constexpr const char* TABLES_FILE = "tables.dat"; //.dat or .txt for the tables file?

	void createTable(const StringVector& args);
	void readTables();
	void printTableNames() const;
};

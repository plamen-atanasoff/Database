#pragma once

#include "Command.h"

#include <string>
#include <vector>

using StringVector = std::vector<std::string>;

struct StringPair {
	String tableName;
	String fileName;
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
};

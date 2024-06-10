#pragma once

#include <cstring>
#include <string>
#include <vector>

#include "Database.h"

using String = std::string;

// make singleton
class Controller
{
public:
	Controller();

	void executeCommand(const String& input);
private:
	Database database;

	static constexpr const char* TABLES_FILE = "tables.dat";
};

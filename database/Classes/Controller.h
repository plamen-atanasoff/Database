#pragma once

#include <cstring>
#include <string>
#include <vector>

#include "Database.h"

using String = std::string;

class Controller
{
public:
	static Controller& getInstance();
	void loadDatabase(const String& databaseFilePath);
	void closeDatabase();

	void executeCommand(const String& input);
private:
	Database* database = nullptr;

	Controller() = default;
	~Controller();
	Controller(const Controller&) = delete;
	Controller& operator=(const Controller&) = delete;

	void free();
};

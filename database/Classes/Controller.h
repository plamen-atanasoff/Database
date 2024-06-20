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

	void run();

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

	bool commandIsLoad(const String& line) const;

	static constexpr const char* DATABASE_NOT_LOADED_MESSAGE = "Database is not loaded";
};

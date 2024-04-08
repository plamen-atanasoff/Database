#include "Controller.h"

#include <fstream>

#include "Command.h"

void Controller::createTable(const StringVector& args)
{}

void Controller::readTables()
{
	std::ifstream ifile(TABLES_FILE, std::ios::binary);
	if (!ifile.is_open()) {
		return;
	}

	StringPair temp;
	size_t size;
	ifile.read(reinterpret_cast<char*>(&size), sizeof(size));
	tables.reserve(size);

	for (size_t i = 0; i < size; i++) {
		ifile.read(reinterpret_cast<char*>(&temp), sizeof(temp)); // would this work with std::string?
		tables.push_back(temp);
	}

	ifile.close();
}

Controller::Controller()
{
	readTables();
}

void Controller::execute(const Command& command)
{
	switch (command.getCommandName()) 
	{
	case CommandType::CREATE:
		createTable(command.getArgs());
		break;
	}
}

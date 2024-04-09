#include "Controller.h"

#include <fstream>
#include <iostream>

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
		ifile.read(reinterpret_cast<char*>(&temp), sizeof(temp));
		tables.push_back(temp);
	}

	ifile.close();
}

void Controller::printTableNames() const
{
	for (const StringPair& pair : tables) {
		std::cout << pair.tableName << '\n';
	}
	std::cout << std::endl;
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
	case CommandType::SHOWTABLES:
		printTableNames();
		break;
	}
}

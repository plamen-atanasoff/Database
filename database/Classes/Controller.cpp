#include "Controller.h"

#include <fstream>
#include <iostream>

#include "Helpers/Command.h"
#include "Factories/ColumnFactory.h"

void Controller::createTable(const std::vector<std::string>& args)
{
	table = Table(args[0]);
}

void Controller::addColumn(const std::vector<std::string>& args)
{
	Column* col = getColumn(args[0], getColumnTypeAsEnum(args[1]));
	// addColumn clones the newly created column
	table.addColumn(*col);

	delete[] col;
}

void Controller::addRecord(const std::vector<std::string>& args)
{
	table.addRecord(args);
}

void Controller::readTables()
{
	std::ifstream ifile(TABLES_FILE, std::ios::binary);
	if (!ifile.is_open()) {
		return;
	}

	StringPair temp;
	size_t size;
	ifile.read(reinterpret_cast<char*>(&size), sizeof(size));
	tablesInfo.reserve(size);

	for (size_t i = 0; i < size; i++) {
		ifile.read(reinterpret_cast<char*>(&temp), sizeof(temp));
		tablesInfo.push_back(temp);
	}

	ifile.close();
}

void Controller::printTableNames() const
{
	for (const StringPair& pair : tablesInfo) {
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
	case CommandType::SHOW_TABLES:
		printTableNames();
		break;
	case CommandType::CREATE_TABLE:
		createTable(command.getArgs());
		break;
	case CommandType::ADD_COLUMN:
		addColumn(command.getArgs());
		break;
	case CommandType::ADD_RECORD:
		addRecord(command.getArgs());
		break;
	}
}

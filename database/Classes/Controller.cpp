#include "Controller.h"

#include <fstream>
#include <iostream>

#include "Helpers/Command.h"
#include "Factories/ColumnFactory.h"

Controller::Controller()
{
	readTables();
}

void Controller::createTable(const std::vector<String>& args)
{
	table = Table(args[0]);
}

void Controller::addColumn(const std::vector<String>& args)
{
	Column* col = getColumn(args[0], getColumnTypeAsEnum(args[1]));
	// addColumn clones the newly created column
	table.addColumn(*col);

	delete[] col;
}

void Controller::addRecord(const std::vector<String>& args)
{
	table.addRecord(args);
}

void Controller::saveTable() const
{
	String fileName;
	if (tableExists()) {
		fileName = getTableFileName();
	}
	else {
		fileName = table.getName();
		fileName.append(".dat");
	}

	std::ofstream ofile(fileName, std::ios::binary);
	if (!ofile.is_open()) {
		throw std::exception("file could not be opened");
	}
	table.writeToFile(ofile);

	ofile.close();
}

void Controller::readTable(const std::vector<String>& args)
{
	// ask to save the current table

	std::ifstream ifile(args[0], std::ios::binary);
	if (!ifile.is_open()) {
		throw std::exception("file could not be opened");
	}
	table.readFromFile(ifile);

	ifile.close();
}

void Controller::deleteRecords(const std::vector<String>& args)
{
	int colPos = std::stoi(args[0]) - 1;
	std::vector<int> recordsPositions = table.getRecordsPositions(colPos, args[1]);
	table.deleteRecords(recordsPositions);
}

void Controller::printTable() const
{
	table.printTable();
}

void Controller::readTables()
{
	std::ifstream ifile(TABLES_FILE, std::ios::binary);
	if (!ifile.is_open()) {
		return;
	}

	size_t size;
	ifile.read(reinterpret_cast<char*>(&size), sizeof(size));

	StringPair temp;
	tablesInfo.reserve(size);
	for (size_t i = 0; i < size; i++) {
		ifile.read(reinterpret_cast<char*>(&temp), sizeof(temp));
		tablesInfo.push_back(temp);
	}

	ifile.close();
}

bool Controller::tableExists() const
{
	for (int i = 0; i < tablesInfo.size(); i++) {
		if (strcmp(table.getName(), tablesInfo[i].tableName) == 0) {
			return true;
		}
	}

	return false;
}

const String Controller::getTableFileName() const
{
	for (int i = 0; i < tablesInfo.size(); i++) {
		if (strcmp(table.getName(), tablesInfo[i].tableName) == 0) {
			return tablesInfo[i].fileName;
		}
	}

	return "";
}

void Controller::printTableNames() const
{
	for (const StringPair& pair : tablesInfo) {
		std::cout << pair.tableName << '\n';
	}
	std::cout << std::endl;
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
	case CommandType::SAVE_TABLE:
		saveTable();
		break;
	case CommandType::READ_TABLE:
		readTable(command.getArgs());
		break;
	case CommandType::DELETE_RECORDS:
		deleteRecords(command.getArgs());
		break;
	case CommandType::PRINT_TABLE:
		// add stream to print to?
		printTable();
		break;
	}
}

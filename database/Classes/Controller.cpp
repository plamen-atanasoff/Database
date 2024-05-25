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

void Controller::saveTable(const std::vector<String>& args) const
{
	String fileN;
	if (args.size() == 0) {
		if (tableExists(table.getName())) {
			fileN = getTableFileName(table.getName());
		}
		else {
			fileN = table.getName();
			fileN.append(".dat");
		}
	}
	else {
		fileN = args[0];
	}

	std::ofstream ofile(fileN, std::ios::binary);
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

void Controller::importTable(const std::vector<String>& args)
{
	std::ifstream ifile(args[0], std::ios::binary);
	if (!ifile.is_open()) {
		return;
	}

	Table t;
	t.readFromFile(ifile);

	ifile.close();

	if (tableExists(t.getName())) {
		return;
	}

	StringPair sp(t.getName(), args[0].c_str());
	writeTable(sp);
	tablesInfo.push_back(sp);
}

void Controller::openTable(const std::vector<String>& args)
{
	// ask to save the current table

	if (!tableExists(args[0].c_str())) {
		return;
	}
	String fileName = getTableFileName(args[0].c_str());
	std::ifstream ifile(fileName, std::ios::binary);
	if (!ifile.is_open()) {
		return;
	}
	table.readFromFile(ifile);

	ifile.close();
}

void Controller::describeColumns() const
{
	table.describeColumns();
}

void Controller::exportTable(const std::vector<String>& args) const
{
	std::ofstream ofile(args[0], std::ios::out | std::ios::trunc);
	if (!ofile.is_open()) {
		return;
	}

	table.printTableToFile(ofile);

	ofile.close();
}

void Controller::updateRecords(const std::vector<String>& args)
{
	int colPosFrom = std::stoi(args[0]) - 1;
	std::vector<int> recordsPositions = table.getRecordsPositions(colPosFrom, args[1]);
	int colPosTo = std::stoi(args[2]) - 1;
	table.updateValues(colPosTo, recordsPositions, args[3]);
}

void Controller::selectRecords(const std::vector<String>& args) const
{
	int colPosFrom = std::stoi(args[0]) - 1;
	std::vector<int> recordsPositions = table.getRecordsPositions(colPosFrom, args[1]);
	table.printTableSelect(recordsPositions);
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

void Controller::writeTable(const StringPair& sp) const
{
	std::fstream file(TABLES_FILE, std::ios::in | std::ios::out | std::ios::binary);
	if (!file.is_open()) {
		return;
	}

	size_t count;
	file.read(reinterpret_cast<char*>(&count), sizeof(count));
	count++;
	file.seekp(0, std::ios::beg);
	file.write(reinterpret_cast<const char*>(&count), sizeof(count));
	file.seekp(0, std::ios::end);
	file.write(reinterpret_cast<const char*>(&sp), sizeof(sp));

	file.close();
}

bool Controller::tableExists(const char* tableName) const
{
	for (int i = 0; i < tablesInfo.size(); i++) {
		if (strcmp(tableName, tablesInfo[i].tableName) == 0) {
			return true;
		}
	}

	return false;
}

const String Controller::getTableFileName(const char* tableName) const
{
	for (int i = 0; i < tablesInfo.size(); i++) {
		if (strcmp(tableName, tablesInfo[i].tableName) == 0) {
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
		saveTable(command.getArgs());
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
	case CommandType::IMPORT_TABLE:
		importTable(command.getArgs());
		break;
	case CommandType::OPEN_TABLE:
		openTable(command.getArgs());
		break;
	case CommandType::DESCRIBE_COLUMNS:
		describeColumns();
		break;
	case CommandType::EXPORT_TABLE:
		exportTable(command.getArgs());
		break;
	case CommandType::UPDATE_RECORDS:
		updateRecords(command.getArgs());
		break;
	case CommandType::SELECT_RECORDS:
		selectRecords(command.getArgs());
		break;
	}
}

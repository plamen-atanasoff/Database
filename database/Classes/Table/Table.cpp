#include "Table.h"

#include <iostream>
#include <iomanip>

#include "../Factories/ColumnFactory.h"

Table::Table(const std::string& name)
{
	strcpy_s(this->name,  name.c_str());
}

// currently only weak exception safety
Table::Table(const Table& other)
{
	copyFrom(other);
}

// currently only weak exception safety
Table& Table::operator=(const Table& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

Table::~Table()
{
	free();
}

void Table::addRecord(const std::vector<std::string>& values)
{
	if (values.size() != cols.size()) {
		return; 
	}

	for (size_t i = 0; i < cols.size(); i++) {
		cols[i]->addValue(values[i]);
	}

	recordsId.push_back(nextRecordId++);
}

void Table::addColumn(const Column& col)
{
	cols.push_back(col.clone());
	cols[cols.size() - 1]->initializeValues(recordsId.size());
}

void Table::writeToFile(std::ofstream& ofile) const
{
	ofile.write(name, MAX_NAME_LENGTH);
	ofile.write(reinterpret_cast<const char*>(&nextRecordId), sizeof(nextRecordId));
	size_t sizeRecords = recordsId.size();
	ofile.write(reinterpret_cast<const char*>(&sizeRecords), sizeof(sizeRecords));
	ofile.write(reinterpret_cast<const char*>(recordsId.data()), sizeof(unsigned) * sizeRecords);
	size_t sizeColumns = cols.size();
	ofile.write(reinterpret_cast<const char*>(&sizeColumns), sizeof(sizeColumns));
	for (int i = 0; i < sizeColumns; i++) {
		cols[i]->writeToFile(ofile);
	}
}

void Table::readFromFile(std::ifstream& ifile)
{
	ifile.read(name, MAX_NAME_LENGTH);
	ifile.read(reinterpret_cast<char*>(&nextRecordId), sizeof(nextRecordId));
	size_t sizeRecords;
	ifile.read(reinterpret_cast<char*>(&sizeRecords), sizeof(sizeRecords));
	recordsId.clear();
	recordsId.resize(sizeRecords);
	ifile.read(reinterpret_cast<char*>(recordsId.data()), sizeof(unsigned) * sizeRecords);
	size_t sizeColumns;
	ifile.read(reinterpret_cast<char*>(&sizeColumns), sizeof(sizeColumns));
	free();
	cols.resize(sizeColumns);
	ColumnType type;
	char name[MAX_NAME_LENGTH]; // change to MAX_NAME_LENGTH of Column
	for (int i = 0; i < sizeColumns; i++) {
		ifile.read(reinterpret_cast<char*>(&type), sizeof(type));
		ifile.read(reinterpret_cast<char*>(name), MAX_NAME_LENGTH);
		cols[i] = getColumn(name, type);
		cols[i]->readFromFile(ifile);
	}
}

std::vector<int> Table::getRecordsPositions(int colPos, const std::string& val) const
{
	return cols[colPos]->getRecordsPositions(val);
}

void Table::deleteRecords(std::vector<int> recordsPositions)
{
	deleteRecordsFromRecordsId(recordsPositions);
	for (size_t i = 0; i < cols.size(); i++) {
		cols[i]->deleteRecords(recordsPositions);
	}
}

void Table::deleteRecordsFromRecordsId(std::vector<int> recordsPositions)
{
	// validate recordsPositions(should contain only positions from 0 to records count - 1)
	// ptr is pointer to the curr record to be removed, i is pointer to the new valid pos, j is pointer to the curr value in values
	size_t i = 0, j = 0;
	for (size_t ptr = 0; ptr < recordsPositions.size(); j++) {
		if (recordsPositions[ptr] == j /* && j + 1 < recordsPositions.size()*/) {
			//recordsId[i] = recordsId[j + 1];
			ptr++;
		}
		else {
			recordsId[i] = recordsId[j];
			i++;
		}
	}
	//i++, j++;
	for (; j < recordsId.size(); j++, i++) {
		recordsId[i] = recordsId[j];
	}

	recordsId.resize(i);
}

//void Table::deleteRecord(int recordPos)
//{
//	recordsId.erase(recordsId.begin() + recordPos);
//	for (size_t i = 0; i < cols.size(); i++) {
//		cols[i]->deleteValue(recordPos);
//	}
//}

void Table::printTable() const
{
	const char* separator = " | ";
	printColumnInfo();
	for (size_t i = 0; i < recordsId.size(); i++) {
		std::cout << std::setw(8) << std::left << recordsId[i] << separator;
		for (size_t j = 0; j < cols.size(); j++) {
			cols[j]->printValueAt(i);
			std::cout << separator;
		}
		std::cout << std::endl;
	}
}

void Table::printColumnInfo() const
{
	const char* separator = " | ";
	std::cout << std::setw(8) << std::left << "Id" << separator;
	for (size_t i = 0; i < cols.size(); i++) {
		std::cout << std::setw(8) << std::left << cols[i]->getName() << separator;
	}
	std::cout << std::endl;
}

const char* Table::getName() const
{
	return name;
}

void Table::copyFrom(const Table& other)
{
	cols.reserve(other.cols.size());
	for (int i = 0; i < other.cols.size(); i++) {
		cols.push_back(other.cols[i]->clone());
	}

	strcpy_s(name, other.name);
	recordsId = other.recordsId;
	nextRecordId = other.nextRecordId;
}

void Table::free()
{
	for (int i = 0; i < cols.size(); i++) {
		delete cols[i];
	}

	cols.clear();
}

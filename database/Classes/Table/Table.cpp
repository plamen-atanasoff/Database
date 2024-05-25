#include "Table.h"

#include <iostream>
#include <iomanip>
#include <cassert>

#include "../Factories/ColumnFactory.h"

Table::Table(const String& name)
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

void Table::addRecord(const std::vector<String>& values)
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
	cols.back()->initializeValues(recordsId.size());
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
	ofile.write(reinterpret_cast<const char*>(&recordsPerPage), sizeof(recordsPerPage));
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
	ifile.read(reinterpret_cast<char*>(&recordsPerPage), sizeof(recordsPerPage));
}

std::vector<int> Table::getRecordsPositions(size_t colPos, const String& val) const
{
	return cols[colPos]->getRecordsPositions(val);
}

void Table::deleteRecords(const std::vector<int>& recordsPositions)
{
	deleteRecordsFromRecordsId(recordsPositions);

	for (size_t i = 0; i < cols.size(); i++) {
		cols[i]->deleteRecords(recordsPositions);
	}
}

void Table::deleteRecordsFromRecordsId(const std::vector<int>& recordsPositions)
{
	assert(recordsPositions.size() <= recordsId.size());
	// ptr is pointer to the current record to be removed,
	// i is pointer to the current valid pos,
	// j is pointer to the current value in values
	size_t i = 0, j = 0;
	for (size_t ptr = 0; ptr < recordsPositions.size(); j++) {
		assert(recordsPositions[ptr] < recordsId.size());

		if (recordsPositions[ptr] == j) {
			ptr++;
		}
		else {
			recordsId[i] = recordsId[j];
			i++;
		}
	}
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

//make this and the next print function into one
void Table::printTable() const
{
	constexpr const char* separator = " | ";

	char command[8]{};
	size_t i = 0;
	unsigned r = recordsPerPage;
	do {
		printColumnInfo();

		for (; i < recordsId.size(); i++) {
			if (i == r) {
				break;
			}
			std::cout << std::setw(3) << std::left << recordsId[i] << separator;
			for (size_t j = 0; j < cols.size(); j++) {
				cols[j]->printValueAt(i);
				std::cout << separator;
			}
			std::cout << std::endl;
		}

		std::cout << "Enter command(prev, next, exit): ";
		std::cin >> command;
		if (strcmp(command, "prev") == 0) {
			if (i == recordsPerPage) {
				i = 0;
				system("cls");
				continue;
			}
			if (i % recordsPerPage == 0) {
				i = i - (size_t)2 * recordsPerPage;
			}
			else {
				i = (i + (recordsPerPage - (i % recordsPerPage))) - (size_t)2 * recordsPerPage;
			}
			r = (unsigned)i + recordsPerPage;
		}
		else if (strcmp(command, "next") == 0) {
			if (i >= recordsId.size()) {
				if (i % recordsPerPage == 0) {
					i -= recordsPerPage;
				}
				else {
					i = (i + (recordsPerPage - (i % recordsPerPage))) - recordsPerPage;
				}
				system("cls");
				continue;
			}
			r += recordsPerPage;
		}

		system("cls");
	} while (strcmp(command, "exit") != 0);
	std::cin.ignore();
}

void Table::printTableToFile(std::ostream& ofile) const
{
	constexpr const char* separator = " | ";

	ofile << std::setw(3) << std::right << "Id" << separator;
	for (size_t i = 0; i < cols.size(); i++) {
		ofile << std::setw(cols[i]->getWidth()) << cols[i]->getName() << separator;
	}
	ofile << std::endl;

	for (size_t i = 0; i < recordsId.size(); i++) {
		ofile << std::setw(3) << std::left << recordsId[i] << separator;
		for (size_t j = 0; j < cols.size(); j++) {
			cols[j]->printValueAtToFile(i, ofile);
			ofile << separator;
		}
		ofile << std::endl;
	}
}

void Table::printColumnInfo() const
{
	const char* separator = " | ";
	std::cout << std::setw(3) << std::right << "Id" << separator;
	for (size_t i = 0; i < cols.size(); i++) {
		std::cout << std::setw(cols[i]->getWidth()) << cols[i]->getName() << separator;
	}
	std::cout << std::endl;
}

void Table::describeColumns() const
{
	const char* separator = " | ";
	std::cout << std::setw(3) << std::right << "Id" << separator;
	for (size_t i = 0; i < cols.size(); i++) {
		std::cout << std::setw(cols[i]->getWidth()) << cols[i]->getName() << ": " << getColumnTypeAsString(cols[i]->getType()) << separator;
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
	int i = 0;
	try {
		for (; i < other.cols.size(); i++) {
			cols.push_back(other.cols[i]->clone());
		}
	}
	catch (const std::bad_alloc&) {
		for (int j = 0; j < i; j++) {
			delete cols[i];
		}
	}

	strcpy_s(name, other.name);
	recordsId = other.recordsId;
	nextRecordId = other.nextRecordId;
	recordsPerPage = other.recordsPerPage;
}

void Table::free()
{
	for (int i = 0; i < cols.size(); i++) {
		delete cols[i];
	}

	cols.clear();
}

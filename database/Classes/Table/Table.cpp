#include "Table.h"

#include <iostream>
#include <iomanip>
#include <cassert>

#include "../Column/ColumnFactory.h"
#include "../Command/Commands/OtherCommands/GetRecordsPositions.h"

Table::Table(const char* name)
{
	if (name == nullptr || strlen(name) == 0) {
		throw std::invalid_argument(IS_EMPTY_MESSAGE);
	}

	if (std::strlen(name) >= MAX_NAME_LENGTH) {
		throw std::invalid_argument(IS_TOO_LONG_MESSAGE + std::to_string(MAX_NAME_LENGTH));
	}

	strcpy_s(this->name,  name);
}

Table::Table(const Table& other)
{
	copyFrom(other);
}

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
		throw std::exception(INVALID_ARGUMENTS_COUNT_MESSAGE);
	}

	for (size_t i = 0; i < cols.size(); i++) {
		cols[i]->addValue(values[i]);
	}

	recordsCount++;
}

void Table::addColumn(const Column& col)
{
	cols.push_back(col.clone());
	cols.back()->initializeValues(recordsCount);
}

void Table::writeToFile(std::ofstream& ofile) const
{
	ofile.write(name, MAX_NAME_LENGTH);
	ofile.write(reinterpret_cast<const char*>(&recordsCount), sizeof(recordsCount));
	size_t sizeColumns = cols.size();
	ofile.write(reinterpret_cast<const char*>(&sizeColumns), sizeof(sizeColumns));
	for (size_t i = 0; i < sizeColumns; i++) {
		cols[i]->writeToFile(ofile);
	}
}

void Table::readFromFile(std::ifstream& ifile)
{
	ifile.read(name, MAX_NAME_LENGTH);
	ifile.read(reinterpret_cast<char*>(&recordsCount), sizeof(recordsCount));
	size_t sizeColumns;
	ifile.read(reinterpret_cast<char*>(&sizeColumns), sizeof(sizeColumns));
	free();
	cols.resize(sizeColumns);
	for (size_t i = 0; i < sizeColumns; i++) {
		cols[i] = ColumnFactory::getFactory().readColumnFromStream(ifile);
		cols[i]->readFromFile(ifile);
	}
}

void Table::deleteRecords(const std::vector<size_t>& recordsPositions)
{
	for (size_t i = 0; i < cols.size(); i++) {
		cols[i]->deleteRecords(recordsPositions);
	}
	recordsCount -= recordsPositions.size();
}

void Table::updateValues(size_t colPos, const std::vector<size_t>& recordsPositions, const String& newVal)
{
	cols[colPos - 1]->updateValues(recordsPositions, newVal);
}

const char* Table::getName() const
{
	return name;
}

size_t Table::getRecordsCount() const
{
	return recordsCount;
}

const Column* Table::getColumn(size_t pos) const
{
	if (pos - 1 >= cols.size()) { // cols start from 1 for the user
		throw std::exception(INVALID_INDEX_MESSAGE);
	}

	return cols[pos - 1];
}

size_t Table::getColumnsSize() const
{
	return cols.size();
}

std::vector<String> Table::getRecordValues(size_t recPos, const std::vector<int>& colsPos) const
{
	std::vector<String> res;
	for (size_t i = 0; i < colsPos.size(); i++) {
		res.push_back(cols.at(colsPos[i] - static_cast<size_t>(1))->getValue(recPos));
	}

	return res;
}

void Table::copyFrom(const Table& other)
{
	ColumnArray newCols;
	size_t newSize = other.cols.size(), i = 0;
	try {
		newCols.reserve(newSize);
		for (; i < newSize; i++) {
			newCols.push_back(other.cols[i]->clone());
		}
	}
	catch (const std::exception&) {
		for (size_t j = 0; j < i; j++) {
			delete cols[j];
		}
		throw;
	}

	cols = std::move(newCols);
	strcpy_s(name, other.name);
	recordsCount = other.recordsCount;
}

void Table::free()
{
	for (size_t i = 0; i < cols.size(); i++) {
		delete cols[i];
	}

	cols.clear();
}

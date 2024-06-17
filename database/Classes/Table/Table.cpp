#include "Table.h"

#include <iostream>
#include <iomanip>
#include <cassert>

#include "../Column/ColumnFactory.h"
#include "../Command/Commands/OtherCommands/GetRecordsPositions.h"

Table::Table(const String& name)
{
	// add validation of name
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
		throw std::exception("invalid arguments count");
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
	for (int i = 0; i < sizeColumns; i++) {
		cols[i] = ColumnFactory::getFactory().readColumnFromStream(ifile);
		cols[i]->readFromFile(ifile);
	}
}

void Table::deleteRecords(const std::vector<size_t>& recordsPositions)
{
	deleteRecordsFromRecordsId(recordsPositions);

	for (size_t i = 0; i < cols.size(); i++) {
		cols[i]->deleteRecords(recordsPositions);
	}
}

void Table::updateValues(int colPos, const std::vector<size_t>& recordsPositions, const String& newVal)
{
	cols[colPos]->updateValues(recordsPositions, newVal);
}

void Table::deleteRecordsFromRecordsId(const std::vector<size_t>& recordsPositions)
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

const char* Table::getName() const
{
	return name;
}

const PrimaryKeyColumn& Table::getRecordsId() const
{
	return recordsId;
}

const Column* Table::getColumn(size_t pos) const
{
	if (pos - 1 >= cols.size()) { // cols start from 1
		throw std::exception("invalid index");
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
}

void Table::free()
{
	for (int i = 0; i < cols.size(); i++) {
		delete cols[i];
	}

	cols.clear();
}

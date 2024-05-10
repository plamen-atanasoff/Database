#include "Table.h"

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

void Table::deleteRecord(int recordPos)
{
	recordsId.erase(recordsId.begin() + recordPos);
	for (size_t i = 0; i < cols.size(); i++) {
		cols[i]->deleteValue(recordPos);
	}
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

#include "Table.h"

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
}

void Table::saveToFile(std::ofstream& ofile) const
{
	ofile.write(name, MAX_NAME_LENGTH);
	ofile.write(reinterpret_cast<const char*>(&nextRecordId), sizeof(nextRecordId));
	size_t sizeRecords = recordsId.size();
	ofile.write(reinterpret_cast<const char*>(&sizeRecords), sizeof(sizeRecords));
	ofile.write(reinterpret_cast<const char*>(recordsId.data()), sizeof(unsigned) * sizeRecords);
	size_t sizeColumns = cols.size();
	ofile.write(reinterpret_cast<const char*>(&sizeColumns), sizeof(sizeColumns));
	for (int i = 0; i < sizeColumns; i++) {
		cols[i]->saveToFile(ofile);
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

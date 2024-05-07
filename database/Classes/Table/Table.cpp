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

void Table::addRecord(const std::initializer_list<std::string>& values)
{
	if (values.size() != cols.size()) {
		return; 
	}

	size_t i = 0;
	for (const std::string& val : values) {
		cols[i]->addValue(val);

		i++;
	}

	recordsId.push_back(nextRecordId++);
}

void Table::addColumn(const Column& col)
{
	cols.push_back(col.clone());
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

#pragma once
#include <vector>
#include <string>
#include "../Columns/Column.h"

using PrimaryKeyColumn = std::vector<unsigned>;
using ColumnArray = std::vector<Column*>;

// table name,
// cols size
// col: datatype, name, values: size, elements
// records size, values: size, elements

// currently primary key can only be one and it must be an unsigned int

class Table
{
public:
	Table() : Table("") {}
	Table(const std::string& name);
	Table(const Table& other);
	Table& operator=(const Table& other);
	~Table();

	void addRecord(const std::vector<std::string>& values);
	void addColumn(const Column& col);

	void printTable() const;
private:
	static constexpr int MAX_NAME_LENGTH = 33;

	char name[MAX_NAME_LENGTH]{};
	PrimaryKeyColumn recordsId;
	ColumnArray cols;
	unsigned nextRecordId = 0;

	void copyFrom(const Table& other);
	void free();
};
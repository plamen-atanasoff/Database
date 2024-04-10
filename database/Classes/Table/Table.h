#pragma once
#include <vector>

class Column;

using PrimaryKeyColumn = std::vector<unsigned>;
using ColumnArray = std::vector<Column>;

// table name,
// cols size
// col: datatype, name, values: size, elements
// records size, values: size, elements

// currently primary key can be only one and it must be an unsigned int

class Table
{
public:

private:
	static constexpr int MAX_NAME_LENGTH = 65;

	char name[MAX_NAME_LENGTH]{};
	PrimaryKeyColumn recordsId;
	ColumnArray cols;
	unsigned nextRecordId = 0;
};
#pragma once
#include <string>
#include <fstream>
#include <vector>
#include "../Factories/ColumnType.h"

class Column {
public:
	Column(const std::string& name, ColumnType type) : type(type) {
		strcpy_s(this->name, name.c_str());
	}
	virtual ~Column() = default;

	virtual void addValue(const std::string& val) = 0;
	virtual void removeValue(int pos) = 0;
	virtual void changeValue(int pos, const std::string& newVal) = 0;

	virtual void printValues() const = 0;
	virtual void printValueAt(size_t pos) const = 0;

	virtual void writeToFile(std::ofstream& ofile) const = 0;
	virtual void readFromFile(std::ifstream& ifile) = 0;

	virtual std::vector<int> getRecordsPositions(const std::string& val) const = 0;
	virtual void deleteValue(int valPos) = 0;

	virtual void initializeValues(size_t recordsCount) = 0;

	virtual Column* clone() const = 0;

	ColumnType getType() const { return type; }
	const char* getName() const { return name; }
protected:
	static constexpr int MAX_NAME_LENGTH = 33;
	ColumnType type;
	char name[MAX_NAME_LENGTH]{};
};
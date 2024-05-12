#pragma once

#include <string>
#include <fstream>
#include <vector>

#include "../Factories/ColumnType.h"

using String = std::string;

class Column {
public:
	Column(const String& name, ColumnType type, size_t width) : type(type) {
		strcpy_s(this->name, name.c_str());
		if (width <= 16) {
			this->width = width;
		}
	}
	virtual ~Column() = default;

	virtual void addValue(const String& val) = 0;
	virtual void deleteValue(size_t pos) = 0;
	virtual void changeValue(size_t pos, const String& newVal) = 0;

	//virtual void printValues() const = 0;
	virtual void printValueAt(size_t pos) const = 0;

	virtual void writeToFile(std::ofstream& ofile) const = 0;
	virtual void readFromFile(std::ifstream& ifile) = 0;

	virtual std::vector<int> getRecordsPositions(const String& val) const = 0;
	virtual void deleteRecords(const std::vector<int>& recordsPositions) = 0;

	virtual void initializeValues(size_t recordsCount) = 0;

	virtual Column* clone() const = 0;

	ColumnType getType() const { return type; }
	const char* getName() const { return name; }
	size_t getWidth() const { return width; }
protected:
	static constexpr int MAX_NAME_LENGTH = 33;
	ColumnType type;
	char name[MAX_NAME_LENGTH]{};
	size_t width = 8;
};
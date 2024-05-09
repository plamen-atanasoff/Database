#pragma once
#include <string>
#include <fstream>
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

	virtual void saveToFile(std::ofstream& ofile) const = 0;

	virtual Column* clone() const = 0;

	ColumnType getType() const { return type; }
	const char* getName() const { return name; }
protected:
	static constexpr int MAX_NAME_LENGTH = 33;
private:
	ColumnType type;
	char name[MAX_NAME_LENGTH]{};
};
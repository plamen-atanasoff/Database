#pragma once
#include <string>
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

	virtual Column* clone() const = 0;
private:
	static constexpr int MAX_NAME_LENGTH = 33;

	char name[MAX_NAME_LENGTH]{};
	ColumnType type;
};
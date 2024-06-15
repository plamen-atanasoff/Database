#include "IntColumn.h"

#include <string>
#include <iostream>
#include <cassert>

IntColumn::IntColumn(const String& name, ColumnType type) : TypeColumn<int>(name, type) {}

Column* IntColumn::clone() const
{
	return new IntColumn(*this);
}

String IntColumn::getValue(size_t pos) const
{
	if (pos >= values.size()) {
		throw std::exception("invalid argument");
	}

	return setValues.contains(pos) ? std::to_string(values[pos]) : "NULL";
}

int IntColumn::convert(const String& value) const
{
	return std::stoi(value);
}

IntColumnCreator::IntColumnCreator(): ColumnCreator(ColumnType::INT) {}

Column* IntColumnCreator::create(const std::vector<String>& args) const
{
	return new IntColumn(args[0], getColumnTypeAsEnum(args[1]));
}

Column* IntColumnCreator::create(const String& name, ColumnType type) const
{
	return new IntColumn(name, type);
}

static IntColumnCreator __;
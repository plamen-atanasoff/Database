#include "DoubleColumn.h"

DoubleColumn::DoubleColumn(const String& name, ColumnType type) : TypeColumn<double>(name, type) {}

Column* DoubleColumn::clone() const
{
	return new DoubleColumn(*this);
}

//same as in IntColumn, should this be in TypeColumn ?
String DoubleColumn::getValue(size_t pos) const
{
	if (pos >= values.size()) {
		throw std::exception("invalid argument");
	}

	return setValues.contains(pos) ? std::to_string(values[pos]) : "NULL";
}

double DoubleColumn::convert(const String& value) const
{
	return std::stod(value);
}

DoubleColumnCreator::DoubleColumnCreator() : ColumnCreator(ColumnType::DOUBLE) {}

Column* DoubleColumnCreator::create(const std::vector<String>& args) const
{
	if (args.size() != 2) {
		throw std::exception("invalid arguments count");
	}

	return new DoubleColumn(args[0], getColumnTypeAsEnum(args[1]));
}

Column* DoubleColumnCreator::create(const String& name, ColumnType type) const
{
	return new DoubleColumn(name, type);
}

static DoubleColumnCreator __;

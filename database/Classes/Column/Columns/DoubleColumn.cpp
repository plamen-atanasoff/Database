#include "DoubleColumn.h"

DoubleColumn::DoubleColumn(const String& name) : TypeColumn<double>(name, ColumnType::DOUBLE) {}

Column* DoubleColumn::clone() const
{
	return new DoubleColumn(*this);
}

double DoubleColumn::convert(const String& value) const
{
	return std::stod(value);
}

DoubleColumnCreator::DoubleColumnCreator() : ColumnCreator(ColumnType::DOUBLE) {}

Column* DoubleColumnCreator::create(const std::vector<String>& args) const
{
	if (args.size() != 1) {
		throw std::exception("invalid arguments count");
	}

	return new DoubleColumn(args[0]);
}

Column* DoubleColumnCreator::create(const String& name) const
{
	return new DoubleColumn(name);
}

static DoubleColumnCreator __;

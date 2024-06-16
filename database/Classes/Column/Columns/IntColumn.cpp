#include "IntColumn.h"

IntColumn::IntColumn(const String& name) : TypeColumn<int>(name, ColumnType::INT) {}

Column* IntColumn::clone() const
{
	return new IntColumn(*this);
}

int IntColumn::convert(const String& value) const
{
	return std::stoi(value);
}

IntColumnCreator::IntColumnCreator(): ColumnCreator(ColumnType::INT) {}

Column* IntColumnCreator::create(const std::vector<String>& args) const
{
	if (args.size() != 1) {
		throw std::exception("invalid arguments count");
	}

	return new IntColumn(args[0]);
}

Column* IntColumnCreator::create(const String& name) const
{
	return new IntColumn(name);
}

static IntColumnCreator __;

#include "StringColumn.h"

StringColumn::StringColumn(const String& name) : TypeColumn<String>(name, ColumnType::STRING) {}

Column* StringColumn::clone() const
{
	return new StringColumn(*this);
}

String StringColumn::convert(const String& value) const
{
	return value;
}

StringColumnCreator::StringColumnCreator() : ColumnCreator(ColumnType::STRING) {}

Column* StringColumnCreator::create(const std::vector<String>& args) const
{
	if (args.size() != 1) {
		throw std::exception("invalid arguments count");
	}

	return new StringColumn(args[0]);
}

Column* StringColumnCreator::create(const String& name) const
{
	return new StringColumn(name);
}

static StringColumnCreator __;

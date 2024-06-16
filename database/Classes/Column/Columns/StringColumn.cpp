#include "StringColumn.h"

StringColumn::StringColumn(const String& name, ColumnType type) : TypeColumn<String>(name, type) {}

Column* StringColumn::clone() const
{
	return new StringColumn(*this);
}

String StringColumn::getValue(size_t pos) const
{
	if (pos >= values.size()) {
		throw std::exception("invalid argument");
	}

	return setValues.contains(pos) ? values[pos] : "NULL";
}

String StringColumn::convert(const String& value) const
{
	return value;
}

StringColumnCreator::StringColumnCreator() : ColumnCreator(ColumnType::STRING) {}

Column* StringColumnCreator::create(const std::vector<String>& args) const
{
	if (args.size() != 2) {
		throw std::exception("invalid arguments count");
	}

	return new StringColumn(args[0], getColumnTypeAsEnum(args[1]));
}

Column* StringColumnCreator::create(const String& name, ColumnType type) const
{
	return new StringColumn(name, type);
}

static StringColumnCreator __;

#include "DescribeColumns.h"

DescribeColumns::DescribeColumns(Table* table) : table(table) {}

void DescribeColumns::execute() const
{
	table->describeColumns();
}

DescribeColumnsCreator::DescribeColumnsCreator() : CommandCreator(CommandType::DESCRIBE_COLUMNS) {}

Command* DescribeColumnsCreator::create(const std::vector<String>& args, Database& database) const
{
	return new DescribeColumns(&database.getTable());
}

static DescribeColumnsCreator __;

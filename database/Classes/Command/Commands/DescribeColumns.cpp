#include "DescribeColumns.h"

#include <iomanip>

DescribeColumns::DescribeColumns(Table* table) : table(table) {}

void DescribeColumns::execute() const
{
	size_t n = table->getColumnsSize();
	for (size_t i = 1; i <= n; i++) {
		const Column* col = table->getColumn(i);
		std::cout << std::setw(col->getWidth()) << col->getName() << ": " << getColumnTypeAsString(col->getType()) << separator;
	}
	std::cout << std::endl;
}

Command* DescribeColumns::clone() const
{
	return new DescribeColumns(*this);
}

DescribeColumnsCreator::DescribeColumnsCreator() : CommandCreator(CommandType::DESCRIBE_COLUMNS) {}

Command* DescribeColumnsCreator::create(const std::vector<String>& args, Database& database) const
{
	return new DescribeColumns(&database.getTable());
}

static DescribeColumnsCreator __;

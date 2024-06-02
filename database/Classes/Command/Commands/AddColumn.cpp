#include "AddColumn.h"

#include "../../Column/ColumnFactory.h"

AddColumn::AddColumn(const String& name, ColumnType type, Table* table) : name(name), type(type), table(table) {}

void AddColumn::execute() const
{
	Column* column = ColumnFactory::getFactory().createColumn(name, type);
	table->addColumn(*column);

	delete[] column;
}

AddColumnCreator::AddColumnCreator() : CommandCreator(CommandType::ADD_COLUMN) {}

Command* AddColumnCreator::create(const std::vector<String>& args, Database& database) const
{
	return new AddColumn(args[0], getColumnTypeAsEnum(args[1]), &database.getTable());
}

static AddColumnCreator __;
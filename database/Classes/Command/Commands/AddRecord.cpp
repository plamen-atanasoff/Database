#include "AddRecord.h"

AddRecord::AddRecord(const std::vector<String>& args, Table* table) : args(args), table(table) {}

void AddRecord::execute() const
{
	table->addRecord(args);
}

Command* AddRecord::clone() const
{
	return new AddRecord(*this);
}

AddRecordCreator::AddRecordCreator() : CommandCreator(CommandType::ADD_RECORD) {}

Command* AddRecordCreator::create(const std::vector<String>& args, Database& database) const
{
	return new AddRecord(args, &database.getTable());
}

static AddRecordCreator __;

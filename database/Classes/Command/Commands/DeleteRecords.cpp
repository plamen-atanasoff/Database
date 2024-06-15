#include "DeleteRecords.h"

DeleteRecords::DeleteRecords(int colPos, const String& value, Table* table) 
	: colPos(colPos), value(value), table(table) {}

void DeleteRecords::execute() const
{
	std::vector<int> recordsPositions = table->getRecordsPositions(colPos, value);
	table->deleteRecords(recordsPositions);
}

DeleteRecordsCreator::DeleteRecordsCreator() : CommandCreator(CommandType::DELETE_RECORDS) {}

Command* DeleteRecordsCreator::create(const std::vector<String>& args, Database& database) const
{
	if (args.size() != 2) {
		throw std::exception("invalid arguments count");
	}

	return new DeleteRecords(std::stoi(args[0]), args[1], &database.getTable());
}

static DeleteRecordsCreator __;

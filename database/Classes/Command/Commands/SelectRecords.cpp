#include "SelectRecords.h"

SelectRecords::SelectRecords(int colPos, const String& value, Table* table) 
	: colPos(colPos), value(value), table(table) {}

void SelectRecords::execute() const
{
	std::vector<int> recordsPositions = table->getRecordsPositions(colPos, value);
	table->printTableSelect(recordsPositions);
}

SelectRecordsCreator::SelectRecordsCreator() : CommandCreator(CommandType::SELECT_RECORDS) {}

Command* SelectRecordsCreator::create(const std::vector<String>& args, Database& database) const
{
	if (args.size() != 2) {
		throw std::exception("invalid arguments count");
	}

	return new SelectRecords(std::stoi(args[0]), args[1], &database.getTable());
}

static SelectRecordsCreator __;

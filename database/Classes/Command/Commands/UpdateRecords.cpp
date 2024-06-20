#include "UpdateRecords.h"

#include "OtherCommands/GetRecordsPositions.h"

UpdateRecords::UpdateRecords(int colPosFrom, const String& value, int colPosTo, const String& newValue, Table* table)
	: colPosFrom(colPosFrom), value(value), colPosTo(colPosTo), newValue(newValue), table(table) {}

void UpdateRecords::execute() const
{
	std::vector<size_t> recordsPositions = GetRecordsPositions::execute(table->getColumn(colPosFrom), value);
	table->updateValues(colPosTo, recordsPositions, newValue);
}

Command* UpdateRecords::clone() const
{
	return new UpdateRecords(*this);
}

UpdateRecordsCreator::UpdateRecordsCreator() : CommandCreator(CommandType::UPDATE_RECORDS) {}

Command* UpdateRecordsCreator::create(const std::vector<String>& args, Database& database) const
{
	if (args.size() != 4) {
		throw std::exception("invalid arguments count");
	}

	return new UpdateRecords(std::stoi(args[0]), args[1], std::stoi(args[2]), args[3], &database.getTable());
}

static UpdateRecordsCreator __;

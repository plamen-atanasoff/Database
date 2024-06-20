#include "SelectOnto.h"

#include "OtherCommands/GetRecordsPositions.h"
#include "OtherCommands/ParseStringToIntArray.h"

SelectOnto::SelectOnto(const String& resultTableName, const std::vector<int>& columnsInd, 
	size_t searchColInd, const String& value, Table* table) 
	: resultTableName(resultTableName), columnsInd(columnsInd), searchColInd(searchColInd), value(value), table(table) {}

void SelectOnto::execute() const
{
	Table resTable(resultTableName.c_str());

	for (size_t i = 0; i < columnsInd.size(); i++) {
		Column* curCol = table->getColumn(columnsInd[i])->clone();
		curCol->deleteRecords();
		try {
			resTable.addColumn(*curCol);
		}
		catch (const std::exception&) {
			delete curCol;
			throw;
		}
	}

	std::vector<size_t> recordsPositions = GetRecordsPositions::execute(table->getColumn(searchColInd), value);

	for (size_t i = 0; i < recordsPositions.size(); i++) {
		std::vector<String> curValues = table->getRecordValues(recordsPositions[i], columnsInd);
		resTable.addRecord(curValues);
	}

	*table = resTable;
}

Command* SelectOnto::clone() const
{
	return new SelectOnto(*this);
}

SelectOntoCreator::SelectOntoCreator() : CommandCreator(CommandType::SELECT_ONTO) {}

Command* SelectOntoCreator::create(const std::vector<String>& args, Database& database) const
{
	if (args.size() != 4) {
		throw std::exception("invalid arguments count");
	}

	return new SelectOnto(args[0], ParseStringToIntArray::execute(args[1], ','), static_cast<size_t>(std::stoull(args[2])), args[3], &database.getTable());
}

static SelectOntoCreator __;

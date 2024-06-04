#include "SelectOnto.h"

SelectOnto::SelectOnto(const String& resultTableName, const std::vector<int>& columnsInd, 
	size_t searchColInd, const String& value, Table* table) 
	: resultTableName(resultTableName), columnsInd(columnsInd), searchColInd(searchColInd), value(value), table(table) {}

void SelectOnto::execute() const
{
	Table resTable(resultTableName);

	for (size_t i = 0; i < columnsInd.size(); i++) {
		//find a better way to add columns
		Column* curCol = table->getColumn(columnsInd[i])->clone();
		curCol->deleteRecords();
		resTable.addColumn(*curCol); // add try catch if you leave it like this
		delete curCol;
	}

	std::vector<int> recordsPositions = table->getRecordsPositions(searchColInd, value);

	for (size_t i = 0; i < recordsPositions.size(); i++) {
		std::vector<String> curValues = table->getRecordValues(recordsPositions[i], columnsInd);
		resTable.addRecord(curValues);
	}

	*table = resTable;
}

SelectOntoCreator::SelectOntoCreator() : CommandCreator(CommandType::SELECT_ONTO) {}

Command* SelectOntoCreator::create(const std::vector<String>& args, Database& database) const
{
	if (args.size() != 4) {
		throw std::exception("invalid arguments count");
	}

	return new SelectOnto(args[0], parseArray(args[1]), static_cast<size_t>(std::stoull(args[2])), args[3], &database.getTable());
}

static SelectOntoCreator __;

std::vector<String> splitString(const String& string, char delimiter);

std::vector<int> parseArray(const String& string) {
	std::vector<String> tokens = splitString(string, ',');
	std::vector<int> res(tokens.size());

	for (size_t i = 0; i < tokens.size(); i++) {
		res[i] = std::stoi(tokens[i]);
	}

	return res;
}
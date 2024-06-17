#include "SelectRecords.h"

#include "OtherCommands/GetRecordsPositions.h"

SelectRecords::SelectRecords(int colPos, const String& value, Table* table, unsigned recordsPerPage = 2)
	: colPos(colPos), value(value), table(table), recordsPerPage(recordsPerPage) {}

void SelectRecords::execute() const
{
	std::vector<size_t> recordsPositions = GetRecordsPositions::execute(table->getColumn(colPos), value);

	char command[8]{};
	size_t i = 0, n = recordsPositions.size(), m = table->getColumnsSize();
	unsigned r = recordsPerPage;
	do {
		printColumnInfo();

		for (; i < n; i++) {
			if (i == r) {
				break;
			}
			for (size_t j = 0; j < m; j++) {
				table->getColumn(j + 1)->printValueAt(recordsPositions[i]);
				std::cout << separator;
			}
			std::cout << std::endl;
		}

		std::cout << "Enter command(prev, next, exit): ";
		std::cin >> command;
		if (strcmp(command, "prev") == 0) {
			if (i == recordsPerPage) {
				i = 0;
				system("cls");
				continue;
			}
			if (i % recordsPerPage == 0) {
				i = i - (size_t)2 * recordsPerPage;
			}
			else {
				i = (i + (recordsPerPage - (i % recordsPerPage))) - (size_t)2 * recordsPerPage;
			}
			r = (unsigned)i + recordsPerPage;
		}
		else if (strcmp(command, "next") == 0) {
			if (i >= n) {
				if (i % recordsPerPage == 0) {
					i -= recordsPerPage;
				}
				else {
					i = (i + (recordsPerPage - (i % recordsPerPage))) - recordsPerPage;
				}
				system("cls");
				continue;
			}
			r += recordsPerPage;
		}

		system("cls");
	} while (strcmp(command, "exit") != 0);
	std::cin.ignore();
}

void SelectRecords::printColumnInfo() const
{
	size_t n = table->getColumnsSize();
	for (size_t i = 0; i < n; i++) {
		std::cout << std::setw(table->getColumn(i + 1)->getWidth()) << table->getColumn(i + 1)->getName() << separator;
	}
	std::cout << std::endl;
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

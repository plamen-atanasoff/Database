#include "SelectRecords.h"

#include "OtherCommands/GetRecordsPositions.h"

SelectRecords::SelectRecords(int colPos, const String& value, Table* table, unsigned recordsPerPage = 10)
	: colPos(colPos), value(value), table(table), recordsPerPage(recordsPerPage) {}

void SelectRecords::execute() const
{
	std::vector<size_t> recordsPositions = GetRecordsPositions::execute(table->getColumn(colPos), value);

	size_t i = 0, n = recordsPositions.size(), m = table->getColumnsSize();
	if (n == 0) {
		std::cout << "Table is empty" << std::endl;
		return;
	}

	char command[8]{};
	unsigned r = recordsPerPage;
	bool atBorder = false;
	do {
		if (!atBorder) {
			printColumnInfo();

			for (; i < n; i++) {
				if (i == r) {
					break;
				}
				for (size_t j = 1; j <= m; j++) {
					table->getColumn(j)->printValueAt(recordsPositions[i]);
					std::cout << separator;
				}
				std::cout << std::endl;
			}
			std::cout << "Page " << r / recordsPerPage << std::endl;
		}
		
		std::cout << "Enter command(prev, next, exit): ";
		std::cin >> command;
		if (strcmp(command, "prev") == 0) {
			if (i == recordsPerPage || (i == n && r == recordsPerPage)) {
				atBorder = true;
				continue;
			}
			if (i % recordsPerPage == 0) {
				i = i - (size_t)2 * recordsPerPage;
			}
			else {
				i = (i + (recordsPerPage - (i % recordsPerPage))) - (size_t)2 * recordsPerPage;
			}
			r = (unsigned)i + recordsPerPage;
			atBorder = false;
		}
		else if (strcmp(command, "next") == 0) {
			if (i == n) {
				atBorder = true;
				continue;
			}
			r += recordsPerPage;
			atBorder = false;
		}

		system("cls");
	} while (strcmp(command, "exit") != 0);
	std::cin.ignore();
}

Command* SelectRecords::clone() const
{
	return new SelectRecords(*this);
}

void SelectRecords::printColumnInfo() const
{
	size_t n = table->getColumnsSize();
	for (size_t i = 1; i <= n; i++) {
		std::cout << std::setw(table->getColumn(i)->getWidth()) << table->getColumn(i)->getName() << separator;
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

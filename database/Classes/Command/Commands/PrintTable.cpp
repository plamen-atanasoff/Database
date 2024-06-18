#include "PrintTable.h"

PrintTable::PrintTable(Table* table, unsigned recordsPerPage = 2) 
	: table(table), recordsPerPage(recordsPerPage) {}

void PrintTable::execute() const
{
	size_t i = 0, n = table->getRecordsId().size(), m = table->getColumnsSize();
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
				for (size_t j = 0; j < m; j++) {
					table->getColumn(j + 1)->printValueAt(i);
					std::cout << separator;
				}
				std::cout << std::endl;
			}
		}

		std::cout << "Enter command(prev, next, exit): ";
		std::cin >> command;
		if (strcmp(command, "prev") == 0) {
			if (i == recordsPerPage) {
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

void PrintTable::printColumnInfo() const
{
	size_t n = table->getColumnsSize();
	for (size_t i = 0; i < n; i++) {
		std::cout << std::setw(table->getColumn(i + 1)->getWidth()) << table->getColumn(i + 1)->getName() << separator;
	}
	std::cout << std::endl;
}

PrintTableCreator::PrintTableCreator() : CommandCreator(CommandType::PRINT_TABLE) {}

Command* PrintTableCreator::create(const std::vector<String>& args, Database& database) const
{
	return new PrintTable(&database.getTable());
}

static PrintTableCreator __;

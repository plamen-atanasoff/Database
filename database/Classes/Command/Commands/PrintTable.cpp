#include "PrintTable.h"

PrintTable::PrintTable(Table* table, unsigned recordsPerPage = 10) 
	: table(table), recordsPerPage(recordsPerPage) {}

void PrintTable::execute() const
{
	size_t i = 0, n = table->getRecordsCount(), m = table->getColumnsSize();
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
					table->getColumn(j)->printValueAt(i);
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

Command* PrintTable::clone() const
{
	return new PrintTable(*this);
}

void PrintTable::printColumnInfo() const
{
	size_t n = table->getColumnsSize();
	for (size_t i = 1; i <= n; i++) {
		std::cout << std::setw(table->getColumn(i)->getWidth()) << table->getColumn(i)->getName() << separator;
	}
	std::cout << std::endl;
}

PrintTableCreator::PrintTableCreator() : CommandCreator(CommandType::PRINT_TABLE) {}

Command* PrintTableCreator::create(const std::vector<String>& args, Database& database) const
{
	return new PrintTable(&database.getTable());
}

static PrintTableCreator __;

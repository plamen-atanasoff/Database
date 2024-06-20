#include "ShowTables.h"

ShowTables::ShowTables(const std::vector<StringPair>& tables) : tables(tables) {}

void ShowTables::execute() const
{
	size_t n = tables.size();

	if (n == 0) {
		std::cout << "There are no tables in the catalog" << std::endl;
		return;
	}

	for (size_t i = 0; i < n; i++) {
		std::cout << tables[i].tableName << '\n';
	}
	std::cout << std::endl;
}

Command* ShowTables::clone() const 
{
	return new ShowTables(*this);
}

ShowTablesCreator::ShowTablesCreator() : CommandCreator(CommandType::SHOW_TABLES) {}

Command* ShowTablesCreator::create(const std::vector<String>& args, Database& database) const
{
	if (args.size() != 0) {
		throw std::exception("invalid arguments count");
	}

	return new ShowTables(database.getTablesInfo());
}

static ShowTablesCreator __;

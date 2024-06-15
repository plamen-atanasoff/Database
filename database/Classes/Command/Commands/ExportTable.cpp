#include "ExportTable.h"

ExportTable::ExportTable(const String& filePath, Table* table) : filePath(filePath), table(table) {}

void ExportTable::execute() const
{
	std::ofstream ofile(filePath, std::ios::out | std::ios::trunc);
	if (!ofile.is_open()) {
		return;
	}

	table->printTableToFile(ofile);

	ofile.close();
}

ExportTableCreator::ExportTableCreator() : CommandCreator(CommandType::EXPORT_TABLE) {}

Command* ExportTableCreator::create(const std::vector<String>& args, Database& database) const
{
	if (args.size() != 1) {
		throw std::exception("invalid arguments count");
	}

	return new ExportTable(args[0], &database.getTable());
}

static ExportTableCreator __;

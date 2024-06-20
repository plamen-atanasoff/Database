#include "ExportTable.h"

ExportTable::ExportTable(const String& filePath, Table* table) : filePath(filePath), table(table) {}

void ExportTable::execute() const
{
	std::ofstream ofile(filePath, std::ios::out | std::ios::trunc);
	if (!ofile.is_open()) {
		return;
	}

	size_t n = table->getColumnsSize(), m = table->getRecordsCount();
	for (size_t i = 0; i < n; i++) {
		ofile << std::setw(table->getColumn(i + 1)->getWidth()) << table->getColumn(i + 1)->getName() << separator;
	}
	ofile << std::endl;

	for (size_t i = 0; i < m; i++) {
		for (size_t j = 0; j < n; j++) {
			table->getColumn(j + 1)->printValueAtToStream(i, ofile);
			ofile << separator;
		}
		ofile << std::endl;
	}

	ofile.close();
}

Command* ExportTable::clone() const
{
	return new ExportTable(*this);
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

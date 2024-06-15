#include "SaveTableAs.h"

SaveTableAs::SaveTableAs(const String& fileName, const Table* table) : fileName(fileName), table(table) {}

void SaveTableAs::execute() const
{
	std::ofstream ofile(fileName, std::ios::binary);
	if (!ofile.is_open()) {
		throw std::exception("file could not be opened");
	}
	table->writeToFile(ofile);

	ofile.close();
}

SaveTableAsCreator::SaveTableAsCreator() : CommandCreator(CommandType::SAVE_TABLE_TO_FILE) {}

Command* SaveTableAsCreator::create(const std::vector<String>& args, Database& database) const
{
	if (args.size() != 1) {
		throw std::exception("invalid arguments count");
	}

	return new SaveTableAs(args[0], &database.getTable());
}

static SaveTableAsCreator __;
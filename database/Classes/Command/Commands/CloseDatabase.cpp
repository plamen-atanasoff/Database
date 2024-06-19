#include "CloseDatabase.h"

void CloseDatabase::execute() const
{
	Controller::getInstance().closeDatabase();
}

CloseDatabaseCreator::CloseDatabaseCreator() : CommandCreator(CommandType::CLOSE_DATABASE) {}

Command* CloseDatabaseCreator::create(const std::vector<String>& args, Database& database) const
{
	if (args.size() != 0) {
		throw std::exception("invalid arguments count");
	}

	return new CloseDatabase();
}

static CloseDatabaseCreator __;

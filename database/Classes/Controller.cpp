#include "Controller.h"

#include "Command/CommandFactory.h"
#include "Command/Commands/OtherCommands/ReadTablesInfo.h"

Controller::~Controller()
{
	free();
}

Controller& Controller::getInstance()
{
	static Controller controller;
	return controller;
}

void Controller::loadDatabase(const String& databaseFilePath)
{
	closeDatabase();

	database = new Database(databaseFilePath);
	ReadTablesInfo::execute(database->getTablesInfoFileName(), &database->getTablesInfo());
}

void Controller::closeDatabase()
{
	if (database) {
		free();
	}
}

void Controller::executeCommand(const String& input)
{
	if (!database) {
		throw std::exception("Database is not loaded");
	}
	
	Command* command = nullptr;
	try {
		command = CommandFactory::getFactory().createCommand(input, *database);

		if (command) {
			command->execute();
		}
	}
	catch (const std::exception&) {
		delete command;
		throw;
	}
	delete command;
}

void Controller::free()
{
	delete database;
	database = nullptr;
}

#include "Controller.h"

#include "Command/CommandFactory.h"
#include "Command/Commands/ReadTablesInfo.h"

Controller::Controller()
{
	Command* command = nullptr;
	try {
		command = new ReadTablesInfo(database.getTablesInfoFileName(), &database.getTablesInfo());
		command->execute();
	}
	catch (const std::exception&) {
		delete command;
		throw;
	}
	delete command;
}

void Controller::executeCommand(const String& input)
{
	Command* command = nullptr;
	try {
		command = CommandFactory::getFactory().createCommand(input, database);

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

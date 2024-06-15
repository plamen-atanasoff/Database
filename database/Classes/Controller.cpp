#include "Controller.h"

#include "Command/CommandFactory.h"
#include "Command/Commands/OtherCommands/ReadTablesInfo.h"

Controller::Controller()
{
	ReadTablesInfo::execute(database.getTablesInfoFileName(), &database.getTablesInfo());
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

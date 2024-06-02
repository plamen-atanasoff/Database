#include "Controller.h"

#include "Command/CommandFactory.h"
#include "Command/Commands/ReadTablesInfo.h"

Controller::Controller()
{
	Command* command = new ReadTablesInfo(TABLES_FILE, &database.getTablesInfo());
	command->execute();
	delete command;
}

void Controller::executeCommand(const String& input)
{
	Command* command = CommandFactory::getFactory().createCommand(input, database);
	if (command) {
		command->execute();
		delete command;
	}
	// create else case
}

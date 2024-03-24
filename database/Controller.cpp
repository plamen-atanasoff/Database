#include "Controller.h"

#include "Command.h"

void Controller::createTable(const StringVector& args)
{}

void Controller::execute(const Command& command)
{
	switch (command.getCommandName()) 
	{
	case CommandName::CREATE:
		createTable(command.getArgs());
		break;
	}
}

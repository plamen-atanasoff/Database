#include "Command.h"

#include "CommandFactory.h"

CommandCreator::CommandCreator(CommandType type) : type(type)
{
	CommandFactory::getFactory().addCreator(*this);
}

CommandType CommandCreator::getCommandType() const
{
	return type;
}

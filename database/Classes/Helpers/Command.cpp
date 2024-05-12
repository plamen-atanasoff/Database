#include "Command.h"

#include <string>
#include <vector>
#include <sstream>
#include <exception>

#include "../Factories/CommandFactory.h"
#include "HelperFunctions.h"

using StringVector = std::vector<std::string>;
using String = std::string;

Command::Command(CommandType type, const StringVector& args) 
	: type(type), args(args) 
{}

// command is in the form: commandType arg1 arg2 ... argN
Command Command::create(const String& line)
{
	size_t delimiterPos = line.find_first_of(' ');
	String type = line.substr(0, delimiterPos);
	CommandType commandType = getCommandTypeAsEnum(type);
	StringVector args;
	if (delimiterPos != String::npos) {
		String argsString = line.substr(delimiterPos + 1);
		args = splitString(argsString, ' ');
	}

	return Command(commandType, args);
}

CommandType Command::getCommandName() const
{
	return type;
}

const StringVector& Command::getArgs() const
{
	return args;
}

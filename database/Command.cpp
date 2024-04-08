#include "Command.h"

#include <string>
#include <vector>
#include <sstream>
#include <exception>

using StringVector = std::vector<std::string>;
using String = std::string;

Command::Command(CommandType name, StringVector args) 
	: name(name), args(args) 
{}

// command is in the form: commandName arg1 arg2 ... argN
Command Command::create(String line)
{
	String name = line.substr(0, line.find_first_of(' '));
	CommandType commandName = getCommandNameAsEnum(name);
	line = line.substr(line.find_first_of(' ') + 1);
	StringVector args = splitString(line, ' ');

	return Command(commandName, args);
}

CommandType Command::getCommandName() const
{
	return name;
}

const StringVector& Command::getArgs() const
{
	return args;
}

CommandType getCommandNameAsEnum(const String& name) {
	for (int i = 0; i < (int)CommandType::COMMANDS_COUNT; i++) {
		if (name == getCommandName((CommandType)i)) {
			return (CommandType)i;
		}
	}
}

const char* getCommandName(CommandType commandName) {
	switch (commandName)
	{
	case CommandType::CREATE:
		return "create";
	}
}

// TODO: move this to MyString or Helper
StringVector splitString(const String& str, char delimiter) 
{
	StringVector tokens;
	std::istringstream iss(str);
	String token;

	while (std::getline(iss, token, delimiter))
	{
		tokens.push_back(token);
	}

	return tokens;
}
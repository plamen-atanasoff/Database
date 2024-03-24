#include "Command.h"

#include <string>
#include <vector>
#include <sstream>
#include <exception>

using StringVector = std::vector<std::string>;
using String = std::string;

Command::Command(CommandName name, StringVector args) 
	: name(name), args(args) 
{}

// command is in the form: commandName arg1 arg2 ... argN
Command Command::create(String line)
{
	String name = line.substr(0, line.find_first_of(' '));
	CommandName commandName = getCommandNameAsEnum(name);
	line = line.substr(line.find_first_of(' ') + 1);
	StringVector args = splitString(line, ' ');

	return Command(commandName, args);
}

CommandName Command::getCommandName() const
{
	return name;
}

const StringVector& Command::getArgs() const
{
	return args;
}

CommandName getCommandNameAsEnum(const String& name) {
	for (int i = 0; i < (int)CommandName::COMMANDS_COUNT; i++) {
		if (name == getCommandName((CommandName)i)) {
			return (CommandName)i;
		}
	}
}

const char* getCommandName(CommandName commandName) {
	switch (commandName)
	{
	case CommandName::CREATE:
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
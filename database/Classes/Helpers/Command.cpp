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

// command is in the form: commandType arg1 arg2 ... argN
Command Command::create(String line)
{
	size_t delimiterPos = line.find_first_of(' ');
	String name = line.substr(0, delimiterPos);
	CommandType commandType = getCommandTypeAsEnum(name);
	StringVector args;
	if (delimiterPos != String::npos) {
		line = line.substr(delimiterPos + 1);
		args = splitString(line, ' ');
	}

	return Command(commandType, args);
}

CommandType Command::getCommandName() const
{
	return name;
}

const StringVector& Command::getArgs() const
{
	return args;
}

CommandType getCommandTypeAsEnum(const String& name) {
	for (int i = 0; i < (int)CommandType::COMMANDS_COUNT; i++) {
		if (name == getCommandName((CommandType)i)) {
			return (CommandType)i;
		}
	}

	throw std::exception("no such command available");
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
#pragma once

#include <string>
#include <vector>

#include "../Factories/CommandFactory.h"

using StringVector = std::vector<std::string>;
using String = std::string;

class Command {
public:
	static Command create(String line);

	CommandType getCommandName() const;
	const StringVector& getArgs() const;
private:
	CommandType name;
	StringVector args;

	Command(CommandType name, StringVector args);
};

CommandType getCommandTypeAsEnum(const String& name);
StringVector splitString(const String& str, char delimiter);
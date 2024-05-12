#pragma once

#include <string>
#include <vector>

#include "../Factories/CommandFactory.h"

using StringVector = std::vector<std::string>;
using String = std::string;

class Command {
public:
	static Command create(const String& line);

	Command(CommandType type, const StringVector& args);

	CommandType getCommandName() const;
	const StringVector& getArgs() const;
private:
	CommandType type;
	StringVector args;
};

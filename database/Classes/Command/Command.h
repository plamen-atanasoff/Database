#pragma once

#include <string>
#include <vector>

#include "CommandType.h"
#include "../Controller.h"

class Command {
public:
	virtual ~Command() = default;
	virtual void execute() const = 0;
};

class CommandCreator {
public:
	CommandCreator(CommandType type);
	virtual ~CommandCreator() = default;

	virtual Command* create(const std::vector<String>& args, Database& database) const = 0;
	
	CommandType getCommandType() const;
private:
	CommandType type;
};
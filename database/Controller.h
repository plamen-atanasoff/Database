#pragma once

#include "Command.h"

#include <string>
#include <vector>

using StringVector = std::vector<std::string>;

class Controller
{
private:
	void createTable(const StringVector& args);
public:
	void execute(const Command& command);
};

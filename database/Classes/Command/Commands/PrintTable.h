#pragma once

#include "../Command.h"

using String = std::string;

class PrintTable : public Command
{
public:
	PrintTable(Table* table);

	virtual void execute() const override;
private:
	Table* table = nullptr;
};

class PrintTableCreator : public CommandCreator {
public:
	PrintTableCreator();
	virtual Command* create(const std::vector<String>& args, Database& database) const override;
};
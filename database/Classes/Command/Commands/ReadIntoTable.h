#pragma once

#include <string>

#include "../Command.h"
#include "../../Table/Table.h"

using String = std::string;

class ReadIntoTable : public Command {
public:
	ReadIntoTable(const String& fileName, Table* table);

	virtual void execute() const override;
private:
	String fileName;
	Table* table = nullptr;
};

class ReadIntoTableCreator : public CommandCreator {
public:
	ReadIntoTableCreator();
	virtual Command* create(const std::vector<String>& args, Database& database) const override;
};
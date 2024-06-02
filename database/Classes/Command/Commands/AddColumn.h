#pragma once

#include "../Command.h"

class AddColumn : public Command {
public:
	AddColumn(const String& name, ColumnType type, Table* table);

	virtual void execute() const;
private:
	String name;
	ColumnType type;
	Table* table = nullptr;
};

class AddColumnCreator : public CommandCreator {
public:
	AddColumnCreator();
	virtual Command* create(const std::vector<String>& args, Database& database) const override;
};
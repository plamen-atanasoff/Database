#pragma once

#include "../Command.h"

class CreateTable : public Command {
public:
	CreateTable(const String& name, Table* table);
	virtual void execute() const override;
private:
	String name;
	Table* table = nullptr;
};

class CreateTableCreator : public CommandCreator {
public:
	CreateTableCreator();
	virtual Command* create(const std::vector<String>& args, Database& database) const override;
};
#pragma once

#include "../Command.h"

class OpenTable : public Command {
public:
	OpenTable(const String& tableName, const std::vector<StringPair>& tables, Table* table);

	virtual void execute() const override;
private:
	String tableName;
	const std::vector<StringPair>& tables;
	Table* table = nullptr;
};

class OpenTableCreator : public CommandCreator {
public:
	OpenTableCreator();
	virtual Command* create(const std::vector<String>& args, Database& database) const override;
};
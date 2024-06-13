#pragma once

#include "../Command.h"

class ShowTables : public Command {
public:
	ShowTables(const std::vector<StringPair>& tables);

	virtual void execute() const override;
private:
	const std::vector<StringPair>& tables;
};

class ShowTablesCreator : public CommandCreator {
public:
	ShowTablesCreator();
	virtual Command* create(const std::vector<String>& args, Database& database) const override;
};
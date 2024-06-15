#pragma once

#include "../Command.h"

class DescribeColumns : public Command {
public:
	DescribeColumns(Table* table);

	virtual void execute() const;
private:
	Table* table = nullptr;
};

class DescribeColumnsCreator : public CommandCreator {
public:
	DescribeColumnsCreator();
	virtual Command* create(const std::vector<String>& args, Database& database) const override;
};
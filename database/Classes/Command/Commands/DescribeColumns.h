#pragma once

#include "../Command.h"

class DescribeColumns : public Command {
public:
	DescribeColumns(Table* table);

	virtual void execute() const;
	virtual Command* clone() const override;
private:
	Table* table = nullptr;

	static constexpr const char* separator = " | ";
};

class DescribeColumnsCreator : public CommandCreator {
public:
	DescribeColumnsCreator();
	virtual Command* create(const std::vector<String>& args, Database& database) const override;
};
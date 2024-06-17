#pragma once

#include "../Command.h"

using String = std::string;

class PrintTable : public Command
{
public:
	PrintTable(Table* table, unsigned recordsPerPage);

	virtual void execute() const override;
private:
	Table* table = nullptr;
	const unsigned recordsPerPage;

	static constexpr const char* separator = " | ";

	void printColumnInfo() const;
};

class PrintTableCreator : public CommandCreator {
public:
	PrintTableCreator();
	virtual Command* create(const std::vector<String>& args, Database& database) const override;
};
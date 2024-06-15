#pragma once

#include "../Command.h"

class SaveTable : public Command {
public:
	SaveTable(const std::vector<StringPair>& tables, const Table* table);

	virtual void execute() const;
private:
	const std::vector<StringPair>& tables;
	const Table* table = nullptr;

	String getFileName() const;
};

class SaveTableCreator : public CommandCreator {
public:
	SaveTableCreator();
	virtual Command* create(const std::vector<String>& args, Database& database) const override;
};
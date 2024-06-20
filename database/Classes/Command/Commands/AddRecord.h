#pragma once

#include "../Command.h"

class AddRecord : public Command {
public:
	AddRecord(const std::vector<String>& args, Table* table);

	virtual void execute() const;
	virtual Command* clone() const override;
private:
	const std::vector<String> args;
	Table* table = nullptr;
};

class AddRecordCreator : public CommandCreator {
public:
	AddRecordCreator();
	virtual Command* create(const std::vector<String>& args, Database& database) const override;
};
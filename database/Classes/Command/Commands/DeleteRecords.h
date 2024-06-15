#pragma once

#include "../Command.h"

class DeleteRecords : public Command {
public:
	DeleteRecords(int colPos, const String& value, Table* table);

	virtual void execute() const;
private:
	int colPos;
	String value;
	Table* table = nullptr;
};

class DeleteRecordsCreator : public CommandCreator {
public:
	DeleteRecordsCreator();
	virtual Command* create(const std::vector<String>& args, Database& database) const override;
};
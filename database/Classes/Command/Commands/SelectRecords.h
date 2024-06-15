#pragma once

#include "../Command.h"

class SelectRecords : public Command {
public:
	SelectRecords(int colPos, const String& value, Table* table);

	virtual void execute() const;
private:
	int colPos;
	String value;
	Table* table = nullptr;
};

class SelectRecordsCreator : public CommandCreator {
public:
	SelectRecordsCreator();
	virtual Command* create(const std::vector<String>& args, Database& database) const override;
};
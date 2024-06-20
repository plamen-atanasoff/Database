#pragma once

#include "../Command.h"

class SelectOnto : public Command {
public:
	SelectOnto(const String& resultTableName, const std::vector<int>& columnsInd, size_t searchColInd, const String& value, Table* table);

	virtual void execute() const override;
	virtual Command* clone() const override;
private:
	String resultTableName;
	std::vector<int> columnsInd;
	size_t searchColInd;
	String value;
	Table* table = nullptr;
};

class SelectOntoCreator : public CommandCreator {
public:
	SelectOntoCreator();
	virtual Command* create(const std::vector<String>& args, Database& database) const override;
};

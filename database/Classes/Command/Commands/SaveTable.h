#pragma once

#include "../Command.h"

class SaveTable : public Command {
public:
	SaveTable(const String& fileName, Table* table);

	virtual void execute() const;
private:
	String fileName;
	Table* table = nullptr;
};

class SaveTableCreator : public CommandCreator {
public:
	SaveTableCreator();
	virtual Command* create(const std::vector<String>& args, Database& database) const override;
};
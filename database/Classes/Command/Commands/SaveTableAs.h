#pragma once

#include "../Command.h"

class SaveTableAs : public Command {
public:
	SaveTableAs(const String& fileName, const Table* table);

	virtual void execute() const;
private:
	String fileName;
	const Table* table = nullptr;
};

class SaveTableAsCreator : public CommandCreator {
public:
	SaveTableAsCreator();
	virtual Command* create(const std::vector<String>& args, Database& database) const override;
};
#pragma once

#include "../Command.h"

class CloseDatabase : public Command {
public:
	CloseDatabase() = default;

	virtual void execute() const;
	virtual Command* clone() const override;
};

class CloseDatabaseCreator : public CommandCreator {
public:
	CloseDatabaseCreator();
	virtual Command* create(const std::vector<String>& args, Database& database) const override;
};
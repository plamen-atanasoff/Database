#include "CreateTable.h"

CreateTable::CreateTable(const String& name, Table* table) : name(name), table(table) {}

void CreateTable::execute() const
{
    *table = Table(name);
}

CreateTableCreator::CreateTableCreator() : CommandCreator(CommandType::CREATE_TABLE) {}

Command* CreateTableCreator::create(const std::vector<String>& args, Database& database) const
{
    if (args.size() != 1) {
        throw std::exception("invalid arguments count");
    }

    return new CreateTable(args[0], &database.getTable());
}

static CreateTableCreator __;

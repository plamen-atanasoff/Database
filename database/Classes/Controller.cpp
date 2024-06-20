#include "Controller.h"

#include "Command/CommandFactory.h"
#include "Command/Commands/OtherCommands/ReadTablesInfo.h"

Controller::~Controller()
{
	free();
}

Controller& Controller::getInstance()
{
	static Controller controller;
	return controller;
}

void Controller::run()
{
	String line;

	while (true)
	{
		std::cout << "Enter command: ";
		std::getline(std::cin, line);
		system("cls");

		if (line == "exit") {
			char answer;
			std::cout << "Do you want to save the current table(y/n)?";
			std::cin >> answer;
			if (answer == 'y') {
				this->executeCommand("save");
			}
			break;
		}
		else if (commandIsLoad(line)) {
			size_t commandEnd = line.find_first_of(' ');
			String databaseFileName = line.substr(commandEnd + 1);
			this->loadDatabase(databaseFileName);
		}
		else {
			try {
				this->executeCommand(line);
			}
			catch (const std::exception& e) {
				std::cout << e.what() << std::endl << std::endl;
			}
		}
	}
}

void Controller::loadDatabase(const String& databaseFilePath)
{
	closeDatabase();

	database = new Database(databaseFilePath);
	ReadTablesInfo::execute(database->getTablesInfoFileName(), &database->getTablesInfo());
}

void Controller::closeDatabase()
{
	if (database) {
		free();
	}
}

void Controller::executeCommand(const String& input)
{
	if (!database) {
		throw std::exception(DATABASE_NOT_LOADED_MESSAGE);
	}
	
	Command* command = nullptr;
	try {
		command = CommandFactory::getFactory().createCommand(input, *database);

		if (command) {
			command->execute();
		}
	}
	catch (const std::exception&) {
		delete command;
		throw;
	}
	delete command;
}

void Controller::free()
{
	delete database;
	database = nullptr;
}

bool Controller::commandIsLoad(const String& line) const
{
	size_t commandEnd = line.find_first_of(' ');
	return line.substr(0, commandEnd) == "load";
}

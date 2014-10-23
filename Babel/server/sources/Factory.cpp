#include "Factory.hpp"
#include "Command/CommandUpdate.hpp"
#include "Command/CommandAdd.hpp"

ICommand	*Factory::getCommand(ICommand::Instruction instruction){
	switch (instruction)
	{
	case ICommand::ADD:
		return new CommandAdd;
	case ICommand::UPDATE:
		return new CommandUpdate;
	default:
		return NULL;
	}
}
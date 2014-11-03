#pragma once

#include "ICommand.hpp"

namespace Factory{
	std::string getName(int instruction);
	ICommand	*getCommand(ICommand::Instruction instruction);
}
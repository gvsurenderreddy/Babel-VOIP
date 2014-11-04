#pragma once

#include "ICommand.hpp"

#include <string>

namespace Factory{
	std::string getName(int instruction);
	ICommand	*getCommand(ICommand::Instruction instruction);
}
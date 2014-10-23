#pragma once

#include "ICommand.hpp"

namespace Factory{
	ICommand *getCommand(ICommand::Instruction instruction);
}
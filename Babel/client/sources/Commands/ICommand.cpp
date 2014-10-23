#include "ICommand.hpp"
#include "CommandReg.hpp"
#include "CommandLog.hpp"
#include "CommandList.hpp"
#include "CommandShow.hpp"
#include "CommandAdd.hpp"
#include "CommandAcceptAdd.hpp"
#include "CommandDel.hpp"
#include "CommandExit.hpp"
#include "CommandUpdate.hpp"
#include "CommandSend.hpp"
#include "CommandCall.hpp"
#include "CommandAcceptCall.hpp"
#include "CommandCloseCall.hpp"
#include "CommandErr.hpp"

const unsigned int	ICommand::MAGIC_CODE = 0x150407CA;
const unsigned int	ICommand::HEADER_SIZE = sizeof ICommand::Header;

ICommand	*ICommand::getCommand(ICommand::Instruction instructionCode) {
	switch (instructionCode) {
	case ICommand::REG:
		return new CommandReg;
	case ICommand::LOG:
		return new CommandLog;
	case ICommand::LIST:
		return new CommandList;
	case ICommand::SHOW:
		return new CommandShow;
	case ICommand::ADD:
		return new CommandAdd;
	case ICommand::ACCEPT_ADD:
		return new CommandAcceptAdd;
	case ICommand::DEL:
		return new CommandDel;
	case ICommand::EXIT:
		return new CommandExit;
	case ICommand::UPDATE:
		return new CommandUpdate;
	case ICommand::SEND:
		return new CommandSend;
	case ICommand::CALL:
		return new CommandCall;
	case ICommand::ACCEPT_CALL:
		return new CommandAcceptCall;
	case ICommand::CLOSE_CALL:
		return new CommandCloseCall;
	case ICommand::ERR:
		return new CommandErr;
	default:
		return NULL;
	}
}

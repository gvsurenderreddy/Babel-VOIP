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
#include "CommandHandshake.hpp"
#include "CommandAcceptCall.hpp"
#include "CommandCloseCall.hpp"
#include "CommandErr.hpp"

const int32_t		ICommand::MAGIC_CODE = 0x150407CA;
const unsigned int	ICommand::HEADER_SIZE = sizeof(ICommand::Header);

std::shared_ptr<ICommand>	ICommand::getCommand(ICommand::Instruction instructionCode) {
	switch (instructionCode) {
	case ICommand::REG:
		return std::make_shared<CommandReg>();
	case ICommand::LOG:
		return std::make_shared<CommandLog>();
	case ICommand::LIST:
		return std::make_shared<CommandList>();
	case ICommand::SHOW:
		return std::make_shared<CommandShow>();
	case ICommand::ADD:
		return std::make_shared<CommandAdd>();
	case ICommand::ACCEPT_ADD:
		return std::make_shared<CommandAcceptAdd>();
	case ICommand::DEL:
		return std::make_shared<CommandDel>();
	case ICommand::EXIT:
		return std::make_shared<CommandExit>();
	case ICommand::UPDATE:
		return std::make_shared<CommandUpdate>();
	case ICommand::SEND:
		return std::make_shared<CommandSend>();
	case ICommand::CALL:
		return std::make_shared<CommandCall>();
	case ICommand::ACCEPT_CALL:
		return std::make_shared<CommandAcceptCall>();
	case ICommand::CLOSE_CALL:
		return std::make_shared<CommandCloseCall>();
	case ICommand::HANDSHAKE:
		return std::make_shared<CommandHandshake>();
	case ICommand::ERR:
		return std::make_shared<CommandErr>();
	default:
		return nullptr;
	}
}

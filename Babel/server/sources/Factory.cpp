#include "Factory.hpp"
#include "Command/CommandUpdate.hpp"
#include "Command/CommandAdd.hpp"
#include "Command/CommandReg.hpp"
#include "Command/CommandLog.hpp"
#include "Command/CommandList.hpp"
#include "Command/CommandShow.hpp"
#include "Command/CommandCall.hpp"
#include "Command/CommandAcceptAdd.hpp"
#include "Command/CommandDel.hpp"
#include "Command/CommandExit.hpp"
#include "Command/CommandSend.hpp"
#include "Command/CommandAcceptCall.hpp"
#include "Command/CommandCloseCall.hpp"
#include "Command/CommandErr.hpp"

ICommand	*Factory::getCommand(ICommand::Instruction instruction){
	switch (instruction)
	{
	case ICommand::ADD:
        std::cout << "  # PACKCMD [0x" << instruction << "] [ICommand::ADD]" << std::endl;
		return new CommandAdd;
    case ICommand::UPDATE:
        std::cout << "  # PACKCMD [0x" << instruction << "] [ICommand::UPDATE]" << std::endl;
		return new CommandUpdate;
    case ICommand::REG:
        std::cout << "  # PACKCMD [0x" << instruction << "] [ICommand::REG]" << std::endl;
		return new CommandReg;
    case ICommand::LOG:
        std::cout << "  # PACKCMD [0x" << instruction << "] [ICommand::LOG]" << std::endl;
		return new CommandLog;
    case ICommand::LIST:
        std::cout << "  # PACKCMD [0x" << instruction << "] [ICommand::LIST]" << std::endl;
		return new CommandList;
    case ICommand::SHOW:
        std::cout << "  # PACKCMD [0x" << instruction << "] [ICommand::SHOW]" << std::endl;
		return new CommandShow;
    case ICommand::CALL:
        std::cout << "  # PACKCMD [0x" << instruction << "] [ICommand::CALL]" << std::endl;
		return new CommandCall;
    case ICommand::ACCEPT_ADD:
        std::cout << "  # PACKCMD [0x" << instruction << "] [ICommand::ACCEPT_ADD]" << std::endl;
		return new CommandAcceptAdd;
    case ICommand::DEL:
        std::cout << "  # PACKCMD [0x" << instruction << "] [ICommand::DEL]" << std::endl;
		return new CommandDel;
    case ICommand::EXIT:
        std::cout << "  # PACKCMD [0x" << instruction << "] [ICommand::EXIT]" << std::endl;
		return new CommandExit;
    case ICommand::SEND:
        std::cout << "  # PACKCMD [0x" << instruction << "] [ICommand::SEND]" << std::endl;
		return new CommandSend;
    case ICommand::ACCEPT_CALL:
        std::cout << "  # PACKCMD [0x" << instruction << "] [ICommand::ACCEPT_CALL]" << std::endl;
		return new CommandAcceptCall;
    case ICommand::CLOSE_CALL:
        std::cout << "  # PACKCMD [0x" << instruction << "] [ICommand::CLOSE_CALL]" << std::endl;
		return new CommandCloseCall;
    case ICommand::ERR:
        std::cout << "  # PACKCMD [0x" << instruction << "] [ICommand::ERR]" << std::endl;
		return new CommandErr;
	default:
        std::cout << "  # PACKCMD [0x" << instruction << "] [UNKNOWN CMD]" << std::endl;
		return NULL;
	}
}
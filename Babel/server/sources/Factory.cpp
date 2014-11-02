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

#include <string>

std::string Factory::getName(int instruction)
{
    switch (instruction)
    {
    case ICommand::ADD:
        return "ADD";
    case ICommand::UPDATE:
        return "UPDATE";
    case ICommand::REG:
        return "REG";
    case ICommand::LOG:
        return "LOG";
    case ICommand::LIST:
        return "LIST";
    case ICommand::SHOW:
        return "SHOW";
    case ICommand::CALL:
        return "CALL";
    case ICommand::ACCEPT_ADD:
        return "ACCEPT_ADD";
    case ICommand::DEL:
        return "DEL";
    case ICommand::EXIT:
        return "EXIT";
    case ICommand::SEND:
        return "SEND";
    case ICommand::ACCEPT_CALL:
        return "ACCEPT_CALL";
    case ICommand::CLOSE_CALL:
        return "CLOSE_CALL";
    case ICommand::ERR:
        return "CommandErr";
    default:
        return "UNKNOWN";
    }
}

ICommand	*Factory::getCommand(ICommand::Instruction instruction)
{
	switch (instruction)
	{
	case ICommand::ADD:
        std::cout << "[ADD]" << std::endl;
		return new CommandAdd;
    case ICommand::UPDATE:
        std::cout << "[UPDATE]" << std::endl;
		return new CommandUpdate;
    case ICommand::REG:
        std::cout << "[REG]" << std::endl;
		return new CommandReg;
    case ICommand::LOG:
        std::cout << "[LOG]" << std::endl;
		return new CommandLog;
    case ICommand::LIST:
        std::cout << "[LIST]" << std::endl;
		return new CommandList;
    case ICommand::SHOW:
        std::cout << "[SHOW]" << std::endl;
		return new CommandShow;
    case ICommand::CALL:
        std::cout << "[CALL]" << std::endl;
		return new CommandCall;
    case ICommand::ACCEPT_ADD:
        std::cout << "[ACCEPT_ADD]" << std::endl;
		return new CommandAcceptAdd;
    case ICommand::DEL:
        std::cout << "[DEL]" << std::endl;
		return new CommandDel;
    case ICommand::EXIT:
        std::cout << "[EXIT]" << std::endl;
		return new CommandExit;
    case ICommand::SEND:
        std::cout << "[SEND]" << std::endl;
		return new CommandSend;
    case ICommand::ACCEPT_CALL:
        std::cout << "[ACCEPT_CALL]" << std::endl;
		return new CommandAcceptCall;
    case ICommand::CLOSE_CALL:
        std::cout << "[CLOSE_CALL]" << std::endl;
		return new CommandCloseCall;
    case ICommand::ERR:
		return new CommandErr;
	default:
        std::cout << "[ --- UNKNOWN CMD --- ]" << std::endl;
		return NULL;
	}
}
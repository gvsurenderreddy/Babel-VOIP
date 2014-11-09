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
#include "Command/CommandHandshake.hpp"
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
    case ICommand::HANDSHAKE:
        return "CommandHandshake";
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
		return new CommandAdd;
    case ICommand::UPDATE:
		return new CommandUpdate;
    case ICommand::REG:
		return new CommandReg;
    case ICommand::LOG:
		return new CommandLog;
    case ICommand::LIST:
		return new CommandList;
    case ICommand::SHOW:
		return new CommandShow;
    case ICommand::CALL:
		return new CommandCall;
    case ICommand::ACCEPT_ADD:
		return new CommandAcceptAdd;
    case ICommand::DEL:
		return new CommandDel;
    case ICommand::EXIT:
		return new CommandExit;
    case ICommand::SEND:
		return new CommandSend;
    case ICommand::ACCEPT_CALL:
		return new CommandAcceptCall;
    case ICommand::CLOSE_CALL:
		return new CommandCloseCall;
    case ICommand::HANDSHAKE:
        return new CommandHandshake;
    case ICommand::ERR:
		return new CommandErr;
	default:
		return NULL;
	}
}
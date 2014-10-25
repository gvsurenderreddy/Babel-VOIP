#include "ServerCommunication.hpp"
#include "CommandShow.hpp"
#include "CommandAdd.hpp"
#include "CommandDel.hpp"
#include "CommandSend.hpp"
#include "CommandCall.hpp"
#include "CommandAcceptCall.hpp"
#include "CommandCloseCall.hpp"
#include "CommandErr.hpp"

const ServerCommunication::HandleCommand ServerCommunication::handleCommandsTab[] = {
	{ ICommand::SHOW,					&ServerCommunication::handleShowCommand			},
	{ ICommand::ADD,					&ServerCommunication::handleAddCommand			},
	{ ICommand::DEL,					&ServerCommunication::handleDelCommand			},
	{ ICommand::SEND,					&ServerCommunication::handleSendCommand			},
	{ ICommand::CALL,					&ServerCommunication::handleCallCommand			},
	{ ICommand::ACCEPT_CALL,			&ServerCommunication::handleAcceptCallCommand	},
	{ ICommand::CLOSE_CALL,				&ServerCommunication::handleCloseCallCommand	},
	{ ICommand::ERR,					&ServerCommunication::handleErrCommand			},
	{ ICommand::UNKNOWN_INSTRUCTION,	NULL											}
};

const ServerCommunication::HandleError ServerCommunication::handleErrorsTab[] = {
	{ ICommand::REG,					&ServerCommunication::receiveServerAnswerForReg			},
	{ ICommand::LOG,					&ServerCommunication::receiveServerAnswerForLog			},
	{ ICommand::ADD,					&ServerCommunication::receiveServerAnswerForAdd			},
	{ ICommand::ACCEPT_ADD,				&ServerCommunication::receiveServerAnswerForAcceptAdd	},
	{ ICommand::DEL,					&ServerCommunication::receiveServerAnswerForDel			},
	{ ICommand::EXIT,					&ServerCommunication::receiveServerAnswerForExit		},
	{ ICommand::UPDATE,					&ServerCommunication::receiveServerAnswerForUpdate		},
	{ ICommand::SEND,					&ServerCommunication::receiveServerAnswerForSend		},
	{ ICommand::CALL,					&ServerCommunication::receiveServerAnswerForCall		},
	{ ICommand::ACCEPT_CALL,			&ServerCommunication::receiveServerAnswerForAcceptCall	},
	{ ICommand::CLOSE_CALL,				&ServerCommunication::receiveServerAnswerForCloseCall	},
	{ ICommand::UNKNOWN_INSTRUCTION,	NULL													}
};

ServerCommunication::ServerCommunication(void) {
	connect(&mCommandPacketBuilder, SIGNAL(receiveCommand(const ICommand *)), this, SLOT(treatCommand(const ICommand *)));
}

ServerCommunication::~ServerCommunication(void) {
}

void	ServerCommunication::treatCommand(const ICommand *command) {
	ICommand::Instruction instruction = command->getInstruction();

	int i;
	for (i = 0; handleCommandsTab[i].instruction != ICommand::UNKNOWN_INSTRUCTION && handleCommandsTab[i].instruction != instruction; i++);

	if (handleCommandsTab[i].instruction == instruction)
		(this->*handleCommandsTab[i].handler)(command);
}

void	ServerCommunication::connectToServer(const QString &addr, int port) {
	mCommandPacketBuilder.connectToServer(addr, port);
}

void	ServerCommunication::handleShowCommand(const ICommand *command) {
	const CommandShow *commandShow = dynamic_cast<const CommandShow *>(command);

	emit receiveContactInfo(commandShow->getAccountName(), commandShow->getPseudo(), commandShow->getStatus(), commandShow->isConnected());
}

void	ServerCommunication::handleAddCommand(const ICommand *command) {
	const CommandAdd *commandAdd = dynamic_cast<const CommandAdd *>(command);

	emit receiveContactInvitation(commandAdd->getAccountName());
}

void	ServerCommunication::handleDelCommand(const ICommand *command) {
	const CommandDel *commandDel = dynamic_cast<const CommandDel *>(command);

	emit receiveContactDeletion(commandDel->getAccountName());
}

void	ServerCommunication::handleSendCommand(const ICommand *command) {
	const CommandSend *commandSend = dynamic_cast<const CommandSend *>(command);

	emit receiveMessage(commandSend->getAccountName(), commandSend->getTextMessage());
}

void	ServerCommunication::handleCallCommand(const ICommand *command) {
	const CommandCall *commandCall = dynamic_cast<const CommandCall *>(command);

	emit receiveCallInvitation(commandCall->getAccountName());
}

void	ServerCommunication::handleAcceptCallCommand(const ICommand *command) {
	const CommandAcceptCall *commandAcceptCall = dynamic_cast<const CommandAcceptCall *>(command);

	emit receiveCallAnswer(commandAcceptCall->getAccountName(), commandAcceptCall->getHost(), commandAcceptCall->hasAccepted());
}

void	ServerCommunication::handleCloseCallCommand(const ICommand *command) {
	const CommandCloseCall *commandCloseCall = dynamic_cast<const CommandCloseCall *>(command);

	emit receiveCallClose(commandCloseCall->getAccountName());
}

void	ServerCommunication::handleErrCommand(const ICommand *command) {
	const CommandErr *commandErr = dynamic_cast<const CommandErr *>(command);
	ICommand::Instruction instruction = commandErr->getInstructionCode();
	CommandErr::ErrorCode error_code = commandErr->getErrorCode();
	bool success = error_code != CommandErr::OK;

	int i;
	for (i = 0; handleErrorsTab[i].instruction != ICommand::UNKNOWN_INSTRUCTION && handleErrorsTab[i].instruction != instruction; i++);
	if (handleErrorsTab[i].instruction == instruction)
		emit (this->*handleErrorsTab[i].signal)(success, error_code);
}

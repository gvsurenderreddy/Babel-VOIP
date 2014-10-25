#include "ServerCommunication.hpp"
#include "CommandShow.hpp"
#include "CommandAdd.hpp"
#include "CommandDel.hpp"
#include "CommandSend.hpp"
#include "CommandCall.hpp"
#include "CommandAcceptCall.hpp"
#include "CommandCloseCall.hpp"
#include "CommandReg.hpp"
#include "CommandLog.hpp"
#include "CommandList.hpp"
#include "CommandExit.hpp"
#include "CommandAcceptAdd.hpp"
#include "CommandUpdate.hpp"
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
	{ ICommand::REG,					&ServerCommunication::receiveServerAnswerForRegistration			},
	{ ICommand::LOG,					&ServerCommunication::receiveServerAnswerForAuthentication			},
	{ ICommand::ADD,					&ServerCommunication::receiveServerAnswerForAddingContact			},
	{ ICommand::ACCEPT_ADD,				&ServerCommunication::receiveServerAnswerForAcceptingContact		},
	{ ICommand::DEL,					&ServerCommunication::receiveServerAnswerForDeletingContact			},
	{ ICommand::EXIT,					&ServerCommunication::receiveServerAnswerForDisconnecting			},
	{ ICommand::UPDATE,					&ServerCommunication::receiveServerAnswerForUpdatingInfo			},
	{ ICommand::SEND,					&ServerCommunication::receiveServerAnswerForSendingMessage			},
	{ ICommand::CALL,					&ServerCommunication::receiveServerAnswerForCallingContact			},
	{ ICommand::ACCEPT_CALL,			&ServerCommunication::receiveServerAnswerForAcceptingCallInvitation	},
	{ ICommand::CLOSE_CALL,				&ServerCommunication::receiveServerAnswerForTerminatingCall			},
	{ ICommand::UNKNOWN_INSTRUCTION,	NULL																}
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

void	ServerCommunication::createAccount(const QString &accountName, const QString &pseudo, const QString &password) {
	CommandReg *commandReg = new CommandReg;

	commandReg->setAccountName(accountName);
	commandReg->setPseudo(pseudo);
	commandReg->setPassword(password);

	mCommandPacketBuilder.sendCommand(commandReg);
}

void	ServerCommunication::authenticate(const QString &accountName, const QString &password) {
	CommandLog *commandLog = new CommandLog;

	commandLog->setAccountName(accountName);
	commandLog->setPassword(password);

	mCommandPacketBuilder.sendCommand(commandLog);
}

void	ServerCommunication::getContactsInfo(void) {
	mCommandPacketBuilder.sendCommand(new CommandList);
}

void	ServerCommunication::getContactInfo(const QString &accountName) {
	CommandShow *commandShow = new CommandShow;

	commandShow->setAccountName(accountName);

	mCommandPacketBuilder.sendCommand(commandShow);
}

void	ServerCommunication::addContact(const QString &accountName) {
	CommandAdd *commandAdd = new CommandAdd;

	commandAdd->setAccountName(accountName);

	mCommandPacketBuilder.sendCommand(commandAdd);
}

void	ServerCommunication::acceptContactInvitation(const QString &accountName, bool hasAccepted) {
	CommandAcceptAdd *commandAcceptAdd = new CommandAcceptAdd;

	commandAcceptAdd->setAccountName(accountName);
	commandAcceptAdd->setHasAccepted(hasAccepted);

	mCommandPacketBuilder.sendCommand(commandAcceptAdd);
}

void	ServerCommunication::deleteContact(const QString &accountName) {
	CommandDel *commandDel = new CommandDel;

	commandDel->setAccountName(accountName);

	mCommandPacketBuilder.sendCommand(commandDel);
}

void	ServerCommunication::sendMessage(const QString &accountName, const QString &message) {
	CommandSend *commandSend = new CommandSend;

	commandSend->setAccountName(accountName);
	commandSend->setTextMessage(message);

	mCommandPacketBuilder.sendCommand(commandSend);
}

void	ServerCommunication::disconnect(void) {
	mCommandPacketBuilder.sendCommand(new CommandExit);
}

void	ServerCommunication::updateInfo(const QString &accountName, const QString &pseudo, const QString &password, Contact::Status status) {
	CommandUpdate *commandUpdate = new CommandUpdate;

	commandUpdate->setAccountName(accountName);
	commandUpdate->setPseudo(pseudo);
	commandUpdate->setPassword(password);
	commandUpdate->setStatus(status);

	mCommandPacketBuilder.sendCommand(commandUpdate);
}

void	ServerCommunication::call(const QString &accountName) {
	CommandCall *commandCall = new CommandCall;

	commandCall->setAccountName(accountName);

	mCommandPacketBuilder.sendCommand(commandCall);
}

void	ServerCommunication::acceptCallInvitation(const QString &accountName, bool hasAccepted) {
	CommandAcceptCall *commandAcceptCall = new CommandAcceptCall;

	commandAcceptCall->setAccountName(accountName);
	commandAcceptCall->setHasAccepted(hasAccepted);

	mCommandPacketBuilder.sendCommand(commandAcceptCall);
}

void	ServerCommunication::terminateCall(const QString &accountName) {
	CommandCloseCall *commandCloseCall = new CommandCloseCall;

	commandCloseCall->setAccountName(accountName);

	mCommandPacketBuilder.sendCommand(commandCloseCall);
}

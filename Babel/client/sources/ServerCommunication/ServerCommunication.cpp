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
#include "CommandHandshake.hpp"
#include "SocketException.hpp"

const ServerCommunication::HandleCommand ServerCommunication::handleCommandsTab[] = {
	{ ICommand::SHOW,					&ServerCommunication::handleShowCommand			},
	{ ICommand::ADD,					&ServerCommunication::handleAddCommand			},
	{ ICommand::DEL,					&ServerCommunication::handleDelCommand			},
	{ ICommand::SEND,					&ServerCommunication::handleSendCommand			},
	{ ICommand::CALL,					&ServerCommunication::handleCallCommand			},
	{ ICommand::ACCEPT_CALL,			&ServerCommunication::handleAcceptCallCommand	},
	{ ICommand::CLOSE_CALL,				&ServerCommunication::handleCloseCallCommand	},
	{ ICommand::ERR,					&ServerCommunication::handleErrCommand			},
    { ICommand::HANDSHAKE,              &ServerCommunication::handleHandshakeCommand    },
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

ServerCommunication::ServerCommunication(void) : mHasHandshaked(false) {
	connect(&mCommandPacketBuilder, SIGNAL(receiveCommand(const std::shared_ptr<ICommand> &)), this, SLOT(treatCommand(const std::shared_ptr<ICommand> &)));
	connect(&mCommandPacketBuilder, SIGNAL(disconnectedFromHost()), this, SLOT(onDisconnection()));
}

ServerCommunication::~ServerCommunication(void) {
}

void	ServerCommunication::treatCommand(const std::shared_ptr<ICommand> &command) {
	ICommand::Instruction instruction = command->getInstruction();

    if (mHasHandshaked == false && instruction != ICommand::HANDSHAKE) {
        mCommandPacketBuilder.close();
        return;
    }

	int i;
	for (i = 0; handleCommandsTab[i].instruction != ICommand::UNKNOWN_INSTRUCTION && handleCommandsTab[i].instruction != instruction; i++);

	if (handleCommandsTab[i].instruction == instruction)
		(this->*handleCommandsTab[i].handler)(command);
}

void    ServerCommunication::handleHandshakeCommand(const std::shared_ptr<ICommand> &) {
    mHasHandshaked = true;
}

void	ServerCommunication::handleShowCommand(const std::shared_ptr<ICommand> &command) {
	std::shared_ptr<CommandShow> commandShow = std::dynamic_pointer_cast<CommandShow>(command);

	Contact contact;
	contact.setAccountName(commandShow->getAccountName());
	contact.setPseudo(commandShow->getPseudo());
	contact.setStatus(commandShow->getStatus());
	contact.setIsConnected(commandShow->isConnected());

	emit receiveContactInfo(contact);
}

void	ServerCommunication::handleAddCommand(const std::shared_ptr<ICommand> &command) {
	std::shared_ptr<CommandAdd> commandAdd = std::dynamic_pointer_cast<CommandAdd>(command);

	Contact contact;
	contact.setAccountName(commandAdd->getAccountName());
	emit receiveContactInvitation(contact);
}

void	ServerCommunication::handleDelCommand(const std::shared_ptr<ICommand> &command) {
	std::shared_ptr<CommandDel> commandDel = std::dynamic_pointer_cast<CommandDel>(command);

	Contact contact;
	contact.setAccountName(commandDel->getAccountName());

	emit receiveContactDeletion(contact);
}

void	ServerCommunication::handleSendCommand(const std::shared_ptr<ICommand> &command) {
	std::shared_ptr<CommandSend> commandSend = std::dynamic_pointer_cast<CommandSend>(command);

	Contact contact;
	contact.setAccountName(commandSend->getAccountName());

	emit receiveMessage(contact, commandSend->getTextMessage());
}

void	ServerCommunication::handleCallCommand(const std::shared_ptr<ICommand> &command) {
	std::shared_ptr<CommandCall> commandCall = std::dynamic_pointer_cast<CommandCall>(command);

	Contact contact;
	contact.setAccountName(commandCall->getAccountName());

	emit receiveCallInvitation(contact);
}

void	ServerCommunication::handleAcceptCallCommand(const std::shared_ptr<ICommand> &command) {
	std::shared_ptr<CommandAcceptCall> commandAcceptCall = std::dynamic_pointer_cast<CommandAcceptCall>(command);

	Contact contact;
	contact.setAccountName(commandAcceptCall->getAccountName());
	contact.setHost(commandAcceptCall->getHost());

	emit receiveCallAnswer(contact, commandAcceptCall->hasAccepted());
}

void	ServerCommunication::handleCloseCallCommand(const std::shared_ptr<ICommand> &command) {
	std::shared_ptr<CommandCloseCall> commandCloseCall = std::dynamic_pointer_cast<CommandCloseCall>(command);

	Contact contact;
	contact.setAccountName(commandCloseCall->getAccountName());

	emit receiveCallClose(contact);
}

void	ServerCommunication::handleErrCommand(const std::shared_ptr<ICommand> &command) {
	std::shared_ptr<CommandErr> commandErr = std::dynamic_pointer_cast<CommandErr>(command);
	ICommand::Instruction instruction = commandErr->getInstructionCode();

	ErrorStatus errorStatus;
	errorStatus.setErrorCode(commandErr->getErrorCode());
	errorStatus.setErrorOccurred(commandErr->getErrorCode() != ErrorStatus::OK);

	int i;
	for (i = 0; handleErrorsTab[i].instruction != ICommand::UNKNOWN_INSTRUCTION && handleErrorsTab[i].instruction != instruction; i++);
	if (handleErrorsTab[i].instruction == instruction)
		emit (this->*handleErrorsTab[i].signal)(errorStatus);
}

void	ServerCommunication::createAccount(const Contact &contact) {
	CommandReg commandReg;

	commandReg.setAccountName(contact.getAccountName());
	commandReg.setPseudo(contact.getPseudo());
	commandReg.setPassword(contact.getPassword());

	mCommandPacketBuilder.sendCommand(&commandReg);
}

void	ServerCommunication::authenticate(const Contact &contact) {
	CommandLog commandLog;

	commandLog.setAccountName(contact.getAccountName());
	commandLog.setPassword(contact.getPassword());

	mCommandPacketBuilder.sendCommand(&commandLog);
}

void	ServerCommunication::getContactsInfo(void) {
	CommandList commandList;

	mCommandPacketBuilder.sendCommand(&commandList);
}

void	ServerCommunication::getContactInfo(const Contact &contact) {
	CommandShow commandShow;

	commandShow.setAccountName(contact.getAccountName());

	mCommandPacketBuilder.sendCommand(&commandShow);
}

void	ServerCommunication::addContact(const Contact &contact) {
	CommandAdd commandAdd;

	commandAdd.setAccountName(contact.getAccountName());

	mCommandPacketBuilder.sendCommand(&commandAdd);
}

void	ServerCommunication::acceptContactInvitation(const Contact &contact, bool hasAccepted) {
	CommandAcceptAdd commandAcceptAdd;

	commandAcceptAdd.setAccountName(contact.getAccountName());
	commandAcceptAdd.setHasAccepted(hasAccepted);

	mCommandPacketBuilder.sendCommand(&commandAcceptAdd);
}

void	ServerCommunication::deleteContact(const Contact &contact) {
	CommandDel commandDel;

	commandDel.setAccountName(contact.getAccountName());

	mCommandPacketBuilder.sendCommand(&commandDel);
}

void	ServerCommunication::sendMessage(const Contact &contact, const QString &message) {
	CommandSend commandSend;

	commandSend.setAccountName(contact.getAccountName());
	commandSend.setTextMessage(message);

	mCommandPacketBuilder.sendCommand(&commandSend);
}

void	ServerCommunication::disconnect(void) {
	CommandExit commandExit;

	mCommandPacketBuilder.sendCommand(&commandExit);
}

void	ServerCommunication::updateInfo(const Contact &contact) {
	CommandUpdate commandUpdate;

	commandUpdate.setAccountName(contact.getAccountName());
	commandUpdate.setPseudo(contact.getPseudo());
	commandUpdate.setPassword(contact.getPassword());
	commandUpdate.setStatus(contact.getStatus());

	mCommandPacketBuilder.sendCommand(&commandUpdate);
}

void	ServerCommunication::call(const Contact &contact) {
	CommandCall commandCall;

	commandCall.setAccountName(contact.getAccountName());

	mCommandPacketBuilder.sendCommand(&commandCall);
}

void	ServerCommunication::acceptCallInvitation(const Contact &contact, bool hasAccepted) {
	CommandAcceptCall commandAcceptCall;

	commandAcceptCall.setAccountName(contact.getAccountName());
	commandAcceptCall.setHasAccepted(hasAccepted);

	mCommandPacketBuilder.sendCommand(&commandAcceptCall);
}

void	ServerCommunication::terminateCall(const Contact &contact) {
    CommandCloseCall commandCloseCall;

    commandCloseCall.setAccountName(contact.getAccountName());

    mCommandPacketBuilder.sendCommand(&commandCloseCall);
}

void	ServerCommunication::sendHandshake(void) {
    CommandHandshake commandHandshake;

    mCommandPacketBuilder.sendCommand(&commandHandshake);
}

void	ServerCommunication::connectToServer(const QString &addr, int port) {
	ErrorStatus errorStatus;

	try {
		mCommandPacketBuilder.connectToServer(addr, port);
        sendHandshake();
		errorStatus.setErrorCode(ErrorStatus::OK);
		errorStatus.setErrorOccurred(false);
	}
	catch (const SocketException &) {
		errorStatus.setErrorCode(ErrorStatus::FAIL_INIT_SOCKET);
		errorStatus.setErrorOccurred(true);
	}

	emit receiveAnswerForConnectionToServer(errorStatus);
}

void	ServerCommunication::onDisconnection(void) {
	mHasHandshaked = false;
	emit disconnectedFromServer();
}
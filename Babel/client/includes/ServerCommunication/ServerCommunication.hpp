#pragma once

#include <qobject.h>
#include "ICommand.hpp"
#include "CommandPacketBuilder.hpp"
#include "CommandErr.hpp"
#include "Contact.hpp"

class ServerCommunication : public QObject {

	Q_OBJECT

	// handle commands
	private:
		struct HandleCommand {
			ICommand::Instruction	instruction;
			void					(ServerCommunication::*handler)(const ICommand *command);
		};

		static const ServerCommunication::HandleCommand	handleCommandsTab[];

		void	handleShowCommand(const ICommand *command);
		void	handleAddCommand(const ICommand *command);
		void	handleDelCommand(const ICommand *command);
		void	handleSendCommand(const ICommand *command);
		void	handleCallCommand(const ICommand *command);
		void	handleAcceptCallCommand(const ICommand *command);
		void	handleCloseCallCommand(const ICommand *command);
		void	handleErrCommand(const ICommand *command);

	// handle server errors
	private:
		struct HandleError {
			ICommand::Instruction	instruction;
			void					(ServerCommunication::*signal)(bool success, CommandErr::ErrorCode);
		};

		static const ServerCommunication::HandleError handleErrorsTab[];

	// signals
	signals:
		void	receiveContactInfo(const QString &accountName, const QString &pseudo, Contact::Status status, bool isConnected);
		void	receiveContactInvitation(const QString &accountName);
		void	receiveContactDeletion(const QString &accountName);
		void	receiveMessage(const QString &accountName, const QString &message);
		void	receiveCallInvitation(const QString &accountName);
		void	receiveCallAnswer(const QString &accountName, const QString &host, bool hasAccepted);
		void	receiveCallClose(const QString &accountName);
		void	receiveServerAnswerForRegistration(bool success, CommandErr::ErrorCode errorCode);
		void	receiveServerAnswerForAuthentication(bool success, CommandErr::ErrorCode errorCode);
		void	receiveServerAnswerForAddingContact(bool success, CommandErr::ErrorCode errorCode);
		void	receiveServerAnswerForAcceptingContact(bool success, CommandErr::ErrorCode errorCode);
		void	receiveServerAnswerForDeletingContact(bool success, CommandErr::ErrorCode errorCode);
		void	receiveServerAnswerForDisconnecting(bool success, CommandErr::ErrorCode errorCode);
		void	receiveServerAnswerForUpdatingInfo(bool success, CommandErr::ErrorCode errorCode);
		void	receiveServerAnswerForSendingMessage(bool success, CommandErr::ErrorCode errorCode);
		void	receiveServerAnswerForCallingContact(bool success, CommandErr::ErrorCode errorCode);
		void	receiveServerAnswerForAcceptingCallInvitation(bool success, CommandErr::ErrorCode errorCode);
		void	receiveServerAnswerForTerminatingCall(bool success, CommandErr::ErrorCode errorCode);

	// send commands slots
	public:
		void	createAccount(const QString &accountName, const QString &pseudo, const QString &password);
		void	authenticate(const QString &accountName, const QString &password);
		void	getContactsInfo(void);
		void	getContactInfo(const QString &accountName);
		void	addContact(const QString &accountName);
		void	acceptContactInvitation(const QString &accountName, bool hasAccepted);
		void	deleteContact(const QString &accountName);
		void	sendMessage(const QString &accountName, const QString &message);
		void	disconnect(void);
		void	updateInfo(const QString &accountName, const QString &pseudo, const QString &password, Contact::Status status);
		void	call(const QString &accountName);
		void	acceptCallInvitation(const QString &accountName, bool hasAccepted);
		void	terminateCall(const QString &accountName);

	// ctor - dtor
	public:
		ServerCommunication(void);
		~ServerCommunication(void);

	// coplien form
	private:
		ServerCommunication(const ServerCommunication &) : QObject() {}
		const ServerCommunication &operator=(const ServerCommunication &) { return *this; }

	// connect to server
	public:
		void	connectToServer(const QString &addr, int port);

	// receive command
	private slots :
		void	treatCommand(const ICommand *command);

	// attributes
	private:
		CommandPacketBuilder	mCommandPacketBuilder;

};

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
		void	receiveServerAnswerForReg(bool success, CommandErr::ErrorCode errorCode);
		void	receiveServerAnswerForLog(bool success, CommandErr::ErrorCode errorCode);
		void	receiveServerAnswerForAdd(bool success, CommandErr::ErrorCode errorCode);
		void	receiveServerAnswerForAcceptAdd(bool success, CommandErr::ErrorCode errorCode);
		void	receiveServerAnswerForDel(bool success, CommandErr::ErrorCode errorCode);
		void	receiveServerAnswerForExit(bool success, CommandErr::ErrorCode errorCode);
		void	receiveServerAnswerForUpdate(bool success, CommandErr::ErrorCode errorCode);
		void	receiveServerAnswerForSend(bool success, CommandErr::ErrorCode errorCode);
		void	receiveServerAnswerForCall(bool success, CommandErr::ErrorCode errorCode);
		void	receiveServerAnswerForAcceptCall(bool success, CommandErr::ErrorCode errorCode);
		void	receiveServerAnswerForCloseCall(bool success, CommandErr::ErrorCode errorCode);

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

#pragma once

#include <qobject.h>
#include "ICommand.hpp"
#include "CommandPacketBuilder.hpp"

class ServerCommunication : public QObject {

	Q_OBJECT

	// handle commands
	private:
		struct HandleCommand {
			ICommand::Instruction	instruction;
			void					(ServerCommunication::*handler)(const ICommand *command);
		};

		static const ServerCommunication::HandleCommand	handleCommandsTab[];

		void	handleRegCommand(const ICommand *command);
		void	handleLogCommand(const ICommand *command);
		void	handleListCommand(const ICommand *command);
		void	handleShowCommand(const ICommand *command);
		void	handleAddCommand(const ICommand *command);
		void	handleAcceptAddCommand(const ICommand *command);
		void	handleDelCommand(const ICommand *command);
		void	handleExitCommand(const ICommand *command);
		void	handeUpdateCommand(const ICommand *command);
		void	handleSendCommand(const ICommand *command);
		void	handleCallCommand(const ICommand *command);
		void	handleAcceptCallCommand(const ICommand *command);
		void	handleCloseCallCommand(const ICommand *command);
		void	handleErrCommand(const ICommand *command);

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

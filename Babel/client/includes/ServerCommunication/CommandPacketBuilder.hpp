#pragma once

#include "IClientSocket.hpp"
#include <qlist.h>
#include <qobject.h>

class CommandPacketBuilder : public QObject, public IClientSocket::OnSocketEvent {

	Q_OBJECT

	// Command
	public:
		enum Instruction {
		};

		struct Command {
			CommandPacketBuilder::Instruction	instruction;
			int									nbArgs;
			QList<int>							argsSizes;
			QList<char *>						args;
		};

	// handle build state
	private:
		enum State {
			INSTRUCTION,
			ARGS_SIZE,
			ARGS
		};

	// ctor - dtor
	public:
		CommandPacketBuilder(void);
		~CommandPacketBuilder(void);

	// coplien form
	private:
		CommandPacketBuilder(const CommandPacketBuilder &) : QObject() {}
		const CommandPacketBuilder &operator=(const CommandPacketBuilder &) { return *this; }

	// send command
	public:
		void	connectToServer(const QString &addr, int port);
		void	sendCommand(const CommandPacketBuilder::Command &command);

	// receive command
	signals:
		void	receiveCommand(const CommandPacketBuilder::Command &command);

	// socket events
	public:
		void	onBytesWritten(IClientSocket *socket, unsigned int nbBytes);
		void	onSocketReadable(IClientSocket *socket, unsigned int nbBytesToRead);
		void	onSocketClosed(IClientSocket *socket);

	// attributes
	private:
		IClientSocket				*mClient;
		Command						mCurrentCommand;
		CommandPacketBuilder::State	mCurrentState;

};

#pragma once

#include "ICommand.hpp"
#include "IClientSocket.hpp"
#include <qlist.h>
#include <qobject.h>

class CommandPacketBuilder : public QObject, public IClientSocket::OnSocketEvent {

	Q_OBJECT

	// handle build state
	private:
		enum State {
			HEADER,
			CONTENT
		};

	// header
	private:
		static const int	MAGIC_CODE;
		static const int	HEADER_SIZE;

		struct Header {
			int		magicCode;
			char	instructionCode;
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
		void	sendCommand(const ICommand *command);

	// receive command
	signals:
		void	receiveCommand(const ICommand *command);

	// build commands
	private:
		void	fetchCommandHeader(void);
		void	fetchCommandContent(void);

	// socket events
	public:
		void	onBytesWritten(IClientSocket *socket, unsigned int nbBytes) {}
		void	onSocketReadable(IClientSocket *socket, unsigned int nbBytesToRead);
		void	onSocketClosed(IClientSocket *socket);

	// attributes
	private:
		IClientSocket				*mClient;
		ICommand					*mCurrentCommand;
		CommandPacketBuilder::State	mCurrentState;

};

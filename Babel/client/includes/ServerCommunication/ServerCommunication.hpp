#pragma once

#include <qobject.h>
#include "ICommand.hpp"
#include "CommandPacketBuilder.hpp"

class ServerCommunication : public QObject {

	Q_OBJECT

	// ctor - dtor
	public:
		ServerCommunication(void);
		~ServerCommunication(void);

	// coplien form
	private:
		ServerCommunication(const ServerCommunication &) {}
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

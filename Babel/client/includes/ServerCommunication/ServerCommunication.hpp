#pragma once

#include "ICommand.hpp"
#include "CommandPacketBuilder.hpp"

class ServerCommunication {

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
		void	treatCommand(const ICommand &command);

	// attributes
	private:
		CommandPacketBuilder	mCommandPacketBuilder;

};

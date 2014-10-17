#pragma once

#include <QtWidgets/QMainWindow>
#include "IClientSocket.hpp"
#include "IServerSocket.hpp"

class ReceiveSound : public QMainWindow, public IServerSocket::OnSocketEvent, public IClientSocket::OnSocketEvent {
	// default ctor-dtor
	public:
		ReceiveSound(void);
		~ReceiveSound(void);

	// private coplien form
	private:
		ReceiveSound(const ReceiveSound &) {}
		const ReceiveSound &operator=(const ReceiveSound &) { return *this; }

	// start-stop
	public:
		void	onNewConnection(IServerSocket *socket);
		void	onBytesWritten(IClientSocket *socket, unsigned int nbBytes){}
		void	onSocketReadable(IClientSocket *socket);
		void	onSocketClosed(IClientSocket *socket){}

	private:
		IClientSocket *client;
		IServerSocket *server;
};

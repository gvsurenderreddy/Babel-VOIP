#pragma once

#include <QtWidgets/QMainWindow>
#include "IClientSocket.hpp"
#include "IServerSocket.hpp"
#include <QThread>
#include <iostream>

class ReceiveSound : public QMainWindow, public IClientSocket::OnSocketEvent {
	Q_OBJECT
	// default ctor-dtor
	public:
		ReceiveSound(void);
		~ReceiveSound(void);

	// private coplien form
	private:
		ReceiveSound(const ReceiveSound &) {}
		const ReceiveSound &operator=(const ReceiveSound &) { return *this; }

	// public SLOT
		public :
			void	onThreadStart(void);

	// start-stop
	public:
		void	onSocketReadable(IServerSocket *socket);
		void	onNewConnection(IServerSocket *socket);

		void	onBytesWritten(IClientSocket *socket, unsigned int nbBytes) { std::cout << "SEND BYTES " << nbBytes << std::endl; }
		void	onSocketReadable(IClientSocket *socket) {}
		 void	onSocketClosed(IClientSocket *socket) {}

	private:
		IClientSocket *client;
		IServerSocket *server;
};

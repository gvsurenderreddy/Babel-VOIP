#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SimpleWindow.h"
#include "IClientSocket.hpp"
#include "IServerSocket.hpp"

class SimpleWindow : public QMainWindow, public IServerSocket::OnSocketEvent, public IClientSocket::OnSocketEvent {

	Q_OBJECT

	public:
		SimpleWindow(QWidget *parent = 0);
		~SimpleWindow() {}

		void	onBytesWritten(IClientSocket *socket, unsigned int nbBytes);
		void	onSocketReadable(IClientSocket *socket);
		void	onSocketClosed(IClientSocket *socket);
		void	onNewConnection(IServerSocket *socket);

	private:
		Ui::SimpleWindowClass ui;

		/* UDP */
		/*IClientSocket *client;*/

		/* TCP */
		
		IClientSocket *client;
		IServerSocket *server;
		

};

#include "SimpleWindow.hpp"
#include "TcpClient.hpp"
#include "TcpServer.hpp"
#include "UdpClient.hpp"
#include <qbytearray.h>
#include <iostream>

/* TCP */
/*
SimpleWindow::SimpleWindow(QWidget *parent) : QMainWindow(parent) {
	ui.setupUi(this);

	server = new TcpServer;
	client = NULL;

	server->createServer(4242, 1024);
	server->setOnSocketEventListener(this);
}

void	SimpleWindow::onSocketReadable(IClientSocket *socket) {
	IClientSocket::Message msg;

	std::cout << "OnSocketadyRead" << std::endl;
	msg = client->receive(1024);
	std::cout << "READ: " << QString(QByteArray(msg.msg, msg.msgSize)).toStdString() << std::endl;

	msg.msg = "hello world :)\n";
	msg.msgSize = std::string("hello world :)\n").size();
	client->send(msg);
}

void	SimpleWindow::onSocketClosed(IClientSocket *socket) {
	std::cout << "socket closed" << std::endl;
}

void	SimpleWindow::onNewConnection(IServerSocket *socket) {
	if (server->hasClientInQueue()) {
		std::cout << "new connection" << std::endl;
		client = server->getNewClient();
		client->setOnSocketEventListener(this);
	}
}

void	SimpleWindow::onBytesWritten(IClientSocket *socket, unsigned int nbBytes) {
	std::cout << nbBytes << " bytes written" << std::endl;
}
*/

/* UDP */
SimpleWindow::SimpleWindow(QWidget *parent) : QMainWindow(parent) {
	ui.setupUi(this);

	client = new UdpClient;

	client->connect("127.0.0.1", 4243);
	client->setOnSocketEventListener(this);
}

void	SimpleWindow::onSocketReadable(IClientSocket * /*socket*/) {
	IClientSocket::Message msg;

	std::cout << "OnSocketadyRead" << std::endl;
	msg = client->receive(1024);
	std::cout << "READ: " << QString(QByteArray(msg.msg, msg.msgSize)).toStdString() << std::endl;

	msg.msg = "hello world :)\n";
	msg.msgSize = std::string("hello world :)\n").size();
	client->send(msg);
}

void	SimpleWindow::onSocketClosed(IClientSocket * /*socket*/) {
	std::cout << "socket closed" << std::endl;
}

void	SimpleWindow::onBytesWritten(IClientSocket * /*socket*/, unsigned int nbBytes) {
	std::cout << nbBytes << " bytes written" << std::endl;
}

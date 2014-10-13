#include <iostream>
#include "qtnetwork_tests.h"
#include "WindowsTcpClient.hpp"
#include "WindowsTcpServer.hpp"

qtnetwork_tests::qtnetwork_tests(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	server = new WindowsTcpServer;
	client = NULL;

	server->createServer(4242, 1024);
	server->setOnSocketEventListener(this);
}

qtnetwork_tests::~qtnetwork_tests()
{

}

void	qtnetwork_tests::onSocketReadyRead(IClientSocket *socket) {
	std::string buffer;

	std::cout << "OnSocketadyRead" << std::endl;
	if (client->receive(buffer, 1024)) {
		std::cout << "READ: " << buffer << std::endl;
		std::cout << "WRITE: " << client->send("hello world :)\n") << std::endl;
	}
}

void	qtnetwork_tests::onSocketClosed(IClientSocket *socket) {
	std::cout << "socket closed" << std::endl;
}

void	qtnetwork_tests::onNewConnection(IServerSocket *socket) {
	if (server->hasClientInQueue()) {
		std::cout << "new connection" << std::endl;
		client = server->acceptFirstClientInQueue();
		client->setOnSocketEventListener(this);
	}
}

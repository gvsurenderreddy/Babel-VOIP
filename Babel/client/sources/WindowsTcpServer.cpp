#include "WindowsTcpServer.hpp"
#include "WindowsTcpClient.hpp"
#include "SocketException.hpp"

WindowsTcpServer::WindowsTcpServer(void)
	: mListener(NULL) {}

void	WindowsTcpServer::createServer(int port, int queueSize) {
	if (mQTcpServer.listen(QHostAddress::Any, port) == false)
		throw new SocketException("fail QTcpServer::listen");

	mQTcpServer.setMaxPendingConnections(queueSize);

	QObject::connect(&mQTcpServer, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

void	WindowsTcpServer::closeServer(void) {
	if (mQTcpServer.isListening())
		mQTcpServer.close();
}

IClientSocket	*WindowsTcpServer::acceptFirstClientInQueue(void) {
	QTcpSocket *qTcpSocket = mQTcpServer.nextPendingConnection();

	if (qTcpSocket == NULL)
		throw new SocketException("fail QTcpSocket::nextPendingConnection()");

	IClientSocket *clientSocket = new WindowsTcpClient;
	clientSocket->initFromSocket(qTcpSocket);

	return clientSocket;
}

bool	WindowsTcpServer::hasClientInQueue(void) const {
	return mQTcpServer.hasPendingConnections();
}

void	WindowsTcpServer::setOnSocketEventListener(IServerSocket::OnSocketEvent *listener) {
	mListener = listener;
}

void	WindowsTcpServer::onNewConnection(void) {
	if (mListener)
		mListener->onNewConnection(this);
}

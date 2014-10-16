#include "TcpServer.hpp"
#include "TcpClient.hpp"
#include "SocketException.hpp"

TcpServer::TcpServer(void)
	: mListener(NULL) {}

void	TcpServer::createServer(int port, int queueSize) {
	if (mQTcpServer.listen(QHostAddress::Any, port) == false)
		throw new SocketException("fail QTcpServer::listen");

	mQTcpServer.setMaxPendingConnections(queueSize);

	QObject::connect(&mQTcpServer, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

void	TcpServer::closeServer(void) {
	if (mQTcpServer.isListening())
		mQTcpServer.close();
}

IClientSocket	*TcpServer::getNewClient(void) {
	QTcpSocket *qTcpSocket = mQTcpServer.nextPendingConnection();

	if (qTcpSocket == NULL)
		throw new SocketException("fail QTcpSocket::nextPendingConnection");

	IClientSocket *clientSocket = new TcpClient;
	clientSocket->initFromSocket(qTcpSocket);

	return clientSocket;
}

bool	TcpServer::hasClientInQueue(void) const {
	return mQTcpServer.hasPendingConnections();
}

void	TcpServer::setOnSocketEventListener(IServerSocket::OnSocketEvent *listener) {
	mListener = listener;
}

void	TcpServer::onNewConnection(void) {
	if (mListener)
		mListener->onNewConnection(this);
}

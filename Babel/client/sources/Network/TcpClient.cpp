#include "TcpClient.hpp"
#include "SocketException.hpp"
#include <qhostaddress.h>

TcpClient::TcpClient(void)
	: mQTcpSocket(NULL), mIsReadable(false), mListener(NULL) {}

TcpClient::~TcpClient(void) {
	if (mQTcpSocket)
		delete mQTcpSocket;
}

void	TcpClient::connect(const std::string &addr, int port) {
	mQTcpSocket = new QTcpSocket(this);
	mQTcpSocket->connectToHost(QString(addr.c_str()), port);

	if (mQTcpSocket->waitForConnected(-1) == false)
		throw new SocketException("fail QTcpSocket::connectToHost & QTcpSocket::waitForConnected");

	QObject::connect(mQTcpSocket, SIGNAL(readyRead()), this, SLOT(markAsReadable()));
	QObject::connect(mQTcpSocket, SIGNAL(disconnected()), this, SLOT(close()));
	QObject::connect(mQTcpSocket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
}

void	TcpClient::initFromSocket(void *socket) {
	mQTcpSocket = reinterpret_cast<QTcpSocket *>(socket);

	QObject::connect(mQTcpSocket, SIGNAL(readyRead()), this, SLOT(markAsReadable()));
	QObject::connect(mQTcpSocket, SIGNAL(disconnected()), this, SLOT(close()));
	QObject::connect(mQTcpSocket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
}

void	TcpClient::closeClient(void) {
	close();
}

void	TcpClient::close(void) {
	if (mQTcpSocket)
		mQTcpSocket->disconnectFromHost();

	if (mListener)
		mListener->onSocketClosed(this);
}

void	TcpClient::send(const IClientSocket::Message &message) {
	int ret = mQTcpSocket->write(message.msg, message.msgSize);

	if (ret == -1)
		throw new SocketException("fail QTcpSocket::write");
}

IClientSocket::Message	TcpClient::receive(unsigned int sizeToRead) {
	IClientSocket::Message message;

	if (!isReadable())
		throw new SocketException("Socket not readable");

	message.msg = new char[sizeToRead + 1];
	message.msgSize = mQTcpSocket->read(message.msg, sizeToRead);
	message.host = (mQTcpSocket->peerAddress()).toString().toStdString();
	message.port = mQTcpSocket->peerPort();
	mIsReadable = false;

	if (message.msgSize == -1)
		throw new SocketException("fail QTcpSocket::read");

	return message;
}

bool	TcpClient::isReadable(void) const {
	return mIsReadable;
}

bool	TcpClient::isWritable(void) const {
	return true;
}

void	TcpClient::markAsReadable(void) {
	mIsReadable = true;

	if (mListener)
		mListener->onSocketReadable(this);
}

void	TcpClient::bytesWritten(qint64 nbBytes) {
	if (mListener)
		mListener->onBytesWritten(this, nbBytes);
}

void	TcpClient::setOnSocketEventListener(OnSocketEvent *listener) {
	mListener = listener;
}

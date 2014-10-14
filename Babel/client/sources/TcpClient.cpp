#include "TcpClient.hpp"
#include "SocketException.hpp"

TcpClient::TcpClient(void)
	: mQTcpSocket(NULL), mListener(NULL), mIsReadable(false) {}

TcpClient::~TcpClient(void) {
	if (mQTcpSocket)
		delete mQTcpSocket;
}

void	TcpClient::connectToServer(const std::string &addr, int port) {
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


void	TcpClient::send(const std::string &data) {
	int ret = mQTcpSocket->write(data.c_str());

	if (ret == -1)
		throw new SocketException("fail QTcpSocket::write");
}

void	TcpClient::receive(std::string &data, unsigned int sizeToRead) {
	if (!isReadable())
		throw new SocketException("Socket not readable");

	char *readBuffer = new char[sizeToRead + 1];
	int ret = mQTcpSocket->read(readBuffer, sizeToRead);
	mIsReadable = false;

	if (ret == -1)
		throw new SocketException("fail QTcpSocket::read");

	readBuffer[ret] = '\0';
	data = readBuffer;
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

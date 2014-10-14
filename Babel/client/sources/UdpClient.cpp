#include "UdpClient.hpp"
#include "SocketException.hpp"

UdpClient::UdpClient(void)
	: mQUdpSocket(NULL), mListener(NULL), mIsReadable(false) {}

UdpClient::~UdpClient(void) {
	if (mQUdpSocket)
		delete mQUdpSocket;
}

void	UdpClient::connectToServer(const std::string &addr, int port) {
	mQUdpSocket = new QUdpSocket(this);
	mQUdpSocket->connectToHost(QString(addr.c_str()), port);

	if (mQUdpSocket->waitForConnected(-1) == false)
		throw new SocketException("fail QTcpSocket::connectToHost & QTcpSocket::waitForConnected");

	QObject::connect(mQUdpSocket, SIGNAL(readyRead()), this, SLOT(markAsReadable()));
	QObject::connect(mQUdpSocket, SIGNAL(disconnected()), this, SLOT(close()));
	QObject::connect(mQUdpSocket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
}

void	UdpClient::initFromSocket(void *socket) {
	mQUdpSocket = reinterpret_cast<QUdpSocket *>(socket);

	QObject::connect(mQUdpSocket, SIGNAL(readyRead()), this, SLOT(markAsReadable()));
	QObject::connect(mQUdpSocket, SIGNAL(disconnected()), this, SLOT(close()));
}

void	UdpClient::closeClient(void) {
	close();
}

void	UdpClient::close(void) {
	if (mQUdpSocket)
		mQUdpSocket->disconnectFromHost();

	if (mListener)
		mListener->onSocketClosed(this);
}


void	UdpClient::send(const std::string &data) {
	int ret = mQUdpSocket->write(data.c_str());

	if (ret == -1)
		throw new SocketException("fail QTcpSocket::write");
}

void	UdpClient::receive(std::string &data, unsigned int sizeToRead) {
	if (!isReadable())
		throw new SocketException("Socket not readable");

	char *readBuffer = new char[sizeToRead + 1];
	int ret = mQUdpSocket->read(readBuffer, sizeToRead);
	mIsReadable = false;

	if (ret == -1)
		throw new SocketException("fail QTcpSocket::read");

	readBuffer[ret] = '\0';
	data = readBuffer;
}

bool	UdpClient::isReadable(void) const {
	return mIsReadable;
}

bool	UdpClient::isWritable(void) const {
	return true;
}

void	UdpClient::markAsReadable(void) {
	mIsReadable = true;

	if (mListener)
		mListener->onSocketReadable(this);
}

void	UdpClient::bytesWritten(qint64 nbBytes) {
	if (mListener)
		mListener->onBytesWritten(this, nbBytes);
}

void	UdpClient::setOnSocketEventListener(OnSocketEvent *listener) {
	mListener = listener;
}

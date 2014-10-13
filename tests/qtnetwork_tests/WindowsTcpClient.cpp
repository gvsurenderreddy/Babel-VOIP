#include "WindowsTcpClient.hpp"
#include "SocketException.hpp"

WindowsTcpClient::WindowsTcpClient(void)
	: mQTcpSocket(NULL), mListener(NULL), mIsReadable(false) {}

WindowsTcpClient::~WindowsTcpClient(void) {
	if (mQTcpSocket)
		delete mQTcpSocket;
}

void	WindowsTcpClient::connectToServer(const std::string &addr, int port) {
	mQTcpSocket = new QTcpSocket(this);
	mQTcpSocket->connectToHost(QString(addr.c_str()), port);

	if (mQTcpSocket->waitForConnected(-1) == false)
		throw new SocketException("fail QTcpSocket::connectToHost & QTcpSocket::waitForConnected");

	QObject::connect(mQTcpSocket, SIGNAL(readyRead()), this, SLOT(markAsReadable()));
	QObject::connect(mQTcpSocket, SIGNAL(disconnected()), this, SLOT(close()));
}

void	WindowsTcpClient::initFromSocket(void *socket) {
	mQTcpSocket = reinterpret_cast<QTcpSocket *>(socket);

	QObject::connect(mQTcpSocket, SIGNAL(readyRead()), this, SLOT(markAsReadable()));
	QObject::connect(mQTcpSocket, SIGNAL(disconnected()), this, SLOT(close()));
}

void	WindowsTcpClient::closeClient(void) {
	close();
}

void	WindowsTcpClient::close(void) {
	if (mQTcpSocket)
		mQTcpSocket->disconnectFromHost();

	if (mListener)
		mListener->onSocketClosed(this);
}


unsigned int	WindowsTcpClient::send(const std::string &data) {
	int ret = mQTcpSocket->write(data.c_str());

	if (ret == -1)
		throw new SocketException("fail QTcpSocket::write");

	return ret;
}

unsigned int	WindowsTcpClient::receive(std::string &data, unsigned int sizeToRead) {
	if (!isReadable())
		throw new SocketException("Socket not readable");

	char *readBuffer = new char[sizeToRead + 1];
	int ret = mQTcpSocket->read(readBuffer, sizeToRead);
	mIsReadable = false;

	if (ret == -1)
		throw new SocketException("fail QTcpSocket::read");

	readBuffer[ret] = '\0';
	data = readBuffer;

	return ret;
}

bool	WindowsTcpClient::isReadable(void) const {
	return mIsReadable;
}

void	WindowsTcpClient::markAsReadable(void) {
	mIsReadable = true;

	if (mListener)
		mListener->onSocketReadyRead(this);
}

void	WindowsTcpClient::setOnSocketEventListener(OnSocketEvent *listener) {
	mListener = listener;
}

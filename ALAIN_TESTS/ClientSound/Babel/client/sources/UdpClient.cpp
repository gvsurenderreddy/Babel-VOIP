#include "UdpClient.hpp"
#include "SocketException.hpp"

UdpClient::UdpClient(void)
	: mQUdpSocket(NULL), mListener(NULL), mIsReadable(false) {}

UdpClient::~UdpClient(void) {
	if (mQUdpSocket)
		delete mQUdpSocket;
}

void	UdpClient::connect(const std::string &/*addr*/, int port) {
	mQUdpSocket = new QUdpSocket(this);

	if (mQUdpSocket->bind(QHostAddress::LocalHost, port) == false)
		throw new SocketException("fail QUdpSocket::bind");

	QObject::connect(mQUdpSocket, SIGNAL(readyRead()), this, SLOT(markAsReadable()));
	QObject::connect(mQUdpSocket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
}

void	UdpClient::initFromSocket(void *socket) {
	mQUdpSocket = reinterpret_cast<QUdpSocket *>(socket);

	QObject::connect(mQUdpSocket, SIGNAL(readyRead()), this, SLOT(markAsReadable()));
	QObject::connect(mQUdpSocket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
}

void	UdpClient::closeClient(void) {
	close();
}

void	UdpClient::close(void) {
	if (mQUdpSocket)
		mQUdpSocket->close();

	if (mListener)
		mListener->onSocketClosed(this);
}


void	UdpClient::send(const IClientSocket::Message &message) {
	int ret = mQUdpSocket->writeDatagram(message.msg, message.msgSize, QHostAddress(QString(message.host.c_str())), message.port);

	if (ret == -1)
		throw new SocketException("fail QTcpSocket::write");
}

IClientSocket::Message	UdpClient::receive(unsigned int sizeToRead) {
	IClientSocket::Message message;
	QHostAddress host;
	quint16 port;

	if (!isReadable())
		throw new SocketException("Socket not readable");

	message.msg = new char[sizeToRead + 1];
	message.msgSize = mQUdpSocket->readDatagram(message.msg, sizeToRead, &host, &port);
	message.host = host.toString().toStdString();
	message.port = port;
	mIsReadable = false;

	if (message.msgSize == -1)
		throw new SocketException("fail QTcpSocket::read");

	return message;
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

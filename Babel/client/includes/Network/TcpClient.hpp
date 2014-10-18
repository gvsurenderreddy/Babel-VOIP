#pragma once

#include "IClientSocket.hpp"
#include <QtNetwork/qtcpsocket.h>

class TcpClient : public QObject, public IClientSocket {

	Q_OBJECT

	// default ctor-dtor
	public:
		TcpClient(void);
		~TcpClient(void);

	// private coplien form
	private:
		TcpClient(const TcpClient &) : QObject() {}
		const TcpClient &operator=(const TcpClient &) { return *this; }

	// start-stop
	public:
		void	connect(const std::string &addr, int port);
		void	initFromSocket(void *socket);
		void	closeClient(void);

	// set listener
	public:
		void	setOnSocketEventListener(IClientSocket::OnSocketEvent *listener);

	// recv / send
	public:
		void	send(const Message &message);
		Message	receive(unsigned int sizeToRead);

	// handle state
	public:
		bool	isReadable(void) const;
		bool	isWritable(void) const;

	// slots
	private slots:
		void	bytesWritten(qint64 nbBytes);
		void	markAsReadable(void);
		void	close(void);

	// attributes
	private:
		QTcpSocket	*mQTcpSocket;
		bool		mIsReadable;

		IClientSocket::OnSocketEvent	*mListener;

};

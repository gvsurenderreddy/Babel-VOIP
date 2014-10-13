#pragma once

#include "IClientSocket.hpp"
#include <QtNetwork\qtcpsocket.h>

class WindowsTcpClient : public QObject, public IClientSocket {

	Q_OBJECT

	// default ctor-dtor
	public:
		WindowsTcpClient(void);
		~WindowsTcpClient(void);

	// private coplien form
	private:
		WindowsTcpClient(const WindowsTcpClient &) {}
		const WindowsTcpClient &operator=(const WindowsTcpClient &) { return *this; }

	// start-stop
	public:
		void	connectToServer(const std::string &addr, int port);
		void	initFromSocket(void *socket);
		void	closeClient(void);

	// set listener
	public:
		void	setOnSocketEventListener(IClientSocket::OnSocketEvent *listener);

	// recv / send
	public:
		unsigned int	send(const std::string &data);
		unsigned int	receive(std::string &data, unsigned int sizeToRead);

	// handle state
	public:
		bool	isReadable(void) const;

	// slots
	private slots:
		void	markAsReadable(void);
		void	close(void);

	// attributes
	private:
		QTcpSocket	*mQTcpSocket;
		bool		mIsReadable;

		IClientSocket::OnSocketEvent	*mListener;

};

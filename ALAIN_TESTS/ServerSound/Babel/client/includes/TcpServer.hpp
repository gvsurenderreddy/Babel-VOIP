#pragma once

#include "IServerSocket.hpp"
#include <QtNetwork/QTcpServer>

class TcpServer : public QObject, public IServerSocket {

	Q_OBJECT

	// default ctor-dtor
	public:
		TcpServer(void);
		~TcpServer(void) {}

	// private coplien form
	private:
		TcpServer(const TcpServer &) {}
		const TcpServer &operator=(const TcpServer &) { return *this; }

	// init
	public:
		void	createServer(int port, int queueSize);
		void	closeServer(void);

	// listeners
	public:
		void	setOnSocketEventListener(IServerSocket::OnSocketEvent *listener);

	// slots
	private slots:
		void	onNewConnection(void);

	// handle clients
	public:
		IClientSocket	*getNewClient(void);
		bool			hasClientInQueue(void) const;

	// attributes
	private:
		QTcpServer mQTcpServer;
		IServerSocket::OnSocketEvent *mListener;

};

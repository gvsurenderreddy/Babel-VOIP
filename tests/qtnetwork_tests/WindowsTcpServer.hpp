#pragma once

#include "IServerSocket.hpp"
#include <QtNetwork/QTcpServer>

class WindowsTcpServer : public QObject, public IServerSocket {

	Q_OBJECT

	// default ctor-dtor
	public:
		WindowsTcpServer(void);
		~WindowsTcpServer(void) {}

	// private coplien form
	private:
		WindowsTcpServer(const WindowsTcpServer &) {}
		const WindowsTcpServer &operator=(const WindowsTcpServer &) { return *this; }

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
		IClientSocket	*acceptFirstClientInQueue(void);
		bool			hasClientInQueue(void) const;

	// attributes
	private:
		QTcpServer	mQTcpServer;

		IServerSocket::OnSocketEvent *mListener;

};

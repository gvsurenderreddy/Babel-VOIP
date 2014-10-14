#pragma once

#include <string>

class IClientSocket {

	// CallBack Interface
	public:
		class OnSocketEvent {
			public:
				virtual	~OnSocketEvent() {}
				virtual	void	onBytesWritten(IClientSocket *socket, unsigned int nbBytes) = 0;
				virtual void	onSocketReadable(IClientSocket *socket) = 0;
				virtual void	onSocketClosed(IClientSocket *socket) = 0;
		};

	// virtual destructor
	public:
		virtual ~IClientSocket(void) {}

	// start - stop
	public:
		virtual void	connectToServer(const std::string &addr, int port) = 0;
		virtual void	initFromSocket(void *socket) = 0;
		virtual	void	closeClient(void) = 0;

	// recv / send
	public:
		virtual void	send(const std::string &data) = 0;
		virtual void	receive(std::string &data, unsigned int sizeToRead) = 0;

	// handle state
	public:
		virtual bool	isWritable(void) const = 0;
		virtual bool	isReadable(void) const = 0;

	// set listener
	public:
		virtual void	setOnSocketEventListener(IClientSocket::OnSocketEvent *listener) = 0;

};

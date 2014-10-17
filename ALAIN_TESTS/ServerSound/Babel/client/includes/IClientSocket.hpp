#pragma once

#include <string>

class IClientSocket {

	// Message Data
	public:
		struct Message {
			char		*msg;
			int			msgSize;
			std::string	host;
			int			port;
		};

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
		virtual void	connect(const std::string &addr, int port) = 0;
		virtual void	initFromSocket(void *socket) = 0;
		virtual	void	closeClient(void) = 0;

	// recv / send
	public:
		virtual void	send(const Message &message) = 0;
		virtual Message	receive(unsigned int sizeToRead) = 0;

	// handle state
	public:
		virtual bool	isWritable(void) const = 0;
		virtual bool	isReadable(void) const = 0;

	// set listener
	public:
		virtual void	setOnSocketEventListener(IClientSocket::OnSocketEvent *listener) = 0;

};

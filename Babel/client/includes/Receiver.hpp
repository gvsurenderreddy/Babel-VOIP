#pragma once

#include <qobject.h>
#include "ISoundDevice.hpp"
#include "IClientSocket.hpp"
#include "EncodeManager.hpp"

class Receiver : public QObject, public IClientSocket::OnSocketEvent {

	// ctor - dtor
	public:
		Receiver(void);
		~Receiver(void);

	// coplien form
	private:
		Receiver(const Receiver &) : QObject() {}
		const Receiver &operator=(const Receiver &) { return *this; }

	// start
	public:
		void	start(void);

	// socket callbacks
	public:
		void	onBytesWritten(IClientSocket *socket, unsigned int nbBytes) {}
		void	onSocketReadable(IClientSocket *socket);
		void	onSocketClosed(IClientSocket *socket) {}

	// attributes
	private:
		IClientSocket	*mClient;
		ISoundDevice	*mOutput;
		EncodeManager	mEncodeManager;

};

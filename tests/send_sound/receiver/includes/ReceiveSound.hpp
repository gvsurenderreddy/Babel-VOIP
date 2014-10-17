#pragma once

#include "IClientSocket.hpp"
#include "SoundOutputDevice.hpp"

class ReceiveSound : public IClientSocket::OnSocketEvent {

	// default ctor-dtor
	public:
		ReceiveSound(void);
		~ReceiveSound(void) {}

	// private coplien form
	private:
		ReceiveSound(const ReceiveSound &) {}
		const ReceiveSound &operator=(const ReceiveSound &) { return *this; }

	// start-stop
	public:
		void	onBytesWritten(IClientSocket *socket, unsigned int nbBytes){}
		void	onSocketReadable(IClientSocket *socket);
		void	onSocketClosed(IClientSocket *socket){}

	private:
		IClientSocket *client;
		SoundOutputDevice output;

};

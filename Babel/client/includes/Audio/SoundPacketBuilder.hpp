#pragma once

#include "Sound.hpp"
#include "IClientSocket.hpp"
#include <qobject.h>

class SoundPacketBuilder : public QObject, public IClientSocket::OnSocketEvent {

	Q_OBJECT

	// ctor - dtor
	public:
		SoundPacketBuilder(void);
		~SoundPacketBuilder(void);

	// coplien form
	private:
		SoundPacketBuilder(const SoundPacketBuilder &) {}
		const SoundPacketBuilder &operator=(const SoundPacketBuilder &) { return *this; }
	// send sound
	public slots:
		void	sendSound(const Sound::Encoded &command);

	public:
		void	acceptPacketsFrom(const QString &addr, int port);

	// receive sound
	signals:
		void	receiveSound(const Sound::Encoded &sound);

	// socket events
	public:
		void	onBytesWritten(IClientSocket *socket, unsigned int nbBytes);
		void	onSocketReadable(IClientSocket *socket, unsigned int nbBytesToRead);
		void	onSocketClosed(IClientSocket *socket);

	// attributes
	private:
		IClientSocket	*mClient;
		QString			mAcceptedHost;
		int				mAcceptedPort;

		static const int DEFAULT_BABEL_CALL_PORT;

};

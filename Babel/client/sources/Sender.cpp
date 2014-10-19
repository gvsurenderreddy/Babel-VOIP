#include "Sender.hpp"
#include "UdpClient.hpp"
#include "SoundInputDevice.hpp"

Sender::Sender(void)
	: mClient(NULL), mInput(NULL)
{
	mClient = new UdpClient;
	mInput = new SoundInputDevice;

	mClient->connect("127.0.0.1", 4242);
}

Sender::~Sender(void) {
	if (mClient)
		delete mClient;

	if (mInput)
		delete mInput;
}

void	Sender::run(void) {
	Sound::Decoded sound;

	mInput->startStream();
	while (true) {
		*mInput >> sound;

		if (sound.buffer) {
			Sound::Encoded encoded = mEncodeManager.encode(sound);

			IClientSocket::Message message;
			message.host = "127.0.0.1";
			message.port = 4243;
			message.msg = reinterpret_cast<char *>(encoded.buffer);
			message.msgSize = encoded.size;

			mClient->send(message);
		}
	}
}

#include "SoundInputDevice.hpp"
#include "ReceiveSound.hpp"
#include "UdpClient.hpp"
#include "myThread.hpp"

ReceiveSound::ReceiveSound(void){
	client = new UdpClient;
	client->connect("127.0.0.1", 4243);

	MyThread *thread = new MyThread(this);
	thread->start();
}

void ReceiveSound::onThreadStart(void) {
	SoundInputDevice input;
	input.startStream();

	IClientSocket::Message msg;
	msg.host = "127.0.0.1";
	msg.port = 4242;

	while (true) {
		Sound::Decoded *sound = NULL;
		input >> sound;
		if (sound) {
			msg.msg = new char[sound->size  * sizeof(float)];
			msg.msgSize = sound->size * sizeof(float);
			memcpy(msg.msg, sound->buffer, sound->size * sizeof(float));
			client->send(msg);
		}
	}
	input.stopStream();
}

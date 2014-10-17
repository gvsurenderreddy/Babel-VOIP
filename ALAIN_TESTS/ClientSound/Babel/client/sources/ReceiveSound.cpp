#include "SoundInputDevice.hpp"
#include "SoundOutputDevice.hpp"
#include "ReceiveSound.hpp"
#include "TcpClient.hpp"
#include "TcpServer.hpp"
#include "myThread.hpp"
#include <iostream>
#include <QThread>


ReceiveSound::ReceiveSound(void){
	client = new TcpClient;

	client->connect("127.0.0.1", 4242);
	client->setOnSocketEventListener(this);
	MyThread *thread = new MyThread(this);

	thread->start();
}

ReceiveSound::~ReceiveSound(void) {}

void ReceiveSound::onThreadStart(void) {
	SoundInputDevice input;
	IClientSocket::Message msg;

	Sound::Decoded *sound = new Sound::Decoded;
	std::cout << "PREND SON start thread" << std::endl;
	input.startStream();
	while (true){
		input >> sound;
		if (sound) {
			//std::cout << "send sound" << std::endl;
			char *message = new char[sound->size  * sizeof(float)];
			memcpy(message, sound->buffer, sound->size * sizeof(float));
			msg.msg = message;
			msg.msgSize = sound->size * sizeof(float);
			client->send(msg);
		}
	}
	input.stopStream();
}

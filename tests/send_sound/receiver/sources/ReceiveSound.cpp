#include "ReceiveSound.hpp"
#include "UdpClient.hpp"
#include <iostream>


ReceiveSound::ReceiveSound(void){
	client = new UdpClient;
	client->connect("127.0.0.1", 4242);
	client->setOnSocketEventListener(this);

	output.startStream();
}

void	ReceiveSound::onSocketReadable(IClientSocket *socket){
	IClientSocket::Message msg;
	msg = client->receive(3840);

	Sound::Decoded *sound = new Sound::Decoded;
	sound->buffer = new float[msg.msgSize / sizeof(float)];
	sound->size = msg.msgSize / sizeof(float);
	memcpy(sound->buffer, msg.msg, msg.msgSize);

	output << sound;
}
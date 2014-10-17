#include "SoundInputDevice.hpp"
#include "SoundOutputDevice.hpp"
#include "ReceiveSound.hpp"
#include "TcpClient.hpp"
#include "TcpServer.hpp"
#include <iostream>


ReceiveSound::ReceiveSound(void){
	server = new TcpServer;

	server->createServer(4242, 1024);
	server->setOnSocketEventListener(this);
}

ReceiveSound::~ReceiveSound(void) {}

void	ReceiveSound::onNewConnection(IServerSocket *socket){
	if (server->hasClientInQueue()) {
		std::cout << "new connection" << std::endl;
		client = server->getNewClient();
		client->setOnSocketEventListener(this);
	}
}

void	ReceiveSound::onSocketReadable(IClientSocket *socket){
	IClientSocket::Message msg;
	SoundOutputDevice output;
	Sound::Decoded *sound = new Sound::Decoded;
	std::cout << "READABLE" << std::endl;
	msg = client->receive(1024);
	float *buffer = new float[msg.msgSize / sizeof(float)];
	memcpy(buffer, msg.msg, msg.msgSize / sizeof(float));

	output.startStream();
	if (sound) {
		output << sound;
	}
	output.stopStream();
}
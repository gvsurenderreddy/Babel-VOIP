#include "ServerManager.hpp"
#include "IClientSocket.hpp"
#include "IServerSocket.hpp"

#include <iostream>

const unsigned int ServerManager::LISTEN_PORT = 4242;
const unsigned int ServerManager::QUEUE_SIZE = 1024;

const unsigned int ServerManager::BUFFER_SIZE = 1024;

ServerManager::ServerManager(IServerSocket* serverSocket) : mServerSocket(serverSocket) {
    mServerSocket->createServer(ServerManager::LISTEN_PORT, ServerManager::QUEUE_SIZE);
    mServerSocket->setOnSocketEventListener(this);
    mServerSocket->run();
}

ServerManager::~ServerManager() {
    std::cout << __FUNCTION__ << std::endl;
    mServerSocket->closeServer();
    delete mServerSocket;
}

void ServerManager::onNewConnection(IServerSocket *socket) {
    std::cout << __FUNCTION__ << std::endl;
    if (socket->hasClientInQueue()) 
        mClientsSocket.push_back(socket->getNewClient());
}

void ServerManager::onSocketReadyRead(IClientSocket *socket) {
    std::cout << __FUNCTION__ << std::endl;
    IClientSocket::Message message = socket->receive(ServerManager::BUFFER_SIZE);
    std::cout << "Received : '" << message.msg << "'" << std::endl;
}

void ServerManager::onSocketClosed(IClientSocket *socket) {
    std::cout << __FUNCTION__ << std::endl;

    std::list<IClientSocket*>::iterator it = mClientsSocket.begin();
    std::list<IClientSocket*>::iterator it_end = mClientsSocket.begin();

    while (it != it_end)
    {
        if (*it == socket)
        {
            delete (*it);
            it = mClientsSocket.erase(it);
        }
        else
            ++it;
    }
}

void ServerManager::onBytesWriten(IClientSocket *socket, unsigned int nbBytes) {
    std::cout << __FUNCTION__ << std::endl;
    (void)socket;
    (void)length;
}

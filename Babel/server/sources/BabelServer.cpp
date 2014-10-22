#include "BabelServer.hpp"
#include "IServerSocket.hpp"
#include "TcpServer.hpp"

#include <iostream>

const unsigned int BabelServer::BABEL_DEFAULT_LISTEN_PORT = 4242;
const unsigned int BabelServer::BABEL_DEFAULT_QUEUE_SIZE = 128;

BabelServer::BabelServer() : mServerSocket(NULL)
{
    std::cout << __FUNCTION__ << std::endl;
}

BabelServer::~BabelServer()
{
    std::cout << __FUNCTION__ << std::endl;
    if (mServerSocket)
        delete mServerSocket;
}

void BabelServer::run()
{
    std::cout << __FUNCTION__ << std::endl;
    mServerSocket = reinterpret_cast<IServerSocket*>(new TcpServer);
    mServerSocket->setOnSocketEventListener(this);
    mServerSocket->createServer(BabelServer::BABEL_DEFAULT_LISTEN_PORT, BabelServer::BABEL_DEFAULT_QUEUE_SIZE);
    mServerSocket->run();
}

void BabelServer::onNewConnection(IServerSocket *socket)
{
    std::cout << __FUNCTION__ << std::endl;
    if (socket->hasClientInQueue())
        mClientsSocket.push_back(socket->getNewClient());
}

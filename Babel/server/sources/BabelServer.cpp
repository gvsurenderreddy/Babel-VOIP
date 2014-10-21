#include "BabelServer.hpp"
#include "IServerSocket.hpp"
#include "TcpServer.hpp"

#include <iostream>

const unsigned int BabelServer::BABEL_DEFAULT_LISTEN_PORT = 4242;
const unsigned int BabelServer::BABEL_DEFAULT_QUEUE_SIZE = 128;

BabelServer::BabelServer() : mServerSocket(NULL)
{

}

BabelServer::~BabelServer()
{
    if (mServerSocket)
        delete mServerSocket;
}

void BabelServer::run()
{
    mServerSocket = reinterpret_cast<IServerSocket*>(new TcpServer);
    mServerSocket->setOnSocketEventListener(this);
    mServerSocket->createServer(BabelServer::BABEL_DEFAULT_LISTEN_PORT, BabelServer::BABEL_DEFAULT_QUEUE_SIZE);
    mServerSocket->run();
}

void BabelServer::onNewConnection(IServerSocket *socket)
{
    if (socket->hasClientInQueue())
        mClientsSocket.push_back(socket->getNewClient());
}

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

/*
** OnClientEvent
*/
bool BabelServer::onSubscribe(const std::string &acount, const std::string &password){
	acount;
	password;
	return (true);
}

bool BabelServer::onConnect(const std::string &account, const std::string &password){
	account;
	password;
	return (true);
}

void BabelServer::onDisconnect(const std::string &account){
	account;
}

const std::string &BabelServer::onGetContact(const std::list<std::string> &contacts){
	contacts;
	return ("");
}

bool BabelServer::onUpdate(const std::string &account, const std::string &password){
	password;
	account;
	return (true);
}

bool BabelServer::onAddContact(const std::string &account){
	account;
	return (true);
}

void BabelServer::DellContact(const std::string &args){
	args;
}

void BabelServer::onAcceptContact(const bool &accept, const std::string &account){
	accept;
	account;
}

void BabelServer::onCallSomeone(const std::string &account){
	account;
}

void BabelServer::onHangCall(const bool &hang, const std::string &account){
	hang;
	account;
}
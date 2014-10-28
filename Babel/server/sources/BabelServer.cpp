#include "BabelServer.hpp"
#include "IServerSocket.hpp"
#include "TcpServer.hpp"

#include <iomanip>
#include <iostream>
#include <fstream>
#include <algorithm>


#include <boost/filesystem.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

const unsigned int BabelServer::BABEL_DEFAULT_LISTEN_PORT = 4243;
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

void BabelServer::onNewConnection(IServerSocket *serverSocket)
{
    if (serverSocket->hasClientInQueue())
        mClients.push_back(new Client(serverSocket->getNewClient(), *this));
}

/*
** OnClientEvent
*/
bool BabelServer::onSubscribe(const std::string &account, const std::string &password)
{
    /*
    const std::string& filename = "user/" + account + ".xml";

    if (boost::filesystem::exists(filename) == true)
        return false;

    BabelServer::Account newAccount(account, password);

    std::ofstream ofs(filename);
    if (!ofs.good() || ofs.fail())
        return false;
    
    boost::archive::xml_oarchive oa(ofs);
    oa << newAccount;
    */
    return (true);
}

bool BabelServer::onConnect(const std::string &account, const std::string &password){

    std::cout << "account: '" << account << "'" << std::endl;
    std::cout << "password: '" << password << "'" << std::endl;
    /*
    const std::string& filename = "user/" + account + ".xml";

    if (boost::filesystem::exists(filename) == false)
        return false;

    BabelServer::Account wantedAccount;

    std::ifstream ifs(filename);
    if (!ifs.good() || ifs.fail())
        return false;

    boost::archive::xml_iarchive ia(ifs);
    ia >> wantedAccount;

    if (wantedAccount.mPassword != password)
        return false;
        */
    return true;
}

void BabelServer::onDisconnect(const std::string &account){

    auto it = std::find_if(mClients.begin(), mClients.end(), [&](Client* client)
    { return client->getName() == account; });
    if (mClients.end() != it)
    {
        // notify each of his contacts
        std::for_each((*it)->getContact().begin(), (*it)->getContact().end(), [this](const std::string &account)
        {
            auto it = std::find_if(mClients.begin(), mClients.end(), [&](Client* client) { return client->getName() == account; });
            if (mClients.end() != it) // check if he is here
            {
                // envoyer une commande pour indiquer aux clients que un de ses contacts s'est deconnect�
            }
        });
        // (*it)->setConnected(false); // set the client to disconnect state
    }
}

const std::string &BabelServer::onGetContact(const std::list<std::string> &contacts){
    contacts;
    std::string test = "";
    return (test);
}

bool BabelServer::onUpdate(const std::string &account, const std::string &password, const std::string &currentAccount){
	/*
	trouver le comte avec CurrentAccount
	changer mdp / nom de comte du comte trouver
	erreur si account n'existe pas
	erreur taille de mot de passe 6
	*/
	
	password;
    account;
	currentAccount;
    return (true);
}

bool BabelServer::onAddContact(const std::string &account){
	std::vector<std::string> args;

	/*
	trouver le compte correspondant lui faire une demande d'ajout
	via compte->handleCmd(Icommand::ADD, args)
	erreur si account n'exist pas
	*/

    args.push_back(account);
    return (true);
}

bool BabelServer::DellContact(const std::string &account){
	std::vector<std::string> args;
	/*
	trouver le compte correspondant lui notifier du delete
	via compte->handleCmd(Icommand::DEll, args)
	erreur si account n'exist pas
	*/

	args.push_back(account);
	return true;
}

bool BabelServer::onAcceptContact(bool accept, const std::string &account){
    accept;
    account;
	return true;
}

void BabelServer::onCallSomeone(const std::string &account){
    account;
}

void BabelServer::onHangCall(const bool &hang, const std::string &account){
    hang;
    account;
}

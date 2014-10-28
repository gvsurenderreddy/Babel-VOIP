#include "BabelServer.hpp"
#include "IServerSocket.hpp"
#include "TcpServer.hpp"
#include "Database.hpp"

#include <iomanip>
#include <iostream>
#include <fstream>
#include <algorithm>

/*
#include <boost/filesystem.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
*/
const unsigned int BabelServer::BABEL_DEFAULT_LISTEN_PORT = 4243;
const unsigned int BabelServer::BABEL_DEFAULT_QUEUE_SIZE = 128;

BabelServer::BabelServer() : mServerSocket(NULL)
{
    boost::filesystem::path abs_path = boost::filesystem::complete(Database::FOLDER);
    if (!(boost::filesystem::exists(abs_path)))
        boost::filesystem::create_directory(abs_path);
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
    std::cout << std::endl << "Une ip vient de se connecté au port du serveur" << std::endl << std::endl;
    if (serverSocket->hasClientInQueue())
        mClients.push_back(new Client(serverSocket->getNewClient(), *this));
}

bool BabelServer::onSubscribe(const std::string &account, const std::string &pseudo, const std::string &password)
{
    std::cout << __FUNCTION__ << std::endl;

    boost::filesystem::path abs_path = boost::filesystem::complete(Database::FOLDER + account + Database::EXTENSION);
    std::string abs_path_str = abs_path.string();

    const std::string& filename = Database::FOLDER + account + Database::EXTENSION;

    if (boost::filesystem::exists(filename) == true)
    {
        std::cerr << "account '" << account << "' is already taken (filename: <" << filename << ">)" << std::endl;
        return false;
    }

    std::ofstream ofs(filename);

    if (!ofs.good() || ofs.fail())
    {
        std::cerr << "ofs.good|fail had failed" << std::endl;
        return false;
    }

    Database::Account userCreated;

    userCreated.setLogin(account);
    userCreated.setPassword(password);
    userCreated.setPseudo(pseudo);

    bool ret;

    try
    {
        boost::archive::xml_oarchive oa(ofs);
        oa << BOOST_SERIALIZATION_NVP(userCreated);
        ret = true;
        std::cerr << "Inscription de account:'" << account << "' password:'" << password << "' pseudo:'" << pseudo << "'" << std::endl;
    }
    catch (const boost::archive::archive_exception& e)
    {
        std::cerr << "failed to serialize Database::Account with xml_oarchive: " << e.what();
        ofs.setstate(std::ios::failbit);
        ret = false;
    }

    ofs.close();

    return (ret);
}

bool BabelServer::onConnect(const std::string &account, const std::string &password)
{
    std::cout << __FUNCTION__ << std::endl;

    std::cout << "Tentative de connexion:" << std::endl;
    std::cout << " - Account : '" << account << "'" << std::endl;
    std::cout << " - Password: '" << password << "'" << std::endl;

    boost::filesystem::path abs_path = boost::filesystem::complete(Database::FOLDER + account + Database::EXTENSION);
    std::string abs_path_str = abs_path.string();

    const std::string& filename = Database::FOLDER + account + Database::EXTENSION;

    if (boost::filesystem::exists(filename) == false)
    {
        std::cerr << "account '" << account << "' doesn't exist (filename: <" << filename << ">)" << std::endl;
        return false;
    }

    std::ifstream ifs(filename);

    if (!ifs.good() || ifs.fail())
    {
        std::cerr << "ifs.good|fail had failed" << std::endl;
        return false;
    }

    Database::Account userSelected;

    bool ret;

    try
    {
        boost::archive::xml_iarchive ia(ifs);
        ia >> BOOST_SERIALIZATION_NVP(userSelected);
        std::cout << "Fichier:" << std::endl;
        std::cout << " - Account : '" << userSelected.getLogin() << "'" << std::endl;
        std::cout << " - Password: '" << userSelected.getPassword() << "'" << std::endl;
        std::cout << " - Pseudo  : '" << userSelected.getPseudo() << "'" << std::endl;

        if (userSelected.getPassword() == password)
        {
            std::cerr << account << " has connected successfully with password:'" << password << "', welcome <" << userSelected.getPseudo() << ">" << std::endl;
            ret = true;
        }
        else
        {
            std::cerr << "account : '" << account << "' has entered wrong password:'" << password << "'" << std::endl;
            ret = false;
        }
    }
    catch (const boost::archive::archive_exception& e)
    {
        std::cerr << "failed to unserialize Database::Account with xml_iarchive: " << e.what();
        ifs.setstate(std::ios::failbit);
        ret = false;
    }

    ifs.close();

    return (ret);
}

void BabelServer::onDisconnect(const std::string &account)
{
    account;
    /*
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
    */

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

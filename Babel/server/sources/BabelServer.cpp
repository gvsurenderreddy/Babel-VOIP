#include "BabelServer.hpp"
#include "IServerSocket.hpp"
#include "TcpServer.hpp"
#include "Database.hpp"

#include <iomanip>
#include <iostream>
#include <fstream>
#include <algorithm>

#include <boost/filesystem.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include <utility>

BabelServer::BabelServer() : mServerSocket(NULL)
{
    const boost::filesystem::path& absolutePathDatabaseFolder = boost::filesystem::complete(Database::DATABASE_FOLDER);
    if (boost::filesystem::exists(absolutePathDatabaseFolder) == false)
        boost::filesystem::create_directory(absolutePathDatabaseFolder);
    const std::string& absolutePathDatabaseFolderStr = absolutePathDatabaseFolder.string();
    mAccountsFilePath = absolutePathDatabaseFolderStr + Database::DATABASE_ACCOUNTS_FILENAME + Database::DATABASE_EXTENSION;
    importAccountsFromFile(mAccountsFilePath);
}

BabelServer::~BabelServer()
{
    if (mServerSocket)
        delete mServerSocket;
    exportAccountsFromFile(mAccountsFilePath);
}

void BabelServer::importAccountsFromFile(const std::string& path)
{
    std::ifstream ifs(path);
    if (!ifs.good() || ifs.fail())
        return;
    boost::archive::text_iarchive ia(ifs);
    ia >> *this;
    ifs.close();
}

void BabelServer::exportAccountsFromFile(const std::string& path)
{
    std::ofstream ofs(path, std::ofstream::out | std::ofstream::trunc);
    if (!ofs.good() || ofs.fail())
        return;
    boost::archive::text_oarchive oa(ofs);
    oa << *this;
    ofs.close();
}

void BabelServer::startServer()
{
    mServerSocket = dynamic_cast<IServerSocket*>(new TcpServer);
    mServerSocket->setOnSocketEventListener(this);
    mServerSocket->createServer(BabelServer::BABEL_DEFAULT_LISTEN_PORT, BabelServer::BABEL_DEFAULT_QUEUE_SIZE);
    mServerSocket->run();
}

void BabelServer::onNewConnection(IServerSocket *serverSocket)
{
    if (serverSocket->hasClientInQueue())
        mClients.push_back(new Client(serverSocket->getNewClient(), *this));
}

bool BabelServer::onSubscribe(const std::string &account, const std::string &password)
{
    if (mAccounts.find(account) == mAccounts.end())
    {
        std::cout << "[SUCCESS] [REG] account '" << account << "' is now registered" << std::endl;
        mAccounts[account] = password;
        return true;
    }
    else
    {
        std::cerr << "[FAILED] [REG] account '" << account << "' is already taken" << std::endl;
        return false;
    }
}

bool BabelServer::onConnect(const std::string &account, const std::string &password, Client *caller)
{
    auto found = std::find_if(mAccounts.begin(), mAccounts.end(), [&](const std::pair<std::string, std::string>& item) -> bool
    { return item.first == account && item.second == password; });
    if (found != mAccounts.end())
    {
        std::cout << "[SUCCESS] [LOG] account '" << account << "' is now connected" << std::endl;
		caller->setAccount(account);
		caller->loadData();
		this->updateContact(caller->getContact(), caller->getAccount(), caller->getPseudo(), caller->getStatus(), true);
        return true;
    }
    else
    {
        std::cerr << "[FAILED] [LOG] [account or password] are wrong" << std::endl;
        return false;
    }
}

void	BabelServer::onDisconnect(Client *caller)
{
	this->updateContact(caller->getContact(), caller->getAccount(), caller->getPseudo(), caller->getStatus(), false);
}

void	BabelServer::onList(Client *caller){
	std::vector<std::string>		args;
	const std::list<std::string>	&contacts = caller->getContact();
	Client							*currentContact;

	/*
	for each contacts{
	currentContact = this->findClient *it
	if contact != NULL
	args.push_back(currentContact->getAccount);
	args.push_back(currentContact->getPseudo);
	args.push_back("");
	args[2] += currentContact->getStatus;
	args.push_back("");
	args[3] += currentContact->getIsConnect;
	caller->handleCmd->packCmd(ICommand::SHOW, args);
	}
	*/
}

bool BabelServer::onUpdate(const std::string &account, const std::string &password, std::string pseudo, char status, const std::string &currentAccount){
	/*
	if (password.size < 6 && mClient.find("account") != mClient.end())
		return false;
	else{
		mClient[account] = password;
		mClient.delete("currentAccount");
		this->updateContact(contact, account, pseudo, status, true);
	}
	*/
	password;
    account;
	currentAccount;
    return (true);
}

bool BabelServer::onAddContact(const std::string &targetAccount, std::string &callerAccount){
	std::vector<std::string>	args;
	Client						*target;

	/*
	target = this->findClient(tragetAccount)
	if target == NULL return false
	args.push_back(callerAccount);
	target->handleCmd->packCmd(callerAccount)
	*/
    return (true);
}

bool BabelServer::onDelContact(const std::string &account){
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
    account;
    if (accept)
        return true;
    else
        return false;
}

void BabelServer::onCallSomeone(const std::string &account){
    account;
}

void BabelServer::onHangCall(const bool &hang, const std::string &account){
    hang;
    account;
}

/*
** Handle Client
*/

void	BabelServer::updateContact(std::list<std::string> contact, std::string account, std::string pseudo, char status, bool isConnected){
	std::vector<std::string>	args;

	args.push_back(account);
	args.push_back(pseudo);
	args.push_back("");
	args[2] += status;
	args.push_back("");
	args[3] += isConnected;

	//PAS TROP COMPRIS CE QUE TA FAIS FAUDRA QUE TU M4EXPLIQUE JAI ESSAYER DE MADAPTER NORMALEMENT C4EST BON
	// A FAIRE AUSSI POUR LE CONNECTED ET UPDATE
	/*std::for_each(contact.begin(), contact.end(), [this](const std::string &account){
	auto it = std::find_if(mClients.begin(), mClients.end(), [&](Client* client) { return client->getName() == account; });
	if (mClients.end() != it)
	it->handleCmd->packCmd(ICommand::SHOW, &args);
	}*/

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

Client	*findClient(std::string account){
	return NULL;
}
﻿#include "BabelServer.hpp"
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
    if (mAccounts.find(account) != mAccounts.end())
        return false;
    mAccounts[account] = password;
    return true;
}

bool BabelServer::onConnect(const std::string &account, const std::string &password, Client *caller)
{
    auto target = std::find_if(mAccounts.begin(), mAccounts.end(), [&](const std::pair<std::string, std::string>& item) -> bool
    { return item.first == account && item.second == password; });
    if (target == mAccounts.end())
        return false;
    caller->setAccount(account);
    caller->loadData();
    this->updateContact(caller->getContact(), caller->getAccount(), caller->getPseudo(), caller->getStatus(), true);
    return true;
}

void BabelServer::onDisconnect(Client *caller)
{
	this->updateContact(caller->getContact(), caller->getAccount(), caller->getPseudo(), caller->getStatus(), false);
}

void BabelServer::onList(Client *caller)
{
	std::vector<std::string>		args;
	const std::list<std::string>	&contacts = caller->getContact();
	Client							*currentContact;

    std::for_each(contacts.begin(), contacts.end(), [&](const std::string &account) {
        if ((currentContact = findClient(account)))
        {
            args.clear();
            args.push_back(currentContact->getAccount());
            args.push_back(currentContact->getPseudo());
            args.push_back("");
            args[2] += currentContact->getStatus();
            args.push_back("");
            args[3] += currentContact->isConnect();
            caller->handleCmd->packCmd(ICommand::SHOW, args);
        }
    });
}

bool BabelServer::onUpdate(const std::string &account, const std::string &password, std::string pseudo, char status)
{
    Client* client;
    if (password.size() < 6 || !(client = findClient(account)))
        return false;
    mAccounts[account] = password;
    updateContact(client->getContact(), account, pseudo, status, true);
    return true;
}

bool BabelServer::onAddContact(const std::string &targetAccount, const std::string &callerAccount)
{
    Client* client;
	std::vector<std::string> args;
	if (!(client = findClient(targetAccount)))
        return false;
	args.push_back(callerAccount);
	client->handleCmd->packCmd(ICommand::ADD, args);
    return (true);
}

bool BabelServer::onDelContact(const std::string &targetAccount, const std::string &callerAccount)
{
    Client* client;
	std::vector<std::string> args;

    if (!(client = findClient(targetAccount)))
        return false;
    args.push_back(callerAccount);
    client->handleCmd->packCmd(ICommand::DEL, args);
    return true;
}

bool BabelServer::onAcceptContact(bool accept, const std::string &account)
{
    Client* client;

    if (!(client = findClient(account)))
        return false;
    if (accept)
        return true;
    else
        return false;
}

void BabelServer::onCallSomeone(const std::string &account)
{
    Client* client;
    std::vector<std::string> args;

    if (!(client = findClient(account)))
        return;
    args.push_back(account);
    client->handleCmd->packCmd(ICommand::CALL, args);
}

void BabelServer::onHangCall(bool hang, const std::string &account)
{
    hang;
    account;
}

void	BabelServer::updateContact(const std::list<std::string>& contact, const std::string& account, const std::string& pseudo, char status, bool isConnected)
{
	std::vector<std::string> args;

	args.push_back(account);
	args.push_back(pseudo);
	args.push_back("");
	args[2] += status;
	args.push_back("");
	args[3] += isConnected;

    std::for_each(contact.begin(), contact.end(), [&](const std::string &account) {
        Client* client = findClient(account);
        if (client)
            client->handleCmd->packCmd(ICommand::SHOW, args);
    });
}

Client	*BabelServer::findClient(const std::string& account) const
{
    auto it = std::find_if(mClients.begin(), mClients.end(), [account](Client* client)
    { return client->getAccount() == account; });
    return (mClients.end() != it ? *it : NULL);
}
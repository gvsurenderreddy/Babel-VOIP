#include "Client.hpp"
#include "Database.hpp"

#include <fstream>
#include <algorithm>
#include <iostream>
#include <ctime>

/*
** Copelien
*/
/* TODO: init default account, pseudo, status, statusCall */
Client::Client(IClientSocket* clientSocket, Client::OnClientEvent* listenerClient) : 
Socket(clientSocket),
status(Client::Status::DISCONNECTED),
statusCall(Client::StatusCall::NONE),
pseudo(""),
account(""),
isConnected(false),
Listener(listenerClient)
{
    initialize();
    if (this->Socket)
        this->Socket->setOnSocketEventListener(this);
    this->handleCmd = this->Socket ? new HandleCmd(this->Socket) : NULL;
    const boost::filesystem::path& absolutePathDatabaseUsersFolder = boost::filesystem::complete(Database::DATABASE_FOLDER_USERS);
    if (boost::filesystem::exists(absolutePathDatabaseUsersFolder) == false)
        boost::filesystem::create_directory(absolutePathDatabaseUsersFolder);
    usersFolderPath = absolutePathDatabaseUsersFolder.string();
}

Client::~Client()
{

}

void Client::initialize(void)
{
    this->setConnected(false);
    this->setStatusCall(Client::StatusCall::NONE);
    this->setStatus(Client::Status::DISCONNECTED);
    updateLastPingTime();
}

/*
** IClientSocket::OnSocketEvent
*/
void	Client::onSocketReadable(IClientSocket *, unsigned int){
	std::vector<std::string> *param;

    while (this->handleCmd && (param = this->handleCmd->unPackCmd()) != NULL) {
        this->treatCommand(this->handleCmd->getInstruction(), *param);
		delete param;
        param = NULL;
	}
}

void	Client::onSocketClosed(IClientSocket*)
{
    std::cout << "[SOCKET CLIENT CLOSE]";
    if (this->isConnect())
    {
    	std::cout << " account: '" << account << "'" << std::endl;
        this->initialize();
    	this->saveData();
    }
    else
    {
    	std::cout << " not logged user" << std::endl;
    }
}

/*
** internal functions
*/
bool Client::saveData(void)
{
    const std::string& path = usersFolderPath + this->account + Database::DATABASE_EXTENSION;
    std::cout << "[DATABASE] update user file '" << path << "'" << std::endl;
    std::ofstream ofs(path, std::ofstream::out | std::ofstream::trunc);
    if (!ofs.good() || ofs.fail())
        return false;
    boost::archive::text_oarchive oa(ofs);
    oa << *this;
    ofs.close();
    return true;
}

bool Client::loadData(void)
{
    const std::string& path = usersFolderPath + this->account + Database::DATABASE_EXTENSION;
    std::ifstream ifs(path);
    if (!ifs.good() || ifs.fail())
        return false;
    boost::archive::text_iarchive ia(ifs);
    ia >> *this;
    ifs.close();
    return true;
}

/*
** Use client's data
*/

// ** Setter
void Client::setConnected(bool state) { this->isConnected = state; }
void Client::setStatus(Client::Status state) { this->status = state; }
void Client::setStatusCall(Client::StatusCall state) { this->statusCall = state; }
void Client::setPseudo(const std::string& pseudoName) { this->pseudo = pseudoName; }
void Client::setAccount(const std::string& accountName) { this->account = accountName; }
void Client::addContact(const std::string& accountName)
{ 
    if (std::find(this->contact.begin(), this->contact.end(), accountName) == this->contact.end())
        this->contact.push_back(accountName);
}
void Client::delContact(const std::string& accountName)
{
    if (std::find(this->contact.begin(), this->contact.end(), accountName) != this->contact.end())
        this->contact.remove(accountName);
}
void Client::clearContact() { this->contact.clear(); }
void Client::updateLastPingTime() { this->lastPingTime = std::time(nullptr); }

// ** Getter
Client::Status				  Client::getStatus(void) const { return this->status; }
Client::StatusCall			  Client::getStatusCall(void) const { return this->statusCall; }
const std::string&            Client::getPseudo(void) const { return this->pseudo; }
const std::string&            Client::getAccount(void) const { return this->account; }
const std::list<std::string>& Client::getContact(void) const { return this->contact; }
IClientSocket*                Client::getSocket(void) const { return this->Socket; }
bool						  Client::isConnect(void) const { return this->isConnected; }
time_t		                  Client::getLastPingTime() const { return this->lastPingTime; }

bool                          Client::isAlreadyFriends(const std::string& accountName) const
{
    return (std::find(this->contact.begin(), this->contact.end(), accountName) != this->contact.end());
}

const Client::HandleCommand Client::handleCommandsTab[] =
{
    { ICommand::ADD, &Client::OnClientEvent::onAdd },
    { ICommand::UPDATE, &Client::OnClientEvent::onUpdate },
    { ICommand::REG, &Client::OnClientEvent::onReg },
    { ICommand::LOG, &Client::OnClientEvent::onLog },
    { ICommand::LIST, &Client::OnClientEvent::onList },
    { ICommand::SHOW, &Client::OnClientEvent::onShow },
    { ICommand::CALL, &Client::OnClientEvent::onCall },
    { ICommand::ACCEPT_ADD, &Client::OnClientEvent::onAcceptAdd },
    { ICommand::DEL, &Client::OnClientEvent::onDel },
    { ICommand::EXIT, &Client::OnClientEvent::onExit },
    { ICommand::SEND, &Client::OnClientEvent::onSend },
    { ICommand::ACCEPT_CALL, &Client::OnClientEvent::onAcceptCall },
    { ICommand::CLOSE_CALL, &Client::OnClientEvent::onCloseCall },
    { ICommand::UNKNOWN_INSTRUCTION, NULL }
};

void	Client::treatCommand(ICommand::Instruction instruction, std::vector<std::string> &param)
{
    int i;
    for (i = 0; handleCommandsTab[i].instruction != ICommand::UNKNOWN_INSTRUCTION && handleCommandsTab[i].instruction != instruction; ++i);

    if (handleCommandsTab[i].instruction == instruction && this->Listener)
        ((this->Listener)->*handleCommandsTab[i].handler)(this, param, instruction);
}

void Client::display() const
{
    std::cout
        << "        [#] account      : '" << this->getAccount() << "'" << std::endl
        << "        [#] pseudo       : '" << this->getPseudo() << "'" << std::endl
        << "        [#] status       : '" << this->getStatus() << "'" << std::endl
        << "        [#] statusCall   : '" << this->getStatusCall() << "'" << std::endl
        << "        [#] isConnected  : '" << std::boolalpha << this->isConnect() << "'" << std::endl
        << "        [#] lastPingTime : '" << this->getLastPingTime() << "'" << std::endl
        << "        [#] contacts     : ";
    if (this->getContact().size())
    {
        std::for_each(this->getContact().begin(), this->getContact().end(), [](const std::string &targetAccount) {
            std::cout << "'" << targetAccount << "' ";
        });
        std::cout << std::endl;
    }
    else
        std::cout << " no friends" << std::endl;
}

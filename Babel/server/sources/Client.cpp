#include "Client.hpp"
#include "Database.hpp"
#include "ErrorCodes.hpp"

#include <fstream>
#include <algorithm>
#include <iostream>

/*
** Copelien
*/
Client::Client(IClientSocket* clientSocket, Client::OnClientEvent &listenerClient) : Socket(clientSocket), Listener(listenerClient), isConnected(false)
{
    this->Socket->setOnSocketEventListener(this);
	handleCmd = new HandleCmd(clientSocket);
    const boost::filesystem::path& absolutePathDatabaseUsersFolder = boost::filesystem::complete(Database::DATABASE_FOLDER_USERS);
    if (boost::filesystem::exists(absolutePathDatabaseUsersFolder) == false)
        boost::filesystem::create_directory(absolutePathDatabaseUsersFolder);
    usersFolderPath = absolutePathDatabaseUsersFolder.string();
}

Client::~Client()
{

}

/*
** Callback from IClientSocket
*/
void	Client::onBytesWritten(IClientSocket *socket, unsigned int nbBytes){
    std::cout << nbBytes << " bytes sended" << std::endl;
	socket;
}

void	Client::onSocketReadable(IClientSocket *socket, unsigned int nbBytesToRead){
	std::vector<std::string> *param;

	socket;
	nbBytesToRead;
	while ((param = this->handleCmd->unPackCmd()) != NULL){
		this->exeCmd(this->handleCmd->getInstruction(), *param);
		delete param;
        param = NULL;
	}
}

void	Client::onSocketClosed(IClientSocket *socket){
	socket;
}

/*
** Function for serialization5
*/
void			Client::saveData(void){

    const std::string& path = usersFolderPath + this->account + Database::DATABASE_EXTENSION;
    std::ofstream ofs(path, std::ofstream::out | std::ofstream::trunc);
    if (!ofs.good() || ofs.fail())
        return;
    boost::archive::text_oarchive oa(ofs);
    oa << *this;
    ofs.close();
}

void	Client::loadData(void){
    const std::string& path = usersFolderPath + this->account + Database::DATABASE_EXTENSION;
    std::ifstream ifs(path);
    if (!ifs.good() || ifs.fail())
        return;
    boost::archive::text_iarchive ia(ifs);
    ia >> *this;
    ifs.close();
}

/*
** Use client's data
** Setter
*/
void	Client::setStatus(int state){this->status = state;}
void	Client::setPseudo(const std::string name){this->account = name;}
void	Client::setAccount(const std::string account){this->account = account;}
void	Client::addContact(const std::string name){this->contact.push_back(name);}
void	Client::delContact(const std::string name){this->contact.remove(name);}
/*
** Getter
*/
int								Client::getStatus(void){return this->status;}
const std::string				&Client::getPseudo(void){return this->pseudo;}
const std::string				&Client::getAccount(void){return this->account;}
const std::list<std::string>	&Client::getContact(void){return this->contact;}
bool							Client::isConnect(void){return this->isConnected;}

/*
** Function cmd
*/
void	Client::Subscribe(std::vector<std::string> &args){
	
	bool ret = this->Listener.onSubscribe(args[0], args[2]);

    if (ret == true)
        std::cout << "Inscription Disponible" << std::endl;
    else
        std::cout << "Inscription Déjà existante" << std::endl;

	if (ret == true)
    {
		this->account = args[0];
		this->pseudo = args[1];
		this->contact.clear();
		this->status = 1;
		this->saveData();
	}

	args.clear();
	args.push_back("");
    args[0] += ret == true ? ErrorCode::OK : ErrorCode::THE_IMPOSSIBLE_HAPPENED;
	args.push_back("");
	args[1] += ICommand::REG;
	this->handleCmd->packCmd(ICommand::ERR, args);
}

void	Client::Connect(std::vector<std::string> &args){
    bool ret = this->Listener.onConnect(args[0], args[1], this);

    if (ret == true)
        std::cout << "Connexion success" << std::endl;
    else
        std::cout << "Connexion wrong password" << std::endl;

	this->isConnected = ret;

	args.clear();
	args.push_back("");
    args[0] += ret == true ? ErrorCode::OK : ErrorCode::THE_IMPOSSIBLE_HAPPENED;
	args.push_back("");
	args[1] += ICommand::LOG;
  	this->handleCmd->packCmd(ICommand::ERR, args);
}

void		Client::Disconnect(std::vector<std::string> &args){
    bool	ret;

	if (this->account == args[0])
    {
		this->Listener.onDisconnect(this);
		this->saveData();
		this->isConnected = false;
        ret = true;
	}
	else
        ret = false;

	args.clear();
	args.push_back("");
    args[0] += ret == true ? ErrorCode::OK : ErrorCode::THE_IMPOSSIBLE_HAPPENED;
	args.push_back("");
    args[1] += ICommand::EXIT;
	this->handleCmd->packCmd(ICommand::ERR, args);
}

void	Client::Update(std::vector<std::string> &args){
    bool ret;

	if (args[1].empty() == false && (args[3][0] >= 0 && args[3][0] <= 10) && args[0].empty() == false && args[2].empty() == false)
    {
		if ((ret = this->Listener.onUpdate(args[0], args[2], args[1], args[3][0])))
        {
			this->pseudo = args[1];
			this->status = args[3][0];
		}
	}
	else
        ret = false;

	args.clear();
	args.push_back("");
    args[0] += ret == true ? ErrorCode::OK : ErrorCode::THE_IMPOSSIBLE_HAPPENED;
	args.push_back("");
	args[1] += ICommand::UPDATE;
	this->handleCmd->packCmd(ICommand::ERR, args);
}

void	Client::AddContact(std::vector<std::string> &args){
	bool ret;

	if (args[0].empty() == false)
		ret = this->Listener.onAddContact(args[0], this->account);
	else 
		ret = false;

	args.clear();
	args.push_back("");
    args[0] += ret == true ? ErrorCode::OK : ErrorCode::THE_IMPOSSIBLE_HAPPENED;
	args.push_back("");
    args[1] += ICommand::ADD;
	this->handleCmd->packCmd(ICommand::ERR, args);
}

void	Client::DelContact(std::vector<std::string> &args){
	bool ret;

	if (args[0].empty() == false)
		ret = this->Listener.onDelContact(args[0], this->account);
	else
		ret = false;

	args.clear();
	args.push_back("");
    args[0] += ret == true ? ErrorCode::OK : ErrorCode::THE_IMPOSSIBLE_HAPPENED;
	args.push_back("");
	args[1] += ICommand::DEL;
	this->handleCmd->packCmd(ICommand::ERR, args);
}

void	Client::AcceptContact(std::vector<std::string> &args){
    this->Listener.onAcceptContact(args[1][0], args[0], this->account);
}

void	Client::CallSomeone(std::vector<std::string> &args){
	bool	ret;

	ret = !Listener.onCallSomeone(args[0], this->account);

	args.clear();
	args.push_back("");
    args[0] += ret;
	args.push_back("");
	args[1] += ICommand::CALL;
	this->handleCmd->packCmd(ICommand::ERR, args);
}

void	Client::HangCall(std::vector<std::string> &args){
	args.clear();
	args.push_back("");
	args[0] += ErrorCode::OK;
	args.push_back("");
	args[1] += ICommand::ACCEPT_CALL;
	this->handleCmd->packCmd(ICommand::ERR, args);
}

void	Client::List(std::vector<std::string> &){
	this->Listener.onList(this);
}

void	Client::Show(std::vector<std::string> &args){
	args.clear();
	args.push_back("");
	args[0] += ErrorCode::OK;
	args.push_back("");
	args[1] += ICommand::SHOW;
	this->handleCmd->packCmd(ICommand::SHOW, args);
}

void	Client::SendMsg(std::vector<std::string> &args){

    bool ret;

    if (args[0].empty() == false)
        ret = this->Listener.onSendMsg(args[0], args[1], this->account);
    else
        ret = false;

    args.clear();
    args.push_back("");
    args[0] += ret == true ? ErrorCode::OK : ErrorCode::THE_IMPOSSIBLE_HAPPENED;
    args.push_back("");
    args[1] += ICommand::SEND;
    this->handleCmd->packCmd(ICommand::ERR, args);
}

void	Client::CloseCall(std::vector<std::string> &args){
	args.clear();
	args.push_back("");
    args[0] += ErrorCode::OK;
	args.push_back("");
	args[1] += ICommand::CLOSE_CALL;
	this->handleCmd->packCmd(ICommand::ERR, args);
}

const Client::HandleCommand Client::handleCommandsTab[] = {
    { ICommand::ADD, &Client::AddContact },
    { ICommand::UPDATE, &Client::Update },
    { ICommand::REG, &Client::Subscribe },
    { ICommand::LOG, &Client::Connect },
    { ICommand::LIST, &Client::List },
    { ICommand::SHOW, &Client::Show },
    { ICommand::CALL, &Client::CallSomeone },
    { ICommand::ACCEPT_ADD, &Client::AcceptContact },
    { ICommand::DEL, &Client::DelContact },
    { ICommand::EXIT, &Client::Disconnect },
    { ICommand::SEND, &Client::SendMsg },
    { ICommand::ACCEPT_CALL, &Client::HangCall },
    { ICommand::CLOSE_CALL, &Client::CloseCall },
    { ICommand::UNKNOWN_INSTRUCTION, NULL }
};

void	Client::exeCmd(ICommand::Instruction instruction, std::vector<std::string> &param)
{
    int i;
    for (i = 0; handleCommandsTab[i].instruction != ICommand::UNKNOWN_INSTRUCTION && handleCommandsTab[i].instruction != instruction; i++);

    if (handleCommandsTab[i].instruction == instruction)
        (this->*handleCommandsTab[i].handler)(param);
}
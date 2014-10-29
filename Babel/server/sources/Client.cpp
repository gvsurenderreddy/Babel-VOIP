#include "Client.hpp"
#include "Database.hpp"

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

	this->account = args[0];
	this->pseudo = args[1];
	this->contact.clear();
	this->status = 1;
	this->saveData();

	args.clear();
	args.push_back("");
	args[0] += !ret;
	args.push_back("");
	args[1] += ICommand::REG;
	this->handleCmd->packCmd(ICommand::ERR, args);
}

void	Client::Connect(std::vector<std::string> &args){
    bool ret = this->Listener.onConnect(args[0], args[1], this);

	this->isConnected = true;

	args.clear();
	args.push_back("");
    args[0] += !ret;
	args.push_back("");
	args[1] += ICommand::LOG;
  	this->handleCmd->packCmd(ICommand::ERR, args);
}

void		Client::Disconnect(std::vector<std::string> &args){
	bool	error = false;

	if (this->account == args[0]){
		this->Listener.onDisconnect(this);
		this->saveData();
		this->isConnected = false;
	}
	else
		error = true;

	args.clear();
	args.push_back("");
	args[0] += error;
	args.push_back("");
    args[1] += ICommand::EXIT;
	this->handleCmd->packCmd(ICommand::ERR, args);
}

void	Client::Update(std::vector<std::string> &args){
	bool error = false;

	if (args[1].empty() == false &&
		(args[3][0] >= 0 && args[3][0] <= 10) &&
		args[0].empty() == false &&
		args[2].empty() == false
		){
		error = !this->Listener.onUpdate(args[0], args[2], this->account);
		if (error == false){
			this->pseudo = args[1];
			this->status = args[3][0];
		}
	}
	else
		error = true;

	args.clear();
	args.push_back("");
	args[0] += error;
	args.push_back("");
	args[1] += ICommand::UPDATE;
	this->handleCmd->packCmd(ICommand::ERR, args);
}

void	Client::AddContact(std::vector<std::string> &args){
	bool error = false;

	if (args[0].empty() == false)
		error = !this->Listener.onAddContact(args[0]);
	else 
		error = true;

	args.clear();
	args.push_back("");
	args[0] += error;
	args.push_back("");
    args[1] += ICommand::ADD;
	this->handleCmd->packCmd(ICommand::ERR, args);
}

void	Client::DelContact(std::vector<std::string> &args){
	bool error = false;

	if (args[0].empty() == false)
		error = !this->Listener.onAddContact(args[0]);
	else
		error = true;

	args.clear();
	args.push_back("");
	args[0] += error;
	args.push_back("");
	args[1] += ICommand::DEL;
	this->handleCmd->packCmd(ICommand::ERR, args);
}

void	Client::AcceptContact(std::vector<std::string> &args){
    bool error = !args[0].empty() && this->Listener.onAcceptContact(args[1][0], args[0]) ? false : true;

	args.clear();
	args.push_back("");
	args[0] += error;
	args.push_back("");
	args[1] += ICommand::ACCEPT_ADD;
	this->handleCmd->packCmd(ICommand::ERR, args);
}

void	Client::CallSomeone(std::vector<std::string> &args){
	args.clear();
	args.push_back("");
	args[0] += 1;
	args.push_back("");
	args[1] += ICommand::CALL;
	this->handleCmd->packCmd(ICommand::ERR, args);
}

void	Client::HangCall(std::vector<std::string> &args){
	args.clear();
	args.push_back("");
	args[0] += 1;
	args.push_back("");
	args[1] += ICommand::ACCEPT_CALL;
	this->handleCmd->packCmd(ICommand::ERR, args);
}

void	Client::List(std::vector<std::string> &args){
	this->Listener.onList(this);
	args;
}

void	Client::Show(std::vector<std::string> &args){
	args.clear();
	args.push_back("");
	args[0] += 1;
	args.push_back("");
	args[1] += ICommand::SHOW;
	this->handleCmd->packCmd(ICommand::SHOW, args);
}

void	Client::SendMsg(std::vector<std::string> &args){
	args.clear();
	args.push_back("");
	args[0] += 1;
	args.push_back("");
	args[1] += ICommand::SEND;
	this->handleCmd->packCmd(ICommand::ERR, args);
}

void	Client::CloseCall(std::vector<std::string> &args){
	args.clear();
	args.push_back("");
	args[0] += 1;
	args.push_back("");
	args[1] += ICommand::CLOSE_CALL;
	this->handleCmd->packCmd(ICommand::ERR, args);
}

void	Client::exeCmd(ICommand::Instruction instruction, std::vector<std::string> &param){
	switch (instruction)
	{
	case ICommand::ADD:
		this->AddContact(param);
        break;
	case ICommand::UPDATE:
        this->Update(param);
        break;
	case ICommand::REG:
        this->Subscribe(param);
        break;
    case ICommand::LOG:
        this->Connect(param);
        break;
	case ICommand::LIST:
        this->List(param);
        break;
	case ICommand::SHOW:
        this->Show(param);
        break;
	case ICommand::CALL:
        this->CallSomeone(param);
        break;
	case ICommand::ACCEPT_ADD:
        this->AcceptContact(param);
        break;
	case ICommand::DEL:
        this->DelContact(param);
        break;
	case ICommand::EXIT:
        this->Disconnect(param);
        break;
	case ICommand::SEND:
        this->SendMsg(param);
        break;
	case ICommand::ACCEPT_CALL:
        this->HangCall(param);
        break;
    case ICommand::CLOSE_CALL:
        this->CloseCall(param);
        break;
	default:
        std::cout << "Unknown command" << std::endl;
		return ;
	}
}
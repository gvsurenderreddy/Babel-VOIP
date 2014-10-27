#include "Client.hpp"
#include <fstream>
#include <algorithm>

#include <iostream>

/*
** Copelien
*/
Client::Client(IClientSocket* clientSocket, Client::OnClientEvent &listenerClient) : mSocket(clientSocket), mListener(listenerClient), isConnected(false)
{
    mSocket->setOnSocketEventListener(this);
	handleCmd = new HandleCmd(clientSocket);
}

Client::~Client()
{

}

/*
** Callback from IClientSocket
*/
void	Client::onBytesWritten(IClientSocket *socket, unsigned int nbBytes){
	nbBytes;
	socket;
}

void	Client::onSocketReadable(IClientSocket *socket, unsigned int nbBytesToRead){
	std::vector<std::string> *param;

	socket;
	nbBytesToRead;
	while ((param = this->handleCmd->unPackCmd()) != NULL){
		this->exeCmd(this->handleCmd->getInstruction(), param);
		delete param;
	}
}

void	Client::onSocketClosed(IClientSocket *socket){
	socket;
}

/*
** Function for serialization
*/
/*void			Client::savData(void){
	std::string path = "user/";

	path += this->account;
	std::ofstream file(path.c_str());
	boost::archive::text_oarchive archive(file);
	archive << *this;
}

void	Client::loadData(void){
	std::string path = "user/";

	path += this->account;
	std::ifstream file(path.c_str());
	boost::archive::text_iarchive archive(file);
	archive >> *this;
}*/

/*
** Use client's data
** Setter
*/
void	Client::setState(const std::string state){this->state = state;}
void	Client::setName(const std::string name){this->account = name;}
void	Client::setAccount(const std::string account){this->account = account;}
void	Client::addContact(const std::string name){this->contact.push_back(name);}
void	Client::dellContact(const std::string name){this->contact.remove(name);}
/*
** Getter
*/
const std::string				&Client::getState(void){return this->state;}
const std::string				&Client::getName(void){return this->name;}
const std::string				&Client::getAccount(void){return this->account;}
const std::list<std::string>	&Client::getContact(void){return this->contact;}

/*
** Function cmd
*/
void	Client::Subscribe(std::vector<std::string> *args){
    mListener.onSubscribe((*args)[0], (*args)[1]);
	this->handleCmd->packCmd(ICommand::ERR, args);
}

void	Client::Connect(std::vector<std::string> *args){
    if (mListener.onConnect((*args)[0], (*args)[1]))
    {
        isConnected = true;
    }
  	this->handleCmd->packCmd(ICommand::ERR, args);
}

void	Client::Disconnect(std::vector<std::string> *args){
    mListener.onDisconnect((*args)[0]);
    isConnected = false;
	this->handleCmd->packCmd(ICommand::ERR, args);
}

void	Client::GetContact(std::vector<std::string> *args){
	this->handleCmd->packCmd(ICommand::ERR, args);
}

void	Client::Update(std::vector<std::string> *args){
	this->handleCmd->packCmd(ICommand::ERR, args);
}

void	Client::AddContact(std::vector<std::string> *args){
	this->handleCmd->packCmd(ICommand::ERR, args);
}

void	Client::DellContact(std::vector<std::string> *args){
	this->handleCmd->packCmd(ICommand::ERR, args);
}

void	Client::AcceptContact(std::vector<std::string> *args){
	this->handleCmd->packCmd(ICommand::ERR, args);
}

void	Client::CallSomeone(std::vector<std::string> *args){
	this->handleCmd->packCmd(ICommand::ERR, args);
}

void	Client::HangCall(std::vector<std::string> *args){
	this->handleCmd->packCmd(ICommand::ERR, args);
}

void	Client::List(std::vector<std::string> *args){
	this->handleCmd->packCmd(ICommand::SHOW, args);
}

void	Client::Show(std::vector<std::string> *args){
	this->handleCmd->packCmd(ICommand::SHOW, args);
}

void	Client::SendMsg(std::vector<std::string> *args){
	this->handleCmd->packCmd(ICommand::ERR, args);
}

void	Client::CloseCall(std::vector<std::string> *args){
	this->handleCmd->packCmd(ICommand::ERR, args);
}

void	Client::exeCmd(ICommand::Instruction instruction, std::vector<std::string> *param){
	switch (instruction)
	{
	case ICommand::ADD:
		this->AddContact(param);
	case ICommand::UPDATE:
		this->Update(param);
	case ICommand::REG:
		this->Subscribe(param);
	case ICommand::LOG:
		this->Connect(param);
	case ICommand::LIST:
		this->List(param);
	case ICommand::SHOW:
		this->Show(param);
	case ICommand::CALL:
		this->CallSomeone(param);
	case ICommand::ACCEPT_ADD:
		this->AcceptContact(param);
	case ICommand::DEL:
		this->DellContact(param);
	case ICommand::EXIT:
		this->Disconnect(param);
	case ICommand::SEND:
		this->SendMsg(param);
	case ICommand::ACCEPT_CALL:
		this->HangCall(param);
	case ICommand::CLOSE_CALL:
		this->CloseCall(param);
	default:
		return ;
	}
}
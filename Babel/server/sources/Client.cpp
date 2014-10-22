#include "Client.hpp"
#include <fstream>
#include <algorithm>

/*
** Copelien
*/
Client::Client(IClientSocket &_socket, Client::OnClientEvent &_listener)
:socket(_socket), listener(_listener){
    std::cout << __FUNCTION__ << std::endl;
}

Client::~Client(){
    std::cout << __FUNCTION__ << std::endl;
}

/*
** Callback from IClientSocket
*/
void	Client::onBytesWritten(IClientSocket *socket, unsigned int nbBytes){
    std::cout << __FUNCTION__ << std::endl;
	nbBytes;
	socket;
}

void	Client::onSocketReadable(IClientSocket *socket, unsigned int nbBytesToRead){
    std::cout << __FUNCTION__ << std::endl;
	socket;
	nbBytesToRead;
}

void	Client::onSocketClosed(IClientSocket *socket){
    std::cout << __FUNCTION__ << std::endl;
	socket;
}

/*
** Function for serialization
*/
void			Client::savData(void){
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
}

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
void	Client::update(const std::vector<std::string> &args){
	args;
}

void	Client::Subscribe(const std::vector<std::string> &args){
	args;
}

void	Client::Connect(const std::vector<std::string> &args){
	args;
}

void	Client::Disconnect(const std::vector<std::string> &args){
	args;
}

void	Client::GetContact(const std::vector<std::string> &args){
	args;
}

void	Client::Update(const std::vector<std::string> &args){
	args;
}

void	Client::AddContact(const std::vector<std::string> &args){
	args;
}

void	Client::DellContact(const std::vector<std::string> &args){
	args;
}

void	Client::AcceptContact(const std::vector<std::string> &args){
	args;
}

void	Client::CallSomeone(const std::vector<std::string> &args){
	args;
}

void	Client::HangCall(const std::vector<std::string> &args){
	args;
}

void	Client::exeCmd(const int token, const std::vector<std::string> &args){
	args;
	token;
}
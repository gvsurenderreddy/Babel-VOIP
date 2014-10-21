#include "Client.hpp"

/*
** Copelien
*/
Client::Client(IClientSocket &_socket, Client::OnClientEvent &_listener){

}

Client::~Client(){

}

/*
** Callback from IClientSocket
*/
void	Client::onBytesWritten(IClientSocket *socket, unsigned int nbBytes){

}

void	Client::onSocketReadable(IClientSocket *socket, unsigned int nbBytesToRead){

}

void	Client::onSocketClosed(IClientSocket *socket){

}

/*
** Function for serialization
*/
void	Client::savData(void){

}

void	Client::loadData(void){

}

/*
** Use client's data
** Setter
*/
void	Client::setState(const std::string state){

}

void	Client::setName(const std::string account){

}

void	Client::setAccount(const std::string account){

}

void	Client::addContact(const std::string name){

}

void	Client::dellContact(const std::string name){

}
/*
** Getter
*/
const std::string				&Client::getState(void){

}

const std::string				&Client::getName(void){

}

const std::string				&Client::getAccount(void){

}

const std::vector<std::string>	&Client::getContact(void){

}

/*
** Function cmd
*/
void	Client::update(const std::vector<std::string> &args){

}

void	Client::Subscribe(const std::vector<std::string> &args){

}

void	Client::Connect(const std::vector<std::string> &args){

}

void	Client::Disconnect(const std::vector<std::string> &args){

}

void	Client::GetContact(const std::vector<std::string> &args){

}

void	Client::Update(const std::vector<std::string> &args){

}

void	Client::AddContact(const std::vector<std::string> &args){

}

void	Client::DellContact(const std::vector<std::string> &args){

}

void	Client::AcceptContact(const std::vector<std::string> &args){

}

void	Client::CallSomeone(const std::vector<std::string> &args){

}

void	Client::HangCall(const std::vector<std::string> &args){

}

void	Client::exeCmd(const int token, const std::vector<std::string> &args){

}












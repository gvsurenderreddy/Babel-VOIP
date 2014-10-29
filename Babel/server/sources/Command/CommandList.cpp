#include "Command/CommandList.hpp"

CommandList::CommandList(){

}
CommandList::~CommandList(){

}

/*
** Heritage from ICommand
*/
std::vector<std::string>		*CommandList::getParam(IClientSocket *socket){
	std::vector<std::string>	*t = new std::vector<std::string>;
	socket;
	return t;
}

IClientSocket::Message		*CommandList::setParam(std::vector<std::string> *param){
	param;
	return NULL;
}

unsigned int				CommandList::getSizeBody(void){
	return 0;
}
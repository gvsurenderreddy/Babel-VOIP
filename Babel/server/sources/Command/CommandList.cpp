#include "Command/CommandList.hpp"

CommandList::CommandList(){

}
CommandList::~CommandList(){

}

/*
** Heritage from ICommand
*/
std::vector<std::string>		*CommandList::getParam(IClientSocket *){
	return new std::vector<std::string>;
}

IClientSocket::Message			*CommandList::setParam(const std::vector<std::string> &){
	return NULL;
}

unsigned int					CommandList::getSizeBody(void){
	return 0;
}
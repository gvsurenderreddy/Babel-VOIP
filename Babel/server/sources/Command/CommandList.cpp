#include "Command/CommandList.hpp"

CommandList::CommandList(){

}
CommandList::~CommandList(){

}

/*
** Heritage from ICommand
*/
std::vector<std::string>		*CommandList::getParam(IClientSocket *){
	std::vector<std::string>	*t = new std::vector<std::string>;

	return t;
}

IClientSocket::Message		*CommandList::setParam(std::vector<std::string> *){
	return NULL;
}

unsigned int				CommandList::getSizeBody(void){
	return 0;
}
#include "Command/CommandExit.hpp"

CommandExit::CommandExit(){

}
CommandExit::~CommandExit(){

}

/*
** Heritage from ICommand
*/
std::vector<std::string>		*CommandExit::getParam(IClientSocket *){
	return NULL;
}

IClientSocket::Message			*CommandExit::setParam(const std::vector<std::string> &){
	return NULL;
}

unsigned int					CommandExit::getSizeBody(void){
	return 0;
}
#include "Command/CommandExit.hpp"

CommandExit::CommandExit(){

}
CommandExit::~CommandExit(){

}

/*
** Heritage from ICommand
*/
std::vector<std::string>		*CommandExit::getParam(IClientSocket *socket){
	std::vector<std::string>	*t = new std::vector<std::string>;
	socket;
	return t;
}

IClientSocket::Message		*CommandExit::setParam(std::vector<std::string> *param){
	param;
	return NULL;
}

unsigned int				CommandExit::getSizeBody(void){
	return 0;
}
#include "Command/CommandExit.hpp"

CommandExit::CommandExit(){

}
CommandExit::~CommandExit(){

}

/*
** Heritage from ICommand
*/
std::vector<std::string>		*CommandExit::getParam(IClientSocket *){
	std::vector<std::string>	*t = new std::vector<std::string>;

	return t;
}

IClientSocket::Message		*CommandExit::setParam(std::vector<std::string> *){
	return NULL;
}

unsigned int				CommandExit::getSizeBody(void){
	return 0;
}
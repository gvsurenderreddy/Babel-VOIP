#include "Command/CommandExit.hpp"

std::vector<std::string>		*CommandExit::getParam(IClientSocket *){
   return new std::vector<std::string>;
}

IClientSocket::Message			*CommandExit::setParam(const std::vector<std::string> &){
	return NULL;
}

unsigned int					CommandExit::getSizeBody(void){
	return 0;
}
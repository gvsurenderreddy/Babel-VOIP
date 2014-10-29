#pragma once

#include "ICommand.hpp"

class CommandExit : public ICommand{
public:
	CommandExit();
	~CommandExit();

	//body
	struct Body{

	};

	//heritage from ICommand
	std::vector<std::string>	*getParam(IClientSocket *socket);
	IClientSocket::Message		*setParam(std::vector<std::string> *param);
    unsigned int				getSizeBody(void);
};
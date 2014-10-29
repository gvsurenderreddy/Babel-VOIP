#pragma once

#include "ICommand.hpp"

class CommandLog : public ICommand{
public:
	CommandLog();
	~CommandLog();

	//body
	struct Body{
		char				accountName[256];
		char				password[256];
	};

	//heritage from ICommand
	std::vector<std::string>	*getParam(IClientSocket *socket);
	IClientSocket::Message		*setParam(std::vector<std::string> *param);
    unsigned int				getSizeBody(void);
};
#pragma once

#include "ICommand.hpp"

class CommandUpdate : public ICommand{
public:
	CommandUpdate();
	~CommandUpdate();

	//body
	struct __attribute__ ((packed)) Body{
		char	accountName[256];
		char	pseudo[256];
		char	password[256];
		char	status;
	};

	//heritage from ICommand
	std::vector<std::string>	*getParam(IClientSocket *socket);
	IClientSocket::Message		*setParam(std::vector<std::string> *param);
    unsigned int				getSizeBody(void);
};
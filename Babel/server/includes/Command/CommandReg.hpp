#pragma once

#include "ICommand.hpp"

class CommandReg : public ICommand{
public:
	CommandReg();
	~CommandReg();

	//body
	struct NO_PADDING Body{
		char				accountName[256];
		char				pseudo[256];
		char				password[256];
	};

	//heritage from ICommand
	std::vector<std::string>	*getParam(IClientSocket *socket);
	IClientSocket::Message		*setParam(std::vector<std::string> *param);
    unsigned int				getSizeBody(void);
};
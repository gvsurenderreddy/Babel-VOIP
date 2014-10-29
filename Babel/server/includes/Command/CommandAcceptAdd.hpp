#pragma once

#include "ICommand.hpp"

class CommandAcceptAdd : public ICommand{
public:
	CommandAcceptAdd();
	~CommandAcceptAdd();

	//body
	struct Body{
		char				accountName[256];
		char				hasAccepted;
	};

	//heritage from ICommand
	std::vector<std::string>	*getParam(IClientSocket *socket);
	IClientSocket::Message		*setParam(std::vector<std::string> *param);
	unsigned int				getSizeBody(void);
};
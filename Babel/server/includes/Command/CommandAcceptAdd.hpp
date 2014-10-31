#pragma once

#include "ICommand.hpp"

class CommandAcceptAdd : public ICommand{
public:
	CommandAcceptAdd();
	~CommandAcceptAdd();

	//body
	struct __attribute__ ((packed)) Body{
		char				accountName[256];
		char				hasAccepted;
	};

	struct __attribute__ ((packed)) BodySend{
		ICommand::Header	header;
		char				accountName[256];
		char				hasAccepted;
	};


	//heritage from ICommand
	std::vector<std::string>	*getParam(IClientSocket *socket);
	IClientSocket::Message		*setParam(std::vector<std::string> *param);
	unsigned int				getSizeBody(void);
};
#pragma once

#include "ICommand.hpp"

class CommandShow : public ICommand{
public:
	CommandShow();
	~CommandShow();

	//body
	struct NO_PADDING Body{
		char				accountName[256];
	};

	struct NO_PADDING BodySend{
		ICommand::Header	header;
		char				accountName[256];
		char				pseudo[256];
		char				status;
		char				isConnected;
	};

	//heritage from ICommand
	std::vector<std::string>	*getParam(IClientSocket *socket);
	IClientSocket::Message		*setParam(const std::vector<std::string> &param);
    unsigned int				getSizeBody(void);
};
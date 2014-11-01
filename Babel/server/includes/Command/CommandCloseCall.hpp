#pragma once

#include "ICommand.hpp"

class CommandCloseCall : public ICommand{
public:
	CommandCloseCall();
	~CommandCloseCall();

	//body
	struct NO_PADDING Body{
		char	accountName[256];
	};

	struct NO_PADDING BodySend{
		ICommand::Header	header;
		char				accountName[256];
	};

	//heritage from ICommand
	std::vector<std::string>	*getParam(IClientSocket *socket);
	IClientSocket::Message		*setParam(std::vector<std::string> *param);
	unsigned int				getSizeBody(void);
};
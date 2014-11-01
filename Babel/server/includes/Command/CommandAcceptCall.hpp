#pragma once

#include "ICommand.hpp"

class CommandAcceptCall : public ICommand{
public:
	CommandAcceptCall();
	~CommandAcceptCall();

	//body
	struct NO_PADDING Body{
		char				accountName[256];
		char				hasAccepted;
	};
	struct NO_PADDING BodySend{
		ICommand::Header	header;
		char				accountName[256];
		char				host[15];
		char				hasAccepted;
	};

	//heritage from ICommand
	std::vector<std::string>	*getParam(IClientSocket *socket);
	IClientSocket::Message		*setParam(const std::vector<std::string> &param);
    unsigned int				getSizeBody(void);
};
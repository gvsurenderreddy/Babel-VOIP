#pragma once

#include "ICommand.hpp"

class CommandAcceptCall : public ICommand{
public:
	CommandAcceptCall();
	~CommandAcceptCall();

	//body
	struct Body{
		char				accountName[256];
		char				hasAccepted;
	};

	//heritage from ICommand
	std::vector<std::string>	*getParam(IClientSocket *socket);
	IClientSocket::Message		*setParam(std::vector<std::string> *param);
	int							getSizeBody(void);
};
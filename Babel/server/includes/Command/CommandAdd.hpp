#pragma once

#include "ICommand.hpp"

class CommandAdd : public ICommand{
public:
	CommandAdd();
	~CommandAdd();

	//body
	struct Body{
		char	accountName[256];
	};

	struct BodySend{
		ICommand::Header	header;
		char				accountName[256];
	};

	//heritage from ICommand
	std::vector<std::string>	*getParam(IClientSocket *socket);
	IClientSocket::Message		*setParam(std::vector<std::string> *param);
	int							getSizeBody(void);
};
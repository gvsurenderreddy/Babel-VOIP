#pragma once

#include "ICommand.hpp"

class CommandDel : public ICommand{
public:
	CommandDel();
	~CommandDel();

	//body
	struct Body{
		char	accountName[256];
	};

	//heritage from ICommand
	std::vector<std::string>	*getParam(IClientSocket *socket);
	IClientSocket::Message		*setParam(std::vector<std::string> *param);
    unsigned int				getSizeBody(void);
};
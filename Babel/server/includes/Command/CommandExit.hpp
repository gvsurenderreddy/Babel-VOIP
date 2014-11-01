#pragma once

#include "ICommand.hpp"

class CommandExit : public ICommand{
public:
	CommandExit();
	~CommandExit();

	//body
	struct NO_PADDING Body{

	};

	//heritage from ICommand
	std::vector<std::string>	*getParam(IClientSocket *socket);
	IClientSocket::Message		*setParam(const std::vector<std::string> &param);
    unsigned int				getSizeBody(void);
};
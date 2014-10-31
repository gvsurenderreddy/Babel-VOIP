#pragma once

#include "ICommand.hpp"

class CommandList : public ICommand{
public:
	CommandList();
	~CommandList();

	//body
	struct __attribute__ ((packed)) Body{
		
	};

	//heritage from ICommand
	std::vector<std::string>	*getParam(IClientSocket *socket);
	IClientSocket::Message		*setParam(std::vector<std::string> *param);
    unsigned int				getSizeBody(void);
};
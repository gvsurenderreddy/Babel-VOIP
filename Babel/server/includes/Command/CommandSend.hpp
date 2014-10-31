#pragma once

#include "ICommand.hpp"

class CommandSend : public ICommand{
public:
	CommandSend();
	~CommandSend();

	//body
	struct __attribute__ ((packed)) Body{
		char				accountName[256];
		char				textMessage[4096];
	};

    struct __attribute__ ((packed)) BodySend{
        ICommand::Header	header;
        char				accountName[256];
        char				textMessage[4096];
    };

	//heritage from ICommand
	std::vector<std::string>	*getParam(IClientSocket *socket);
	IClientSocket::Message		*setParam(std::vector<std::string> *param);
    unsigned int				getSizeBody(void);
};
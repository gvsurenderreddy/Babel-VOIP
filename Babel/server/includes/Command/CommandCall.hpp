#pragma once

#include "ICommand.hpp"

class CommandCall : public ICommand{
public:
	CommandCall();
	~CommandCall();

	//body
	struct __attribute__ ((packed)) Body{
		char	accountName[256];
	};

    struct __attribute__ ((packed)) BodySend{
        ICommand::Header	header;
        char				accountName[256];
    };

	//heritage from ICommand
	std::vector<std::string>	*getParam(IClientSocket *socket);
	IClientSocket::Message		*setParam(std::vector<std::string> *param);
    unsigned int				getSizeBody(void);
};
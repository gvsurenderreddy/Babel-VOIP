#pragma once

#include "ICommand.hpp"

class CommandAdd : public ICommand{
public:
	CommandAdd();
	~CommandAdd();

	//body
#ifdef WIN32
	struct __declspec(align(1)) Body{
		char	accountName[256];
	};

	struct __declspec(align(1)) BodySend{
		ICommand::Header	header;
		char				accountName[256];
	};
#else
	struct __attribute__((packed)) Body{
		char	accountName[256];
	};

	struct __attribute__((packed)) BodySend{
		ICommand::Header	header;
		char				accountName[256];
	};
#endif

	//heritage from ICommand
	std::vector<std::string>	*getParam(IClientSocket *socket);
	IClientSocket::Message		*setParam(std::vector<std::string> *param);
    unsigned int			    getSizeBody(void);
};
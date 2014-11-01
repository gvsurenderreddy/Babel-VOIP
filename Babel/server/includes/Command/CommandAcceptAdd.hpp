#pragma once

#include "ICommand.hpp"

class CommandAcceptAdd : public ICommand{
public:
	CommandAcceptAdd();
	~CommandAcceptAdd();

	//body
#ifdef WIN32
	struct __declspec(align(1)) Body{
		char				accountName[256];
		char				hasAccepted;
	};

	struct __declspec(align(1)) BodySend{
		ICommand::Header	header;
		char				accountName[256];
		char				hasAccepted;
	};
#else
	struct __attribute__((packed)) Body{
		char				accountName[256];
		char				hasAccepted;
	};

	struct __attribute__((packed)) BodySend{
		ICommand::Header	header;
		char				accountName[256];
		char				hasAccepted;
	};
#endif

	//heritage from ICommand
	std::vector<std::string>	*getParam(IClientSocket *socket);
	IClientSocket::Message		*setParam(std::vector<std::string> *param);
	unsigned int				getSizeBody(void);
};
#pragma once

#include "ICommand.hpp"

class CommandShow : public ICommand{
public:
	CommandShow();
	~CommandShow();

	//body
#ifdef WIN32
	struct __declspec(align(1)) Body{
		char				accountName[256];
	};

	struct __declspec(align(1)) BodySend{
		ICommand::Header	header;
		char				accountName[256];
		char				pseudo[256];
		char				status;
		char				isConnected;
	};
#else
	struct __attribute__((packed)) Body{
		char				accountName[256];
	};

	struct __attribute__((packed)) BodySend{
		ICommand::Header	header;
		char				accountName[256];
		char				pseudo[256];
		char				status;
		char				isConnected;
	};
#endif

	//heritage from ICommand
	std::vector<std::string>	*getParam(IClientSocket *socket);
	IClientSocket::Message		*setParam(std::vector<std::string> *param);
    unsigned int				getSizeBody(void);
};
#pragma once

#include "ICommand.hpp"

class CommandLog : public ICommand{
public:
	CommandLog();
	~CommandLog();

	//body
#ifdef WIN32
	struct __declspec(align(1)) Body{
		char				accountName[256];
		char				password[256];
	};
#else
	struct __attribute__((packed)) Body{
		char				accountName[256];
		char				password[256];
	};
#endif

	//heritage from ICommand
	std::vector<std::string>	*getParam(IClientSocket *socket);
	IClientSocket::Message		*setParam(std::vector<std::string> *param);
    unsigned int				getSizeBody(void);
};
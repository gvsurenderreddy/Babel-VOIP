#pragma once

#include "ICommand.hpp"

class CommandUpdate : public ICommand{
public:
	CommandUpdate();
	~CommandUpdate();

	//body
#ifdef WIN32
	struct __declspec(align(1)) Body{
		char	accountName[256];
		char	pseudo[256];
		char	password[256];
		char	status;
	};
#else
	struct __attribute__((packed)) Body{
		char	accountName[256];
		char	pseudo[256];
		char	password[256];
		char	status;
	};
#endif

	//heritage from ICommand
	std::vector<std::string>	*getParam(IClientSocket *socket);
	IClientSocket::Message		*setParam(std::vector<std::string> *param);
    unsigned int				getSizeBody(void);
};
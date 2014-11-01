#pragma once

#include "ICommand.hpp"

class CommandExit : public ICommand{
public:
	CommandExit();
	~CommandExit();

	//body
#ifdef WIN32
	struct __declspec(align(1)) Body{

	};
#else
	struct __attribute__((packed)) Body{

	};
#endif

	//heritage from ICommand
	std::vector<std::string>	*getParam(IClientSocket *socket);
	IClientSocket::Message		*setParam(std::vector<std::string> *param);
    unsigned int				getSizeBody(void);
};
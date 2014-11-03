#pragma once

#include "ICommand.hpp"

class CommandLog : public ICommand{
public:
	CommandLog();
	~CommandLog();

	//body
    #pragma pack(push, 1)
	struct Body{
		char				accountName[256];
		char				password[256];
	};
    #pragma pack(pop)

	//heritage from ICommand
	std::vector<std::string>	*getParam(IClientSocket *socket);
	IClientSocket::Message		*setParam(const std::vector<std::string> &param);
    unsigned int				getSizeBody(void);
};
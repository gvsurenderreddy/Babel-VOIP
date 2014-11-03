#pragma once

#include "ICommand.hpp"

class CommandUpdate : public ICommand{
public:
	CommandUpdate();
	~CommandUpdate();

	//body
    #pragma pack(push, 1)
	struct Body{
		char	accountName[256];
		char	pseudo[256];
		char	password[256];
		char	status;
	};
    #pragma pack(pop)

	//heritage from ICommand
	std::vector<std::string>	*getParam(IClientSocket *socket);
	IClientSocket::Message		*setParam(const std::vector<std::string> &param);
    unsigned int				getSizeBody(void);
};
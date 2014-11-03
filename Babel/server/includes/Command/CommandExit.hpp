#pragma once

#include "ICommand.hpp"

class CommandExit : public ICommand{
public:
	CommandExit();
	~CommandExit();

	//body
    #pragma pack(push, 1)
	struct Body{

	};
    #pragma pack(pop)

	//heritage from ICommand
	std::vector<std::string>	*getParam(IClientSocket *socket);
	IClientSocket::Message		*setParam(const std::vector<std::string> &param);
    unsigned int				getSizeBody(void);
};
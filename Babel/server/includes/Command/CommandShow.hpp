#pragma once

#include "ICommand.hpp"

class CommandShow : public ICommand{
public:
	CommandShow();
	~CommandShow();

	//body
    #pragma pack(push, 1)
	struct Body{
		char				accountName[256];
	};

	struct BodySend{
		ICommand::Header	header;
		char				accountName[256];
		char				pseudo[256];
		char				status;
		char				isConnected;
	};
    #pragma pack(pop)

	//heritage from ICommand
	std::vector<std::string>	*getParam(IClientSocket *socket);
	IClientSocket::Message		*setParam(const std::vector<std::string> &param);
    unsigned int				getSizeBody(void);
};
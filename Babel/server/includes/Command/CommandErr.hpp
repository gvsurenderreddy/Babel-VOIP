#pragma once

#include "ICommand.hpp"

class CommandErr : public ICommand{
public:
	CommandErr();
	~CommandErr();

	//body
	struct NO_PADDING Body{
		ICommand::Header	header;
		int					instructionCode;
		int					errorCode;
	};

	//heritage from ICommand
	std::vector<std::string>	*getParam(IClientSocket *socket);
	IClientSocket::Message		*setParam(const std::vector<std::string> &param);
    unsigned int				getSizeBody(void);
};
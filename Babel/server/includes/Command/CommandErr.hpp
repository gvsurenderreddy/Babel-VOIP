#pragma once

#include "ICommand.hpp"

class CommandErr : public ICommand{
public:
	CommandErr();
	~CommandErr();

	//body
#ifdef WIN32
	struct __declspec(align(1)) Body{
		ICommand::Header	header;
		int					instructionCode;
		int					errorCode;
	};
#else
	struct __attribute__((packed)) Body{
		ICommand::Header	header;
		int					instructionCode;
		int					errorCode;
	};
#endif

	//heritage from ICommand
	std::vector<std::string>	*getParam(IClientSocket *socket);
	IClientSocket::Message		*setParam(std::vector<std::string> *param);
    unsigned int				getSizeBody(void);
};
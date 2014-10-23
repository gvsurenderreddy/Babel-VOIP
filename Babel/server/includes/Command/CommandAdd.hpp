#pragma once

#include "ICommand.hpp"

class CommandAdd : public ICommand{
public:
	//body
	struct Body{
		char	accountName[256];
	};

	//heritage from ICommand
	std::vector<std::string>	*getParam(TcpClient &socket);
	ICommand::Instruction		getInstruction(void);
	int							getSizeHeader(void);
	int							getSizeBody(void);
};
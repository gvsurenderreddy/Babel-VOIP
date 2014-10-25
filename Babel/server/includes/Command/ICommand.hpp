#pragma once

#include <vector>
#include <string>
#include "TcpClient.hpp"

class ICommand{
public:
	//instruction
	enum Instruction {
		REG				= 1,
		LOG				= 2,
		LIST			= 3,
		SHOW			= 4,
		ADD				= 5,
		ACCEPT_ADD		= 6,
		DEL				= 7,
		EXIT			= 8,
		UPDATE			= 9,
		SEND			= 10, 
		CALL			= 11,
		ACCEPT_CALL		= 12,
		CLOSE_CALL		= 13,
		ERR				= 14
	};

	//header
	static const unsigned int	MAGIC_CODE;
	static const unsigned int	HEADER_SIZE;

	struct Header{
		int	magicCode;
		int	instructionCode;
	};

	//virtual destructor
	virtual ~ICommand() {}

	//handle ICommand
	virtual std::vector<std::string>	*getParam(IClientSocket *socket) = 0;
	virtual IClientSocket::Message		*setParam(std::vector<std::string> *param) = 0;
	virtual int							getSizeBody(void) = 0;
};
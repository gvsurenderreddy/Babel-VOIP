#pragma once

#include <vector>
#include <string>
#include "TcpClient.hpp"

class ICommand{
public:
	//instruction
	enum Instruction {
        REG         = 0x01,
        LOG         = 0x02,
        LIST        = 0x03,
        SHOW        = 0x04,
        ADD         = 0x05,
        ACCEPT_ADD  = 0x06,
        DEL         = 0x07,
        EXIT        = 0x08,
        UPDATE      = 0x09,
        SEND        = 0x0A,
        CALL        = 0x0B,
        ACCEPT_CALL = 0x0C,
        CLOSE_CALL  = 0x0D,
        ERR         = 0x0E,
        UNKNOWN_INSTRUCTION
	};

	//header
	static const unsigned int	MAGIC_CODE;
	static const unsigned int	HEADER_SIZE;

#ifdef WIN32
	struct __declspec(align(1)) Header{
		int	magicCode;
		int	instructionCode;
	};
#else
	struct __attribute__((packed)) Header{
		int	magicCode;
		int	instructionCode;
	};
#endif

	//virtual destructor
	virtual ~ICommand() {}

	//handle ICommand
	virtual std::vector<std::string>	*getParam(IClientSocket *socket) = 0;
	virtual IClientSocket::Message		*setParam(std::vector<std::string> *param) = 0;
    virtual unsigned int				getSizeBody(void) = 0;
};
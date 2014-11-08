#pragma once

#include "ICommand.hpp"

class CommandErr : public ICommand, private boost::noncopyable {

    // default ctor-dtor
    public:
        CommandErr() { }
        virtual ~CommandErr() { }

    // private coplien form
    private:
        CommandErr(const CommandErr &) = delete;
        const CommandErr & operator = (const CommandErr &) = delete;

	//body
    #pragma pack(push, 1)
	struct Body{
		ICommand::Header	header;
		int32_t				instructionCode;
		int32_t				errorCode;
	};
    #pragma pack(pop)

	//heritage from ICommand
	std::vector<std::string>	*getParam(IClientSocket *socket);
	IClientSocket::Message		*setParam(const std::vector<std::string> &param);
    unsigned int				getSizeBody(void);
};
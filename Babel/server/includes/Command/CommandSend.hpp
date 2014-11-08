#pragma once

#include "ICommand.hpp"

class CommandSend : public ICommand, private boost::noncopyable {

    // default ctor-dtor
    public:
        CommandSend() { }
        virtual ~CommandSend() { }

    // private coplien form
    private:
        CommandSend(const CommandSend &) = delete;
        const CommandSend & operator = (const CommandSend &) = delete;

	//body
    #pragma pack(push, 1)
	struct Body{
		char				accountName[256];
		char				textMessage[4096];
	};

	struct BodySend{
		ICommand::Header	header;
		char				accountName[256];
		char				textMessage[4096];
	};
    #pragma pack(pop)

	//heritage from ICommand
	std::vector<std::string>	*getParam(IClientSocket *socket);
	IClientSocket::Message		*setParam(const std::vector<std::string> &param);
    unsigned int				getSizeBody(void);
};
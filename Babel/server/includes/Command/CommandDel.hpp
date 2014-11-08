#pragma once

#include "ICommand.hpp"

class CommandDel : public ICommand, private boost::noncopyable {

    // default ctor-dtor
    public:
        CommandDel() { }
        virtual ~CommandDel() { }

    // private coplien form
    private:
        CommandDel(const CommandDel &) = delete;
        const CommandDel & operator = (const CommandDel &) = delete;

	//body
    #pragma pack(push, 1)
	struct Body{
		char	accountName[256];
	};

	struct BodySend{
		ICommand::Header	header;
		char				accountName[256];
	};
    #pragma pack(pop)

	//heritage from ICommand
	std::vector<std::string>	*getParam(IClientSocket *socket);
	IClientSocket::Message		*setParam(const std::vector<std::string> &param);
    unsigned int				getSizeBody(void);
};
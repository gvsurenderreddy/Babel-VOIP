#pragma once

#include "ICommand.hpp"

class CommandAcceptAdd : public ICommand, private boost::noncopyable {

    // default ctor-dtor
    public:
        CommandAcceptAdd() { }
        virtual ~CommandAcceptAdd() { }

    // private coplien form
    private:
        CommandAcceptAdd(const CommandAcceptAdd &) = delete;
        const CommandAcceptAdd & operator = (const CommandAcceptAdd &) = delete;

	//body
    #pragma pack(push, 1)
	struct Body{
		char				accountName[256];
		char				hasAccepted;
	};

	struct BodySend{
		ICommand::Header	header;
		char				accountName[256];
		char				hasAccepted;
	};
    #pragma pack(pop)

	//heritage from ICommand
	std::vector<std::string>	*getParam(IClientSocket *socket);
	IClientSocket::Message		*setParam(const std::vector<std::string> &param);
	unsigned int				getSizeBody(void);
};
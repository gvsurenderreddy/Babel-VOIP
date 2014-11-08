#pragma once

#include "ICommand.hpp"

class CommandAcceptCall : public ICommand, private boost::noncopyable {

    // default ctor-dtor
    public:
        CommandAcceptCall() { }
        virtual ~CommandAcceptCall() { }

    // private coplien form
    private:
        CommandAcceptCall(const CommandAcceptCall &) = delete;
        const CommandAcceptCall & operator = (const CommandAcceptCall &) = delete;

	//body
    #pragma pack(push, 1)
	struct Body{
		char				accountName[256];
		char				hasAccepted;
	};
	struct BodySend{
		ICommand::Header	header;
		char				accountName[256];
		char				host[15];
		char				hasAccepted;
	};
    #pragma pack(pop)

	//heritage from ICommand
	std::vector<std::string>	*getParam(IClientSocket *socket);
	IClientSocket::Message		*setParam(const std::vector<std::string> &param);
    unsigned int				getSizeBody(void);
};
#pragma once

#include "ICommand.hpp"

class CommandCall : public ICommand, private boost::noncopyable {
    
    // default ctor-dtor
    public:
        CommandCall() { }
        virtual ~CommandCall() { }

    // private coplien form
    private:
        CommandCall(const CommandCall &) = delete;
        const CommandCall & operator = (const CommandCall &) = delete;


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
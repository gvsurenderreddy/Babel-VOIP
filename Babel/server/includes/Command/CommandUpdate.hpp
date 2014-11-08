#pragma once

#include "ICommand.hpp"

class CommandUpdate : public ICommand, private boost::noncopyable {

    // default ctor-dtor
    public:
        CommandUpdate() { }
        virtual ~CommandUpdate() { }

    // private coplien form
    private:
        CommandUpdate(const CommandUpdate &) = delete;
        const CommandUpdate & operator = (const CommandUpdate &) = delete;

	//body
    #pragma pack(push, 1)
	struct Body{
		char	accountName[256];
		char	pseudo[256];
		char	password[256];
		char	status;
	};
    #pragma pack(pop)

	//heritage from ICommand
	std::vector<std::string>	*getParam(IClientSocket *socket);
	IClientSocket::Message		*setParam(const std::vector<std::string> &param);
    unsigned int				getSizeBody(void);
};
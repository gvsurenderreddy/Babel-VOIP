#pragma once

#include "ICommand.hpp"

class CommandAdd : public ICommand, private boost::noncopyable {

    // default ctor-dtor
    public:
        CommandAdd() { }
        virtual ~CommandAdd() { }

    // private coplien form
    private:
        CommandAdd(const CommandAdd &) = delete;
        const CommandAdd & operator = (const CommandAdd &) = delete;

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
    unsigned int			    getSizeBody(void);
};
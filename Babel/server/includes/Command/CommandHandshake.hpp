#pragma once

#include "ICommand.hpp"

class CommandHandshake : public ICommand, private boost::noncopyable {

    // default ctor-dtor
    public:
        CommandHandshake() { }
        virtual ~CommandHandshake() { }

    // private coplien form
    private:
        CommandHandshake(const CommandHandshake &) = delete;
        const CommandHandshake & operator = (const CommandHandshake &) = delete;

	//body
    #pragma pack(push, 1)
	struct Body{

	};

    struct BodySend{
        ICommand::Header	header;
    };
    #pragma pack(pop)

	//heritage from ICommand
	std::vector<std::string>	*getParam(IClientSocket *socket);
	IClientSocket::Message		*setParam(const std::vector<std::string> &param);
    unsigned int				getSizeBody(void);
};
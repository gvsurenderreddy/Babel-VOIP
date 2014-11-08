#pragma once

#include "ICommand.hpp"

class CommandExit : public ICommand, private boost::noncopyable {

    // default ctor-dtor
    public:
        CommandExit() { }
        virtual ~CommandExit() { }

    // private coplien form
    private:
        CommandExit(const CommandExit &) = delete;
        const CommandExit & operator = (const CommandExit &) = delete;

	//body
    #pragma pack(push, 1)
	struct Body{

	};
    #pragma pack(pop)

	//heritage from ICommand
	std::vector<std::string>	*getParam(IClientSocket *socket);
	IClientSocket::Message		*setParam(const std::vector<std::string> &param);
    unsigned int				getSizeBody(void);
};
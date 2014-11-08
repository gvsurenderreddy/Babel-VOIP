#pragma once

#include "ICommand.hpp"

class CommandList : public ICommand, private boost::noncopyable {

    // default ctor-dtor
    public:
        CommandList() { }
        virtual ~CommandList() { }

    // private coplien form
    private:
        CommandList(const CommandList &) = delete;
        const CommandList & operator = (const CommandList &) = delete;

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
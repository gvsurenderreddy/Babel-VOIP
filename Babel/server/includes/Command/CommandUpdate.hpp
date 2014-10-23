#include "ICommand.hpp"

class CommandUpdate : public ICommand{
public:
	//body
	struct Body{
		char	accountName[256];
		char	pseudo[256];
		char	password[256];
		char	status;
	};

	//heritage from ICommand
	std::vector<std::string>	*getParam(TcpClient &socket);
	ICommand::Instruction		getInstruction(void);
	int							getSizeHeader(void);
	int							getSizeBody(void);
};
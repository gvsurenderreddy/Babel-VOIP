#include "ICommand.hpp"
#include "TcpClient.hpp"

class HandleCmd{
public:
	HandleCmd(TcpClient &socket);
	~HandleCmd();

	std::vector<std::string>	*unPackCmd(void);
	ICommand::Instruction		getInstruction(void);

private:
	ICommand				*body;
	ICommand::Header		*header;
	TcpClient				&socket;
	ICommand::Instruction	instruction;
};
#include "ICommand.hpp"
#include "TcpClient.hpp"

class HandleCmd{
public:
	HandleCmd(IClientSocket *socket);
	~HandleCmd();

	std::vector<std::string>	*unPackCmd(void);
	ICommand::Instruction		getInstruction(void);
	void						packCmd(ICommand::Instruction instruction, std::vector<std::string> &param);

private:
	ICommand				*body;
	ICommand::Header		*header;
	IClientSocket			*socket;
	ICommand::Instruction	instruction;
};
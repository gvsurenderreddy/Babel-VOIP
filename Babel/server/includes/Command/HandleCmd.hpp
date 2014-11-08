#include "ICommand.hpp"
#include "TcpClient.hpp"

class HandleCmd : private boost::noncopyable {
public:
    HandleCmd(IClientSocket *socket) : header(NULL), socket(socket) { }
    virtual ~HandleCmd() { }

private:
    HandleCmd(const HandleCmd &) = delete;
    const HandleCmd & operator = (const HandleCmd &) = delete;

public:
	std::vector<std::string>	*unPackCmd(void);
	ICommand::Instruction		getInstruction(void);
	void						packCmd(ICommand::Instruction instruction, const std::vector<std::string> &param);

private:
	ICommand				*body;
	ICommand::Header		*header;
	IClientSocket			*socket;
	ICommand::Instruction	instruction;
};
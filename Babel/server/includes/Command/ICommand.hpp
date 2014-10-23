#include <vector>
#include <string>

class ICommand{
public:
	//instruction
	enum Instruction {
		REG,
		LOG,
		LIST,
		SHOW,
		ADD,
		ACCEPT_ADD,
		DEL,
		EXIT,
		UPDATE,
		SEND,
		CALL,
		ACCEPT_CALL,
		CLOSE_CALL,
		ERR
	};

	//header
	static const unsigned int	MAGIC_CODE;
	static const unsigned int	HEADER_SIZE;

	struct Header{
		int	magicCode;
		int	instructionCode;
	};

	//virtual destructor
	virtual ~ICommand() {}

	//handle ICommand
	virtual std::vector<std::string>	getParam(void) = 0;
	virtual ICommand::Instruction		getInstruction(void) = 0;
	virtual int							getSizeHeader(void) = 0;
	virtual int							getSizeBody(void) = 0;
};
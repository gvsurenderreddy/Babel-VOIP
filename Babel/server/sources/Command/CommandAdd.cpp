#include "../../includes/Command/CommandAdd.hpp"

/*
** Heritage from ICommand
*/
std::vector<std::string>	CommandAdd::getParam(void){
	std::vector<std::string>	t;
	return t;
}

ICommand::Instruction		CommandAdd::getInstruction(void){
	ICommand::Instruction	t;
	return t;
}

int							CommandAdd::getSizeHeader(void){
	return ICommand::HEADER_SIZE;
}

int							CommandAdd::getSizeBody(void){
	return sizeof CommandAdd::Body;
}
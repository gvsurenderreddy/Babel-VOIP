#include "../../includes/Command/CommandUpdate.hpp"

/*
** Heritage from ICommand
*/
std::vector<std::string>	CommandUpdate::getParam(void){
	std::vector<std::string>	t;
	return t;
}

ICommand::Instruction		CommandUpdate::getInstruction(void){
	ICommand::Instruction	t;
	return t;
}

int							CommandUpdate::getSizeHeader(void){
	return ICommand::HEADER_SIZE;
}

int							CommandUpdate::getSizeBody(void){
	return sizeof CommandUpdate::Body;
}
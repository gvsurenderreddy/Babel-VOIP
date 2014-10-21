#include "CommandList.hpp"

CommandList::CommandList(void) {
}

CommandList::~CommandList(void) {
}

ICommand::Instruction	CommandList::getInstruction(void) const {
}

IClientSocket::Message	CommandList::getMessage(void) const {
}

unsigned int	CommandList::getSizeToRead(void) const {
}

void	CommandList::initFromMessage(const IClientSocket::Message &message) {
}

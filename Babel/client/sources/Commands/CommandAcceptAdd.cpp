#include "CommandAcceptAdd.hpp"
#include "CommandException.hpp"
#include <cstring>

CommandAcceptAdd::CommandAcceptAdd(void)
	: mAccountName(""), mHasAccepted(false) {}

CommandAcceptAdd::~CommandAcceptAdd(void) {
}

ICommand::Instruction	CommandAcceptAdd::getInstruction(void) const {
	return ICommand::ACCEPT_ADD;
}

IClientSocket::Message	CommandAcceptAdd::getMessage(void) const {
	IClientSocket::Message message;
	CommandAcceptAdd::PacketFromClient *packet = new CommandAcceptAdd::PacketFromClient;

	std::memset(packet, 0, sizeof(CommandAcceptAdd::PacketFromClient));
	std::memcpy(packet->accountName, mAccountName.toStdString().c_str(), MIN(mAccountName.length(), sizeof(packet->accountName) - 1));
	packet->hasAccepted = mHasAccepted;
	packet->header.magicCode = ICommand::MAGIC_CODE;
	packet->header.instructionCode = ICommand::ACCEPT_ADD;

	message.msg = reinterpret_cast<char *>(packet);
	message.msgSize = sizeof(CommandAcceptAdd::PacketFromClient);

	return message;
}

unsigned int	CommandAcceptAdd::getSizeToRead(void) const {
	throw new CommandException("No packet are sent from the server for this command");
}

void	CommandAcceptAdd::initFromMessage(const IClientSocket::Message &) {
	throw new CommandException("No packet are sent from the server for this command");
}

const QString	&CommandAcceptAdd::getAccountName(void) const {
	return mAccountName;
}

bool	CommandAcceptAdd::hasAccepted(void) const {
	return mHasAccepted;
}

void	CommandAcceptAdd::setAccountName(const QString &accountName) {
	mAccountName = accountName;
}

void	CommandAcceptAdd::setHasAccepted(bool hasAccepted) {
	mHasAccepted = hasAccepted;
}

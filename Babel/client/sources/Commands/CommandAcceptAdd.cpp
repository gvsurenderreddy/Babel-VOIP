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
	CommandAcceptAdd::PacketFromClient packet;

	std::memset(&packet, 0, sizeof(CommandAcceptAdd::PacketFromClient));
	std::memcpy(packet.accountName, mAccountName.toStdString().c_str(), std::min(mAccountName.length(), static_cast<int>(sizeof(packet.accountName) - 1)));
	packet.hasAccepted = mHasAccepted;

	IClientSocket::Message message;
	message.msg.assign(reinterpret_cast<char *>(&packet), reinterpret_cast<char *>(&packet + 1));
	message.msgSize = sizeof(CommandAcceptAdd::PacketFromClient);

	return message;
}

unsigned int	CommandAcceptAdd::getSizeToRead(void) const {
	throw CommandException("No packet are sent from the server for this command");
}

void	CommandAcceptAdd::initFromMessage(const IClientSocket::Message &) {
	throw CommandException("No packet are sent from the server for this command");
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

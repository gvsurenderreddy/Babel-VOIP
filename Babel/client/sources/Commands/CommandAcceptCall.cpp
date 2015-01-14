#include "CommandAcceptCall.hpp"
#include "CommandException.hpp"
#include <cstring>

CommandAcceptCall::CommandAcceptCall(void)
: mAccountName(""), mHost(""), mHasAccepted(false) {}

CommandAcceptCall::~CommandAcceptCall(void) {
}

ICommand::Instruction	CommandAcceptCall::getInstruction(void) const {
	return ICommand::ACCEPT_CALL;
}

IClientSocket::Message	CommandAcceptCall::getMessage(void) const {
	CommandAcceptCall::PacketFromClient packet;

	std::memset(&packet, 0, sizeof(CommandAcceptCall::PacketFromClient));
	std::memcpy(packet.accountName, mAccountName.toStdString().c_str(), std::min(static_cast<int>(sizeof(packet.accountName) - 1), mAccountName.length()));
	packet.hasAccepted = mHasAccepted;

	IClientSocket::Message message;
	message.msg.assign(reinterpret_cast<char *>(&packet), reinterpret_cast<char *>(&packet + 1));
	message.msgSize = sizeof(CommandAcceptCall::PacketFromClient);

	return message;
}

unsigned int	CommandAcceptCall::getSizeToRead(void) const {
  return sizeof(CommandAcceptCall::PacketFromServer);
}

void	CommandAcceptCall::initFromMessage(const IClientSocket::Message &message) {
  if (message.msgSize != sizeof(CommandAcceptCall::PacketFromServer))
		throw CommandException("Message has an invalid size");

	CommandAcceptCall::PacketFromServer packet = *reinterpret_cast<const CommandAcceptCall::PacketFromServer *>(message.msg.data());

	packet.accountName[sizeof(packet.accountName) - 1] = 0;
	mAccountName = packet.accountName;
	mHost = packet.host;
	mHasAccepted = packet.hasAccepted;
}

const QString	&CommandAcceptCall::getAccountName(void) const {
	return mAccountName;
}

const QString	&CommandAcceptCall::getHost(void) const {
	return mHost;
}

bool	CommandAcceptCall::hasAccepted(void) const {
	return mHasAccepted;
}

void	CommandAcceptCall::setAccountName(const QString &accountName) {
	mAccountName = accountName;
}

void	CommandAcceptCall::setHost(const QString &host) {
	mHost = host;
}

void	CommandAcceptCall::setHasAccepted(bool hasAccepted) {
	mHasAccepted = hasAccepted;
}

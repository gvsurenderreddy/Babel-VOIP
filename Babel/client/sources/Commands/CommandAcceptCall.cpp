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
	IClientSocket::Message message;
	CommandAcceptCall::PacketFromClient *packet = new CommandAcceptCall::PacketFromClient;

	std::memset(packet, 0, sizeof(CommandAcceptCall::PacketFromClient));
	std::memcpy(packet->accountName, mAccountName.toStdString().c_str(), MIN(sizeof(packet->accountName), mAccountName.length()));
	packet->hasAccepted = mHasAccepted;
	packet->header.magicCode = ICommand::MAGIC_CODE;
	packet->header.instructionCode = ICommand::ACCEPT_CALL;

	message.msg = reinterpret_cast<char *>(packet);
	message.msgSize = sizeof(CommandAcceptCall::PacketFromClient);

	return message;
}

unsigned int	CommandAcceptCall::getSizeToRead(void) const {
  return sizeof(CommandAcceptCall::PacketFromServer);
}

void	CommandAcceptCall::initFromMessage(const IClientSocket::Message &message) {
  if (message.msgSize != sizeof(CommandAcceptCall::PacketFromServer))
		throw new CommandException("Message has an invalid size");

	CommandAcceptCall::PacketFromServer *packet = reinterpret_cast<CommandAcceptCall::PacketFromServer *>(message.msg);
	mAccountName = packet->accountName;
	mHost = packet->host;
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

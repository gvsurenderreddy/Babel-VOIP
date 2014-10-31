#include "CommandShow.hpp"
#include "CommandException.hpp"
#include <cstring>

CommandShow::CommandShow(void)
: mAccountName(""), mPseudo(""), mStatus(Contact::DISCONNECTED), mIsConnected(false) {}

CommandShow::~CommandShow(void) {
}

ICommand::Instruction	CommandShow::getInstruction(void) const {
	return ICommand::SHOW;
}

IClientSocket::Message	CommandShow::getMessage(void) const {
	IClientSocket::Message message;
	CommandShow::PacketFromClient *packet = new CommandShow::PacketFromClient;

	std::memset(packet, 0, sizeof(CommandShow::PacketFromClient));
	std::memcpy(packet->accountName, mAccountName.toStdString().c_str(), MIN(mAccountName.length(), sizeof(packet->accountName) - 1));
	packet->header.magicCode = ICommand::MAGIC_CODE;
	packet->header.instructionCode = ICommand::SHOW;

	message.msg = reinterpret_cast<char *>(packet);
	message.msgSize = sizeof(CommandShow::PacketFromClient);

	return message;
}

unsigned int	CommandShow::getSizeToRead(void) const {
  return sizeof(PacketFromServer);
}

void	CommandShow::initFromMessage(const IClientSocket::Message &message) {
  if (message.msgSize != sizeof(CommandShow::PacketFromServer))
		throw CommandException("Message has an invalid size");

	CommandShow::PacketFromServer *packet = new CommandShow::PacketFromServer;
	packet->accountName[sizeof(packet->accountName) - 1] = 0;
	mAccountName = packet->accountName;
	packet->pseudo[sizeof(packet->pseudo) - 1] = 0;
	mPseudo = packet->pseudo;
	mStatus = static_cast<Contact::Status>(packet->status);
	mIsConnected = packet->isConnected;
}

const QString	&CommandShow::getAccountName(void) const {
	return mAccountName;
}

const QString	&CommandShow::getPseudo(void) const {
	return mPseudo;
}

Contact::Status	CommandShow::getStatus(void) const {
	return mStatus;
}

bool	CommandShow::isConnected(void) const {
	return mIsConnected;
}

void	CommandShow::setAccountName(const QString &accountName) {
	mAccountName = accountName;
}

void	CommandShow::setPseudo(const QString &pseudo) {
	mPseudo = pseudo;
}

void	CommandShow::setStatus(Contact::Status status) {
	mStatus = status;
}

void	CommandShow::setIsConnected(bool isConnected) {
	mIsConnected = isConnected;
}

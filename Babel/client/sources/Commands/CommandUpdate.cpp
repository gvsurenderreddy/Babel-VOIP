#include "CommandUpdate.hpp"
#include "CommandException.hpp"
#include <cstring>

CommandUpdate::CommandUpdate(void)
: mAccountName(""), mPseudo(""), mPassword(""), mStatus(Contact::DISCONNECTED) {}

CommandUpdate::~CommandUpdate(void) {
}

ICommand::Instruction	CommandUpdate::getInstruction(void) const {
	return ICommand::UPDATE;
}

IClientSocket::Message	CommandUpdate::getMessage(void) const {
	IClientSocket::Message message;
	CommandUpdate::PacketFromClient *packet = new CommandUpdate::PacketFromClient;

	std::memset(packet, 0, sizeof(CommandUpdate::PacketFromClient));
	std::memcpy(packet->accountName, mAccountName.toStdString().c_str(), MIN(mAccountName.length(), sizeof(packet->accountName) - 1));
	std::memcpy(packet->password, mPassword.toStdString().c_str(), MIN(mPassword.length(), sizeof(packet->password) - 1));
	std::memcpy(packet->pseudo, mPseudo.toStdString().c_str(), MIN(mPseudo.length(), sizeof(packet->pseudo) - 1));
	packet->status = mStatus;
	packet->header.magicCode = ICommand::MAGIC_CODE;
	packet->header.instructionCode = ICommand::UPDATE;

	message.msg = reinterpret_cast<char *>(packet);
	message.msgSize = sizeof(CommandUpdate::PacketFromClient);

	return message;
}

unsigned int	CommandUpdate::getSizeToRead(void) const {
	throw CommandException("No packet are sent from the server for this command.");
}

void	CommandUpdate::initFromMessage(const IClientSocket::Message &) {
	throw CommandException("No packet are sent from the server for this command.");
}

const QString	&CommandUpdate::getAccountName(void) const {
	return mAccountName;
}

const QString	&CommandUpdate::getPseudo(void) const {
	return mPseudo;
}

const QString	&CommandUpdate::getPassword(void) const {
	return mPassword;
}

Contact::Status	CommandUpdate::getStatus(void) const {
	return mStatus;
}

void	CommandUpdate::setAccountName(const QString &accountName) {
	mAccountName = accountName;
}

void	CommandUpdate::setPseudo(const QString &pseudo) {
	mPseudo = pseudo;
}

void	CommandUpdate::setPassword(const QString &password) {
	mPassword = password;
}

void	CommandUpdate::setStatus(Contact::Status status) {
	mStatus = status;
}

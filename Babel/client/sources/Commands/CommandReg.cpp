#include "CommandReg.hpp"
#include "CommandException.hpp"
#include <cstring>

CommandReg::CommandReg(void)
	: mAccountName(""), mPseudo(""), mPassword("") {}

CommandReg::~CommandReg(void) {
}

ICommand::Instruction	CommandReg::getInstruction(void) const {
	return ICommand::REG;
}

IClientSocket::Message	CommandReg::getMessage(void) const {
	IClientSocket::Message message;
	CommandReg::PacketFromClient *packet = new CommandReg::PacketFromClient;

	std::memset(packet, 0, sizeof(CommandReg::PacketFromClient));
	std::memcpy(packet->accountName, mAccountName.toStdString().c_str(), MIN(mAccountName.length(), sizeof(packet->accountName) - 1));
	std::memcpy(packet->password, mPassword.toStdString().c_str(), MIN(mPassword.length(), sizeof(packet->password) - 1));
	std::memcpy(packet->pseudo, mPseudo.toStdString().c_str(), MIN(mPseudo.length(), sizeof(packet->pseudo) - 1));
	packet->header.magicCode = ICommand::MAGIC_CODE;
	packet->header.instructionCode = ICommand::REG;

	message.msg = reinterpret_cast<char *>(packet);
	message.msgSize = sizeof(CommandReg::PacketFromClient);

	return message;
}

unsigned int	CommandReg::getSizeToRead(void) const {
	throw CommandException("No packet are sent from the server for this command.");
}

void	CommandReg::initFromMessage(const IClientSocket::Message &) {
	throw CommandException("No packet are sent from the server for this command.");
}

const QString	&CommandReg::getAccountName(void) const {
	return mAccountName;
}

const QString	&CommandReg::getPseudo(void) const {
	return mPseudo;
}

const QString	&CommandReg::getPassword(void) const {
	return mPassword;
}

void	CommandReg::setAccountName(const QString &accountName) {
	mAccountName = accountName;
}

void	CommandReg::setPseudo(const QString &pseudo) {
	mPseudo = pseudo;
}

void	CommandReg::setPassword(const QString &password) {
	mPassword = password;
}

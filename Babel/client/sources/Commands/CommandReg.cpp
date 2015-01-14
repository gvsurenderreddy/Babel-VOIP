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
	CommandReg::PacketFromClient packet;

	std::memset(&packet, 0, sizeof(CommandReg::PacketFromClient));
	std::memcpy(packet.accountName, mAccountName.toStdString().c_str(), std::min(mAccountName.length(), static_cast<int>(sizeof(packet.accountName) - 1)));
	std::memcpy(packet.password, mPassword.toStdString().c_str(), std::min(mPassword.length(), static_cast<int>(sizeof(packet.password) - 1)));
	std::memcpy(packet.pseudo, mPseudo.toStdString().c_str(), std::min(mPseudo.length(), static_cast<int>(sizeof(packet.pseudo) - 1)));

	IClientSocket::Message message;
	message.msg.assign(reinterpret_cast<char *>(&packet), reinterpret_cast<char *>(&packet + 1));
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

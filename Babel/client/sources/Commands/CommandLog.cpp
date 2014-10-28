#include "CommandLog.hpp"
#include "CommandException.hpp"
#include <cstring>

CommandLog::CommandLog(void)
	: mAccountName(""), mPassword("") {}

CommandLog::~CommandLog(void) {
}

ICommand::Instruction	CommandLog::getInstruction(void) const {
	return ICommand::LOG;
}

IClientSocket::Message	CommandLog::getMessage(void) const {
	IClientSocket::Message message;
	CommandLog::PacketFromClient *packet = new CommandLog::PacketFromClient;

	std::memset(packet, 0, sizeof(CommandLog::PacketFromClient));
	std::memcpy(packet->accountName, mAccountName.toStdString().c_str(), MIN(mAccountName.length(), sizeof(packet->accountName) - 1));
	std::memcpy(packet->password, mPassword.toStdString().c_str(), MIN(mPassword.length(), sizeof(packet->password) - 1));
	packet->header.magicCode = ICommand::MAGIC_CODE;
	packet->header.instructionCode = ICommand::LOG;

	message.msg = reinterpret_cast<char *>(packet);
	message.msgSize = sizeof(CommandLog::PacketFromClient);

	return message;
}

unsigned int	CommandLog::getSizeToRead(void) const {
	throw CommandException("No packet are sent from the server for this command.");
}

void	CommandLog::initFromMessage(const IClientSocket::Message &) {
	throw CommandException("No packet are sent from the server for this command.");
}

const QString	&CommandLog::getAccountName(void) const {
	return mAccountName;
}

const QString	&CommandLog::getPassword(void) const {
	return mPassword;
}

void	CommandLog::setAccountName(const QString &accountName) {
	mAccountName = accountName;
}

void	CommandLog::setPassword(const QString &password) {
	mPassword = password;
}

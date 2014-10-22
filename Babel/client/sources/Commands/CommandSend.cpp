#include "CommandSend.hpp"
#include"CommandException.hpp"

CommandSend::CommandSend(void)
	: mAccountName(""), mTextMessage("") {}

CommandSend::~CommandSend(void) {
}

ICommand::Instruction	CommandSend::getInstruction(void) const {
	return ICommand::SEND;
}

IClientSocket::Message	CommandSend::getMessage(void) const {
	IClientSocket::Message message;
	CommandSend::PacketFromClient *packet = new CommandSend::PacketFromClient;

	std::memset(packet, 0, sizeof CommandSend::PacketFromClient);
	std::memcpy(packet->accountName, mAccountName.toStdString().c_str(), MIN(mAccountName.length(), sizeof packet->accountName));
	std::memcpy(packet->textMessage, mTextMessage.toStdString().c_str(), MIN(mTextMessage.length(), sizeof packet->textMessage));
	packet->header.magicCode = ICommand::MAGIC_CODE;
	packet->header.instructionCode = ICommand::LOG;

	message.msg = reinterpret_cast<char *>(packet);
	message.msgSize = sizeof CommandSend::PacketFromClient;

	return message;
}

unsigned int	CommandSend::getSizeToRead(void) const {
	return sizeof PacketFromServer;
}

void	CommandSend::initFromMessage(const IClientSocket::Message &message) {
	if (message.msgSize != sizeof CommandSend::PacketFromServer)
		throw new CommandException("Message has an invalid size");

	CommandSend::PacketFromServer *packet = reinterpret_cast<CommandSend::PacketFromServer *>(message.msg);
	mAccountName = packet->accountName;
	mTextMessage = packet->textMessage;
}

const QString	&CommandSend::getAccountName(void) const {
	return mAccountName;
}

const QString	&CommandSend::getTextMessage(void) const {
	return mTextMessage;
}

void	CommandSend::setAccountName(const QString &accountName) {
	mAccountName = accountName;
}

void	CommandSend::setTextMessage(const QString &textMessage) {
	mTextMessage = textMessage;
}

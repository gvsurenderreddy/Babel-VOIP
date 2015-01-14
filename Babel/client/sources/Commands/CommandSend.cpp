#include "CommandSend.hpp"
#include"CommandException.hpp"
#include <cstring>

CommandSend::CommandSend(void)
	: mAccountName(""), mTextMessage("") {}

CommandSend::~CommandSend(void) {
}

ICommand::Instruction	CommandSend::getInstruction(void) const {
	return ICommand::SEND;
}

IClientSocket::Message	CommandSend::getMessage(void) const {
	CommandSend::PacketFromClient packet;

	std::memset(&packet, 0, sizeof(CommandSend::PacketFromClient));
	std::memcpy(packet.accountName, mAccountName.toStdString().c_str(), std::min(mAccountName.length(), static_cast<int>(sizeof(packet.accountName) - 1)));
	std::memcpy(packet.textMessage, mTextMessage.toStdString().c_str(), std::min(mTextMessage.length(), static_cast<int>(sizeof(packet.textMessage) - 1)));

	IClientSocket::Message message;
	message.msg.assign(reinterpret_cast<char *>(&packet), reinterpret_cast<char *>(&packet + 1));
	message.msgSize = sizeof(CommandSend::PacketFromClient);

	return message;
}

unsigned int	CommandSend::getSizeToRead(void) const {
  return sizeof(PacketFromServer);
}

void	CommandSend::initFromMessage(const IClientSocket::Message &message) {
  if (message.msgSize != sizeof(CommandSend::PacketFromServer))
		throw CommandException("Message has an invalid size");

	CommandSend::PacketFromServer packet = *reinterpret_cast<const CommandSend::PacketFromServer *>(message.msg.data());

	packet.accountName[sizeof(packet.accountName) - 1] = 0;
	mAccountName = packet.accountName;
	packet.textMessage[sizeof(packet.textMessage) - 1] = 0;
	mTextMessage = packet.textMessage;
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

#include "CommandPacketBuilder.hpp"
#include "TcpClient.hpp"
#include "CommandException.hpp"
#include "SocketException.hpp"
#include <iostream>
CommandPacketBuilder::CommandPacketBuilder(void)
	: mClient(NULL), mCurrentCommand(NULL), mCurrentState(CommandPacketBuilder::HEADER)
{
	mClient = new TcpClient;
	mClient->setOnSocketEventListener(this);
}

CommandPacketBuilder::~CommandPacketBuilder(void) {
	if (mClient)
		delete mClient;

	if (mCurrentCommand)
		delete mCurrentCommand;
}

void	CommandPacketBuilder::sendCommand(const ICommand *command) {
	try {
		mClient->send(command->getMessage());
	}
	catch (const SocketException &e) {
		emit disconnectedFromHost();
	}
}

void	CommandPacketBuilder::connectToServer(const QString &addr, int port) {
	mClient->connect(addr.toStdString(), port);
}

void	CommandPacketBuilder::fetchCommandHeader(void) {
    std::cout << "fetch header" << std::endl;
	IClientSocket::Message message = mClient->receive(ICommand::HEADER_SIZE);
	ICommand::Header *header = reinterpret_cast<ICommand::Header *>(message.msg);

	mCurrentCommand = ICommand::getCommand(static_cast<ICommand::Instruction>(header->instructionCode));
	mCurrentState = CommandPacketBuilder::CONTENT;

    std::cout << std::endl;
    std::cout << "=== DEBUG ===" << std::endl;
    std::cout << "size to read: " << ICommand::HEADER_SIZE << std::endl;
    std::cout << "msg size: " << message.msgSize << std::endl;
    std::cout << "intruction code: " << std::hex << static_cast<ICommand::Instruction>(header->instructionCode) << std::endl;
    std::cout << "mCurrentCommand: " << mCurrentCommand << std::endl;
    std::cout << "magic code: " << std::hex << header->magicCode << std::endl;
    std::cout << "=== END DEBUG ===" << std::endl;
    std::cout << std::endl;

	if (header->magicCode != ICommand::MAGIC_CODE || mCurrentCommand == NULL) {
        std::cout << "wrong magic code or mcurrentcommand" << std::endl;
        std::cout << std::hex << header->magicCode << std::endl << std::hex << ICommand::MAGIC_CODE << std::endl;
        std::cout << mCurrentCommand << std::endl;
        std::cout << std::hex << static_cast<ICommand::Instruction>(header->instructionCode) << std::endl;
		mClient->closeClient();
		return;
	}

	onSocketReadable(mClient, mClient->nbBytesToRead());
}

void	CommandPacketBuilder::fetchCommandContent(void) {
    std::cout << "fetch content" << std::endl;
    std::cout << "size to read: " << mCurrentCommand->getSizeToRead() << std::endl;
	IClientSocket::Message message = mClient->receive(mCurrentCommand->getSizeToRead());
    std::cout << "msg size: " << message.msgSize << std::endl;
	try {
		mCurrentCommand->initFromMessage(message);
	}
	catch (const CommandException &e) {
        std::cout << "command exception" << std::endl;
        std::cout << e.what() << std::endl;
		mClient->closeClient();
		return;
	}

	emit receiveCommand(mCurrentCommand);

	resetCurrentCommand();
	onSocketReadable(mClient, mClient->nbBytesToRead());
}

void	CommandPacketBuilder::onSocketReadable(IClientSocket *, unsigned int nbBytesToRead) {
    std::cout << "SOCKET READABLE" << std::endl;
	if (mCurrentState == CommandPacketBuilder::HEADER && nbBytesToRead >= ICommand::HEADER_SIZE)
		fetchCommandHeader();
	else if (mCurrentState == CommandPacketBuilder::CONTENT && nbBytesToRead >= mCurrentCommand->getSizeToRead())
		fetchCommandContent();
}

void	CommandPacketBuilder::onSocketClosed(IClientSocket *) {
	resetCurrentCommand();
	emit disconnectedFromHost();
}

void	CommandPacketBuilder::resetCurrentCommand(void) {
	if (mCurrentCommand)
		delete mCurrentCommand;

	mCurrentCommand = NULL;
	mCurrentState = CommandPacketBuilder::HEADER;
}
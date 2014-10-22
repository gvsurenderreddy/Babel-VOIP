#include "CommandPacketBuilder.hpp"
#include "TcpClient.hpp"

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
	mClient->send(command->getMessage());
}

void	CommandPacketBuilder::connectToServer(const QString &addr, int port) {
	mClient->connect(addr.toStdString(), port);
}

void	CommandPacketBuilder::fetchCommandHeader(void) {
	IClientSocket::Message message = mClient->receive(ICommand::HEADER_SIZE);

	// check magiccode
	// init mCurrentCommand

	mCurrentState = CommandPacketBuilder::CONTENT;

	onSocketReadable(mClient, mClient->nbBytesToRead());
}

void	CommandPacketBuilder::fetchCommandContent(void) {
	IClientSocket::Message message = mClient->receive(mCurrentCommand->getSizeToRead());

	mCurrentCommand->initFromMessage(message);
	emit receiveCommand(mCurrentCommand);

	delete mCurrentCommand;
	mCurrentCommand = NULL;

	mCurrentState = CommandPacketBuilder::HEADER;

	onSocketReadable(mClient, mClient->nbBytesToRead());
}

void	CommandPacketBuilder::onSocketReadable(IClientSocket *, unsigned int nbBytesToRead) {
	if (mCurrentState == CommandPacketBuilder::HEADER && nbBytesToRead >= ICommand::HEADER_SIZE)
		fetchCommandHeader();
	else if (mCurrentState == CommandPacketBuilder::CONTENT && nbBytesToRead >= mCurrentCommand->getSizeToRead())
		fetchCommandContent();
}

void	CommandPacketBuilder::onSocketClosed(IClientSocket *) {
	if (mCurrentCommand) {
		delete mCurrentCommand;
		mCurrentCommand = NULL;
	}
}

#include "TcpClient.hpp"

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <string>

#include <cstring>
#include <cstdio>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

TcpClient::TcpClient() : mSocket(NULL), mListener(NULL)
{

}

TcpClient::~TcpClient()
{
    closeClient();
}

void TcpClient::connect(const std::string &/* addr */, int /* port */)
{

}

void TcpClient::initFromSocket(void *socket)
{
    mSocket = static_cast<tcp::socket*>(socket);
    startRecv();
    std::cout << "  [TCP CLIENT] inserted on address " << getRemoteIp() << std::endl;
}

void TcpClient::closeClient()
{
    std::cout << "  [TCP CLIENT] removed on address  " << getRemoteIp() << std::endl;
    if (mSocket)
        mSocket->close();
    if (mListener)
        mListener->onSocketClosed(this);
}

void TcpClient::startRecv()
{
    mSocket->async_receive(boost::asio::buffer(mReadBuffer, TcpClient::BUFFER_SIZE), [this](const boost::system::error_code& error, std::size_t bytesTransfered) {
        if (!error)
        {
            std::string str(mReadBuffer, bytesTransfered);
            std::string test = str;
            std::replace(test.begin(), test.end(), '\0', '.');
            if (mSocket && 1 == 2)
                std::cout << "  RECV " << bytesTransfered << " bytes from :: " << getRemoteIp() << std::endl << "  {" << std::endl << test << std::endl << "  }" << std::endl << std::endl;
            mBuffer.insert(mBuffer.end(), str.begin(), str.end());
            if (mListener)
                mListener->onSocketReadable(this, bytesTransfered);
            startRecv();
        }
        else
        {
            std::cout << "  [Error Client RECV] " << error.message() << std::endl;
            closeClient();
        }
    });
}

void TcpClient::send(const IClientSocket::Message &msg)
{
    boost::mutex::scoped_lock lock(mMutex);
    {
        bool write_in_progress = !mWriteMessageQueue.empty();
        if (msg.msgSize <= 0)
            return;
        mWriteMessageQueue.push_back(msg);
        if (!write_in_progress)
        {
            boost::asio::async_write(*mSocket,
                boost::asio::buffer(mWriteMessageQueue.front().msg, mWriteMessageQueue.front().msgSize),
                boost::bind(&TcpClient::sendHandler, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
        }
    }
}

#include "ICommand.hpp"

void TcpClient::sendHandler(const boost::system::error_code &error, std::size_t bytesTransfered)
{
    if (!error)
    {
        if (mListener)
            mListener->onBytesWritten(this, bytesTransfered);
        boost::mutex::scoped_lock lock(mMutex);
        {
            ICommand::Header *header = reinterpret_cast<ICommand::Header *>(mWriteMessageQueue.front().msg);

            // std::cout << "magicCode       sended: '" << std::hex << header->magicCode << "'" << std::endl;
            // std::cout << "instructionCode sended: '" << std::hex << header->instructionCode << "'" << std::endl;

            std::string str(mWriteMessageQueue.front().msg, bytesTransfered);
            std::string test = str;
            std::replace(test.begin(), test.end(), '\0', '.');
            if (mSocket && 1 == 2)
                std::cout << "  SEND " << bytesTransfered << " bytes " << std::endl << "  {" << std::endl << test << std::endl << "  }" << std::endl << std::endl;
            if (header->instructionCode == ICommand::ADD)
            {
                std::cout << "  ## SEND for COMMAND ADD : " << bytesTransfered << std::endl;
            }
            if (bytesTransfered == static_cast<unsigned int>(mWriteMessageQueue.front().msgSize))
            {
				//std::cout << "POP SEND" << std::endl;
                delete[] mWriteMessageQueue.front().msg;
                mWriteMessageQueue.pop_front();
            }
            else
            {
                //std::cout << "SEND PART SEND" << std::endl;
                Message& messageFront = mWriteMessageQueue.front();
                messageFront.msgSize -= bytesTransfered;
                char* tmp = new char[messageFront.msgSize + 1];
                memcpy(tmp, messageFront.msg, messageFront.msgSize);
                tmp[messageFront.msgSize] = '\0';
                delete[] messageFront.msg;
                messageFront.msg = tmp;
            }
            if (!mWriteMessageQueue.empty())
            {
                boost::asio::async_write(*mSocket,
                    boost::asio::buffer(mWriteMessageQueue.front().msg, mWriteMessageQueue.front().msgSize),
                    boost::bind(&TcpClient::sendHandler, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
            }
        }
    }
    else
    {
        std::cout << "  [Error Client SEND] " << error.message() << std::endl;
        closeClient();
    }
}

IClientSocket::Message TcpClient::receive(unsigned int sizeToRead)
{
	IClientSocket::Message message;
	
    if (sizeToRead > mBuffer.size())
    {
        message.msg = NULL;
        message.msgSize = -1;
        return message;
    }

    std::string str(mBuffer.begin(), mBuffer.begin() + sizeToRead);
    message.msg = new char[str.size() + 1];
    message.msgSize = str.size();
    std::copy(str.begin(), str.end(), message.msg);
    message.msg[str.size()] = '\0';
    
    mBuffer.erase(mBuffer.begin(), mBuffer.begin() + sizeToRead);

    return message;
}

unsigned int TcpClient::nbBytesToRead() const
{
    return mBuffer.size();
}

const std::string TcpClient::getRemoteIp() const
{
    return mSocket->remote_endpoint().address().to_string();
}

void TcpClient::setOnSocketEventListener(IClientSocket::OnSocketEvent *listener)
{
    mListener = listener;
}

#include "TcpClient.hpp"

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <string>

#include <cstring>
#include <cstdio>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

const int TcpClient::BUFFER_SIZE = 1024;

TcpClient::TcpClient() : mListener(NULL), mSocket(NULL), mNbBytesToRead(0), mBuffer(NULL)
{
    std::cout << __FUNCTION__ << std::endl;
    mBufferTmp = new char[TcpClient::BUFFER_SIZE];
}

TcpClient::~TcpClient()
{
    std::cout << __FUNCTION__ << std::endl;
    closeClient();
}

void TcpClient::connect(const std::string &/* addr */, int /* port */)
{
    std::cout << __FUNCTION__ << std::endl;
}

void TcpClient::initFromSocket(void *socket)
{
    std::cout << __FUNCTION__ << std::endl;
    mSocket = reinterpret_cast<tcp::socket*>(socket);
    startRead();
}

void TcpClient::closeClient()
{
    std::cout << __FUNCTION__ << std::endl;
    if (mSocket)
        mSocket->close();
    if (mListener)
        mListener->onSocketClosed(this);
}


/*----------------------------------------------*/


void TcpClient::startRead()
{
    std::cout << __FUNCTION__ << std::endl;
    std::memset(mBufferTmp, 0x00, TcpClient::BUFFER_SIZE);
    mSocket->async_receive(boost::asio::buffer(mBufferTmp, TcpClient::BUFFER_SIZE),
        boost::bind(&TcpClient::readHandler, this, boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}


/*----------------------------------------------*/


void TcpClient::send(const IClientSocket::Message &msg)
{
    std::cout << __FUNCTION__ << std::endl;

    boost::mutex::scoped_lock lock(mMutex);
    {
        bool write_in_progress = !mWriteMessageQueue.empty();
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

void TcpClient::sendHandler(const boost::system::error_code &error, std::size_t bytesTransfered)
{
    std::cout << __FUNCTION__ << std::endl;

    if (!error)
    {
        if (mListener)
            mListener->onBytesWritten(this, bytesTransfered);
        boost::mutex::scoped_lock lock(mMutex);
        {
            mWriteMessageQueue.pop_front();
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
        std::cerr << error.message() << std::endl;
        closeClient();
    }
}


/*----------------------------------------------*/


IClientSocket::Message TcpClient::receive(unsigned int sizeToRead)
{
    std::cout << __FUNCTION__ << std::endl;

    if (sizeToRead > mNbBytesToRead)
        exit(42);
    else
        mNbBytesToRead -= sizeToRead;

    IClientSocket::Message message;

    message.msg = new char[sizeToRead];
    message.msgSize = sizeToRead;

    std::memcpy(message.msg, mBuffer, sizeToRead);
    std::memmove(mBuffer, &mBuffer[sizeToRead], mNbBytesToRead);
    mBuffer = (char*)std::realloc(mBuffer, mNbBytesToRead);

    return message;
}

void TcpClient::readHandler(const boost::system::error_code & error, std::size_t bytesTransfered)
{
    std::cout << __FUNCTION__ << std::endl;

    if (!error)
    {
        mNbBytesToRead += bytesTransfered;
        mBuffer = (char *)std::realloc(mBuffer, mNbBytesToRead);
        memcpy(&mBuffer[mNbBytesToRead - bytesTransfered], mBufferTmp, bytesTransfered);
        if (mListener)
            mListener->onSocketReadable(this, bytesTransfered);
        startRead();
    }
    else
    {
        std::cout << error.message() << std::endl;
        closeClient();
    }
}


/*----------------------------------------------*/


unsigned int TcpClient::nbBytesToRead() const
{
    std::cout << __FUNCTION__ << std::endl;
    return mNbBytesToRead;
}

void TcpClient::setOnSocketEventListener(IClientSocket::OnSocketEvent *listener)
{
    std::cout << __FUNCTION__ << std::endl;
    mListener = listener;
}

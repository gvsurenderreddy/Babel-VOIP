#include "TcpClient.hpp"

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <string>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

const int TcpClient::BUFFER_SIZE = 4096;

TcpClient::TcpClient() : mListener(NULL), mSocket(NULL)
{
    std::cout << __FUNCTION__ << std::endl;
    mMessage.msg = new char[TcpClient::BUFFER_SIZE];
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
    mNbBytesToRead = 0;
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
    memset(mMessage.msg, 0x00, sizeof(char) * TcpClient::BUFFER_SIZE);
    mMessage.msgSize = 0;
    mSocket->async_receive(boost::asio::buffer(mMessage.msg, TcpClient::BUFFER_SIZE),
        boost::bind(&TcpClient::readHandler, this, boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}


/*----------------------------------------------*/


void TcpClient::send(const IClientSocket::Message &msg)
{
    std::cout << __FUNCTION__ << std::endl;
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

void TcpClient::sendHandler(const boost::system::error_code &error, std::size_t bytesTransfered)
{
    std::cout << __FUNCTION__ << std::endl;
    if (!error)
    {
        if (mListener)
            mListener->onBytesWritten(this, bytesTransfered);
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
    else
    {
        std::cerr << error.message() << std::endl;
        closeClient();
    }
}

/*----------------------------------------------*/


IClientSocket::Message TcpClient::receive(unsigned int /*sizeToRead*/)
{
    std::cout << __FUNCTION__ << std::endl;
    return mMessage;
}

void TcpClient::readHandler(const boost::system::error_code & error, std::size_t bytesTransfered)
{
    std::cout << __FUNCTION__ << std::endl;
    if (!error)
    {
        if (mListener)
        {
            mListener->onSocketReadable(this, bytesTransfered);
            std::cout << "SET" << std::endl;
        }
        else
        {
            std::cout << "PAS SET" << std::endl;
        }
        mNbBytesToRead = bytesTransfered;
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

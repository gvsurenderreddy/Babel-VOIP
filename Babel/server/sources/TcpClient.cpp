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
    boost::asio::async_read(
        *mSocket,
        boost::asio::buffer(mMessage.msg, TcpClient::BUFFER_SIZE),
        boost::bind(&TcpClient::readHandler, this,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}


/*----------------------------------------------*/


void TcpClient::send(const IClientSocket::Message &msg)
{
    std::cout << __FUNCTION__ << std::endl;
    std::cout << "Trying to send '" << msg.msg << "' (" << msg.msgSize << ")" << std::endl;
    boost::asio::async_write(
        *mSocket,
        boost::asio::buffer(msg.msg, msg.msgSize),
        boost::bind(&TcpClient::sendHandler, this,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}

void TcpClient::sendHandler(const boost::system::error_code &error, std::size_t bytesTransfered)
{
    std::cout << __FUNCTION__ << std::endl;
    if (!error)
    {
        if (mListener)
            mListener->onBytesWritten(this, bytesTransfered);
        std::cout << "bytesTransfered: '" << bytesTransfered << "'" << std::endl;
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
            mListener->onSocketReadable(this, bytesTransfered);
        mNbBytesToRead = bytesTransfered;
        std::cout << "bytesTransfered: '" << bytesTransfered << "'" << std::endl;
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








/*
void TcpServer::read_header()
{
    boost::asio::async_read(
        *mSocket,
        boost::asio::buffer(mBuffer, header_size),
        boost::bind(&TcpServer::handle_read_header, this,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}

void TcpServer::handle_read_header(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (error)
    {
        std::cerr << error.message() << std::endl;
        return;
    }
    //if (!record_stamp()) return;

    // Read data.
    boost::asio::async_read(
        *mSocket,
        boost::asio::buffer(mBuffer, data_size),
        boost::bind(&TcpServer::handle_read_data, this,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}

void TcpServer::handle_read_data(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (error)
    {
        std::cerr << error.message() << std::endl;
        return;
    }
    //if (!record_stamp()) return;
    read_header();
}
*/
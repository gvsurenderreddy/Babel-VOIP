#include "TcpClient.hpp"

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <string>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

TcpClient::TcpClient() : mListener(NULL), mSocket(NULL)
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
    mSocket = reinterpret_cast<tcp::socket*>(socket);
    mNbBytesToRead = 0;
}

void TcpClient::closeClient()
{
    mSocket->close();
    if (mListener)
        mListener->onSocketClosed(this);
}


/*----------------------------------------------*/


void TcpClient::send(const IClientSocket::Message &msg)
{
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
    if (!error)
    {
        if (mListener)
            mListener->onBytesWritten(this, bytesTransfered);
        std::cout << "bytesTransfered: '" << bytesTransfered << "'" << std::endl;
    }
    else
        std::cerr << error.message() << std::endl;
}

/*----------------------------------------------*/


IClientSocket::Message TcpClient::receive(unsigned int sizeToRead)
{
    std::cout << "Trying to receive send '" << sizeToRead << "' caracters" << std::endl;
    mMessage.msg = new char[sizeToRead];
    boost::asio::async_read(
        *mSocket,
        boost::asio::buffer(mMessage.msg, sizeToRead),
        boost::bind(&TcpClient::readHandler, this,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
    return mMessage;
}

void TcpClient::readHandler(const boost::system::error_code & error, std::size_t bytesTransfered)
{
    if (!error)
    {
        if (mListener)
            mListener->onSocketReadable(this, bytesTransfered);
        mNbBytesToRead = bytesTransfered;
        std::cout << "bytesTransfered: '" << bytesTransfered << "'" << std::endl;
    }
    else
        std::cout << error.message() << std::endl;
}


/*----------------------------------------------*/


unsigned int TcpClient::nbBytesToRead() const
{
    return mNbBytesToRead;
}

void TcpClient::setOnSocketEventListener(IClientSocket::OnSocketEvent *listener)
{
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
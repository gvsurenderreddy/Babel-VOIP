#include "BoostTcpClient.hpp"

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <string>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

BoostTcpClient::BoostTcpClient(): mListener(NULL), mSocket(NULL) {

}

BoostTcpClient::~BoostTcpClient() {
    std::cout << __FUNCTION__ << std::endl;
}

void BoostTcpClient::connect(const std::string &/* addr */, int /* port */) {

}

void BoostTcpClient::initFromSocket(void *socket) {
    std::cout << __FUNCTION__ << std::endl;
    mSocket = reinterpret_cast<tcp::socket*>(socket);
    if (mListener)
        mListener->onSocketReadyRead(this);
}

void BoostTcpClient::closeClient() {
    std::cout << __FUNCTION__ << std::endl;
    if (mSocket)
        mSocket->close();
    if (mListener)
        mListener->onSocketClosed(this);
}

void BoostTcpClient::sendHandler(const boost::system::error_code &errorCode, std::size_t bytesTransfered) {
    std::cout << __FUNCTION__ << std::endl;
    if (errorCode == 0)
    {
        mMsgHaveToSend.pop_front();
        if (mListener)
            mListener->onBytesWriten(this, bytesTransfered);
        if (!mMsgHaveToSend.empty())
        {
            boost::asio::async_write(
                *mSocket,
                boost::asio::buffer(mMsgHaveToSend.front().msg, mMsgHaveToSend.front().msgSize),
                boost::bind(&BoostTcpClient::sendHandler, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
        }
    }
    else
        closeClient();
}

void BoostTcpClient::send(const IClientSocket::Message &msg) {
    std::cout << __FUNCTION__ << std::endl;
    bool write_in_progress = !mMsgHaveToSend.empty();
    mMsgHaveToSend.push_back(msg);
    if (!write_in_progress)
    {
        boost::asio::async_write(
            *mSocket,
            boost::asio::buffer(mMsgHaveToSend.front().msg, mMsgHaveToSend.front().msgSize),
            boost::bind(&BoostTcpClient::sendHandler, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }
}

void BoostTcpClient::readHandler(const boost::system::error_code & errorCode, std::size_t bytesTransfered) {
    std::cout << __FUNCTION__ << std::endl;
    if (errorCode == 0)
    {
        IClientSocket::Message message;
        std::cout << mBuffer.data() << std::endl;

        message.msg = mBuffer.data();
        message.msgSize = bytesTransfered;

        mMsgReceived.push_back(message);

        memset(mBuffer.data(), 0, 1024);

        mSocket->async_receive(boost::asio::buffer(mBuffer.data(), 1024), boost::bind(&BoostTcpClient::readHandler, this, boost::asio::placeholders::error));
    }
    else
        closeClient();
}

IClientSocket::Message BoostTcpClient::receive(unsigned int sizeToRead) {
    
    sizeToRead = sizeToRead > 1024 ? 1024 : sizeToRead;

    memset(mBuffer.data(), 0, sizeToRead + 1);

    mSocket->async_receive(boost::asio::buffer(mBuffer.data(), sizeToRead),
        boost::bind(&BoostTcpClient::readHandler, this, boost::asio::placeholders::error));

    IClientSocket::Message message;
    
    message.msg = "";
    message.msgSize = 0;

    if (!mMsgReceived.empty())
    {
        message = mMsgReceived.front();
        mMsgReceived.pop_back();
    }

    return message;
}

bool BoostTcpClient::isWritable() const {
    return mSocket && mSocket->is_open();
}

bool BoostTcpClient::isReadable() const {
    return mSocket && mSocket->is_open();
}

void BoostTcpClient::setOnSocketEventListener(IClientSocket::OnSocketEvent *listener) {
    mListener = listener;
}

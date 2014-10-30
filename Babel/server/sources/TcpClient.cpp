#include "TcpClient.hpp"

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <string>

#include <cstring>
#include <cstdio>

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
    mSocket = static_cast<tcp::socket*>(socket);
    startRecv();
}

void TcpClient::closeClient()
{
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
            if (mSocket)
                std::cout << bytesTransfered << " bytes received from " << mSocket->remote_endpoint().address() << std::endl << "DATA below: " << std::endl << "[" << test << "]" << std::endl;
            mBuffer.insert(mBuffer.end(), str.begin(), str.end());
            if (mListener)
                mListener->onSocketReadable(this, bytesTransfered);
            startRecv();
        }
        else
        {
            std::cout << error.message() << std::endl;
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

void TcpClient::sendHandler(const boost::system::error_code &error, std::size_t bytesTransfered)
{
    if (!error)
    {
        if (mListener)
            mListener->onBytesWritten(this, bytesTransfered);
        boost::mutex::scoped_lock lock(mMutex);
        {
            if (bytesTransfered == mWriteMessageQueue.front().msgSize)
            {
                delete[] mWriteMessageQueue.front().msg;
                mWriteMessageQueue.pop_front();
            }
            else
            {
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
        std::cerr << error.message() << std::endl;
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
    //std::cout << std::endl << "nbBytesToRead (mBuffer.size()) = <" << mBuffer.size() << ">" << std::endl << std::endl;
    return mBuffer.size();
}

void TcpClient::setOnSocketEventListener(IClientSocket::OnSocketEvent *listener)
{
    mListener = listener;
}

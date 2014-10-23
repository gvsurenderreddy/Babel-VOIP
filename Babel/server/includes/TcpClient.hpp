#pragma once

#include "IClientSocket.hpp"

#include <list>
#include <deque>
#include <vector>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/thread/mutex.hpp>

/**
* class TcpClient
*
* Client with TCP Socket sending
*
*/

using namespace boost::asio::ip;

class TcpClient : public IClientSocket
{

    // default ctor-dtor
    public:
        TcpClient();
        ~TcpClient();

    // private coplien form
    private:
        TcpClient(const TcpClient &) {}
        const TcpClient & operator = (const TcpClient &) { return *this; }

    // start - stop
    public:
        void            connect(const std::string &addr, int port);
        void            initFromSocket(void *socket);
        void            closeClient();

    // recv / send
    public:
        void            send(const Message &msg);
        Message         receive(unsigned int nbBytes);
        unsigned int    nbBytesToRead() const;


    // handlers
    private:
        void            startRead();
        void            readHandler(const boost::system::error_code &errorCode, std::size_t bytesTransfered);
        void            sendHandler(const boost::system::error_code &ec, std::size_t bytesTransfered);

    // listeners
    public:
        void            setOnSocketEventListener(IClientSocket::OnSocketEvent *listener);

    // const
    public:
        static const int    BUFFER_SIZE = 1024;

    // attributes
    private:
        boost::asio::io_service                 mIOservice;
        tcp::socket*                            mSocket;
        Message                                 mMessage;
        char                                    mReadBuffer[BUFFER_SIZE];
        std::vector<char>                       mBuffer;
        std::deque<Message>                     mWriteMessageQueue;
        unsigned int                            mNbBytesToRead;
        IClientSocket::OnSocketEvent*           mListener;
        boost::mutex                            mMutex;

};

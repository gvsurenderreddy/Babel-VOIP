#pragma once

#include "IClientSocket.hpp"

#include <list>
#include <deque>
#include <vector>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/thread/mutex.hpp>

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
        void            startRecv();
        void            sendHandler(const boost::system::error_code &ec, std::size_t bytesTransfered);

    // listeners
    public:
        void            setOnSocketEventListener(IClientSocket::OnSocketEvent *listener);

    // get host ip
    public:
        const std::string getRemoteIp() const;

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

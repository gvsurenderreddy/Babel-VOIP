#pragma once

#include "IClientSocket.hpp"

#include <list>
#include <boost/asio.hpp>
#include <boost/array.hpp>

/**
* class BoostTcpClient
*
* Client with TCP Socket sending
*
*/

using namespace boost::asio::ip;

class BoostTcpClient : public IClientSocket
{

    // default ctor-dtor
    public:
        BoostTcpClient();
        ~BoostTcpClient();

    // private coplien form
    private:
        BoostTcpClient(const BoostTcpClient &) {}
        const BoostTcpClient & operator = (const BoostTcpClient &) { return *this; }

    // start - stop
    public:
        void            connect(const std::string &addr, int port);
        void            initFromSocket(void *socket);
        void            closeClient();

    // recv / send
    public:
        void            send(const Message &msg);
        Message         receive(unsigned int nbBytes);

    // handlers
    private:
        void            readHandler(const boost::system::error_code &errorCode, std::size_t bytesTransfered);
        void            sendHandler(const boost::system::error_code &ec, std::size_t bytesTransfered);

    // handle state
    public:
        bool            isWritable() const;
        bool            isReadable() const;

    // listeners
    public:
        void            setOnSocketEventListener(IClientSocket::OnSocketEvent *listener);

    // attributes
    private:
        boost::asio::io_service   mIOservice;
        tcp::socket*              mSocket;

        boost::array<char, 1024>   mBuffer;

        IClientSocket::OnSocketEvent*               mListener;
        std::list<Message>                          mMsgReceived;
        std::list<Message>                          mMsgHaveToSend;

};

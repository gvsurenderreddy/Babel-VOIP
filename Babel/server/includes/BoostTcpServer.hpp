#pragma once

#include "IServerSocket.hpp"

#include <boost/asio.hpp>

/**
* class BoostTcpServer
*
* Server with TCP Socket listening
*
*/

using namespace boost::asio::ip;

class BoostTcpServer : public IServerSocket
{

    // default ctor-dtor
    public:
        BoostTcpServer();
        ~BoostTcpServer();

    // private coplien form
    private:
        BoostTcpServer(const BoostTcpServer &) {}
        const BoostTcpServer & operator = (const BoostTcpServer &) { return *this; }

    // init
    public:
        void            createServer(int port, int queueSize);
        void            closeServer();
    private:
        void            startServer();
        void            startAccept();

    // listeners
    public:
        void            setOnSocketEventListener(IServerSocket::OnSocketEvent *listener);

    // handle clients
    public:
        IClientSocket*  getNewClient() const;
        bool            hasClientInQueue() const;

    // run
    public:
        void run();

    // handlers
    public:
        void            acceptHandler(const boost::system::error_code& error);

    // attributes
    private:
        boost::asio::io_service   mIOservice;
        tcp::acceptor*            mAcceptor;
        boost::asio::signal_set*  mSignals;
        tcp::socket*              mSocket;

        IServerSocket::OnSocketEvent*               mListener;
};

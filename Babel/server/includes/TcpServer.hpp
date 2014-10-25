#pragma once

#include "IServerSocket.hpp"

#include <list>
#include <boost/asio.hpp>
#include <boost/array.hpp>

/**
* class TcpServer
*
* Server with TCP Socket listening
*
*/

using namespace boost::asio::ip;

class TcpServer : public IServerSocket
{
    // default ctor-dtor
    public:
        TcpServer();
        ~TcpServer();

    // private coplien form
    private:
        TcpServer(const TcpServer &) { }
        const TcpServer & operator = (const TcpServer &) { return *this; }

    // init
    public:
        void            createServer(int port, int queueSize);
        void            closeServer();

    // listeners
    public:
        void            setOnSocketEventListener(IServerSocket::OnSocketEvent *listener);

    // handle clients
    public:
        IClientSocket*  getNewClient();
        bool            hasClientInQueue() const;

    // handle signals
    private:
        void startSignals(void);

    // run
    public:
        void run();

    // accept
    public:
        void startAccept(void);

    // attributes
    private:
        boost::asio::io_service                     mService;
        tcp::acceptor*                              mAcceptor;
        std::list<tcp::socket*>                     mSockets;
        IServerSocket::OnSocketEvent*               mListener;

};

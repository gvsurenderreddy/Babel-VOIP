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
        TcpServer(const TcpServer &) : mSigset(mService, SIGTERM, SIGINT) {}
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

    // accept
    public:
        void startAccept(void);

    // attributes
    private:
        boost::asio::io_service                     mService;
        boost::asio::signal_set                     mSigset;
        tcp::acceptor*                              mAcceptor;
        std::list<tcp::socket*>                     mSockets;
        IServerSocket::OnSocketEvent*               mListener;
        int                                         mPort;

};

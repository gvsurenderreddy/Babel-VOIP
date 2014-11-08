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

class TcpServer : public IServerSocket, private boost::noncopyable
{
    // default ctor-dtor
    public:
        TcpServer();
        ~TcpServer();

    // private coplien form
    private:
        TcpServer(const TcpServer &) = delete;
        const TcpServer & operator = (const TcpServer &) = delete;

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
        boost::shared_ptr<tcp::acceptor>            mAcceptor;
        std::list<tcp::socket*>                     mSockets;
        IServerSocket::OnSocketEvent*               mListener;
        int                                         mPort;

};

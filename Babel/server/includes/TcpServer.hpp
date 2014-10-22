#pragma once

#include "IServerSocket.hpp"

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
    // enum
    private:
        enum
        {
            header_size = sizeof(int) + sizeof(char),
            data_size = 10,
            buffer_size = 1024,
            max_stamp = 50
        };

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

    // functions
    public:
        void read_header();

    // functions handlers
    public:
        void startAccept(void);
        void handle_accept(const boost::system::error_code& error);
        void handle_read_header(const boost::system::error_code& error, std::size_t bytes_transferred);
        void handle_read_data(const boost::system::error_code& error, std::size_t bytes_transferred);

    // attributes
    private:
        boost::asio::io_service                     mService;
        tcp::acceptor*                              mAcceptor;
        std::list<tcp::socket*>                     mSockets;
        boost::array< char, buffer_size >           mBuffer;
        unsigned int                                mIndex;

        IServerSocket::OnSocketEvent*               mListener;

};

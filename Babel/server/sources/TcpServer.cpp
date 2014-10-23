#include "TcpServer.hpp"
#include "TcpClient.hpp"

#include <iostream>
#include <boost/bind.hpp>

TcpServer::TcpServer() : mAcceptor(NULL), mListener(NULL)
{
    startSignals();
}

TcpServer::~TcpServer()
{
    closeServer();
}

void TcpServer::createServer(int port, int /*queueSize*/)
{
    mAcceptor = new tcp::acceptor(mService, tcp::endpoint(tcp::v4(), port));
    startAccept();
}

void TcpServer::startSignals(void)
{
    //boost::asio::signal_set signals(mService, SIGINT);
    //signals.async_wait(boost::bind(&boost::asio::io_service::stop, &mService));
}

void TcpServer::startAccept(void)
{
    tcp::socket *socket = new tcp::socket(mService);

    mSockets.push_back(socket);
    mAcceptor->async_accept(*socket, boost::bind(&TcpServer::handle_accept, this, boost::asio::placeholders::error));
}

void TcpServer::handle_accept(const boost::system::error_code& error)
{
    if (error)
        std::cout << error.message() << std::endl;
    else if (mListener)
        mListener->onNewConnection(this);
    startAccept();
}

void TcpServer::closeServer()
{
    std::for_each(mSockets.begin(), mSockets.end(), [](tcp::socket* socket)
    {
        if (socket && socket->is_open())
        {
            socket->close();
            delete socket;
            socket = 0;
        }
    });
    if (mAcceptor && mAcceptor->is_open())
         mAcceptor->close();
}

void TcpServer::setOnSocketEventListener(TcpServer::OnSocketEvent *listener)
{
    mListener = listener;
}

IClientSocket* TcpServer::getNewClient()
{
    std::cout << __FUNCTION__ << std::endl;
    IClientSocket* client = new TcpClient;
    tcp::socket *socket = mSockets.front();
    mSockets.pop_front();
    client->initFromSocket(socket);
    return (client);
}

bool TcpServer::hasClientInQueue() const
{
    return true;
}

void TcpServer::run()
{
    mService.run();
}
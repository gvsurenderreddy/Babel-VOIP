#include "TcpServer.hpp"
#include "TcpClient.hpp"

#include <iostream>
#include <boost/bind.hpp>

TcpServer::TcpServer() : mAcceptor(NULL), mListener(NULL)
{
    std::cout << __FUNCTION__ << std::endl;
    startSignals();
}

TcpServer::~TcpServer()
{
    std::cout << __FUNCTION__ << std::endl;
    closeServer();
}

void TcpServer::createServer(int port, int /*queueSize*/)
{
    std::cout << __FUNCTION__ << std::endl;
    mAcceptor = new tcp::acceptor(mService, tcp::endpoint(tcp::v4(), port));
    startAccept();
}

void TcpServer::startSignals(void)
{
    std::cout << __FUNCTION__ << std::endl;
    //boost::asio::signal_set signals(mService, SIGINT);
    //signals.async_wait(boost::bind(&boost::asio::io_service::stop, &mService));
}

void TcpServer::startAccept(void)
{
    std::cout << __FUNCTION__ << std::endl;
    tcp::socket *socket = new tcp::socket(mService);

    mSockets.push_back(socket);
    mAcceptor->async_accept(*socket, boost::bind(&TcpServer::handle_accept, this, boost::asio::placeholders::error));
}

void TcpServer::handle_accept(const boost::system::error_code& error)
{
    std::cout << __FUNCTION__ << std::endl;
    if (error)
        std::cout << error.message() << std::endl;
    else if (mListener)
        mListener->onNewConnection(this);
    startAccept();
}

void TcpServer::closeServer()
{
    std::cout << __FUNCTION__ << std::endl;
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
    std::cout << __FUNCTION__ << std::endl;
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
    std::cout << __FUNCTION__ << std::endl;
    return true;
}

void TcpServer::run()
{
    std::cout << __FUNCTION__ << std::endl;
    mService.run();
}
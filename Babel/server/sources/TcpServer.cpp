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
    boost::asio::signal_set signals(mService, SIGINT, SIGTERM);
    signals.async_wait([this](const boost::system::error_code& error, int signum) {
        if (!error && (signum == SIGINT || signum == SIGTERM))
            mService.stop();
    });
}

void TcpServer::startAccept(void)
{
    tcp::socket *socket = new tcp::socket(mService);
    mSockets.push_back(socket);
    mAcceptor->async_accept(*socket, [this](const boost::system::error_code& error) {
        if (!error)
        {
            if (mListener)
                mListener->onNewConnection(this);
        }
        else
        {
            std::cout << error.message() << std::endl;
            delete this;
        }
        startAccept();
    });
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
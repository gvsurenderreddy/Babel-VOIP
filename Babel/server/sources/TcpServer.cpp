#include "TcpServer.hpp"
#include "TcpClient.hpp"

#include <iostream>
#include <boost/bind.hpp>

TcpServer::TcpServer() : mSigset(mService, SIGTERM, SIGINT), mAcceptor(NULL), mListener(NULL), mPort(-1)
{
    #if defined(SIGQUIT)
        mSigset.add(SIGQUIT);
    #endif
    #if defined(SIGHUP)
        mSigset.add(SIGHUP);
    #endif
    mSigset.async_wait(boost::bind(&boost::asio::io_service::stop, boost::ref(mService)));
}

TcpServer::~TcpServer()
{
    closeServer();
}

void TcpServer::createServer(int port, int)
{
    tcp::endpoint endpoint(tcp::v4(), port);
    mPort = port;
    mAcceptor = new tcp::acceptor(mService, endpoint);
    std::cout << "[TCP] start listening on port " << port << std::endl;
    startAccept();
    boost::system::error_code ec;
    mService.run(ec);
}

void TcpServer::startAccept(void)
{    tcp::socket *socket = new tcp::socket(mService);

    mSockets.push_back(socket);
    mAcceptor->async_accept(*socket, [this](const boost::system::error_code& error) {
        if (!error)
        {
            if (mListener)
                mListener->onNewConnection(this);
        }
        else
        {
            std::cout << "[TCP] async_accept failed: " << error.message() << std::endl;
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
    std::cout << "[TCP] stop listening on port " << mPort << std::endl;
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

#include "BoostTcpServer.hpp"
#include "BoostTcpClient.hpp"

#include <iostream>
#include <boost/bind.hpp>

    BoostTcpServer::BoostTcpServer() :
        mListener(NULL)
    {
        mSignals = new boost::asio::signal_set(mIOservice, SIGINT, SIGTERM, SIGBREAK);
        mSignals->async_wait(boost::bind(&IServerSocket::closeServer, this));
    }

    BoostTcpServer::~BoostTcpServer() {
        delete mAcceptor;
        delete mSignals;
    }

    void BoostTcpServer::createServer(int port, int /*queueSize*/) {
        std::cout << __FUNCTION__ << std::endl;
        const boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
        mSocket = new tcp::socket(mIOservice);
        mAcceptor = new tcp::acceptor(mIOservice, endpoint);
        startAccept();
    }

    void BoostTcpServer::startAccept() {
        std::cout << __FUNCTION__ << std::endl;
        mSocket->close();
        mAcceptor->async_accept(*mSocket, boost::bind(&BoostTcpServer::acceptHandler, this, boost::asio::placeholders::error));
    }

    void BoostTcpServer::acceptHandler(const boost::system::error_code& error) {
        std::cout << __FUNCTION__ << std::endl;
        if (error == 0 && mListener)
            mListener->onNewConnection(this);
        startAccept();
    }

    void BoostTcpServer::closeServer() {
        std::cout << __FUNCTION__ << std::endl;
        mAcceptor->close();
    }

    void BoostTcpServer::setOnSocketEventListener(BoostTcpServer::OnSocketEvent *listener) {
        mListener = listener;
    }

    IClientSocket* BoostTcpServer::getNewClient() const {

        IClientSocket *clientSocket = new BoostTcpClient;
        clientSocket->initFromSocket(mSocket);

        return clientSocket;
    }

    bool BoostTcpServer::hasClientInQueue() const {
        return true;
    }

    void BoostTcpServer::run() {
        std::cout << __FUNCTION__ << std::endl;
        mIOservice.run();
    }
#pragma once

#include "IServerSocket.hpp"

#include <list>

/**
* class ServerManager
*
* Manage server
*
*/

class ServerManager : public IServerSocket::OnSocketEvent
{

    // default ctor-dtor
    public:
        ServerManager(IServerSocket* serverSocket);
        ~ServerManager();

    // private coplien form
    private:
        ServerManager(const ServerManager &) {}
        const ServerManager & operator = (const ServerManager &) { return *this; }

    // attributes
    private:
        IServerSocket*  mServerSocket;

    // constants
    public:
        static const unsigned int LISTEN_PORT;
        static const unsigned int QUEUE_SIZE;
        static const unsigned int BUFFER_SIZE;

    // CallBack
    public:
        void    onNewConnection(IServerSocket *socket);

    // CallBack Client
    public:
        void        onSocketReadyRead(IClientSocket *socket);
        void        onSocketClosed(IClientSocket *socket);
        void        onBytesWriten(IClientSocket *socket, unsigned int length);

    // attributes
    private:
        std::list<IClientSocket*> mClientsSocket;

};

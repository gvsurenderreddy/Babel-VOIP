#pragma once

#include "IServerSocket.hpp"

#include <list>

/**
* class BabelServer
*
* Manage server
*
*/

class BabelServer : public IServerSocket::OnSocketEvent
{

    // default ctor-dtor
    public:
        BabelServer();
        ~BabelServer();

    // private coplien form
    private:
        BabelServer(const BabelServer &) {}
        const BabelServer & operator = (const BabelServer &) { return *this; }

    // run
    public:
        void run();

    // constants
    public:
        static const unsigned int BABEL_DEFAULT_LISTEN_PORT;
        static const unsigned int BABEL_DEFAULT_QUEUE_SIZE;

    // CallBack
    public:
        void    onNewConnection(IServerSocket *socket);

    // attributes
    private:
        std::list<IClientSocket*>   mClientsSocket;
        IServerSocket*              mServerSocket;

};

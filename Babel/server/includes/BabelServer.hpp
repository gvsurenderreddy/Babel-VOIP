#pragma once

#include "IServerSocket.hpp"
#include "Client.hpp"
#include <list>

/**
* class BabelServer
*
* Manage server
*
*/

class BabelServer : public IServerSocket::OnSocketEvent, Client::OnClientEvent
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
        std::list<Client*>   mClients;
        IServerSocket*       mServerSocket;

	//OnSocketEvent
	public:
		bool onSubscribe(const std::string &acount, const std::string &password);
		bool onConnect(const std::string &account, const std::string &password);
		void onDisconnect(const std::string &account);
		const std::string &onGetContact(const std::list<std::string> &contacts);
		bool onUpdate(const std::string &account, const std::string &password);
		bool onAddContact(const std::string &account);
		void DellContact(const std::string &args);
		void onAcceptContact(const bool &accept, const std::string &account);
		void onCallSomeone(const std::string &account);
		void onHangCall(const bool &hang, const std::string &account);
};

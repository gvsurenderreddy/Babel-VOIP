#pragma once

#include "IServerSocket.hpp"
#include "Client.hpp"

#include <list>
#include <boost/filesystem.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/map.hpp>

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

    // internal functions
    public:
        void importAccountsFromFile(const std::string& path);
        void exportAccountsFromFile(const std::string& path);
        void startServer();

    // constants
    public:
        static const unsigned int BABEL_DEFAULT_LISTEN_PORT = 4243;
        static const unsigned int BABEL_DEFAULT_QUEUE_SIZE = 128;

    // attributes
    private:
        IServerSocket*                     mServerSocket;
        std::list<Client*>                 mClients;
        std::map<std::string, std::string> mAccounts;
        std::string                        mAccountsFilePath;

    // serializer
    private:
	  friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int)
      {
          ar & mAccounts;
      }

    // IServerSocket::OnSocketEvent callbacks
    public:
        void onNewConnection(IServerSocket *socket);

    // Client::OnClientEvent callbacks
	public:
        bool               onSubscribe(const std::string &acount, const std::string& password);
		bool               onConnect(const std::string &account, const std::string &password, Client *caller);
		void               onDisconnect(Client *caller);
		void			   onList(Client *caller);
		bool               onUpdate(const std::string &account, const std::string &password, std::string pseudo, char status);
		bool               onAddContact(const std::string &targetAccount, const std::string &callerAccount);
        bool               onDelContact(const std::string &targetAccount, const std::string &callerAccount);
        bool               onShowContact(const std::string &targetAccount);
		bool               onAcceptContact(bool accept, const std::string &targetAccount, const std::string &callerAcount);
		bool               onCallSomeone(const std::string &targetAccount, std::string &callerAcount);
		void               onHangCall(bool hang, const std::string &targetAccount, std::string &callerAccount);
        bool               onSendMsg(const std::string &targetAccount, const std::string &message, const std::string &callerAccount);
		bool			   onCloseCall(const std::string &targetAccount, const std::string &callerAccount);

	//Handle Client
	private:
        void	updateContact(const std::list<std::string>& contact, const std::string& account, const std::string& pseudo, char status, bool isConnected);
        Client	*findClient(const std::string& account) const;
};

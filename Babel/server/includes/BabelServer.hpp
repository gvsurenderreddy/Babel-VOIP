#pragma once

#include "IServerSocket.hpp"
#include "Client.hpp"
#include <list>
#include <boost/filesystem.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

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
        void                    run();

    // constants
    public:
        static const unsigned int BABEL_DEFAULT_LISTEN_PORT;
        static const unsigned int BABEL_DEFAULT_QUEUE_SIZE;

    // CallBack
    public:
        void                    onNewConnection(IServerSocket *socket);

    // attributes
    private:
        std::list<Client*>      mClients;
        IServerSocket*          mServerSocket;

    // account
    class Account {
        public:
            Account(const std::string& account, const std::string& password) :
                mAccount(account), 
                mPassword(password), 
                mPseudo("Player"), 
                mState("Hors ligne")
            { }
            Account() { }
            std::string mAccount;
            std::string mPassword;
            std::string mPseudo;
            std::string mState;
            std::list<std::string> mFriends;
        private:
            friend class boost::serialization::access;
            template<class Archive>
            void serialize(Archive & ar, const unsigned int version) {
                ar & boost::serialization::make_nvp("mAccount", mAccount);
                ar & boost::serialization::make_nvp("mPassword", mPassword);
                ar & boost::serialization::make_nvp("mPseudo", mPseudo);
                ar & boost::serialization::make_nvp("mState", mState);
                ar & boost::serialization::make_nvp("mFriends", mFriends);
            }
    };

	//OnSocketEvent
	public:
		bool                    onSubscribe     (const std::string &acount, const std::string &password);
		bool                    onConnect       (const std::string &account, const std::string &password);
		void                    onDisconnect    (const std::string &account);
		const std::string &     onGetContact    (const std::list<std::string> &contacts);
		bool                    onUpdate        (const std::string &account, const std::string &password);
		bool                    onAddContact    (const std::string &account);
		void                    DellContact     (const std::string &args);
		void                    onAcceptContact (bool accept, const std::string &account);
		void                    onCallSomeone   (const std::string &account);
		void                    onHangCall      (const bool &hang, const std::string &account);
};

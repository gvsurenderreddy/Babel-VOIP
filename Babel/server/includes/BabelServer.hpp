#pragma once

#include "IServerSocket.hpp"
#include "Client.hpp"

#include <list>
#include <boost/filesystem.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/map.hpp>

class BabelServer : public IServerSocket::OnSocketEvent, public Client::OnClientEvent, private boost::noncopyable
{

    // default ctor-dtor
    public:
        BabelServer();
        virtual ~BabelServer();

    // private coplien form
    private:
        BabelServer(const BabelServer &) = delete;
        const BabelServer & operator = (const BabelServer &) = delete;

    // internal functions
    public:
        void displayAccounts() const;
        void displayAsciiHeader() const;
        void displayAsciiFooter() const;

        std::string getAbsolutePathAccountsUsersFolder(void) const;
        void cleanWrongsUserFile(void) const;
        void importAccountsUsernamePasswordFromFile(const std::string& path);
        void exportAccountsUsernamePasswordFromFile(const std::string& path);

        void startServer();

        Client* findOnlineClient(const std::string& account) const;
        Client* findOfflineClient(const std::string& account) const;

        void sendStateCommand(Client* client, int errorOccured, ICommand::Instruction instruction) const;

        void notifyMyFriendsOfModificationAboutMe(Client* client);

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
        void serialize(Archive & ar, const unsigned int) {
          ar & mAccounts;
        }

    // IServerSocket::OnSocketEvent callbacks
    public:
        void onNewConnection(IServerSocket *socket);

    // Client::OnClientEvent callbacks
	public:
        void onCloseConnection(Client* client);
        void onAdd(Client* client, std::vector<std::string>& param, ICommand::Instruction instruction);
        void onUpdate(Client* client, std::vector<std::string>& param, ICommand::Instruction instruction);
        void onReg(Client* client, std::vector<std::string>& param, ICommand::Instruction instruction);
        void onLog(Client* client, std::vector<std::string>& param, ICommand::Instruction instruction);
        void onList(Client* client, std::vector<std::string>& param, ICommand::Instruction instruction);
        void onShow(Client* client, std::vector<std::string>& param, ICommand::Instruction instruction);
        void onCall(Client* client, std::vector<std::string>& param, ICommand::Instruction instruction);
        void onAcceptAdd(Client* client, std::vector<std::string>& param, ICommand::Instruction instruction);
        void onDel(Client* client, std::vector<std::string>& param, ICommand::Instruction instruction);
        void onExit(Client* client, std::vector<std::string>& param, ICommand::Instruction instruction);
        void onSend(Client* client, std::vector<std::string>& param, ICommand::Instruction instruction);
        void onAcceptCall(Client* client, std::vector<std::string>& param, ICommand::Instruction instruction);
        void onCloseCall(Client* client, std::vector<std::string>& param, ICommand::Instruction instruction);
};

#pragma once

#ifdef WIN32
# pragma warning(disable: 4308)
#endif

#include "IClientSocket.hpp"
#include "IServerSocket.hpp"
#include "HandleCmd.hpp"

#include <vector>
#include <list>

#include <boost/filesystem.hpp>
#include <boost/serialization/list.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class Client : public IClientSocket::OnSocketEvent{

    // interface for client callback
    public:
	    class OnClientEvent{
	    public:
		    virtual ~OnClientEvent() {}
            virtual void onCloseConnection(Client* client) = 0;
            virtual void onAdd(Client* client, std::vector<std::string>& param, ICommand::Instruction instruction) = 0;
            virtual void onUpdate(Client* client, std::vector<std::string>& param, ICommand::Instruction instruction) = 0;
            virtual void onReg(Client* client, std::vector<std::string>& param, ICommand::Instruction instruction) = 0;
            virtual void onLog(Client* client, std::vector<std::string>& param, ICommand::Instruction instruction) = 0;
            virtual void onList(Client* client, std::vector<std::string>& param, ICommand::Instruction instruction) = 0;
            virtual void onShow(Client* client, std::vector<std::string>& param, ICommand::Instruction instruction) = 0;
            virtual void onCall(Client* client, std::vector<std::string>& param, ICommand::Instruction instruction) = 0;
            virtual void onAcceptAdd(Client* client, std::vector<std::string>& param, ICommand::Instruction instruction) = 0;
            virtual void onDel(Client* client, std::vector<std::string>& param, ICommand::Instruction instruction) = 0;
            virtual void onExit(Client* client, std::vector<std::string>& param, ICommand::Instruction instruction) = 0;
            virtual void onSend(Client* client, std::vector<std::string>& param, ICommand::Instruction instruction) = 0;
            virtual void onAcceptCall(Client* client, std::vector<std::string>& param, ICommand::Instruction instruction) = 0;
            virtual void onCloseCall(Client* client, std::vector<std::string>& param, ICommand::Instruction instruction) = 0;
	    };

    // default ctor-dtor
    public:
        Client(IClientSocket* clientSocket, Client::OnClientEvent* listenerClient);
        virtual ~Client();

    // private coplien form
    private:
        Client(const Client &) : Listener(NULL) { }
        const Client & operator = (const Client &) { return *this; }

    // handle commands
    private:
        struct HandleCommand {
            ICommand::Instruction instruction;
            void				  (Client::OnClientEvent::*handler)(Client*, std::vector<std::string> &param, ICommand::Instruction instruction);
        };
        static const Client::HandleCommand	handleCommandsTab[];
    public:
        void treatCommand(ICommand::Instruction instruction, std::vector<std::string> &args);

	// callback from IClientSocket
    public:
        void onBytesWritten(IClientSocket *, unsigned int);
	    void onSocketReadable(IClientSocket *socket, unsigned int nbBytesToRead);
	    void onSocketClosed(IClientSocket *socket);

	// internal functions
    public:
        static boost::filesystem::path getAbsolutePathDatabaseUsersFolder(void);
	    bool saveData(void);
        bool loadData(void);

    // status
    public:
        enum Status
        {
            CONNECTED = 0x00,
            DISCONNECTED = 0x01,
            BUSY = 0x02,
            AWAY = 0x03,
            KIPOUR = 0x04,
            SLEEPING = 0x05,
            RAMADAN = 0x06,
            SPORT = 0x07,
            TOILET = 0x08,
            YOLO = 0x09,
            CRYING = 0x0A
        };

    // status communication
    public:
        enum StatusCall
        {
            NONE = 0x00,
            ISWAITING = 0x01,
            ISCALLING = 0x02
        };

	// use client's data :: setter
    public:
        void setConnected(bool state);
        void setStatus(Client::Status state);
        void setStatusCall(Client::StatusCall state);
        void setPseudo(const std::string& pseudoName);
        void setAccount(const std::string& accountName);
        void clearContact();
        void addContact(const std::string& accountName);
        void delContact(const std::string& accountName);
        void setLastPingTime(std::time_t timer);
        void setCommunicationClient(Client*);
        void resetAttributes(void);

    // use client's data :: getter
    public:
        Client::Status				  getStatus(void) const;
        Client::StatusCall			  getStatusCall(void) const;
	    const std::string&            getPseudo(void) const;
	    const std::string&            getAccount(void) const;
	    const std::list<std::string>& getContact(void) const;
        IClientSocket*                getSocket(void) const;
        Client*                       getCommunicationClient(void) const;
        Client::OnClientEvent*        getListener(void) const;
        std::time_t                   getLastPingTime(void) const;
	    bool						  isConnect(void) const;
        bool                          isAlreadyFriends(const std::string& accountName) const;


	// instance of socket for send data
    public:
	    IClientSocket* Socket;

	// handleCmd
    public:
	    HandleCmd*  handleCmd;

    // path folder for storing users data
    private:
        std::string usersFolderPath;

	// boost serialize
    private:
	    friend class boost::serialization::access;
	    template<class Archive>
	    void serialize(Archive & ar, const unsigned int) {
		    ar & this->status;
		    ar & this->account;
		    ar & this->pseudo;
		    ar & this->contact;
        	    ar & this->isConnected;
	    }

	// attributes (data of client + listener)
    private:
        Client::Status			status;
        Client::StatusCall		statusCall;
	    std::string				pseudo;
	    std::list<std::string>	contact;
	    std::string				account;
        bool                    isConnected;
        Client::OnClientEvent*  Listener;
        time_t		            lastPingTime;
        Client*                 communicationClient;

    // display (have to be overload <<)
    public:
        void display() const;
};

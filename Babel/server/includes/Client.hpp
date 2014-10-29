#pragma once

#include "IClientSocket.hpp"
#include "IServerSocket.hpp"
#include "HandleCmd.hpp"

#include <vector>
#include <list>

#include <boost/serialization/list.hpp>
#include <boost/archive/text_oarchive.hpp>	
#include <boost/archive/text_iarchive.hpp>

class Client : public IClientSocket::OnSocketEvent{

public:
	//interface for client callback
	class OnClientEvent{
	public:
		virtual ~OnClientEvent() {}
        virtual bool onSubscribe(const std::string &acount, const std::string &pseudo, const std::string& password) = 0;
		virtual bool onConnect(const std::string &account, const std::string &password) = 0;
		virtual void onDisconnect(const std::string &account) = 0;
		virtual const std::string &onGetContact(const std::list<std::string> &contacts) = 0;
		virtual bool onUpdate(const std::string &account, const std::string &password, const std::string &currentAccount) = 0;
		virtual bool onAddContact(const std::string &account) = 0;
		virtual bool DellContact(const std::string &account) = 0;
		virtual bool onAcceptContact(bool accept, const std::string &account) = 0;
		virtual void onCallSomeone(const std::string &account) = 0;
		virtual void onHangCall(const bool &hang, const std::string &account) = 0;
	};

	//copelien
    Client(IClientSocket* clientSocket, Client::OnClientEvent &listenerClient);
	~Client();

	//callback from IClientSocket
	void	onBytesWritten(IClientSocket *socket, unsigned int nbBytes);
	void	onSocketReadable(IClientSocket *socket, unsigned int nbBytesToRead);
	void	onSocketClosed(IClientSocket *socket);

	//function for serialization
	void	savData(void);
	void	loadData(void);

	//use client's data
	//setter
	void	setState(const std::string state);
	void	setName(const std::string name);
	void	setAccount(const std::string account);
	void	addContact(const std::string name);
	void	dellContact(const std::string name);
	//getter
	const std::string				&getState(void);
	const std::string				&getName(void);
	const std::string				&getAccount(void);
	const std::list<std::string>	&getContact(void);

	//instance of socket for send data
	IClientSocket*	Socket;

private:
	//boost serialize
	friend class boost::serialization::access;
	template<class Archive>
	void	serialize(Archive & ar, const unsigned int version){
		ar & this->status;
		ar & this->pseudo;
		ar & this->contact;
		version;
	}
	
	//data of client
	std::string					status;
	std::string					pseudo;
	std::list<std::string>		contact;
	std::string					account;
    bool                        isConnected;

	//cmd
	HandleCmd	*handleCmd;

	void		Subscribe(std::vector<std::string> &args);
	void		Connect(std::vector<std::string> &args);
	void		Disconnect(std::vector<std::string> &args);
	void		GetContact(std::vector<std::string> &args);
	void		Update(std::vector<std::string> &args);
	void		AddContact(std::vector<std::string> &args);
	void		DellContact(std::vector<std::string> &args);
	void		AcceptContact(std::vector<std::string> &args);
	void		CallSomeone(std::vector<std::string> &args);
	void		HangCall(std::vector<std::string> &args);
	void		List(std::vector<std::string> &args);
	void		Show(std::vector<std::string> &args);
	void		SendMsg(std::vector<std::string> &args);
	void		CloseCall(std::vector<std::string> &args);

	void		exeCmd(ICommand::Instruction instruction, std::vector<std::string> &args);

	//client's listener
    Client::OnClientEvent&      Listener;
};

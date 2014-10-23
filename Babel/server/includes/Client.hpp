#pragma once

#include "IClientSocket.hpp"
#include "IServerSocket.hpp"

#include <vector>
#include <list>

/*#include <boost/serialization/list.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>*/

class Client : public IClientSocket::OnSocketEvent{

public:
	//interface for client callback
	class OnClientEvent{
	public:
		virtual ~OnClientEvent() {}
		virtual bool onSubscribe(const std::string &acount, const std::string &password) = 0;
		virtual bool onConnect(const std::string &account, const std::string &password) = 0;
		virtual void onDisconnect(const std::string &account) = 0;
		virtual const std::string &onGetContact(const std::list<std::string> &contacts) = 0;
		virtual bool onUpdate(const std::string &account, const std::string &password) = 0;
		virtual bool onAddContact(const std::string &account) = 0;
		virtual void DellContact(const std::string &args) = 0;
		virtual void onAcceptContact(const bool &accept, const std::string &account) = 0;
		virtual void onCallSomeone(const std::string &account) = 0;
		virtual void onHangCall(const bool &hang, const std::string &account) = 0;
	};

	//copelien
    Client(IServerSocket *serverSocket);
	~Client();

	//callback from IClientSocket
	void	onBytesWritten(IClientSocket *socket, unsigned int nbBytes);
	void	onSocketReadable(IClientSocket *socket, unsigned int nbBytesToRead);
	void	onSocketClosed(IClientSocket *socket);

    // listeners
    public:
        void setOnClientEventListener(Client::OnClientEvent *listener);

	//function for serialization
	/*void	savData(void);
	void	loadData(void);*/

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
	IClientSocket*	mSocket;

private:
	//boost serialize
	/*friend class boost::serialization::access;
	template<class Archive>
	void	serialize(Archive & ar, const unsigned int version){
		ar & this->state;
		ar & this->name;
		ar & this->contact;
	}*/

	//data of client
	std::string					state;
	std::string					name;
	std::list<std::string>		contact;
	std::string					account;

	//function cmd
	void	update(const std::vector<std::string> &args);
	void	Subscribe(const std::vector<std::string> &args);
	void	Connect(const std::vector<std::string> &args);
	void	Disconnect(const std::vector<std::string> &args);
	void	GetContact(const std::vector<std::string> &args);
	void	Update(const std::vector<std::string> &args);
	void	AddContact(const std::vector<std::string> &args);
	void	DellContact(const std::vector<std::string> &args);
	void	AcceptContact(const std::vector<std::string> &args);
	void	CallSomeone(const std::vector<std::string> &args);
	void	HangCall(const std::vector<std::string> &args);

	void	exeCmd(const int token, const std::vector<std::string> &args);

	//recup cmd
	/*
	std::vector<std::string>	cmdArg;
	std::vector<int>			argSize;
	int							nbArg;
	int							cmdState;*/

	//client's listener
    Client::OnClientEvent*      mListener;
};

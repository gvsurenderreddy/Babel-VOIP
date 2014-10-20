#include "IClientSocket.hpp"
#include <vector>

class Client : public IClientSocket::OnSocketEvent{

public:
	//interface for client callback
	class OnClientEvent{
	public:
		virtual ~OnClientEvent() {}
		virtual bool onSubscribe(std::string acount, std::string password) = 0;
		virtual bool onConnect(std::string account, std::string password) = 0;
		virtual void onDisconnect(std::string account) = 0;
		virtual std::string onGetContact(std::vector<std::string> contacts) = 0;
		virtual bool onUpdate(std::string account, std::string password) = 0;
		virtual bool onAddContact(std::string account) = 0;
		virtual void DellContact(std::vector<std::string> args) = 0;
		virtual void onAcceptContact(bool accept, std::string account) = 0;
		virtual void onCallSomeone(std::string account) = 0;
		virtual void onHangCall(bool hang, std::string account) = 0;
	};

	//constructer / destructer
	Client();
	~Client();

	//callback from IClientSocket
	void	onBytesWritten(IClientSocket *socket, unsigned int nbBytes);
	void	onSocketReadable(IClientSocket *socket, unsigned int nbBytesToRead);
	void	onSocketClosed(IClientSocket *socket);

	//function for serialization
	void	savData(void);
	void	getData(void);

	//use client's data;
	//setter
	void	setState(std::string state);
	void	setName(std::string account);
	void	setAccount(std::string account);
	void	addContact(std::string name);
	void	dellContact(std::string name);
	//getter
	std::string					getState(void);
	std::string					getName(void);
	std::string					getAccount(void);
	std::vector<std::string>	getContact(void);

	//instance of socket for send data
	IClientSocket	&socket;

private:
	//boost serialize
	friend class boost::serialization::access;
	template<class Archive>
	void	serialize(Archive & ar, const unsigned int version);

	//data of client
	std::string					state;
	std::string					name;
	std::vector<std::string>	contact;
	std::string					account;

	//function cmd
	void	update(std::vector<std::string> args);
	void	Subscribe(std::vector<std::string> args);
	void	Connect(std::vector<std::string> args);
	void	Disconnect(std::vector<std::string> args);
	void	GetContact(std::vector<std::string> args);
	void	Update(std::vector<std::string> args);
	void	AddContact(std::vector<std::string> args);
	void	DellContact(std::vector<std::string> args);
	void	AcceptContact(std::vector<std::string> args);
	void	CallSomeone(std::vector<std::string> args);
	void	HangCall(std::vector<std::string> args);

	void	exeCmd(int token, std::vector<std::string> args);

	//recup cmd
	/*
	std::vector<std::string>	cmdArg;
	std::vector<int>			argSize;
	int							nbArg;
	int							cmdState;*/

	//client's listener
	Client::OnClientEvent		&listener;
};

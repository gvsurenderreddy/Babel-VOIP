# Commands

## update
### void Client::update(const std::vector<std::string> &args)
### bool BabelServer::onUpdate(const std::string &account, const std::string &password)

## subscribe
###	void Client::Subscribe(const std::vector<std::string> &args)
* 
### bool BabelServer::onSubscribe(const std::string &acount, const std::string &password)
* 

## connect
### void Client::Connect(const std::vector<std::string> &args)
* 
### bool BabelServer::onConnect(const std::string &account, const std::string &password)	
* 

## disconnect
### void BabelServer::onDisconnect(const std::string &account)
* 
### void Client::Disconnect(const std::vector<std::string> &args)
* 

## getContact	
### const std::string& BabelServer::onGetContact(const std::list<std::string> &contacts)
* 
### void Client::GetContact(const std::vector<std::string> &args)
* 

## addContact
### bool BabelServer::onAddContact(const std::string &account)
* 
### void Client::AddContact(const std::vector<std::string> &args)
* 

## delContact
### void BabelServer::DellContact(const std::string &args)
* 
###	void Client::DellContact(const std::vector<std::string> &args)
* 

## acceptContact
### void BabelServer::onAcceptContact(const bool &accept, const std::string &account)
* 
### void Client::AcceptContact(const std::vector<std::string> &args)
* 

## callSomeone
### void BabelServer::onCallSomeone(const std::string &account)
* 
### void Client::CallSomeone(const std::vector<std::string> &args)
* 

## hangCall
### void BabelServer::onHangCall(const bool &hang, const std::string &account)
* 
### void Client::HangCall(const std::vector<std::string> &args)
* 

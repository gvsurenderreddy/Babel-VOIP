#include "BabelServer.hpp"
#include "IServerSocket.hpp"
#include "TcpServer.hpp"
#include "Database.hpp"
#include "ErrorCode.hpp"

#include <iomanip>
#include <iostream>
#include <fstream>
#include <algorithm>

#include <boost/filesystem.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include <utility>

BabelServer::BabelServer() :mServerSocket(NULL)
{
    displayAsciiHeader();
    mAccountsFilePath = getAbsolutePathAccountsUsersFolder();
    importAccountsUsernamePasswordFromFile(mAccountsFilePath);
}

BabelServer::~BabelServer()
{
    displayAsciiFooter();
    if (mServerSocket)
        delete mServerSocket;
    logOutClients();
    exportAccountsUsernamePasswordFromFile(mAccountsFilePath);
    std::for_each(mClients.begin(), mClients.end(), [](Client* client) { if (client->isConnect()) client->saveData(); });
}

void BabelServer::displayAccounts() const
{
    if (mAccounts.size() == 0)
    {
        std::cout << "[DATABASE] empty" << std::endl;
        return;
    }
    int padding = 20;
    std::cout << "[DATABASE] " << mAccounts.size() << " rows found:" << std::endl;
    std::for_each(mAccounts.begin(), mAccounts.end(),
        [this](const std::pair<std::string, std::string>& item) {
        std::cout << "[DATABASE] ~ " << std::setw(20) << item.first << "  #  " << item.second << std::endl;
    });
}

std::string BabelServer::getAbsolutePathAccountsUsersFolder(void) const
{
    const boost::filesystem::path mAbsolutePathDatabaseFolder = boost::filesystem::complete(Database::DATABASE_FOLDER);
    if (boost::filesystem::exists(mAbsolutePathDatabaseFolder) == false)
        boost::filesystem::create_directory(mAbsolutePathDatabaseFolder);
    const std::string& absolutePathDatabaseFolderStr = mAbsolutePathDatabaseFolder.string();
    return absolutePathDatabaseFolderStr + Database::DATABASE_ACCOUNTS_FILENAME + Database::DATABASE_EXTENSION;
}

void BabelServer::importAccountsUsernamePasswordFromFile(const std::string& path)
{
    std::cout << "[DATABASE] try import users already created" << std::endl;
    std::ifstream ifs(path);
    if (!ifs.good() || ifs.fail())
    {
        std::cout << "[DATABASE] empty" << std::endl;
        return;
    }
    boost::archive::text_iarchive ia(ifs);
    ia >> *this;
    ifs.close();
    displayAccounts();
}

void BabelServer::exportAccountsUsernamePasswordFromFile(const std::string& path)
{
    std::ofstream ofs(path, std::ofstream::out | std::ofstream::trunc);
    if (!ofs.good() || ofs.fail())
        return;
    boost::archive::text_oarchive oa(ofs);
    oa << *this;
    ofs.close();
}

void BabelServer::logOutClients()
{
	std::for_each(mClients.begin(), mClients.end(), [](Client* client) { 
		if (client->isConnect())
		{
            client->setConnected(false);
            client->setStatusCall(Client::StatusCall::NONE);
            client->setStatus(Client::Status::DISCONNECTED);
			client->saveData();
		}
	});
}

void BabelServer::displayAsciiHeader() const
{
    std::cout << std::endl;
    std::cout << "  ____          _            _   " << std::endl;
    std::cout << " |  _ \\        | |          | |  " << std::endl;
    std::cout << " | |_) |  __ _ | |__    ___ | |  " << std::endl;
    std::cout << " |  _ <  / _` || '_ \\  / _ \\| |  " << std::endl;
    std::cout << " | |_) || (_| || |_) ||  __/| |  " << std::endl;
    std::cout << " |____/  \\__,_||_.__/  \\___||_| Epitech Project" << std::endl;
    std::cout << std::endl;
}

void BabelServer::displayAsciiFooter() const
{
    std::cout << "        ____                           " << std::endl;
    std::cout << "   _||__|  |  ______   ______   ______   ______ " << std::endl;
    std::cout << "  (        | |      | |      | |      | |      |" << std::endl;
    std::cout << "  /-()---() ~ ()--() ~ ()--() ~ ()--() ~ ()--()~" << std::endl;
    std::cout << "    (emad_n, ninon_s, guego_p, nguy_1, tran_y)" << std::endl;
    std::cout << std::endl;
}

void BabelServer::startServer()
{
    mServerSocket = dynamic_cast<IServerSocket*>(new TcpServer);
    mServerSocket->setOnSocketEventListener(this);
    mServerSocket->createServer(BabelServer::BABEL_DEFAULT_LISTEN_PORT, BabelServer::BABEL_DEFAULT_QUEUE_SIZE);
    mServerSocket->run();
}

Client* BabelServer::findOnlineClient(const std::string& account) const
{
    auto it = std::find_if(mClients.begin(), mClients.end(), [&account](Client* client)
    { return client->getAccount() == account && client->isConnect(); });
    return (mClients.end() != it ? *it : NULL);
}

Client* BabelServer::findOfflineClient(const std::string& account) const
{
    Client* targetClient = new Client(NULL, NULL);
    targetClient->setAccount(account);
    if (targetClient->loadData())
    {
        return targetClient;
    }   
    else
    {
        delete targetClient;
        return NULL;
    }
}

void BabelServer::sendStateCommand(Client* client, int errorOccured, ICommand::Instruction instruction) const
{
    std::vector<std::string> args;

    args.push_back("");
    args[0] += errorOccured;
    args.push_back("");
    args[1] += instruction;
    client->handleCmd->packCmd(ICommand::ERR, args);
}

void BabelServer::notifyMyFriendsOfModificationAboutMe(Client* client)
{
    std::vector<std::string> args;

    args.push_back(client->getAccount());
    args.push_back(client->getPseudo());
    args.push_back("");
    args[2] += client->getStatus();
    args.push_back("");
    args[3] += client->isConnect();

    std::for_each(client->getContact().begin(), client->getContact().end(), [&](const std::string &accountName) {
        Client* clientTarget = findOnlineClient(accountName);
        if (clientTarget)
            clientTarget->handleCmd->packCmd(ICommand::SHOW, args);
    });
}

/*
** IServerSocket::OnSocketEvent
*/
void BabelServer::onNewConnection(IServerSocket *serverSocket)
{
    if (serverSocket->hasClientInQueue())
        mClients.push_back(new Client(serverSocket->getNewClient(), this));
}

/*
** Client::OnClientEvent
*/

// ** Add
// ** add #nom_de_compte
void BabelServer::onAdd(Client* callerClient, std::vector<std::string>& param, ICommand::Instruction instruction)
{
    if (param.size() == 1)
    {
		if (callerClient->isConnect() == true)
		{
			const std::string& targetAccount = param[0];
			if (targetAccount != callerClient->getAccount())
			{
			    Client* targetClient = findOnlineClient(targetAccount);
			    if (targetClient)
			    {
			    	if (targetClient->isAlreadyFriends(callerClient->getAccount()) == false)
			    	{
				        targetClient->display();
				        sendStateCommand(callerClient, ErrorCode::OK, instruction);

				        std::vector<std::string> args;

				        args.push_back(callerClient->getAccount());

				        targetClient->handleCmd->packCmd(instruction, args);
			        } else sendStateCommand(callerClient, ErrorCode::ALREADY_IN_YOUR_CONTACT_LIST, instruction);		        	
			    } else sendStateCommand(callerClient, ErrorCode::ACTIONS_TO_OFFLINE_ACCOUNT, instruction);
			} else sendStateCommand(callerClient, ErrorCode::CANNOT_ADD_YOURSELF, instruction);
		} else sendStateCommand(callerClient, ErrorCode::YOU_ARE_NOT_LOGGED, instruction);
    } else sendStateCommand(callerClient, ErrorCode::WRONG_PACKET_STRUCT, instruction);
}

// ** Update
// ** update #nom_de_compte #pseudo #pwd #status
void BabelServer::onUpdate(Client* client, std::vector<std::string>& param, ICommand::Instruction instruction)
{
    if (param.size() == 4)
    {
		if (client->isConnect() == true)
		{
			const std::string& account = param[0];
			const std::string& pseudo = param[1];
			const std::string& password = param[2];
			Client::Status status = static_cast<Client::Status>(param[3][0]);

			if (client->getAccount() == account && mAccounts.count(account) && status >= Client::Status::CONNECTED && status <= Client::Status::CRYING)
			{
			    sendStateCommand(client, ErrorCode::OK, instruction);

			    client->setAccount(account);
			    client->setPseudo(pseudo);
			    client->setStatus(status);
			    client->saveData();

			    mAccounts[account] = password;
			}
			else sendStateCommand(client, ErrorCode::WRONG_PACKET_STRUCT, instruction);
		} else sendStateCommand(client, ErrorCode::YOU_ARE_NOT_LOGGED, instruction);
	} else sendStateCommand(client, ErrorCode::WRONG_PACKET_STRUCT, instruction);
}

// ** Inscription
// ** reg #nom_de_compte #pseudo #pwd
void BabelServer::onReg(Client* client, std::vector<std::string>& param, ICommand::Instruction instruction)
{
    if (param.size() == 3)
    {
		if (client->isConnect() == false)
		{
			const std::string& account = param[0];
			const std::string& pseudo = param[1];
			const std::string& password = param[2];

			if (mAccounts.count(account) == 0)
			{
			    sendStateCommand(client, ErrorCode::OK, instruction);

			    mAccounts[account] = password;

			    client->setAccount(account);
			    client->setPseudo(pseudo);
			    client->setStatus(Client::DISCONNECTED);
			    client->setStatusCall(Client::StatusCall::NONE);
			    client->clearContact();
			    client->setConnected(false);

			    client->saveData();
			} else sendStateCommand(client, ErrorCode::REGISTER_ACC_ALREADY_USED, instruction);
		} else sendStateCommand(client, ErrorCode::ALREADY_CONNECTED, instruction);
    } else sendStateCommand(client, ErrorCode::WRONG_PACKET_STRUCT, instruction);
}

// ** Login
// ** log #nom_de_compte #pwd
// ** TODO: check Already Logged
void BabelServer::onLog(Client* client, std::vector<std::string>& param, ICommand::Instruction instruction)
{
    if (param.size() == 2)
    {
		if (client->isConnect() == false)
		{
			const std::string& account = param[0];
			const std::string& password = param[1];

			if (std::find_if(mAccounts.begin(), mAccounts.end(), [&account, &password](const std::pair<std::string, std::string>& item) -> bool
			{ return item.first == account && item.second == password; }) != mAccounts.end())
			{
			    Client* targetClientOffline = findOfflineClient(account);
			    if (targetClientOffline)
			    {
			        if (targetClientOffline->isConnect() == false)
			        {
			            client->setAccount(account);
			            if (client->loadData())
					    {
						    sendStateCommand(client, ErrorCode::OK, instruction);

						    client->setStatus(Client::Status::CONNECTED);
						    client->setStatusCall(Client::StatusCall::NONE);
						    client->setConnected(true);
						    client->saveData();

						    std::vector<std::string> args;
							onList(client, args, ICommand::LIST);
						    notifyMyFriendsOfModificationAboutMe(client);
					    }
					    else sendStateCommand(client, ErrorCode::THE_IMPOSSIBLE_HAPPENED, instruction);
			        } else sendStateCommand(client, ErrorCode::LOGIN_ON_ALREADY_LOGGED_ACCOUNT, instruction);
			        delete targetClientOffline;
			    } else sendStateCommand(client, ErrorCode::UNKNOWN_ACCOUNT, instruction);
			} else sendStateCommand(client, ErrorCode::LOGIN_WRONG_PASSWORD, instruction);
		} else sendStateCommand(client, ErrorCode::ALREADY_CONNECTED, instruction);
    } else sendStateCommand(client, ErrorCode::WRONG_PACKET_STRUCT, instruction);
}

// ** Liste de Show
// ** list
void BabelServer::onList(Client* client, std::vector<std::string>& param, ICommand::Instruction instruction)
{
    if (param.size() == 0)
    {
		if (client->isConnect() == true)
		{
			std::for_each(client->getContact().begin(), client->getContact().end(), [=](const std::string &targetAccount) {
			    std::vector<std::string> args;

			    args.push_back(targetAccount);
			    onShow(client, args, ICommand::SHOW);
			});
		} else sendStateCommand(client, ErrorCode::YOU_ARE_NOT_LOGGED, instruction);
    } else sendStateCommand(client, ErrorCode::WRONG_PACKET_STRUCT, instruction);
}

// ** Show
// ** show #nom_de_compte
void BabelServer::onShow(Client* client, std::vector<std::string>& param, ICommand::Instruction instruction)
{
    if (param.size() == 1)
    {
		if (client->isConnect() == true)
		{
			const std::string& targetAccount = param[0];
			Client* targetClient = findOfflineClient(targetAccount);
			if (targetClient)
			{
			    sendStateCommand(client, ErrorCode::OK, instruction);

			    std::vector<std::string> args;

			    args.push_back(targetClient->getAccount());
			    args.push_back(targetClient->getPseudo());
			    args.push_back("");
			    args[2] += targetClient->getStatus();
			    args.push_back("");
			    args[3] += targetClient->isConnect();

			    delete targetClient;

			    client->handleCmd->packCmd(instruction, args);            
			} else sendStateCommand(client, ErrorCode::UNKNOWN_ACCOUNT, instruction);
		} else sendStateCommand(client, ErrorCode::YOU_ARE_NOT_LOGGED, instruction);
    } else sendStateCommand(client, ErrorCode::WRONG_PACKET_STRUCT, instruction);
}

// ** Call
// ** call #nom_de_compte
void BabelServer::onCall(Client* client, std::vector<std::string>& param, ICommand::Instruction instruction)
{
    if (param.size() == 1)
    {
		if (client->isConnect() == true)
		{
			if (client->getStatusCall() == Client::StatusCall::NONE)
			{
			    const std::string& targetAccount = param[0];
			    if (targetAccount != client->getAccount())
			    {
			        Client* targetClient = findOnlineClient(targetAccount);
			        if (targetClient)
			        {
				    	if (targetClient->isAlreadyFriends(client->getAccount()) == true)
				    	{
				    		if (targetClient->getStatusCall() == Client::StatusCall::NONE)
				    		{
					            sendStateCommand(client, ErrorCode::OK, instruction);

					            client->setStatusCall(Client::StatusCall::ISWAITING);
					            client->saveData();

								targetClient->setStatusCall(Client::StatusCall::ISWAITING);
					            targetClient->saveData();

					            std::vector<std::string> args;

					            args.push_back(client->getAccount());

					            targetClient->handleCmd->packCmd(instruction, args);
				        	} else sendStateCommand(client, ErrorCode::BUSY_CONTACT_CANNOT_REPLY, instruction);
			            } else sendStateCommand(client, ErrorCode::NOT_IN_YOUR_CONTACT_LIST, instruction);		        	
			        } else sendStateCommand(client, ErrorCode::ACTIONS_TO_OFFLINE_ACCOUNT, instruction);
			    } else sendStateCommand(client, ErrorCode::CANNOT_CALL_YOURSELF, instruction);
			} else sendStateCommand(client, ErrorCode::CANNOT_DO_CALL_MULTIPLE, instruction);
		} else sendStateCommand(client, ErrorCode::YOU_ARE_NOT_LOGGED, instruction);
    } else sendStateCommand(client, ErrorCode::WRONG_PACKET_STRUCT, instruction);
}

// ** AcceptAdd
// ** accept_add #nom_de_compte OK/KO
void BabelServer::onAcceptAdd(Client* currentClient, std::vector<std::string>& param, ICommand::Instruction instruction)
{
    if (param.size() == 2)
    {
		if (currentClient->isConnect() == true)
		{
			const std::string& targetAccount = param[0];
			bool accept = param[1][0];
			Client* targetClient = findOnlineClient(targetAccount);
			if (targetClient)
			{
				if (targetClient->isAlreadyFriends(currentClient->getAccount()) == false)
				{
				    sendStateCommand(currentClient, ErrorCode::OK, instruction);

				    if (accept == false)
				        return;

				    std::vector<std::string> argsToCurrentClient;
				    std::vector<std::string> argsToTargetClient;

				    argsToTargetClient.push_back(currentClient->getAccount());
				    argsToCurrentClient.push_back(targetClient->getAccount());

				    targetClient->addContact(currentClient->getAccount());
				    currentClient->addContact(targetClient->getAccount());

				    targetClient->saveData();
				    currentClient->saveData();

				    onShow(targetClient, argsToTargetClient, ICommand::SHOW);
				    onShow(currentClient, argsToCurrentClient, ICommand::SHOW);
				}
				else sendStateCommand(currentClient, ErrorCode::ALREADY_IN_YOUR_CONTACT_LIST, instruction);		        					
			} else sendStateCommand(currentClient, ErrorCode::ACTIONS_TO_OFFLINE_ACCOUNT, instruction);
		} else sendStateCommand(currentClient, ErrorCode::YOU_ARE_NOT_LOGGED, instruction);
    } else sendStateCommand(currentClient, ErrorCode::WRONG_PACKET_STRUCT, instruction);
}

// ** Delete Contact
// ** del #nom_de_compte
void BabelServer::onDel(Client* callerClient, std::vector<std::string>& param, ICommand::Instruction instruction)
{ 
    if (param.size() == 1)
    {
		if (callerClient->isConnect() == true)
		{
			const std::string& targetAccount = param[0];
			Client* targetClientOnline = findOnlineClient(targetAccount);
			Client* targetClientOffline = findOfflineClient(targetAccount);
			if (targetClientOnline || targetClientOffline)
			{
				bool isFriend;
				if (targetClientOnline && targetClientOnline->isAlreadyFriends(callerClient->getAccount()) == true)
					isFriend = true;
				else if (targetClientOffline && targetClientOffline->isAlreadyFriends(callerClient->getAccount()) == true)
					isFriend = true;
				else
					isFriend = false;

				if (isFriend)
				{
				    sendStateCommand(callerClient, ErrorCode::OK, instruction);

				    std::vector<std::string> args;

				    if (targetClientOnline)
				    {
				        targetClientOnline->delContact(callerClient->getAccount());
				        targetClientOnline->saveData();
				        args.push_back(targetAccount);
				        onShow(targetClientOnline, args, ICommand::SHOW);
				    }
				    else
				    {
				        targetClientOffline->delContact(callerClient->getAccount());
				        targetClientOffline->saveData();
				    }
				    
				    callerClient->delContact(targetAccount);
				    callerClient->saveData();

				    args.push_back(callerClient->getAccount());
				    onShow(callerClient, args, ICommand::SHOW);
			    }
			    else sendStateCommand(callerClient, ErrorCode::NOT_IN_YOUR_CONTACT_LIST, instruction);	
			    if (targetClientOffline)
			        delete targetClientOffline;
			} else sendStateCommand(callerClient, ErrorCode::UNKNOWN_ACCOUNT, instruction);
		} else sendStateCommand(callerClient, ErrorCode::YOU_ARE_NOT_LOGGED, instruction);
    } else sendStateCommand(callerClient, ErrorCode::WRONG_PACKET_STRUCT, instruction);
}

// ** Disconnect
// ** exit
void BabelServer::onExit(Client* client, std::vector<std::string>& param, ICommand::Instruction instruction)
{
    if (param.size() == 0)
    {
		if (client->isConnect() == true)
		{
			sendStateCommand(client, ErrorCode::OK, instruction);

            client->setConnected(false);
            client->setStatusCall(Client::StatusCall::NONE);
            client->setStatus(Client::Status::DISCONNECTED);
            client->setLastPingTime(std::time(nullptr));
			client->saveData();

			notifyMyFriendsOfModificationAboutMe(client);
		} else sendStateCommand(client, ErrorCode::YOU_ARE_NOT_LOGGED, instruction);
    } else sendStateCommand(client, ErrorCode::WRONG_PACKET_STRUCT, instruction);
}

// ** Send Messsage
// ** send #nom_de_compte #msg
void BabelServer::onSend(Client* client, std::vector<std::string>& param, ICommand::Instruction instruction)
{
    if (param.size() == 2)
    {
		if (client->isConnect() == true)
		{
			const std::string& targetAccount = param[0];
			const std::string& message = param[1];
			Client* targetClient = findOnlineClient(targetAccount);
			if (targetClient)
			{
				if (targetClient->isAlreadyFriends(client->getAccount()) == true)
				{
				    sendStateCommand(client, ErrorCode::OK, instruction);

				    std::vector<std::string> args;

				    args.push_back(client->getAccount());
				    args.push_back(message);

				    targetClient->handleCmd->packCmd(instruction, args);
				}
                else sendStateCommand(client, ErrorCode::NOT_IN_YOUR_CONTACT_LIST, instruction);
			} else sendStateCommand(client, ErrorCode::ACTIONS_TO_OFFLINE_ACCOUNT, instruction);
		} else sendStateCommand(client, ErrorCode::YOU_ARE_NOT_LOGGED, instruction);
    } else sendStateCommand(client, ErrorCode::WRONG_PACKET_STRUCT, instruction);
}

// ** Accept Call
// ** accept_call #nom_de_compte OK/KO
void BabelServer::onAcceptCall(Client* callerClient, std::vector<std::string>& param, ICommand::Instruction instruction)
{
    if (param.size() == 2)
    {
		if (callerClient->isConnect() == true)
		{
			if (callerClient->getStatusCall() == Client::StatusCall::ISWAITING)
			{
			    const std::string& targetAccount = param[0];
			    bool accept = param[1][0];
			    Client* targetClient = findOnlineClient(targetAccount);
			    if (targetClient)
			    {
			    	if (targetClient->isAlreadyFriends(callerClient->getAccount()) == true)
					{
				        sendStateCommand(callerClient, ErrorCode::OK, instruction);

				        std::vector<std::string> args;

				        callerClient->setStatusCall(Client::StatusCall::ISCALLING);
				        callerClient->saveData();
				        args.push_back(callerClient->getAccount());
				        args.push_back(callerClient->getSocket()->getRemoteIp());
				        args.push_back("");
				        args[2] += accept;
				        targetClient->handleCmd->packCmd(instruction, args);

				        args.clear();

				        targetClient->setStatusCall(Client::StatusCall::ISCALLING);
				        targetClient->saveData();
				        args.push_back(targetClient->getAccount());
				        args.push_back(targetClient->getSocket()->getRemoteIp());
				        args.push_back("");
				        args[2] += accept;
				        callerClient->handleCmd->packCmd(instruction, args);
				    } else sendStateCommand(callerClient, ErrorCode::ACTIONS_TO_OFFLINE_ACCOUNT, instruction);
			    } else sendStateCommand(callerClient, ErrorCode::ACTIONS_TO_OFFLINE_ACCOUNT, instruction);
			} else sendStateCommand(callerClient, ErrorCode::CANNOT_ACCEPT_CALL_FROM_NOT_A_CALLER, instruction);
		} else sendStateCommand(callerClient, ErrorCode::YOU_ARE_NOT_LOGGED, instruction);
    } else sendStateCommand(callerClient, ErrorCode::WRONG_PACKET_STRUCT, instruction);
}

// ** Close Call
// ** close_call #nom_de_compte
void BabelServer::onCloseCall(Client* callerClient, std::vector<std::string>& param, ICommand::Instruction instruction)
{
    if (param.size() == 1)
    {
		if (callerClient->isConnect() == true)
		{
			if (callerClient->getStatusCall() == Client::StatusCall::ISCALLING)
			{
			    const std::string& targetAccount = param[0];
			    Client* targetClient = findOnlineClient(targetAccount);
			    if (targetClient)
			    {
			    	if (targetClient->isAlreadyFriends(callerClient->getAccount()) == true)
					{
				        sendStateCommand(callerClient, ErrorCode::OK, instruction);

				        std::vector<std::string> args;

				        args.push_back(callerClient->getAccount());

				        targetClient->handleCmd->packCmd(instruction, args);
				    } else sendStateCommand(callerClient, ErrorCode::ACTIONS_TO_OFFLINE_ACCOUNT, instruction);
			    } else sendStateCommand(callerClient, ErrorCode::ACTIONS_TO_OFFLINE_ACCOUNT, instruction);
			} else sendStateCommand(callerClient, ErrorCode::CANNOT_CLOSE_CALL_WHEN_YOU_ARENT_CALLING, instruction);
		} else sendStateCommand(callerClient, ErrorCode::YOU_ARE_NOT_LOGGED, instruction);
    } else sendStateCommand(callerClient, ErrorCode::WRONG_PACKET_STRUCT, instruction);
}

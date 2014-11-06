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
    cleanWrongsUserFile();
}

BabelServer::~BabelServer()
{
    displayAsciiFooter();
    if (mServerSocket)
        delete mServerSocket;
    exportAccountsUsernamePasswordFromFile(mAccountsFilePath);
    for (std::list<Client*>::iterator it = mClients.begin(); it != mClients.end(); ++it)
        delete *it;
    mClients.clear();
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

void BabelServer::displayAccounts() const
{
    if (mAccounts.size() == 0)
    {
        std::cout << "[DATABASE] empty" << std::endl;
        return;
    }

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

void BabelServer::cleanWrongsUserFile(void) const
{
    boost::filesystem::path PathDatabaseUsersFolder = Client::getAbsolutePathDatabaseUsersFolder();
    for (boost::filesystem::directory_iterator end_dir_it, it(PathDatabaseUsersFolder); it != end_dir_it; ++it)
    {
        const boost::filesystem::path path = it->path();
        const std::string filename = path.filename().stem().string();
        if (mAccounts.count(filename) == 0)
            boost::filesystem::remove(path);
    }
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

void BabelServer::startServer()
{
    mServerSocket = dynamic_cast<IServerSocket*>(new TcpServer);
    mServerSocket->setOnSocketEventListener(this);
    mServerSocket->createServer(BabelServer::BABEL_DEFAULT_LISTEN_PORT, BabelServer::BABEL_DEFAULT_QUEUE_SIZE);
}

Client* BabelServer::findOnlineClient(const std::string& account) const
{
    auto it = std::find_if(mClients.begin(), mClients.end(), [&account](const Client* client)
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
    std::vector<std::string> args = { std::string(1, errorOccured), std::string(1, instruction) };
    client->handleCmd->packCmd(ICommand::ERR, args);
}

void BabelServer::notifyMyFriendsOfModificationAboutMe(Client* client)
{
    std::vector<std::string> args;
    
    args.push_back(client->getAccount());
    args.push_back(client->getPseudo());
    args.push_back(std::string(1, client->getStatus()));
    args.push_back(std::string(1, client->isConnect()));

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

// ** lost connexion
void BabelServer::onCloseConnection(Client* client)
{
    std::list<Client*>::iterator it = mClients.begin();
    std::list<Client*>::iterator it_end = mClients.end();
    while (it != it_end)
    {
        if (*it == client)
        {
            if (client->isConnect())
            {
                client->disconnect();
                notifyMyFriendsOfModificationAboutMe(client);
                client->saveData();
            }
            it = mClients.erase(it);
        }   
        else
            ++it;
    }
}

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
                Client* targetClientOffline = findOfflineClient(targetAccount);
                if (targetClientOffline)
                {
                    Client* targetClient = findOnlineClient(targetAccount);
                    if (targetClient)
                    {
                        if (targetClient->isAlreadyFriends(callerClient->getAccount()) == false)
                        {
                            sendStateCommand(callerClient, ErrorCode::OK, instruction);

                            std::vector<std::string> argsToTargetClient;
                            argsToTargetClient.push_back(callerClient->getAccount());
                            targetClient->handleCmd->packCmd(instruction, argsToTargetClient);
                        }
                        else sendStateCommand(callerClient, ErrorCode::ALREADY_IN_YOUR_CONTACT_LIST, instruction);
                    }
                    else sendStateCommand(callerClient, ErrorCode::ACTIONS_TO_OFFLINE_ACCOUNT, instruction);
                    delete targetClientOffline;
                }
                else sendStateCommand(callerClient, ErrorCode::UNKNOWN_ACCOUNT, instruction);
			} 
            else sendStateCommand(callerClient, ErrorCode::CANNOT_ADD_YOURSELF, instruction);
		} 
        else sendStateCommand(callerClient, ErrorCode::YOU_ARE_NOT_LOGGED, instruction);
    } 
    else sendStateCommand(callerClient, ErrorCode::WRONG_PACKET_STRUCT, instruction);
}

// ** Update
// ** update #nom_de_compte #pseudo #pwd #status
void BabelServer::onUpdate(Client* currentClient, std::vector<std::string>& param, ICommand::Instruction instruction)
{
    if (param.size() == 4)
    {
        if (currentClient->isConnect() == true)
		{
			const std::string& account = param[0];
			const std::string& pseudo = param[1];
			const std::string& password = param[2];
			Client::Status status = static_cast<Client::Status>(param[3][0]);

            if (currentClient->getAccount() == account && mAccounts.count(account) && status >= Client::Status::CONNECTED && status <= Client::Status::CRYING)
			{
                sendStateCommand(currentClient, ErrorCode::OK, instruction);

                currentClient->setAccount(account);
                currentClient->setPseudo(pseudo);
                currentClient->setStatus(status);
                currentClient->saveData();

			    mAccounts[account] = password;

                std::vector<std::string> args;

                args.push_back(account);
                onShow(currentClient, args, ICommand::SHOW);
                notifyMyFriendsOfModificationAboutMe(currentClient);
			}
            else sendStateCommand(currentClient, ErrorCode::WRONG_PACKET_STRUCT, instruction);
        } 
        else sendStateCommand(currentClient, ErrorCode::YOU_ARE_NOT_LOGGED, instruction);
    } 
    else sendStateCommand(currentClient, ErrorCode::WRONG_PACKET_STRUCT, instruction);
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
			} 
            else sendStateCommand(client, ErrorCode::REGISTER_ACC_ALREADY_USED, instruction);
		} 
        else sendStateCommand(client, ErrorCode::ALREADY_CONNECTED, instruction);
    } 
    else sendStateCommand(client, ErrorCode::WRONG_PACKET_STRUCT, instruction);
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
                    targetClientOffline->display();
			        if (targetClientOffline->isConnect() == false)
			        {
			            client->setAccount(account);
			            if (client->loadData())
					    {
						    sendStateCommand(client, ErrorCode::OK, instruction);

                            client->connect();
						    client->saveData();

						    std::vector<std::string> args;
							onList(client, args, ICommand::LIST);
						    notifyMyFriendsOfModificationAboutMe(client);
					    }
					    else sendStateCommand(client, ErrorCode::THE_IMPOSSIBLE_HAPPENED, instruction);
			        } 
                    else sendStateCommand(client, ErrorCode::LOGIN_ON_ALREADY_LOGGED_ACCOUNT, instruction);
			        delete targetClientOffline;
			    } 
                else sendStateCommand(client, ErrorCode::UNKNOWN_ACCOUNT, instruction);
			} 
            else sendStateCommand(client, ErrorCode::LOGIN_WRONG_PASSWORD, instruction);
		} 
        else sendStateCommand(client, ErrorCode::ALREADY_CONNECTED, instruction);
    } 
    else sendStateCommand(client, ErrorCode::WRONG_PACKET_STRUCT, instruction);
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
		} 
        else sendStateCommand(client, ErrorCode::YOU_ARE_NOT_LOGGED, instruction);
    } 
    else sendStateCommand(client, ErrorCode::WRONG_PACKET_STRUCT, instruction);
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
                args.push_back(std::string(1, client->getStatus()));
                args.push_back(std::string(1, client->isConnect()));
			    delete targetClient;
			    client->handleCmd->packCmd(instruction, args);            
			} 
            else sendStateCommand(client, ErrorCode::UNKNOWN_ACCOUNT, instruction);
		} 
        else sendStateCommand(client, ErrorCode::YOU_ARE_NOT_LOGGED, instruction);
    } 
    else sendStateCommand(client, ErrorCode::WRONG_PACKET_STRUCT, instruction);
}

// ** Call
// ** call #nom_de_compte
void BabelServer::onCall(Client* currentClient, std::vector<std::string>& param, ICommand::Instruction instruction)
{
    if (param.size() == 1)
    {
        if (currentClient->isConnect() == true)
		{
            if (currentClient->getStatusCall() == Client::StatusCall::NONE)
			{
			    const std::string& targetAccount = param[0];
                if (targetAccount != currentClient->getAccount())
			    {
			        Client* targetClient = findOnlineClient(targetAccount);
			        if (targetClient)
			        {
                        if (targetClient->isAlreadyFriends(currentClient->getAccount()) == true)
				    	{
				    		if (targetClient->getStatusCall() == Client::StatusCall::NONE)
				    		{
                                sendStateCommand(currentClient, ErrorCode::OK, instruction);

                                std::vector<std::string> argsToTargetClient;

                                argsToTargetClient.push_back(currentClient->getAccount());

                                currentClient->setStatusCall(Client::StatusCall::ISWAITING);
                                currentClient->saveData();

								targetClient->setStatusCall(Client::StatusCall::ISWAITING);
					            targetClient->saveData();

                                currentClient->setCommunicationClient(targetClient);
                                targetClient->setCommunicationClient(currentClient);

                                targetClient->handleCmd->packCmd(instruction, argsToTargetClient);
                            }
                            else sendStateCommand(currentClient, ErrorCode::BUSY_CONTACT_CANNOT_REPLY, instruction);
                        }
                        else sendStateCommand(currentClient, ErrorCode::NOT_IN_YOUR_CONTACT_LIST, instruction);
                    }
                    else sendStateCommand(currentClient, ErrorCode::ACTIONS_TO_OFFLINE_ACCOUNT, instruction);
                }
                else sendStateCommand(currentClient, ErrorCode::CANNOT_CALL_YOURSELF, instruction);
            }
            else sendStateCommand(currentClient, ErrorCode::CANNOT_DO_CALL_MULTIPLE, instruction);
        }
        else sendStateCommand(currentClient, ErrorCode::YOU_ARE_NOT_LOGGED, instruction);
    }
    else sendStateCommand(currentClient, ErrorCode::WRONG_PACKET_STRUCT, instruction);
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
                    {
                        return;
                    }

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
			} 
            else sendStateCommand(currentClient, ErrorCode::ACTIONS_TO_OFFLINE_ACCOUNT, instruction);
		} 
        else sendStateCommand(currentClient, ErrorCode::YOU_ARE_NOT_LOGGED, instruction);
    } 
    else sendStateCommand(currentClient, ErrorCode::WRONG_PACKET_STRUCT, instruction);
}

// ** Delete Contact
// ** del #nom_de_compte
void BabelServer::onDel(Client* currentClient, std::vector<std::string>& param, ICommand::Instruction instruction)
{ 
    if (param.size() == 1)
    {
        if (currentClient->isConnect() == true)
		{
			const std::string& targetAccount = param[0];
			Client* targetClientOnline = findOnlineClient(targetAccount);
			Client* targetClientOffline = findOfflineClient(targetAccount);
			if (targetClientOnline || targetClientOffline)
			{
				bool isFriend;
                if (targetClientOnline && targetClientOnline->isAlreadyFriends(currentClient->getAccount()) == true)
					isFriend = true;
                else if (targetClientOffline && targetClientOffline->isAlreadyFriends(currentClient->getAccount()) == true)
					isFriend = true;
				else
					isFriend = false;

				if (isFriend)
				{
                    sendStateCommand(currentClient, ErrorCode::OK, instruction);

                    std::vector<std::string> argsToCurrentClient;
                    std::vector<std::string> argsToTargetClient;

                    argsToTargetClient.push_back(currentClient->getAccount());
                    argsToCurrentClient.push_back(targetAccount);

                    currentClient->delContact(targetAccount);
                    currentClient->saveData();

				    if (targetClientOnline)
				    {
                        Client* communicationClient = currentClient->getCommunicationClient();
                        if (communicationClient && communicationClient->getAccount() == targetAccount)
                        {
                            std::vector<std::string> args;

                            args.push_back(communicationClient->getAccount());
                            onCloseCall(currentClient, args, ICommand::CLOSE_CALL);
                        }
                        targetClientOnline->delContact(currentClient->getAccount());
				        targetClientOnline->saveData();
                        targetClientOnline->handleCmd->packCmd(instruction, argsToTargetClient);
				    }
				    else
				    {
                        targetClientOffline->delContact(currentClient->getAccount());
				        targetClientOffline->saveData();
				    }

                    currentClient->handleCmd->packCmd(instruction, argsToCurrentClient);
			    } 
                else sendStateCommand(currentClient, ErrorCode::NOT_IN_YOUR_CONTACT_LIST, instruction);
			    if (targetClientOffline)
			        delete targetClientOffline;
            } 
            else sendStateCommand(currentClient, ErrorCode::UNKNOWN_ACCOUNT, instruction);
        } 
        else sendStateCommand(currentClient, ErrorCode::YOU_ARE_NOT_LOGGED, instruction);
    } 
    else sendStateCommand(currentClient, ErrorCode::WRONG_PACKET_STRUCT, instruction);
}

// ** Disconnect
// ** exit
void BabelServer::onExit(Client* currentClient, std::vector<std::string>& param, ICommand::Instruction instruction)
{
    if (param.size() == 0)
    {
        if (currentClient->isConnect() == true)
		{
            sendStateCommand(currentClient, ErrorCode::OK, instruction);
            
            Client* communicationClient = currentClient->getCommunicationClient();
            if (communicationClient)
            {
                std::vector<std::string> args;

                args.push_back(communicationClient->getAccount());
                onCloseCall(currentClient, args, ICommand::CLOSE_CALL);
            }
            std::cout << "avant la deco" << std::endl;
            currentClient->display();

            currentClient->disconnect();
            notifyMyFriendsOfModificationAboutMe(currentClient);
            currentClient->saveData();
            currentClient->resetAttributes();
        }
        else sendStateCommand(currentClient, ErrorCode::YOU_ARE_NOT_LOGGED, instruction);
    }
    else sendStateCommand(currentClient, ErrorCode::WRONG_PACKET_STRUCT, instruction);
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
			} 
            else sendStateCommand(client, ErrorCode::ACTIONS_TO_OFFLINE_ACCOUNT, instruction);
		} 
        else sendStateCommand(client, ErrorCode::YOU_ARE_NOT_LOGGED, instruction);
    } 
    else sendStateCommand(client, ErrorCode::WRONG_PACKET_STRUCT, instruction);
}

// ** Accept Call
// ** accept_call #nom_de_compte OK/KO
void BabelServer::onAcceptCall(Client* currentClient, std::vector<std::string>& param, ICommand::Instruction instruction)
{
    if (param.size() == 2)
    {
        if (currentClient->isConnect() == true)
		{
            if (currentClient->getStatusCall() == Client::StatusCall::ISWAITING)
			{
			    const std::string& targetAccount = param[0];
			    bool accept = param[1][0];
			    Client* targetClient = findOnlineClient(targetAccount);
			    if (targetClient)
			    {
                    if (targetClient == currentClient->getCommunicationClient())
					{
                        sendStateCommand(currentClient, ErrorCode::OK, instruction);

                        std::vector<std::string> argsToCurrentClient;
                        std::vector<std::string> argsToTargetClient;

                        if (!accept)
                        {
                            currentClient->setStatusCall(Client::StatusCall::ISCALLING);
                            currentClient->saveData();
                            return;
                        }

                        argsToTargetClient.push_back(currentClient->getAccount());
                        argsToTargetClient.push_back(currentClient->getSocket()->getRemoteIp());
                        argsToTargetClient.push_back(std::string(1, accept));

                        argsToCurrentClient.push_back(targetClient->getAccount());
                        argsToCurrentClient.push_back(targetClient->getSocket()->getRemoteIp());
                        argsToCurrentClient.push_back(std::string(1, accept));

                        targetClient->setStatusCall(Client::StatusCall::ISCALLING);
                        currentClient->setStatusCall(Client::StatusCall::ISCALLING);

                        targetClient->saveData();
                        currentClient->saveData();

                        currentClient->setCommunicationClient(targetClient);
                        targetClient->setCommunicationClient(currentClient);

                        targetClient->handleCmd->packCmd(instruction, argsToTargetClient);
                        currentClient->handleCmd->packCmd(instruction, argsToCurrentClient);
                    } 
                    else sendStateCommand(currentClient, ErrorCode::NOT_IN_COMMUNICATION_WITH_HIM, instruction);
                } 
                else sendStateCommand(currentClient, ErrorCode::ACTIONS_TO_OFFLINE_ACCOUNT, instruction);
            } 
            else sendStateCommand(currentClient, ErrorCode::CANNOT_ACCEPT_CALL_FROM_NOT_A_CALLER, instruction);
        } 
        else sendStateCommand(currentClient, ErrorCode::YOU_ARE_NOT_LOGGED, instruction);
    } 
    else sendStateCommand(currentClient, ErrorCode::WRONG_PACKET_STRUCT, instruction);
}

// ** Close Call
// ** close_call #nom_de_compte
void BabelServer::onCloseCall(Client* currentClient, std::vector<std::string>& param, ICommand::Instruction instruction)
{
    if (param.size() == 1)
    {
        if (currentClient->isConnect() == true)
		{
            if (currentClient->getStatusCall() == Client::StatusCall::ISCALLING)
			{
			    const std::string& targetAccount = param[0];
			    Client* targetClient = findOnlineClient(targetAccount);
			    if (targetClient)
			    {
                    if (targetClient == currentClient->getCommunicationClient())
					{
                        sendStateCommand(currentClient, ErrorCode::OK, instruction);

                        std::vector<std::string> argsToCurrentClient;
                        std::vector<std::string> argsToTargetClient;

                        argsToTargetClient.push_back(currentClient->getAccount());
                        argsToCurrentClient.push_back(targetClient->getAccount());

                        currentClient->setStatusCall(Client::StatusCall::NONE);
                        currentClient->saveData();

                        targetClient->setStatusCall(Client::StatusCall::NONE);
                        targetClient->saveData();

                        currentClient->setCommunicationClient(NULL);
                        targetClient->setCommunicationClient(NULL);

                        targetClient->handleCmd->packCmd(instruction, argsToTargetClient);
                        currentClient->handleCmd->packCmd(instruction, argsToCurrentClient);
                    } 
                    else sendStateCommand(currentClient, ErrorCode::NOT_IN_COMMUNICATION_WITH_HIM, instruction);
			    } 
                else sendStateCommand(currentClient, ErrorCode::ACTIONS_TO_OFFLINE_ACCOUNT, instruction);
            } 
            else sendStateCommand(currentClient, ErrorCode::CANNOT_CLOSE_CALL_WHEN_YOU_ARENT_CALLING, instruction);
        } 
        else sendStateCommand(currentClient, ErrorCode::YOU_ARE_NOT_LOGGED, instruction);
    } 
    else sendStateCommand(currentClient, ErrorCode::WRONG_PACKET_STRUCT, instruction);
}

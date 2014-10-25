# Commandes

Ci-dessous se trouve un récapitulatif de quoi doit se trouver où.

#### [1] Client::update

```
client->setState
client->setPseudo
mListener.onUpdate(args[0], args[1], args[2])
```

#### [1] BabelServer::update

```
server->serializer(nom_de_compte)->updatePseudo
server->serializer(nom_de_compte)->updatePassword
server->serializer(nom_de_compte)->updateStatus
```

#### [2] Client::subscribe

```
if (mListener.onSubscribe(args[0], args[1]))
  inscription faite
else
  nom de compte déjà utilisé
```

#### [2] BabelServer::subscribe

```
vérifier que le fichier n'existe pas déjà
sinon server->serializer(nom_de_compte)->insert(password, status, pseudo, liste contact vide)
```

#### [3] Client::connect

```
if (mListener.onConnect(args[0], args[1]))
  client->setConnected = true;
```

#### [3] BabelServer::connect

```
vérifier que le fichier existe déjà
sinon server->serializer(nom_de_compte)->loadData
server->serializer->account == nom_de_compte && server->serializer->password == password
```

#### [4] Client::disconnect

```
client->setConnected = false;
mListener.onDisconnect(args[0])
```

#### [4] BabelServer::disconnect

```
for_each notifier sa std::list<std::string> contacts que ce client s'est deco
```

#### [5] Client::getContact

```

```

#### [5] BabelServer::getContact

```

```

#### [6] Client::addContact

```

```

#### [6] BabelServer::addContact

```

```

#### [7] Client::delContact

```
mContacts.erase(args[0]);
mListener.delContact(args);
```

#### [7] BabelServer::delContact

```
server->serializer(nom_de_compte)->updateContacts
```

#### [8] Client::acceptContact

```
actions
```

#### [8] BabelServer::acceptContact

```
actions
```

#### [9] Client::callSomeone

```
actions
```

#### [9] BabelServer::callSomeone

```
actions
```

#### [10] Client::hangCall

```
actions
```

#### [10] BabelServer::hangCall

```
actions
```

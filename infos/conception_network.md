## Conception Network

Navid est chargé de transposé ça sous forme d'UML et d'implémenté la conception avec Boost::Asio TCP.

Perso, je me charge de l'implémentation QtNetwork TCP et UDP.


### IServerSocket

La classe qui souhaite utiliser un IServerSocket devra implémenter l'interface IServerSocket::OnSocketEvent.

Elle sera automatiquement notifiée lorsqu'un client souhaite se connecter au serveur.

```cpp
class IServerSocket {

	// CallBack interface
	public:
		class OnSocketEvent {
			public:
				virtual ~OnSocketEvent() {}
				virtual void	onNewConnection(IServerSocket *socket) = 0;
				virtual void  onSocketClosed(IServerSocket *socket) = 0;
		};

	// virtual destructor
	public:
		virtual ~IServerSocket(void) {}

	// init
	public:
		virtual void	createServer(int port, int queueSize) = 0;
		virtual void	closeServer(void) = 0;

	// listeners
	public:
		virtual void	setOnSocketEventListener(IServerSocket::OnSocketEvent *listener) = 0;

	// handle clients
	public:
		virtual IClientSocket	getNewClient(void) = 0;
		virtual bool		hasClientInQueue(void) const = 0;

};
```


### IClientSocket

La classe qui souhaite utiliser un IClientSocket devra implémenter l'interface IClientSocket::OnSocketEvent.

Elle sera automatiquement notifiée lorsqu'un client est disponible en écriture et est déconnectée.

```cpp
class IClientSocket {

	// CallBack Interface
	public:
		class OnSocketEvent {
			public:
				virtual	~OnSocketEvent() {}
				virtual void	onBytesWritten(IClientSocket *socket, unsigned int nbBytes) = 0;
				virtual void	onSocketReadable(IClientSocket *socket) = 0;
				virtual void	onSocketClosed(IClientSocket *socket) = 0;
		};

	// virtual destructor
	public:
		virtual ~IClientSocket(void) {}

	// start - stop
	public:
		virtual void	connect(const std::string &addr, int port) = 0;
		virtual void	initFromSocket(void *socket) = 0;
		virtual	void	closeClient(void) = 0;

	// recv / send
	public:
		virtual void      	send(const IMessage &msg) = 0;
		virtual IMessage	*receive(void) = 0;

	// handle state
	public:
	  	virtual bool 	isWritable(void) const = 0;
		virtual bool	isReadable(void) const = 0;

	// set listener
	public:
		virtual void	setOnSocketEventListener(IClientSocket::OnSocketEvent *listener) = 0;

};
```

Au niveau de l'implémentation, c'est très simple au niveau de QtNetwork.

Pareil pour Boost::Asio même si ça peut paraître un peu moins évident au premier abord.

* send fera appel à async_write (au même titre que le write de QtNetwork est asynchrone).

En revanche, c'est au niveau du read que ça se complique un peu:

* Le serveur lancera automatiquement un async_read après l'init
* Le callback de l'async_read (qui est appelé après la lecture de qqc dans la socket) refera un appel à async_read comme il est possible de le voir dans l'exemple sur le site offi d'Asio
* Le msg lu sera stocké dans une liste de messages internes à l'implémentation de IClientSocket
* Le callback de l'async_read fera évidemment appel au listener onSocketReadyRead()
* receive retournera le premier élément de la liste de messages

C'est différent de ce qui sera fait dans l'implémentation via QtNetwork.

* En effet, QtNetwork emet un signal quand la socket est dispo en écriture.
* Le listener onSocketReadyRead est alors appelé
* La fonction receive fera alors un call à la fonction read de QtNetwork et retournera le résultat


### IMessage

```cpp
class IClientSocket {

	struct IMessage {
	  char		*msg;
	  int		msgSize;
	  std::string	host;
	  int		port;
	}

}
```

La structure IClientSocket::IMessage est utilisée pour l'envoie et la réception de data.

Elle est essentielle et au coeur de la conception pour 2 principales raisons:

* Permettre l'envoie de n'importe quel type de data, notamment du son.
* Permettre d'abstraire les socket TCP et UDP sous la même interface IClientSocket malgré les différences de fonctionnement énormes

Lorsque l'on souhaite lire sur une socket, le fonctionnement sera le même en TCP et en UDP: le structure sera entièrement remplie avec les infos suivantes:

* msg => message
* msgSize => taille du message lu
* host => host du sender
* port => port du sender

En revanche, au niveau de l'envoi, la méthode de fonctionnement va légèrement différer entre UDP et TCP

* TCP n'utilisera que les champs msg et msg size
* UDP utilisera tous les champs: il enverra le msg de taille msgSize à @host:port


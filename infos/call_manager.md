# CallManager

## Les classes

### CallManager

CallManager est la classe principale. C'est elle qui fera la liaison entre la classe AudioManager et la classe SoundPacketBuilder.

Elle sera appellée pour:

* démarrer une conversation avec `void startCall(const Contact &contact)`
* terminer une conversation avec `void endCall(void)`

### AudioManager

AudioManager est en charge de récupérer et de jouer du son. Elle fait la liaison entre SoundInputDevice (récupération du son), SoundOutputDevice (jouer du son) et EncodeManager (encode-decode de son)

Elle possède notammant:

* Un slot `void playSound(const Sound::Encoded &sound)` qui sera appelé pour jouer du son
* Un signal `void soundAvailable(const Sound::Encoded &sound)` qui sera émis pour signaler qu'un packet de son est dispo

### SoundPacketBuilder

SoundPacketBuilder est en charge de la communication réseau client-client.

Elle devra tout simplement permettre l'envoi et la réception de packet de son via:

* le slot `void sendSound(const Sound::Encoded &sound)` pour l'envoi
* le signal 'void receiveSound(const Sound::Encoded &sound)' pour la réception

## Utilisation

### Initialisation

* CallManager
  * connect le signal `SoundPacketBuilder::receiveSound` avec le slot `AudioManager::playSound`
  * connect le signal `AudioManager::soundAvailable` avec le slot `SoundPacketBuilder::sendSound`
* AudioManager
  * crée un SoundInputDevice
  * crée un SoundOutputDevice
* SoundPacketBuilder
  * crée un UdpClient
  * connect l'UDP client ("127.0.0.1", 4242 par exemple)
  * set le listener pour être au courant de la disponibilité de paquet en lecture

### StartCall

* CallManager::startCall
  * appelle AudioManager::startRecording
  * appelle AudioManager::startPlaying
  * appelle SoundPacketBuilder::acceptPacketFrom
  * stocke le mCurrentCalledContact
* AudioManager::startRecording
  * appelle SoundInputDevice::startStream
  * démarre un thread (la classe AudioManager hérite de QThread)
* AudioManager::startPlaying
  * appelle SoundOutputDevice::startStream
* SoundPacketBuilder::acceptPacketFrom
  * stock le mAcceptedPort
  * stock le mAcceptedHost

### EndCall

* CallManager::endCall
  * appelle AudioManager::stopRecording
  * appelle AudioManager::stopPlaying
  * reset le mCurrentCalledContact
  * appelle acceptPacketFrom avec des params par défaut pour reset ("", 0 par exemple)
* Sound::stopRecording
  * terminate le thread de lecture de son
  * appelle SoundInputDevice::stopStream
* Sound::stopPlaying
  * appelle SoundOutputDevice::stopStream

### SendSound

Dans le thread de lecture de son (créé dans AudioManager::startRecording):

* Lis du son
* Si du son a pu être lu, on l'encode
* Si du son a pu être lu, on emet le signal ``void AudioManager::soundAvailable(const Sound::Encoded &sound)`

L'émission de ce signal va du coup appeler le slot `void SoundPacketBuilder::sendSound(const Sound::Encoded &sound)`. A l'intérieur de ce slot, il faut:

* Créer un IClientSocket::Message
* Stocker le Sound::Encoded dans le IClientSocket::Message
* Envoyer le son au contact

** Attention **: Dans le cas de socket UDP, il faut spécifier à qui on envoie le message. Il faut donc renseigner le change Message::host et Message::port avec le host et le port du contact.


### ReceiveSound

Lorsque la socket UDP est dispo en lecture, cela signifie que du son est disponible. A ce moment là, il faut:

* Lire la socket: on récupère alors un IClientSocket::Message
* On crée un Sound::Encoded et on stocke ce qu'on a reçu dedans
* On émet le signal `SoundPacketBuilder::receiveSound(const Sound::Encoded &sound)`

Cela va du coup appeler le slot `AudioManager::playSound(const Sound::Encoded &sound)`

Dans ce slot, il faut alors:

* Décoder le son
* Jouer le son

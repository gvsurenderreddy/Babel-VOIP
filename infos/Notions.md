## SERVER SIDE

* Librarie Boost (ASIO) (http://www.boost.org/doc/libs/1_40_0/doc/html/boost_asio.html)
* No libraries QT
* Proxy mode for conference calls or NAT-ed clients


## CLIENT SIDE

* No libraries Boost
* Libraries QT (QThread and QTNetwork)
* Librarie PortAudio (http://www.portaudio.com/) (LibC donc necessite une abstraction C++)


## Compression codec

* Speex (http://www.speex.org/) (LibC donc necessite une abstraction C++)
* Speex est déprécié: Opus est une alternative tolérée: http://www.opus-codec.org/downloads/


## ACCOUNTS

* (md5 / sha1) + salt
* UDP pour la voie
* TCP pour les messages
* Etudier le protocole Boost ASIO <server> et QTNetwork <client> pour avoir une bonne abstraction server


## FEATURES

* Contact List (liste de contacts)
* Make a call (passer un appel)
* Hang up (répondre à un appel)
* Conception de la communication doit etre commune au deux groupes

## BONUS

* Text chat
* Record a call and play it back
* Answering machine
* Conference call
* Video

## MEGA BONUS

* Que les bonus ci-dessus soit implémenté sous forme de plugins

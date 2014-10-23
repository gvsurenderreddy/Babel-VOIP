# Sound Packets

Cette partie permet d'améliorer la transmission du son via internet avec une conception avancée.

## SoundPacket

SoundPacket est la structure qui définit comment sera formaté nos paquets de son à envoyer.

```cpp
struct SoundPacket {
  int   magic_code;
  long  timestamp;
  int   soundSize;
  char  sound[500];
};
```

Cette structure est composée d'un certains nombre d'attributs, dont voici la description:

|type|nom|description|
|----|---|-----------|
|int|magic_code|Contiens le magic code. **Le magic code DOIT avoir pour valeur: 0x150407CA**|
|long|timestamp|Contiens le timestamp de l'heure à laquelle a été créé le paquet de son|
|int|soundSize|Contiens la taille du buffer de son contenue dans `sound`|
|char[500]|sound|Contiens le buffer de son|

## Implémentation

La structure SoundPacket doit être rajoutée dans la classe `SoundPacketBuilder` (c'est obvious vu que c'est elle qui gère le network).

A partir de là, il va falloir effectuer des modifications dans 2 fonctions: `sendSound` et `receiveSound`. Il faudra en effet:

* Créer un `SoundPacket` dans `sendSound`
* Extraire le son d'un `SoundPacket` dans `receiveSound`

### sendSound

Ici, il ne faut donc plus envoyer un Message qui contient le son brut comme on l'a fait jusqu'à maintenant.

Si l'on procède par étape, il faut:

1. Créer une variable `SoundPacket`
2. On initialise tous les attributs du SoundPacket
  * magic_code doit valoir 0x150407CA
  * timestamp doit valoir le timestamp actuel (cf google: comment avoir un timestamp en cpp)
  * soundSize contiens tout simplement la taille du son encodé
  * sound contiens les sons encodé. **Et, non alain, soundPacket.sound = encodedSound.buffer n'est pas la solution :) man memcpy** (et qui dit memcpy, dit allocation de mémoire avant!)
3. A partir de là, notre paquet de son est prêt. Le soucis, c'est qu'on doit utiliser un `IClientSocket::Message` pour envoyer quelque chose. Du coup, on crée un `IClientSocket::Message`
4. Obviously, on initialise notre message
  * message.msgSize vaudra la taille de notre structure SoundPacket (man sizeof)
  * message.msg vaudra le contenu de notre structure. Evidemment, message.msg = soundPacket ne fonctionne pas. Et message.msg = &soundPacket non plus (oui, je te connais alain :D). Man memcpy
5. On envoie le message!

## receiveSound

Ici, on ne reçoit plus le son en brut: on reçois un SoundPacket. Il faudra donc récupérer notre soundPacket puis notre son.

Si l'on procède par étape, il faut:

1. On receive notre `IClientSocket::Message`
2. Comme on souhaite extraite un `SoundPacket`, on crée une variable de ce type.
3. On copie les octets de message.msg dans notre variable SoundPacket: man memcpy :D
4. C'est bon, on a notre SoundPacket: notre son est donc dans soundPacket.sound et sa taille dans soundPacket.soundSize
5. On a plus qu'à créer notre `Sound::Encoded`, à l'initialiser (memcpy!) et à émettre le signal `receiveSound`

## Timestamp

L'attribut timestamp peut paraitre curieux et inutile. Pourtant, il est assez cool.

Le principe est le suivant: quand on reçois un paquet de son, on stocke le timestamp dans un attribut de `SoundPacketBuilder`.

Lors de la réception d'un autre paquet de son, on comparera le timestamp de l'ancien paquet de son avec le timestamp du nouveau paquet de son:

* Si le timestamp reçu est plus grand, alors on récupère le son et on le joue
* Si le timestamp reçu est plus petit, c'est que le paquet reçu est arrivé en retard (le son a été enregistré avant le paquet de son qu'on a réçu avant): on ne traite donc pas ce paquet et on ne fait rien.


## Le mot de la fin

Courage

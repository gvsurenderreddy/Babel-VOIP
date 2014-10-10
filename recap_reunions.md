## Réunion 1


### Serialisation

* [Sérialisation via boost](http://fr.openclassrooms.com/informatique/cours/serialisation-avec-boost)
* Sérialisation XML?


### Utilisateur

* Nom de compte. Unique et choisit à la création du compte. Ne peut pas être modifié
* Pseudo. Possibilité d'avoir le même pseudo que qqn. Peut être modifié.
* Mot de passe. Peut être modifié
* Statut ('mange', 'occupé', 'se branle'...). Peut être modifié.
* Statut en ligne. Définit par le serveur.


### Fonctionnnalités nécessitant une communication avec le serveur

* inscription
* connexion / déconnexion
* lister les contacts
* inviter / accepter / refuser / supprimer un contact
* afficher les infos d'un contact
* appeler / raccrocher / décrocher
* Notifier connexion / déconnexion
* Modifier les infos utilisateurs
* Chat textuel


### Choix du protocole réseaux

* UDP => communication entre clients (voix)
* TCP => communication entre clients et serveur (cmd serveurs + chat textuel)


### Protocole de communication client-server

* Voir le google doc (dispo sur slack)
* Quelques modifications doivent être faites (par exemple: raccrocher devrait être client-client?)
* Même principe que le protocole de communication du zappy.


### Protocole de communication client-client

A définir.


## Réuninon 2


### Protocole client-server

Le protocole client-server a été update (cf drive sur slack).

Le protocole textuel a été changé par un protocole binaire pour répondre au sujet.


### Protocole client-client

Une structure contenant les infos de communication a été définie dans le google doc (cf drive dans slack).


### Infos Annexes

Les 2 protocoles pourront évoluer en fonction de comment fonction portaudio/speex.

# Suivi Conception

* Gestion du timeout pendant le Call (uniquement pour le client-client): Envoi d'un packet, attente de réception de packet.
* Ajouter un ID pour les paquets de son. Si un paquet est antérieur, on ne le traite pas
* Créé une structure pour chaque commande au niveau du client-serveur pour alléger le processus de récup des commandes (2 étapes de lecture au lieu de 3)
* Améliorer le système de code d'erreur: pas juste OK/KO, mais des codes plus explicites.

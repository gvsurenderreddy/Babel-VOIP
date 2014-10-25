# BabelMainWindow: Signals & Slots

## Slots

|Fonction|Description|Données Annexes|
|--------|-----------|---------------|
|void	updateContactList(const QList<Contact> &contacts)|Reset la liste de contacts à afficher||
|void	newContactInvitation(const Contact &contact)|Quand quelqu'un nous a envoyé une invit|contact ne contient que le accountName|
|void	newMessage(const Contact &contact, const QString &message)|Quand quelqu'un nous a envoyé un message|Contact ne contient que le accountName|
|void	newCallInvitation(const Contact &contact)|Quand quelqu'un souhaite nous appeler|Contact ne contient que le accountName|
|void	startingCommunication(const Contact &contact, bool hasAccepted)|quand quelqu'un a répondu à notre demande d'appel|contact ne contient que le accountName|
|void	terminatingCommunication(const Contact &contact)|quand le contact a quitté l'appel||
|void	updateInfo(const Contact &contact)|quand les infos de ntore utilisateurs ont été mises à jours sur le serveur|contact contient l'accountname, le pseudo, le status et le isConnected|
|void	createAccountSuccess(const ErrorStatus &errorStatus)|le serveur nous informe si la création de compte a fonctionné||
|void	authenticateSuccess(const ErrorStatus &errorStatus)|le serveur nous informe si l'authentification a fonctionné||
|void	sendInvitationSuccess(const ErrorStatus &errorStatus)|le serveur nous informe si l'envoi de message a fonctionné||
|void	updateInfoSuccess(const ErrorStatus &errorStatus)|le serveur nous informe si la mise à jour des infos a fonctionné|le slot updateInfo sera appelé également en cas de succès|
|void	callContactSuccess(const ErrorStatus &errorStatus)|le serveur nous informe si l'appel d'un contact a fonctionné|le slot startingCommunication sera appelé une fois que le contact aura accepté ou refusé l'appel|
|void	acceptCallSuccess(const ErrorStatus &errorStatus)|le serveur nous informe s'il y a eu une erreur quand nous avons accepté un appel|le slot startingCommunication sera appelé en cas de succès|
|void	terminateCallSuccess(const ErrorStatus &errorStatus)|le serveur nous informe s'il y a eu erreur quand nous avons demandé de stopper l'appel||

## Signals

|Fonction|Description|Données Annexes|
|--------|-----------|---------------|
|void	askForRegistration(const Contact &contact)|quand on souhaite créer un compte|Il faut renseigner l'accountName, le pseudo et le password dans le contact|
|void	askForAuthentication(const Contact &contact)|quand on souhaite se connecté|Il faut renseigner l'accountName et le password dans le contact|
|void	askForAddingContact(const Contact &contact)|quand on souhaite ajouter un contact|Il faut renseigner l'accountName du contact|
|void	askForAcceptingContact(const Contact &contact, bool hasAccepted)|quand on souhaite accepter ou refuser une demande d'ajout de contact|Il faut renseigner l'accountName du contact|
|void	askForDeletingContact(const Contact &contact)|quand on souhaite supprimer un conact|Il faut renseigner l'accountName du contact|
|void	askForSendingMessage(const Contact &contact, const QString &message)|quand on souhate envoyer un message a un contact|il faut renseigner l'accountName du contact|
|void	askForDisconnection(void)|quand on souhaite se déconnecter||
|void	askForUpdatingInfo(const Contact &contact)|quand on souhaite mettre à jour le profil|il faut renseigner le pseudo, le status et le password|
|void	askForCalling(const Contact &contact)|quand on souhaite appeler un contact|il faut renseigner l'accountName du contact|
|void	askForAcceptingCall(const Contact &contact, bool hasAccepted)|quand on souhaite accepter ou refuser un appel|il faut renseigner l'accountName du contact|
|void	askForTerminatingCall(const Contact &contact)|quand on souhaite quitter un appel|il faut renseigner l'accountName du contact|


## Info Annexes

* Taille max du pseudo: 255 charactères
* Taille max du password: 255 charactères
* Taille max d'un message: 255 charactères

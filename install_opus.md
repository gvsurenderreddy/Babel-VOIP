## Installation Opus

* [Télécharger opus](http://downloads.xiph.org/releases/opus/opus-1.1.tar.gz)
* Dézippé
* Aller dans le dossier opus-1.1/opus-1.1/win32/VS2010
* Lancer la solution opus.sln
* Si une popup s'affiche pour des raisons de compat, sélectionnez tout et cliquez sur ok
* Clic droit sur la solution dans l'exploreur de fichier de visual
* Générer toute la solution
* Les .lib sont dispos dans opus-1.1/opus-1.1/win32/VS2010/Win32/Debug


## Compiler avec Opus

* Clic droit sur le projet
* Propriétés
* Editeur de liens
* Entrée
* Dépendances supplémentaires
* modifier
* ajouter chaque lib


## Rajouter les includes

* Les includes sont dans opus-1.1/opus-1.1/include
* clic droit sur le projet
* propriétés
* répertoire VC++
* répertoires d'includes
* modifier
* ajouter le dossier d'include opus

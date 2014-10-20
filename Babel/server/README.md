## Server


### Fichier .pro

Toutes les informations nécessaires à la compilation (sources, headers, librairies...) se trouvent dans le fichier `server.pro`

Si l'on souhaite ajouter un fichier ou linker le programme avec une librairie, c'est le server.pro qu'il faut modifier!


### Compilation avec qmake

L'intérêt d'un fichier .pro est la possibilité de générer un Makefile Unix ou un projet Visual Studio sans n'avoir rien à gérer.
Il faut indiquer à qmake où se trouve le dossier Boost sur votre ordinateur

* `qmake BOOST_ROOT=/path/to/Boost_root_folder` permet de générer un Makefile pour Unix
* `qmake BOOST_ROOT=C:\Boost\1.56.0\VC\12.0 -tp vc` permet de générer un projet Visual Studio (notamment le fichier .vcxproj)


### Développer

Si l'on développe sous Visual Studio, par exemple, et que l'on souhaite créer un fichier: NE PAS CREER LE FICHIER SOUS VISUAL!

Suivez plutôt ces étapes pour être sûr de ne pas créer de soucis de portabilité:

* Créer un fichier à la main
* Indiquez l'ajout de source dans le fichier .pro
* Regénérer votre projet visual (qmake)
* Retournez sur Visual
* Visual devrait vous indiquer que le projet a été modifié et vous propose de rafraîchir son contenu
* Rafraichissez le contenu :)

# Le projet Neptune
Neptune est un jeu inspiré du jeu bac-à-sable Minecraft écrit en C++ avec OpenGL.

## Pourquoi?
Minecraft est un de mes jeux favoris. J'adore le concept d'un monde bac-à-sable ou tout est possible, mais il y'a plusieurs problèmes avec ce jeu qui m'encourage a faire un jeu inspiré de celui-ci.

### Minecraft: Edition Java
Comme le nom l'indique, "Minecraft: Java Edition" est le jeu original, écrit en Java.
Le problème avec Java est que le code compilé tourne... sur une machine virtuelle! Pas les machines virtuelles qui vous servent a virtualiser une instance de Windows, Linux..., mais plutôt la machine virtuelle Java.
A cause du compilateur "just-in-time" de la VM qui va convetir le "bytecode" Java en code machine que le processeur peux interpréter, l'exécution des programmes tournant sur la JVM va être ralenti.

## Dépendances
Vous avez besoin du matériel suivant pour lancer le jeu:
* Un processeur sur architecture x86_64. (Des versions 32-bit seront fournis pour mobile, aussi.)
* 1go de RAM (pas vraiment requis, mais plutôt pour s'assurer que le jeu fonctionne bien.)
* Un pilote graphique capable de OpenGL 3.3 (Chaque pilote graphique sorti après 2010 devrait le prendre en charge.)

Bibliothèques nécéssaires: (installe les paquets de déveleoppement si vous voulez modifier le code)
* GLM: OpenGL Mathematics (Mathématiques OpenGL). Principalement utilisé pour la caméra.
* Boost: Uniquement nécéssaire pour le développement, est une bibliothèque d'outils qui se compile directement dans le programme.

## Comment compiler?
Il y'a un "Makefile" dans le dossier racine, donc c'est aussi simple que ca:
* Installe les bibliothèques mentionés dans Dépendances avec leur paquets de developpement, une "toolchain" de compilation, et enfin "make"
* Lance "make -j4" et puis vous pouvez lancer l'exécutable du jeu, intitulé "bin/neptune"
* Que le fun commence!

## Crédits
Les bibliothèques suivantes sont intégrés dans le jeu due a leur nature
* GLAD: Gère l'OpenGL
* plthook: Redirige des appels de fonctions vers d'autre fonctions
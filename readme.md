# Game Of Life
## English
This project is a version of [_The Game of Life_ by John Conway](https://playgameoflife.com/) implemented in [C++](https://fr.wikipedia.org/wiki/C%2B%2B) and using the graphical library [SDL2](https://www.libsdl.org/). The main goal was to enjoy coding a project in _C++_ while refreshing best practices of the language. Creating a Game of Life has also been a long-time personal objective, making this the perfect opportunity to finally do it. However, the graphical interface is only functional, as my priority was the game logic.
### Features
This version has several particular aspects, allowing:
* Running automatic generation scrolling.
* Advancing by one generation.
* Going back by one generation.
* Navigating an infinite grid.
* Through a configuration file (examples available in ```configExamples```):
 * Setting the number of neighbors required for a cell to stay alive (0 -> 8).
 * Setting the maximum number of neighbors for a cell to stay alive (0 -> 8).
 * Setting the number of neighbors required for a cell to be born (0 -> 8).
 * Setting the maximum number of neighbors for a cell to be born (0 -> 8).
 * Choosing whether cells have different colors based on the number of neighbors they had in the previous generation.
 * Defining the initial grid state at generation zero (not possible via the interface, see examples for details).


## Français
Ce projet est une version du jeu [_The game of life_ de John Conways](https://playgameoflife.com/) réalisée en [C++](https://fr.wikipedia.org/wiki/C%2B%2B) et utilisant la librairie graphique [SDL2](https://www.libsdl.org/) dans le but de du plaisir en codant un projet en _C++_ et de me rappeler les bonnes pratiques du langage. Faire un _Game of life_"_ est également un objectif personnel depuis longtemps donc ça a été l'occasion de le faire. En revanche l'interface graphique n'est présente que pour le coté fonctionnel, ma priorité étant la logique du jeu.

## Fonctionnalités
Cette version est assez particulière, elle permet: 
* Lancer le défilement des générations automatiques.
* Avancer d'un génération
* Reculer d'une génération
* Naviguer sur la grille infini
* Grace à un fichier de configuration, dont des examples sont présents dans ```configExamples```:
 * Choisir le nombre de voisin nécessaire pour qu'une case reste en vie (0 -> 8)
 * Choisir le nombre de voisin maximum pour qu'une case reste en vie (0 -> 8)
 * Choisir le nombre de voisin nécessaire pour qu'une case naisse (0 -> 8)
 * Choisir le nombre de voisin maximum pour qu'une case naisse (0 -> 8)
 * Choisir si les case ont des couleurs différentes en fonction du nombre de voisinne qu'elles avaient à la génération précédantes
 * Choisir l'état de la grille à la génération zéro (chose impossible sur l'interface) (voir les exemples pour le fonctionnement)
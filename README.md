# ProceduralPaperDungeon
 
GitHub : https://github.com/Cmdu76/ProceduralPaperDungeon  
  
Trello : https://trello.com/b/gaBl2ico/proceduralpaperdungeon  
  
### Explications du jeu
- Donjon composé d'une infinité d'étages, l'objectif étant d'aller le plus haut possible
- Les étages sont composés de plusieurs salles dont le nombre varie aléatoirement selon l'étage
- Certaines salles sont spéciales : elles peuvent comporter des coffres ou des escaliers
- Les coffres améliorent les statiques du joueur (mouvement, dégâts, vie...)
- Les escaliers permettent de monter à l'étage supérieur (pas d'escaliers descendants)
- Les salles comportent aussi un nombre aléatoire d'ennemis
- Il y a plusieurs types d'ennemis, chacun avec des comportements différents
- Des tâches d'encres sont placées aléatoirement dans les salles comme décorations


### Touches
 - ZQSD pour déplacer le personnage
 - Clic droit pour tirer avec le personnage vers l'endroit pointé par la souris
 - Les flèches pour changer directement de salle (seulement pour le Debug)
  
### Partie code
  
##### Utilisation du C++11
- std::unique_ptr, std::shared_ptr
- std::function, lambda
- std::chrono
  
##### OlympusEngine
- Le jeu se base sur le moteur de jeu OlympusEngine : https://github.com/Cmdu76/OlympusEngine
- OlympusEngine utilise la bibliothèque SFML qui permet de gérer des fonctionnalités multimédia bas niveaux : https://www.sfml-dev.org/index-fr.php
- Il repose sur des bibliothèques externes : dirent (gestion de fichiers), FastDynamicCast, PugiXML, ImGUI
- Il comporte d'autres systèmes bas niveaux dans Engine/System
- Il comporte des classes de bases pour la gestion mathématiques (vecteur, aléatoire, ...) dans Engine/Math
- Il comporte des classes de surcouche de SFML dans Engine/Graphics
- Il comporte des classes de gestion haut niveau dans Engine/Application
- La partie principale du moteur est dans Engine/Core, c'est le Entity-Component-System
- Wikipedia : "Entity–component–system (ECS) is an architectural pattern that is mostly used in game development. ECS follows the composition over inheritance principle that allows greater flexibility in defining entities where every object in a game's scene is an entity (e.g. enemies, bullets, vehicles, etc.). Every Entity consists of one or more components which add behavior or functionality. Therefore, the behavior of an entity can be changed at runtime by adding or removing components. This eliminates the ambiguity problems of deep and wide inheritance hierarchies that are difficult to understand, maintain and extend. Common ECS approaches are highly compatible and often combined with data-oriented design techniques."
- Il faut hériter de Entity pour créer de nouvelles entités spécifique à notre jeu
- On ajoute ensuite des Component à nos entités
- Le moteur donne déjà de nombreux Component qui sont suffisant pour créer de nombreux jeux
- Si le jeu requiert d'autres Components plus complexe, il faut hériter de Component ou SceneComponent ou RenderableComponent pour créer les notres

##### Le jeu 
- Dans le main(), nous créeons l'Application, la classe mère du moteur, qu'on paramètre ensuite
- Ensuite nous donnons notre GameState, dans la StateMachine du moteur
- Le GameState est composé de 4 fonctions principales
  - Le constructeur : qui initialise ses données (création du monde, du joueur, ...)
  - handleEvent(...) : qui est appelée quand un évènement clavier/souris/OS est produit
  - update(...) : qui est appelée 60 fois par seconde, qui permet de mettre à jour la logique du jeu
  - render(...) : qui est appelée autant que possible, qui dessine les RenderableComponent des Entités en vie

##### La génération
- Dans le constructeur du GameState, nous créeons le premier FloorData, basé sur la seed passée en paramètre
- Le système de génération permet de charger exactement le même donjon à partir de la même seed
    - 1 : On génère la grille de salles représentant l'étage
    - 2 : On parcourt la grille pour générer les portes entre les salles
    - 3 : On ajoute les coffres et les escaliers dans l'étage
    - 4 : On ajoute les ennemis et les décorations dans chaque salle
- On donne ensuite les données de la salle (RoomData) à la classe Room qui va gérer les entités de la salle à partir des données

##### Le gameplay
- Nous avons notre propre classe Entity qui hérite de oe::Entity
- Elle nous permet de définir des variables et comportements pour le joueur et les IA, comme la Sprite et la gestion des mouvements
- Le joueur est implémenté dans la classe PlayerEntity qui hérite de Entity
- Le joueur possède un ActionComponent et des ActionInputKey qui vont permettre de gérer le clavier et la souris de façon simplifier
- Les IA sont implémentées dans la classe EnemyEntity qui hérite de Entity
- Il y a 3 types d'IA : Bat, Spider et Bouftou
- Les Bats se déplacent peu et tirent à distance
- Les Spiders se déplacent aléatoirement vers le joueur et tirent quand elles sont à proximités
- Les Bouftous se déplacent par "charges" et font des dégats au contact avec le joueur

##### Répartition du travail
- Charles Mailly (Cmdu76) : Génération + GameState + Architecture
- Antoine Gurnaud (Dayamante) : PlayerEntity + EnemyEntity + GameState
  

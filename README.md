# 🦅 Bird Sim - Boids Algorithm in C

Une simulation de nuée interactive (Flocking) basée sur l'algorithme des Boids de Craig Reynolds, écrite en C pur et propulsée par Raylib. 

![Aperçu de la simulation](https://via.placeholder.com/800x450.png?text=Ajoute+une+capture+d'ecran+de+ta+nuee+ici)

## 🌟 Fonctionnalités

La simulation repose sur la combinaison vectorielle de trois règles simples appliquées à chaque entité, générant un comportement de groupe complexe et organique :

* **Séparation :** Calcul d'un vecteur de répulsion pour éviter l'entassement et les collisions avec les voisins immédiats.
* **Cohésion :** Recherche du barycentre du groupe local pour rassembler les individus isolés.
* **Alignement :** Synchronisation du vecteur vitesse (cap et vélocité) avec celui des voisins proches.

**Points techniques additionnels :**
* **Espace Toroïdal :** Calcul des trajectoires et des distances les plus courtes à travers les bordures de l'écran (effet Pac-Man) via un ajustement spatial, permettant un vol continu.
* **Interface Temps Réel :** Intégration de `raygui` pour manipuler les forces de Reynolds en direct sans recompilation.
* **Esthétique :** Rendu graphique utilisant la palette ergonomique *Solarized Light*.

## 🛠️ Technologies & Dépendances

* **Langage :** C
* **Bibliothèque Graphique :** [Raylib](https://www.raylib.com/) (Rendu 2D géométrique)
* **Interface UI :** Raygui (Single-header library)

### Prérequis (Debian / Ubuntu)
Assurez-vous d'avoir les outils de compilation et les dépendances Raylib installés :
```bash
sudo apt update
sudo apt install build-essential git libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev

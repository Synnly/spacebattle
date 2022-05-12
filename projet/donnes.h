#ifndef DONNES_H
#define DONNES_H

/**
 * \file donnees.h
 * \brief En tete des fonctions pour la gestion des donnees du monde
 * \author Fernandes dos Santos Emanuel et Lagarde Tristan
 * \date 31 mars 2022
 */

#include "sdl2-light.h"


/**
 * \brief Largeur de l'écran de jeu
 */
#define SCREEN_WIDTH 300


/**
 * \brief Hauteur de l'écran de jeu
 */
#define SCREEN_HEIGHT 480


/**
 * \brief Taille d'un vaisseau
 */
#define SHIP_SIZE 32


/**
 * \brief Taille du missile
*/
#define MISSILE_SIZE 8


/**
 * \brief Vitesse du missile
*/
#define MISSILE_SPEED 20


/**
 * \brief Vitesse du vaisseau
*/
#define MOVING_STEP 10


/**
 * \brief Vitesse verticale de l'ennemi
 */
#define ENEMY_SPEED 1

/**
 * \brief Nombre d'ennemis
 */
#define NB_ENEMIES 10

/**
 * \brief Vie d'un missile
 */
#define MISSILE_LIFE 1

/**
 *\brief Vie d'un ennemi classique
 */
#define ENEMY_LIFE 1

/**
 *\brief Vie d'un ennemi tank
 */
#define TANK_LIFE 3

/**
 *\brief Vie du joueur
 */
#define PLAYER_LIFE 3

/**
 * \brief Distance en ordonnée entre chaque ennemis
 */
#define VERTICAL_DIST 2*SHIP_SIZE

/**
 * \brief Nombre d'images avant la fermeture du jeu
 */
#define FRAME_CLOSURE 300


/**
 * \brief Taille de la police d'ecriture des textes
 */
#define FONT_SIZE 14


/**
 * \brief Type du vaisseau
 */
#define VAISSEAU_TYPE 0

/**
 * \brief Type du missile
 */
#define MISSILE_TYPE 1

/**
 * \brief Type de l'ennemi classique
 */
#define ENNEMI_TYPE 2

/**
 * \brief Type du vaisseau cassé
 */
#define CASSE_TYPE 3

/**
 * \brief Type du tank
 */
#define TANK_TYPE 4

/**
 * \brief Type de l'ambulance
 */
#define AMBULANCE_TYPE 5

/**
 * \brief Type de la grenouille
 */
#define GRENOUILLE_TYPE 6

/**
 * \brief Type du screamer
 */
#define SCREAMER_TYPE 99

/**
 * \brief Etat du jeu lorsque le joueur a perdu
 */
#define DEFAITE_ETAT 0

/**
 * \brief Etat du jeu lorsque le compte a rebours est en cours
 */
#define COMPTE_ETAT 1

/**
 * \brief Etat du jeu lorsque le jeu est en cours
 */
#define ENCOURS_ETAT 2


/**
 * \brief Représentation d'un sprite
 */
struct sprite_s {
    int x;  /*!< Coordonee x */
    int y;  /*!< Coordonee y */
    unsigned int h; /*!< Hauteur du sprite */
    unsigned int w; /*!< Largeur du sprite */
    unsigned int v; /*!< Vitesse du sprite */
    unsigned int is_visible; /*!< Champ lié à la visibilité du sprite */
    unsigned int type; /*< Champ lié au type de sprite ; 0: vaisseau, 1: missile du vaisseau, 2: ennemi classique, 3: ennemi casse, 4: ennemi tank, 5: ambulance, 6: Grenouille*/
    unsigned int lives;/*!< Champ qui compte le nombre de vie(s) d'un sprite */
};

/**
 * \brief Type qui correspond aux sprites
 */
typedef struct sprite_s sprite_t;


/**
 * \brief Représentation du monde du jeu
*/
struct world_s{
    sprite_t vaisseau;  /*!< Champ lié au vaisseau */
    sprite_t missile;   /*!< Champ lié au missile du vaisseau */
    int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */
    sprite_t enemies[NB_ENEMIES];   /*!< Champ lié au tableau contenant tous les ennemis */
    int nb_ennemis_sortis;  /*!< Champ qui compte le nombre d'ennemis qui sont sortis de l'ecran par la bordure du bas */
    unsigned int score;     /*!< Champ qui compte le score */
    unsigned int pause;     /*!< Champ indiquant si le jeu est en pause */
    unsigned int etat;      /*!< 0 : le joueur a perdu, 1 : le compte a rebours avant la fermeture du jeu est lancé, 2 : Le jeu est en cours, */
    unsigned int frame_count;   /*!< Champ qui compte le nombre d'images avant la fermeture du jeu */
    sprite_t screamer; /*!< Champ lié au screamer */
   
};

/**
 * \brief Type qui correspond aux données du monde
 */
typedef struct world_s world_t;

/**
 * \brief Retourne le score
 * \param world Les données du jeu
 * \return Le score
 */
unsigned int getscore(world_t *world);

/**
 * \brief Met le score
 * \param world Les données du monde
 * \param montant Le monatnt
 */
void setscore(world_t *world_t, unsigned int montant);

/**
 * \brief Retourne le vaisseau
 * \param world Les données du monde
 * \return Le vaisseau
 */
sprite_t *getvaisseau(world_t *world);

/**
 * \brief Retourne le missile
 * \param world Les données du monde
 * \return Le missile
 */
sprite_t *getmissile(world_t *world);

/**
 * \brief Retourne le ieme ennemi
 * \param world Les données du monde
 * \param i L'indice de l'ennemi
 * \return Le ieme ennemi
 */
sprite_t *getenemies(world_t *world, unsigned int i);


/**
 * \brief Met l'etat du gameover
 * \param world Les donnees du jeu
 * \param etat L'etat du game over
 */
void setgameover(world_t *world, unsigned int valetat);

/**
 * \brief Met le nombre d'ennemis sortis
 * \param world Les donnees du jeu
 * \param montant Le nombre d'ennemis
 */
void setnb_ennemis_sortis(world_t *world, unsigned int montant);

/**
 * \brief Retourne le nombre d'ennemis sortis
 * \param world Les donnees du jeu
 * \return Le nombre d'ennemis sortis
 */
unsigned int getnb_ennemis_sortis(world_t *world);

/**
 * \brief Mets l'etat de la pause
 * \param world Les donnees du jeu
 * \param etat L'etat de la pause
 */
void setpause(world_t *world, unsigned int etat);

/**
 * \brief Retourne l'etat de la pause
 * \param world Les donnees du jeu
 * \return L'etat de la pause
 */
unsigned int getpause(world_t *world);

/**
 * \brief Met l'etat de la partie
 * \param world Les donnees du jeu
 * \param etat L'etat de la partie
 */
void setetat(world_t * world, unsigned int valetat);

/**
 * \brief Retourne l'etat de la partie
 * \param world Les donnees du jeu
 * \return L'etat de la partie
 */
unsigned int getetat(world_t *world);

/**
 * \brief Donne la valeur de framecount
 * \param world Les donnees du jeu
 * \param amount La valeur de framcount
 */
void setframecount(world_t *world, unsigned int amount);

/**
 * \brief Donne la valeur de framecount
 * \param world Les donnees du jeu
 * \return La valeur de framecount
 */
unsigned int getframecount(world_t *world);

/**
 * \brief Donne le sprite du screamer
 * \param world Les donnees du jeu
 * \return Le sprite du screamer
 */
sprite_t* getscreamer(world_t* world);


/**
 * \brief Retourne la coordonnée x d'un sprite
 * \param sprite Le sprite
 * \return La coordonnée x
 */
int getx(sprite_t *sprite);

/**
 * \brief Retourne la coordonnée y d'un sprite
 * \param sprite Le sprite
 * \return La coordonnée y
 */
int gety(sprite_t *sprite);

/**
 * \brief Met la coordonnée x du sprite
 * \param sprite Le sprite
 * \param x La coordonnée x
 */
void setx(sprite_t *sprite, int valx);

/**
 * \brief Met la coordonnée y du sprite
 * \param sprite Le sprite
 * \param y La coordonnée y
 */
void sety(sprite_t *sprite, int valy);

/**
 * \brief Retourne la largeur d'un sprite
 * \param sprite Le sprite
 * \return Sa largeur
 */
unsigned int getwidth(sprite_t *sprite);

/**
 * \brief Retourne la hauteurd'un sprite
 * \param sprite Le sprite
 * \return Sa hauteur
 */
unsigned int geth(sprite_t *sprite);

/**
 * \brief Met la largeur du sprite
 * \param sprite Le sprite
 * \param w Sa largeur
 */
void setw(sprite_t *sprite, unsigned int valw);

/**
 * \brief Met la hauteur du sprite
 * \param sprite Le sprite
 * \param h Sa hauteur
 */
void seth(sprite_t *sprite, unsigned int valh);

/**
 * \brief Retourne la vitesse d'un sprite
 * \param sprite Le sprite
 * \return La vitesse
 */
unsigned int getv(sprite_t * sprite);

/**
 * \brief Met la vitesse du sprite
 * \param sprite Le sprite
 * \param x La vitesse
 */
void setv(sprite_t * sprite, unsigned int valv);

/**
 * \brief Retourne le type d'un sprite
 * \param sprite Le sprite
 * \return Le type du sprite
 */
unsigned int gettype(sprite_t *sprite);

/**
 * \brief Met le type du sprite
 * \param sprite Le sprite
 * \param type Le type
 */
void settype(sprite_t *sprite, unsigned int valtype);

/**
 * \brief Retourne les points de vie d'un sprite
 * \param sprite Le sprite
 * \return Ses points de vie
 */
unsigned int getlives(sprite_t *sprite);

/**
 * \brief Met le nombre de poinst de vie du sprite
 * \param sprite Le sprite
 * \param x Le nombre de points de vie
 */
void setlives(sprite_t *sprite, unsigned int vallives);

/**
 * \brief Retourne la visibilité d'un sprite
 * \param sprite Le sprite
 * \return La visibilité du sprite
 */
unsigned int getvisibility(sprite_t *sprite);


/**
 * \brief Fonction qui génère un nombre aléatoire entre a et b(non compris)
 * \param a borne a
 * \param b borne b
 * \return un nombre aléatoire entre a et b
 */
int generate_number(int a, int b);


/**
 * \brief initialisation d'un sprite
 * \param sprite Le sprite à initialiser
 * \param x Coordonnee x
 * \param y Coordonnee y
 * \param w Largeur du sprite
 * \param h Hauteur du sprite
 * \param v Vitesse du sprite
 */
void init_sprite(sprite_t* sprite, int x, int y, unsigned int w, unsigned int h, int v, unsigned int type, unsigned int lives);


/**
 * \brief Affiche les informations d'un sprite
 * \param sprite Le sprite
 */
void print_sprite(sprite_t *sprite);


/**
 * \brief Rends un sprite visible
 * \param sprite Le sprite
 */
void set_visible(sprite_t *sprite);

/**
 * \brief Rends un sprite invisible
 * \param sprite Le sprite
 */
void set_invisible(sprite_t *sprite);

/**
 * \brief Verifie que le vaisseau ne dépasse pas les bords de l'ecran
 * \param sprite Le sprite
 */
void vaisseau_depasse_bords(sprite_t *sprite);

/**
 * \brief Replace l'ennemi au dessus de l'ecran
 * \param world Le monde
 * \param i L'indice du ieme enemi
 */ 
void reset_enemi(world_t *world, unsigned int i);

/**
 * \brief Verifie que l'ennemi n'est pas trop bas
 * \param world Le monde
 */
void ennemi_depasse_bas(world_t* world);

/**
 * \brief Verifie que le missile ne dépasse pas l'écran
 * \param world Le monde
 */
void missile_depasse_haut(world_t* world);

/**
 * \brief Verifie si deux sprites entrent en collision
 * \param sp2 Deuxième sprite
 * \param sp1 Premier sprite
 * \return 1 en cas de collision, 0 sinon
 */
int sprites_collide(sprite_t *sp2, sprite_t *sp1);

/**
 * \brief Fonction qui gère le score
 * \param world Le monde du jeu
 */
void score(world_t* world);

/**
 * \brief Retourne le type d'ennemi à apparaitre en fonction de sa probabilité d'apparition
 * \return Le type de l'ennemi
 */
unsigned int proba_spawn();


/**
 * \brief Gere les collisions entre les missiles et les ennemis
 * \param sp2 Missile
 * \param sp1 Ennemi
 */
void handle_missiles_collide(world_t *world);

/**
 * \brief Gere les collisions entre les missile et l'ambulance et le vaisseau et l'ambulance
 * \param world Les donnees du monde
 */
void handle_ambulance_collide(world_t* world);

/**
 * \brief Gere les collisions entre le vaisseau et les ennemis
 * \param world Le monde du jeu
 */
void handle_vaisseau_collide(world_t* world);

/**
 * \brief Donne un point de vie au sprite
 * \param sprite Le sprite
 */
void heal(sprite_t *sprite);


/**
 * \brief Gère la prise de dégats du sprite
 * \param sprite Un sprite
 */
void take_dmg(sprite_t* sprite);

/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */
void init_data(world_t * world);

/**
 * \brief La fonction qui initialise le tableau contenant les ennemis
 * \param world les données du monde
 */
void init_enemies(world_t* world);


/**
 * \brief La fonction nettoie les données du monde
 * \param world les données du monde
 */
void clean_data(world_t *world);


/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */
int is_game_over(world_t *world);



/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param world les données du monde
 */
void update_data(world_t *world);


/**
 * \brief La fonction met à jour la positions de tous les ennemis
 * \param world les données du monde
 */
void update_enemies(world_t *world);


/**
 * \brief fonction qui gère l'état du jeu
 * \param world le monde du jeu
 */
void compute_game(world_t* world);

/**
 * \brief Rend invisible un sprite s'il n'a plus de vies ou inversement
 * \param sprite Le sprite
 */
void compute_lives(sprite_t *sprite);

/**
 * \brief Gère la visibilité de tous les sprites du jeu
 * \param world Le monde du jeu
 */
void compute_sprites(world_t* world);

/**
 * \brief Fait avancer le missile
 * \param world Les données du jeu
 */
void avance_missile(world_t *world);



/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */
void handle_events(SDL_Event *event,world_t *world);

#endif
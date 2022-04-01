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
#define MISSILE_SPEED 10


/**
 * \brief Vitesse du vaisseau
*/
#define MOVING_STEP 5


/**
 * \brief Vitesse verticale de l'ennemi
 */
#define ENEMY_SPEED 2


/**
 * \brief Représentation d'un sprite
 */
struct sprite_s {
    int x;  /*!< Coordonee x */
    int y;  /*!< Coordonee y */
    unsigned int h; /*!< Hauteur du sprite */
    unsigned int w; /*!< Largeur du sprite */
    unsigned int v; /*!< Vitesse du sprite */
    int is_visible; /*!< Champ lié à la visibilité du sprite */
};

/**
 * \brief Type qui correspond aux sprites
 */
typedef struct sprite_s sprite_t;


/**
 * \brief Représentation du monde du jeu
*/
struct world_s{
    sprite_t vaisseau;
    sprite_t ennemi;         
    sprite_t missile;
    int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */
};

/**
 * \brief Type qui correspond aux données du monde
 */
typedef struct world_s world_t;


/**
 * \brief initialisation d'un sprite
 * \param sprite Le sprite à initialiser
 * \param x Coordonnee x
 * \param y Coordonnee y
 * \param w Largeur du sprite
 * \param h Hauteur du sprite
 * \param v Vitesse du sprite
 */
void init_sprite(sprite_t* sprite, int x, int y, int w, int h, int v);


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
 * \brief Verifie que le sprite n'est pas trop à gauche
 * \param sprite Le sprite
 */
void depasse_gauche(sprite_t *sprite);


/**
 * \brief Verifie que le sprite n'est pas trop à droite
 * \param sprite Le sprite
 */
void depasse_droite(sprite_t *sprite);


/**
 * \brief Verifie que l'ennemi n'est pas trop bas
 * \param sprite Le sprite
 */
void ennemi_depasse_bas(sprite_t *sprite);


/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */
void init_data(world_t * world);


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
 * \param les données du monde
 */
void update_data(world_t *world);


/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */
void handle_events(SDL_Event *event,world_t *world);

#endif
#ifndef GRAPHISMES_H
#define GRAPHISMES_H

/**
 * \file graphismes.h
 * \brief En tete des fonctions pour la gestion des graphiques
 * \author Fernandes dos Santos Emanuel et Lagarde Tristan
 * \date 31 mars 2022
 */

#include "sdl2-light.h"
#include "sdl2-ttf-light.h"
#include "donnes.h"

/**
 * \brief Représentation pour stocker les textures nécessaires à l'affichage graphique
*/
struct ressources_s{
    SDL_Texture* background; /*!< Texture liée à l'image du fond de l'écran. */
    SDL_Texture* ennemi_texture;    /*!< Texture liée à l'image de l'ennemi. */
    SDL_Texture* vaisseau_texture;  /*!< Texture liée à l'image du vaisseau. */
    SDL_Texture* missile_texture;   /*!< Texture liée à l'image du missile. */
    TTF_Font* font; /*!< Police d'ecriture. */
};

/**
 * \brief Type qui correspond aux textures du jeu
*/
typedef struct ressources_s ressources_t;


/**
 * \brief Applique la texture dans un sprite
 * \param renderer Le renderer
 * \param textures La textue à appliquer
 * \param sprite Le sprite
 */
void apply_sprite (SDL_Renderer *renderer, SDL_Texture *textures, sprite_t *sprite);


/**
 * \brief Applique les textures des ennemis
 * \param renderer Le renderer
 * \param textures La texture à appliquer
 * \param enemies Le tableau d'ennemis
 */
void apply_enemies(SDL_Renderer *renderer, SDL_Texture *textures, sprite_t *enemies);


/**
 * \brief La fonction nettoie les textures
 * \param textures les textures
*/
void clean_textures(ressources_t *textures);


/**
 * \brief La fonction initialise les texures
 * \param screen la surface correspondant à l'écran de jeu
 * \param textures les textures du jeu
*/
void init_textures(SDL_Renderer *renderer, ressources_t *textures);


/**
 * \brief La fonction applique la texture du fond sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param textures les textures du jeu
*/
void apply_background(SDL_Renderer *renderer, ressources_t *textures);

/**
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param renderer la surface de l'écran de jeu
 * \param world les données du monde
 * \param textures les textures
 */
void refresh_graphics(SDL_Renderer *renderer, world_t *world,ressources_t *textures);

#endif
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
 * \brief Représentation pour stocker les ressources nécessaires à l'affichage graphique
*/
struct ressources_s{
    SDL_Texture* background; /*!< Texture liée à l'image du fond de l'écran. */
    SDL_Texture* ennemi_texture;    /*!< Texture liée à l'image de l'ennemi classique. */
    SDL_Texture* ennemi_casse_texture;    /*!< Texture liée à l'image de l'ennemi casse. */
    SDL_Texture* tank_texture;      /*!< Texture liée à l'image du tank. */
    SDL_Texture* ambulance_texture; /*!< Texture liée à l'image de l'ambulance */
    SDL_Texture* vaisseau_texture;  /*!< Texture liée à l'image du vaisseau. */
    SDL_Texture* missile_texture;   /*!< Texture liée à l'image du missile. */
    SDL_Texture* grenouille_texture; /*!< Texture liée à l'image de la grenouille */
    TTF_Font* font; /*!< Police d'ecriture. */
};

/**
 * \brief Type qui correspond aux ressources du jeu
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
 * \param texture_ennemi La texture de l'ennemi classique
 * \param texture_casse_ennemi La texture de l'ennemi casse
 * \param tank_texture La texture du tank
 * \param enemies Le tableau d'ennemis
 */
void apply_enemies(SDL_Renderer *renderer, SDL_Texture *texture_ennemi, SDL_Texture *texture_casse_ennemi, SDL_Texture *tank_texture, SDL_Texture* ambulance_texture, SDL_Texture *grenouille_texture, world_t *world);


/**
 * \brief La fonction nettoie les ressources
 * \param ressources les ressources
*/
void clean_ressources(ressources_t *ressources);


/**
 * \brief La fonction initialise les ressources
 * \param screen la surface correspondant à l'écran de jeu
 * \param ressources les ressources du jeu
*/
void init_ressources(SDL_Renderer *renderer, ressources_t *ressources);


/**
 * \brief La fonction applique la texture du fond sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param textures la textures du fond d'ecran
*/
void apply_background(SDL_Renderer *renderer, ressources_t *textures);


/**
 * \brief Affiche le score sur l'ecran
 * \param renderer Le renderer
 * \param world Les donnees du monde
 * \param ressources Les ressources du jeu
 */
void afficher_score(SDL_Renderer *renderer, world_t *world, ressources_t *ressources);

/**
 * \brief Affiche les vies sur l'ecran
 * \param renderer Le renderer
 * \param world Les donnees du monde
 * \param ressources Les ressources du jeu
 */
void afficher_vies(SDL_Renderer *renderer, world_t *world, ressources_t *ressources);

/**
 * \brief Affiche un message en fonction de l'etat du jeu et le score
 * \param renderer Le renderer
 * \param world Les données du monde
 * \param ressources Les ressources du jeu
 */
void afficher_etat_jeu(SDL_Renderer *renderer, world_t *world, ressources_t *ressources);


/**
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param renderer la surface de l'écran de jeu
 * \param world les données du monde
 * \param ressources les ressources
 */
void refresh_graphics(SDL_Renderer *renderer, world_t *world,ressources_t *ressources);

#endif
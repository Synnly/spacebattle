/**
 * \file initialisation.c
 * \brief Implementation des fonction d'initialisation de données et de ressources simultannées
 * \author Fernandes dos Santos Emanuel et Lagarde Tristan
 * \date 31 mars 2022
 */

#include "donnes.h"
#include "graphismes.h"
#include "audio.h"


/**
* \brief fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des ressources, nettoyage des données
* \param window la fenêtre du jeu
* \param renderer le renderer
* \param ressources les ressources
* \param world le monde
*/
void clean(SDL_Window *window, SDL_Renderer * renderer, ressources_t *ressources, world_t * world){
    clean_ressources(ressources);
    clean_sdl(renderer,window);
    
}


/**
 * \brief fonction qui initialise le jeu: initialisation de la partie graphique (SDL), chargement des ressources, initialisation des données
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param ressources les ressources
 * \param world le monde
 */
void init(SDL_Window **window, SDL_Renderer ** renderer, ressources_t *ressources, world_t * world, audio_t *audio){
    init_sdl(window,renderer,SCREEN_WIDTH, SCREEN_HEIGHT);
    init_data(world);
    init_ttf();
    init_ressources(*renderer, ressources);
    init_audio(audio);
    init_sfx(audio);
}
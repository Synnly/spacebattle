/**
 * \file main.c
 * \brief Programme principal initial du niveau 1
 * \author Mathieu Constant
 * \version 1.0
 * \date 18 mars 2020
 */

#include "sdl2-light.h"
#include "donnes.h"
#include "graphismes.h"
#include "initialisation.h"
#include <time.h>

/**
 *  \brief programme principal qui implémente la boucle du jeu
 */
int main(int argc, char* args[]){
    SDL_Event event;
    world_t world;
    ressources_t ressources;
    SDL_Renderer *renderer;
    SDL_Window *window;

    srand(time(NULL));

    //initialisation du jeu
    init(&window,&renderer,&ressources,&world);
    
    while(!is_game_over(&world)){ //tant que le jeu n'est pas fini

        //gestion des évènements
        handle_events(&event,&world);

        if(!world.pause){

            //mise à jour des données liée à la physique du monde
            update_data(&world);
        }

        //rafraichissement de l'écran
        refresh_graphics(renderer,&world,&ressources);
        
        // pause de 10 ms pour controler la vitesse de rafraichissement
        pause(10);
    }
    
    //nettoyage final
    clean(window,renderer,&ressources,&world);
    
    return 0;
}
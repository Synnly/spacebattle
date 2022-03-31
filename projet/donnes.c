/**
 * \file donnees.c
 * \brief Implementation des fonctions pour la gestion des donnees du monde
 * \author Fernandes dos Santos Emanuel et Lagarde Tristan
 * \date 31 mars 2022
 */

#include "sdl2-light.h"
#include "donnes.h"


/**
 * \brief initialisation d'un sprite
 * \param sprite Le sprite à initialiser
 * \param x Coordonnee x
 * \param y Coordonnee y
 * \param w Largeur du sprite
 * \param h Hauteur du sprite
 * \param v Vitesse du sprite
 */
void init_sprite(sprite_t* sprite, int x, int y, int w, int h, int v){
    sprite->x = x;
    sprite->y = y;
    sprite->h = h;
    sprite->w = w;
    sprite->v = v;
    sprite->is_visible = 0; // Sprite de base visible
}


/**
 * \brief Affiche les informations d'un sprite
 * \param sprite Le sprite
 */
void print_sprite(sprite_t *sprite){
    printf("Sprite :\nx,y = %d,%d\nh,w = %d,%d\nv = %d\nis_visible = %s\n", sprite->x, sprite->y, sprite->h, sprite->w, sprite->v, (!sprite->is_visible?"oui":"non"));
}


/**
 * \brief Rends un sprite visible
 * \param sprite Le sprite
 */
void set_visible(sprite_t *sprite){
    sprite->is_visible = 0;
}


/**
 * \brief Rends un sprite invisible
 * \param sprite Le sprite
 */
void set_invisible(sprite_t *sprite){
    sprite->is_visible = 1;
}


/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */
void init_data(world_t * world){

    world->gameover = 0;

    /**
     * Initialisation du vaisseau
     */
    init_sprite(&(world->vaisseau), SCREEN_WIDTH/2, SCREEN_HEIGHT - (int)(1.5*SHIP_SIZE), SHIP_SIZE, SHIP_SIZE, 0);

    /**
     * initialisation de l'ennemi
     */
    init_sprite(&(world->ennemi), SCREEN_WIDTH/2, 2 * SHIP_SIZE, SHIP_SIZE, SHIP_SIZE, 0);

    /**
     * Initialisation du missile
     */
    init_sprite(&(world->missile), SCREEN_WIDTH/2, world->vaisseau.y, MISSILE_SIZE, MISSILE_SIZE, MISSILE_SPEED);
    set_invisible(&(world->missile));
    print_sprite(&(world->vaisseau));
    print_sprite(&(world->ennemi));
}


/**
 * \brief La fonction nettoie les données du monde
 * \param world les données du monde
 */
void clean_data(world_t *world){
    /* utile uniquement si vous avez fait de l'allocation dynamique (malloc); la fonction ici doit permettre de libérer la mémoire (free) */
}


/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */
int is_game_over(world_t *world){
    return world->gameover;
}


/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param les données du monde
 */
void update_data(world_t *world){
    world->ennemi.y+=ENEMY_SPEED;

    if(!world->missile.is_visible){
        world->missile.y-=MISSILE_SPEED;
    }
}


/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */
void handle_events(SDL_Event *event,world_t *world){
    Uint8 *keystates;
    while( SDL_PollEvent( event ) ) {
        
        //Si l'utilisateur a cliqué sur le X de la fenêtre
        if( event->type == SDL_QUIT ) {
            //On indique la fin du jeu
            world->gameover = 1;
        }
       
         //si une touche est appuyée
         if(event->type == SDL_KEYDOWN){
             //si la touche appuyée est 'D'
             if(event->key.keysym.sym == SDLK_d){
                 printf("La touche D est appuyée\n");
              }

            //si la touche appuyée est fleche gauche
            if(event->key.keysym.sym == SDLK_LEFT){
                world->vaisseau.x -= MOVING_STEP;
            }

            //si la touche appuyée est fleche droite
            if(event->key.keysym.sym == SDLK_RIGHT){
                world->vaisseau.x += MOVING_STEP;
            }

            //si la touche appuyée est espace
            if(event->key.keysym.sym == SDLK_SPACE){
                set_visible(&(world->missile));
                world->missile.x = world->vaisseau.x;
                world->missile.y = world->vaisseau.y;
            } 

            //si la touche appuyée est echap
            if(event->key.keysym.sym == SDLK_ESCAPE){
                world->gameover = 1;
            }
        }
    }
}
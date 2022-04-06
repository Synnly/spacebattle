/**
 * \file donnees.c
 * \brief Implementation des fonctions pour la gestion des donnees du monde
 * \author Fernandes dos Santos Emanuel et Lagarde Tristan
 * \date 31 mars 2022
 */

#include "sdl2-light.h"
#include "donnes.h"
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

/* Generation d'un nombre entier compris entre a et b
*/
int generate_number(int a, int b){
    return rand()%(b-a)+a;
}

void init_sprite(sprite_t* sprite, int x, int y, int w, int h, int v){
    sprite->x = x;
    sprite->y = y;
    sprite->h = h;
    sprite->w = w;
    sprite->v = v;
    sprite->is_visible = 0; // Sprite de base visible
}


void print_sprite(sprite_t *sprite){
    printf("Sprite :\nx,y = %d,%d\nh,w = %d,%d\nv = %d\nis_visible = %s\n", sprite->x, sprite->y, sprite->h, sprite->w, sprite->v, (!sprite->is_visible?"oui":"non"));
}


void set_visible(sprite_t *sprite){
    sprite->is_visible = 0;
}


void set_invisible(sprite_t *sprite){
    sprite->is_visible = 1;
}


void depasse_gauche(sprite_t *sprite){
    if(sprite->x<0){
        sprite->x = 0;
    }
}


void depasse_droite(sprite_t *sprite){
    if(sprite->x>SCREEN_WIDTH-SHIP_SIZE){
        sprite->x = SCREEN_WIDTH-SHIP_SIZE;
    }
}


void ennemi_depasse_bas(sprite_t *sprite){
    if(sprite->y>SCREEN_HEIGHT){
        sprite->y = 2 * SHIP_SIZE;
    }
}


int sprites_collide(sprite_t *sp2, sprite_t *sp1){
    // Calcul de la distance entre les deux sprites
    double dist = sqrt(pow((sp2->x - sp1->x), 2) + pow((sp2->y - sp1->y), 2));
    return SHIP_SIZE>dist;
}


void handle_sprites_collide(sprite_t *sp2, sprite_t *sp1){
    // Si les deux sprites entrent en collision ET sont visibles
    if(sprites_collide(sp2, sp1) && !sp2->is_visible && !sp1->is_visible){
        sp2->v = 0;
        sp1->v = 0;
        set_invisible(sp2);
        set_invisible(sp1);
    }
}


void init_data(world_t * world){
    world->gameover = 0;

    /**
     * Initialisation du vaisseau
     */
    init_sprite(&(world->vaisseau), SCREEN_WIDTH/2, SCREEN_HEIGHT - (int)(1.5*SHIP_SIZE), SHIP_SIZE, SHIP_SIZE, 0);

    /**
     * initialisation de l'ennemi
     */
    init_sprite(&(world->ennemi), SCREEN_WIDTH/2, 2 * SHIP_SIZE, SHIP_SIZE, SHIP_SIZE, ENEMY_SPEED);
    
    /**
     * initialisation du tableau des ennemis
     */
    init_enemies(world);

    /**
     * Initialisation du missile
     */
    init_sprite(&(world->missile), SCREEN_WIDTH/2, world->vaisseau.y, MISSILE_SIZE, MISSILE_SIZE, MISSILE_SPEED);
    set_invisible(&(world->missile));
    print_sprite(&(world->vaisseau));
    print_sprite(&(world->ennemi));
    
    
}

void init_enemies(world_t* world){
    for(int i=0;i<NB_ENEMIES;i++){
        init_sprite(&(world->enemies[i]),generate_number(0,SCREEN_WIDTH),-SHIP_SIZE-i*VERTICAL_DIST,SHIP_SIZE,SHIP_SIZE,ENEMY_SPEED);
    }
}


void clean_data(world_t *world){
    /* utile uniquement si vous avez fait de l'allocation dynamique (malloc); la fonction ici doit permettre de libérer la mémoire (free) */
}


int is_game_over(world_t *world){
    return world->gameover;
}


void update_data(world_t *world){
    //L'ennemi entre en contact avec le vaisseau
    handle_sprites_collide(&(world->ennemi),&(world->vaisseau));
    // Test de collision entre le missile et l'ennemi
    handle_sprites_collide(&(world->ennemi),&(world->missile));
    
    //L'ennemi se déplace
    world->ennemi.y+=world->ennemi.v;
    // Si le missile est visible alors il avance.
    if(!world->missile.is_visible){
        world->missile.y-=world->missile.v;
    }

    // Le vaisseau reste sur l'ecran
    depasse_gauche(&(world->vaisseau));
    depasse_droite(&(world->vaisseau));

    // L'ennemi boucle sur l'ecran
    ennemi_depasse_bas(&(world->ennemi));

    

    
    
}


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

            //si la touche appuyée est espace et que le vaisseau est visible
            if(event->key.keysym.sym == SDLK_SPACE && world->vaisseau.is_visible==0){
                set_visible(&(world->missile));
                world->missile.x = world->vaisseau.x;
                world->missile.y = world->vaisseau.y;
                world->missile.v=MISSILE_SPEED;
            } 

            //si la touche appuyée est echap
            if(event->key.keysym.sym == SDLK_ESCAPE){
                world->gameover = 1;
            }
        }
    }
}
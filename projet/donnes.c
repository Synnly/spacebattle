/**
 * \file donnees.c
 * \brief Implementation des fonctions pour la gestion des donnees du monde
 * \author Fernandes dos Santos Emanuel et Lagarde Tristan
 * \date 31 mars 2022
 */

#include "sdl2-light.h"
#include "sdl2-ttf-light.h"
#include "donnes.h"
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

/* Generation d'un nombre entier compris entre a et b */
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
    printf("Sprite : x,y = %d,%d | h,w = %d,%d\nv = %d\nis_visible = %s\n", sprite->x, sprite->y, sprite->h, sprite->w, sprite->v, (!sprite->is_visible?"oui":"non"));
}


void set_visible(sprite_t *sprite){
    sprite->is_visible = 0;
}


void set_invisible(sprite_t *sprite){
    sprite->is_visible = 1;
}


void vaisseau_depasse_bords(sprite_t *sprite){
    /*Bord gauche*/
    if(sprite->x<0){
        sprite->x = 0;
    }

    /*Bord droite*/
    if(sprite->x>SCREEN_WIDTH-SHIP_SIZE){
        sprite->x = SCREEN_WIDTH-SHIP_SIZE;
    }
}


void ennemi_depasse_bas(world_t *world){
    for(int i=0; i<NB_ENEMIES; i++){
        if(world->enemies[i].y>SCREEN_HEIGHT && !world->enemies[i].is_visible){
            world->nb_ennemis_sortis ++;
            set_invisible(&(world->enemies[i]));
        }
    }
}


int sprites_collide(sprite_t *sp2, sprite_t *sp1){
    // Calcul de la distance entre les deux sprites
    double dist = sqrt(pow((sp2->x - sp1->x), 2) + pow((sp2->y - sp1->y), 2));
    return SHIP_SIZE>dist;
}

void score(world_t* world){
    for(int i=0; i<NB_ENEMIES; i++){
        if(sprites_collide(&(world->missile),&(world->enemies[i])) && !world->missile.is_visible && !world->enemies[i].is_visible){
            world->score++;
        }
    }
    if(world->score==NB_ENEMIES){
        world->score*=2;
    }
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
    world->nb_ennemis_sortis = 0;
    world->score = 0;
    world->frame_count = 0;

    //Initialisation du vaisseau
    init_sprite(&(world->vaisseau), SCREEN_WIDTH/2 - SHIP_SIZE/2, SCREEN_HEIGHT - (int)(1.5*SHIP_SIZE), SHIP_SIZE, SHIP_SIZE, 0);
<<<<<<< HEAD
    
=======

>>>>>>> e596624d1d17668ce2937729cfff38d18e08fb6f
    //initialisation du tableau des ennemis
    init_enemies(world);

    //Initialisation du missile
    init_sprite(&(world->missile), SCREEN_WIDTH/2, world->vaisseau.y, MISSILE_SIZE, MISSILE_SIZE, MISSILE_SPEED);
    set_invisible(&(world->missile));   
}

void init_enemies(world_t* world){
    for(int i=0;i<NB_ENEMIES;i++){
        init_sprite(&(world->enemies[i]),generate_number(0,SCREEN_WIDTH-SHIP_SIZE),-SHIP_SIZE-i*VERTICAL_DIST,SHIP_SIZE,SHIP_SIZE,ENEMY_SPEED);
    }
}


void clean_data(world_t *world){
    /* utile uniquement si vous avez fait de l'allocation dynamique (malloc); la fonction ici doit permettre de libérer la mémoire (free) */
}


int is_game_over(world_t *world){
    return world->gameover;
}


void update_enemies(world_t *world){
    for(int i = 0; i<NB_ENEMIES; i++){
        world->enemies[i].y+=world->enemies[i].v;
    }
}

int all_enemies_visible(world_t* world){
    int all_visible = 0;
    for(int i = 0; i<NB_ENEMIES; i ++){
        if(!world->enemies[i].is_visible){
            all_visible = 1;
        }
    }
    return all_visible;
}

void compute_game(world_t* world){
    /*Jeu de base en cours*/
    world->etat=3;

    /*Le joueur a perdu*/
    if(world->vaisseau.is_visible){
        world->etat=0;
        world->frame_count++;
    }

    /*Tous les ennemis ont été tués*/
    if(!world->vaisseau.is_visible && world->score==NB_ENEMIES*2){
        world->etat=1;
        world->frame_count++;
    }

    /*Tous les ennemis n'ont pas été tués*/
    if(!world->vaisseau.is_visible && !all_enemies_visible(world)){
        world->etat=2;
        world->frame_count++;
    }

    /*Temps de latence avant la fermeture du jeu*/
    if(world->frame_count>=FRAME_CLOSURE){
        world->gameover=1;
    }
}

void update_data(world_t *world){

    //Les ennemis entrent en contact avec le vaisseau
    for(int i=0;i<NB_ENEMIES;i++){
        handle_sprites_collide(&(world->enemies[i]),&(world->vaisseau));
    }

    //Test de collision entre le missile et les ennemis
    for(int i=0;i<NB_ENEMIES;i++){
     handle_sprites_collide(&(world->enemies[i]),&(world->missile));
    }

    //LES ennemiS se delpacENT
    update_enemies(world);

    // Si le missile est visible alors il avance.
    if(!world->missile.is_visible){
        world->missile.y-=world->missile.v;
    }

    /* Le vaisseau reste sur l'ecran */
    vaisseau_depasse_bords(&(world->vaisseau));

    /* Detection du depassement du bord bas par les ennemis */
    ennemi_depasse_bas(world);

    /*Gestion de l'état du jeu*/
    compute_game(world);

    /*Gestion des collisions entre missile et ennemis*/
    score(world);
}


void avance_missile(world_t *world){
    set_visible(&(world->missile));

    /* On place le missile au milieu au dessus du sprite du vaisseau */
    world->missile.x = world->vaisseau.x + SHIP_SIZE/2 - MISSILE_SIZE/2;
    world->missile.y = world->vaisseau.y;

    world->missile.v=MISSILE_SPEED;
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
                avance_missile(world);
            } 

            //si la touche appuyée est echap
            if(event->key.keysym.sym == SDLK_ESCAPE){
                world->gameover = 1;
            }
        }
    }
}
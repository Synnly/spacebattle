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

unsigned int getx(sprite_t *sprite){return sprite->x;}

unsigned int gety(sprite_t *sprite){return sprite->y;}

void setx(sprite_t *sprite, unsigned int valx){sprite->x = valx;}

void sety(sprite_t *sprite, unsigned int valy){sprite->y = valy;}

unsigned int getv(sprite_t *sprite){return sprite->v;}

void setv(sprite_t *sprite, unsigned int valv){sprite->v = valv;}

unsigned int gettype(sprite_t *sprite){return sprite->type;}

void settype(sprite_t *sprite, unsigned int valtype){sprite->type = valtype;}

unsigned int getlives(sprite_t *sprite){return sprite->lives;}

void setlives(sprite_t *sprite, unsigned int vallives){sprite->lives = vallives;}


/* Generation d'un nombre entier compris entre a et b */
int generate_number(int a, int b){
    return rand()%(b-a)+a;
}

void init_sprite(sprite_t* sprite, int x, int y, unsigned int w, unsigned int h, int v, unsigned int type, unsigned int lives){
    sprite->x = x;
    sprite->y = y;
    sprite->h = h;
    sprite->w = w;
    sprite->v = v;
    sprite->is_visible = 0; // Sprite de base visible
    sprite->type = type;
    sprite->lives = lives;
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

    /*Bord droit*/
    if(sprite->x>SCREEN_WIDTH-SHIP_SIZE){
        sprite->x = SCREEN_WIDTH-SHIP_SIZE;
    }
}

void reset_enemi(world_t *world, unsigned int i){
    unsigned int num_type = generate_number(1, 8);
    unsigned int type=2;
    unsigned int lives;
    lives=ENEMY_LIFE;
    switch(num_type){
        case 3:{
            type=3;
            break;
        }
        case 4:{
            type=4;
            lives=TANK_LIFE;
            break;
        }
        case 5:{
            type = 5;
            /*L'ambulaces a autant de vie que le joueur car chaque coup sur l'ambulance enleve un point de vie
            au vaisseau */
            lives=PLAYER_LIFE;
            break;
        }
        default:{
            break;
        }
    }
    init_sprite(&(world->enemies[i]), generate_number(0,SCREEN_WIDTH-SHIP_SIZE), -SHIP_SIZE-i*VERTICAL_DIST, SHIP_SIZE, SHIP_SIZE, ENEMY_SPEED, type,lives);
}

void ennemi_depasse_bas(world_t *world){
    for(int i=0; i<NB_ENEMIES; i++){
        if(world->enemies[i].y>SCREEN_HEIGHT){
            world->nb_ennemis_sortis ++;
            reset_enemi(world, i);
        }
    }
    world->nb_ennemis_sortis %= NB_ENEMIES; // Nb d'ennemis qui retourne à 0 quand tous les ennemis sont sortis
}


int sprites_collide(sprite_t *sp2, sprite_t *sp1){
    // Calcul de la distance entre les deux sprites
    double dist = sqrt(pow((sp2->x - sp1->x), 2) + pow((sp2->y - sp1->y), 2));
    return SHIP_SIZE>dist;
}

void score(world_t* world){
    for(int i=0; i<NB_ENEMIES; i++){
        if(sprites_collide(&(world->missile),&(world->enemies[i])) && !world->missile.is_visible && !world->enemies[i].is_visible && (world->enemies[i].lives)==1){
            world->score++;
        }
    }
    if(world->score==NB_ENEMIES){
        world->score*=2;
    }
}

void handle_missiles_collide(world_t *world){
    for(int i=0; i<NB_ENEMIES; i++){
        if(sprites_collide(&(world->missile), &(world->enemies[i])) && !world->missile.is_visible && !world->enemies[i].is_visible){

            if(world->enemies[i].type==5){  
                world->missile.v = 0;
                take_dmg(&(world->missile));
                take_dmg(&(world->vaisseau));
            }
    
            else {
                world->missile.v = 0;
                take_dmg(&(world->missile));
                take_dmg(&(world->enemies[i]));
            }
        }
    }
}

void handle_vaisseau_collide(world_t* world){
    for(int i=0; i<NB_ENEMIES; i++){

        // Si le vaisseau et l'ambulance entrent en collision ET si le vaiseau et l'ambulance sont visibles
        if(sprites_collide(&(world->vaisseau),&(world->enemies[i])) && !world->vaisseau.is_visible && !world->enemies[i].is_visible){

            if(world->enemies[i].type == 5){
                world->enemies[i].v=0;
                take_dmg(&(world->enemies[i]));
                take_dmg(&(world->enemies[i]));
                take_dmg(&(world->enemies[i]));
                heal(&(world->vaisseau), 1);  
            }

            else {
                (&(world->enemies[i]))->v=0;
                take_dmg(&(world->enemies[i]));
                take_dmg(&(world->vaisseau));  
            }
            
        }
    }
}


void heal(sprite_t *sprite, unsigned int montant){
    sprite->lives+=montant;
}

void take_dmg(sprite_t* sprite){
    if(sprite->lives>=1){
        sprite->lives--;
    }
}

void init_data(world_t * world){
    world->gameover = 0;
    world->etat = 3;
    world->nb_ennemis_sortis = 0;
    world->score = 0;
    world->frame_count = 0;
    world->pause = 0;

    //Initialisation du vaisseau
    init_sprite(&(world->vaisseau), SCREEN_WIDTH/2 - SHIP_SIZE/2, SCREEN_HEIGHT - (int)(1.5*SHIP_SIZE), SHIP_SIZE, SHIP_SIZE, 0, 0,PLAYER_LIFE);

    //initialisation du tableau des ennemis
    init_enemies(world);

    //Initialisation du missile du vaisseau
    init_sprite(&(world->missile), SCREEN_WIDTH/2, world->vaisseau.y, MISSILE_SIZE, MISSILE_SIZE, MISSILE_SPEED, 1,0);
    
}

void init_enemies(world_t* world){
    unsigned int type;
    for(int i=0;i<NB_ENEMIES;i++){
        reset_enemi(world, i);
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

        if(world->enemies[i].type == 3){
            world->enemies[i].x = SDL_sin(0.05*world->enemies[i].y)*45+(SCREEN_WIDTH/2);
        }
    }
}

void compute_game(world_t* world){
    /*Le joueur a perdu*/
    if(world->vaisseau.lives == 0){
        world->etat=0;
        world->frame_count++;
    }

    /*Temps de latence avant la fermeture du jeu*/
    if(world->frame_count>=FRAME_CLOSURE){
        world->gameover=1;
    }

    /*Jeu de base en cours*/
    if(world->etat == 3){
        /* Detection du depassement du bord bas par les ennemis */
        ennemi_depasse_bas(world);
    }
}

void compute_lives(sprite_t* sprite){
    if(sprite->lives>0){
        set_visible(sprite);
    }else{
        set_invisible(sprite);
    }
}

void compute_sprites(world_t* world){
    compute_lives(&(world->vaisseau));
    compute_lives(&(world->missile));
    for(int i=0;i<NB_ENEMIES;i++){
        compute_lives(&(world->enemies[i]));
    }
}

void update_data(world_t *world){

    

    //Gestion des collisions entre le vaisseau et les ennemis
    handle_vaisseau_collide(world);

    //Test de collision entre le missile et les ennemis
    handle_missiles_collide(world);

    //LES ennemiS se delpacENT
    update_enemies(world);

    // Si le missile est visible alors il avance.
    if(!world->missile.is_visible){
        world->missile.y-=world->missile.v;
    }

    /* Le vaisseau reste sur l'ecran */
    vaisseau_depasse_bords(&(world->vaisseau));

    /*Gestion de l'état du jeu*/
    compute_game(world);

    //Gestion de la visiblité des sprites
    compute_sprites(world);

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

             //Si le jeu n'est pas en pause
             if(!world->pause){

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
                    world->missile.lives=1;
                }
            }
            //si la touche appuyée est echap
            if(event->key.keysym.sym == SDLK_ESCAPE){
                world->pause += 1;  // On pase à l'etat de pause suivant 
                world->pause %= 2;  // 0 ou 1
            }
        }
    }
}
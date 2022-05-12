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

//Seter et geter de world_t

unsigned int getscore(world_t *world){return world->score;}

void setscore(world_t *world, unsigned int montant){world->score = montant;}

sprite_t *getvaisseau(world_t *world){return &(world->vaisseau);}

sprite_t *getmissile(world_t *world){return &(world->missile);}

sprite_t *getenemies(world_t *world, unsigned int i){return &(world->enemies[i]);}

void setgameover(world_t *world, unsigned int valetat){world->gameover = valetat;}

int is_game_over(world_t *world){return world->gameover;}

void setnb_ennemis_sortis(world_t *world, unsigned int montant){world->nb_ennemis_sortis = montant;}

unsigned int getnb_ennemis_sortis(world_t *world){return world->nb_ennemis_sortis;}

void setpause(world_t *world, unsigned int etat){world->pause = etat;}

unsigned int getpause(world_t *world){return world->pause;}

void setetat(world_t * world, unsigned int valetat){world->etat = valetat;}

unsigned int getetat(world_t *world){return world->etat;}

void setframecount(world_t *world, unsigned int amount){world->frame_count = amount;}

unsigned int getframecount(world_t *world){return world->frame_count;}

sprite_t* getscreamer(world_t* world){return &(world->screamer);}


//Seter et geter de sprite_t
int getx(sprite_t *sprite){return sprite->x;}

int gety(sprite_t *sprite){return sprite->y;}

void setx(sprite_t *sprite, unsigned int valx){sprite->x = valx;}

void sety(sprite_t *sprite, unsigned int valy){sprite->y = valy;}

unsigned int getwidth(sprite_t *sprite){return sprite->w;}

unsigned int geth(sprite_t *sprite){return sprite->h;}

void setw(sprite_t *sprite, unsigned int valw){sprite->w = valw;}

void seth(sprite_t *sprite, unsigned int valh){sprite->h = valh;}

unsigned int getv(sprite_t *sprite){return sprite->v;}

void setv(sprite_t *sprite, unsigned int valv){sprite->v = valv;}

unsigned int gettype(sprite_t *sprite){return sprite->type;}

void settype(sprite_t *sprite, unsigned int valtype){sprite->type = valtype;}

unsigned int getlives(sprite_t *sprite){return sprite->lives;}

void setlives(sprite_t *sprite, unsigned int vallives){sprite->lives = vallives;}

unsigned int getvisibility(sprite_t *sprite){return sprite->is_visible;}

void set_visible(sprite_t *sprite){sprite->is_visible = 0;}

void set_invisible(sprite_t *sprite){sprite->is_visible = 1;}


/* Generation d'un nombre entier compris entre a et b */
int generate_number(int a, int b){
    return rand()%(b-a)+a;
}

void init_sprite(sprite_t* sprite, int x, int y, unsigned int w, unsigned int h, int v, unsigned int type, unsigned int lives){
    setx(sprite, x);
    sety(sprite, y);
    setw(sprite, w);
    seth(sprite, h);
    setv(sprite, v);
    //set_visible(sprite); // Sprite de base visible
    settype(sprite, type);
    setlives(sprite, lives);
}


void print_sprite(sprite_t *sprite){
    printf("Sprite : x,y = %d,%d | h,w = %d,%d\nv = %d\nis_visible = %s\n", getx(sprite), gety(sprite), geth(sprite), getwidth(sprite), getv(sprite), (!getvisibility(sprite)?"oui":"non"));
}


void vaisseau_depasse_bords(sprite_t *sprite){
    /*Bord gauche*/
    if(getx(sprite)<0){
        setx(sprite, 0);
    }

    /*Bord droit*/
    if(getx(sprite)>SCREEN_WIDTH-SHIP_SIZE){
        setx(sprite, SCREEN_WIDTH-SHIP_SIZE);
    }
}

void reset_enemi(world_t *world, unsigned int i){
    unsigned int num_type = proba_spawn();
    unsigned int lives;
    lives=ENEMY_LIFE;
    switch(num_type){
        case 4:{
            lives=TANK_LIFE;
            break;
        }
        case 5:{
            /*L'ambulaces a autant de vie que le joueur car chaque coup sur l'ambulance enleve un point de vie
            au vaisseau */
            lives=PLAYER_LIFE;
            break;
        }
        default:{
            break;
        }
    }
    
    init_sprite(getenemies(world, i), generate_number(0,SCREEN_WIDTH-SHIP_SIZE), -SHIP_SIZE-i*VERTICAL_DIST, SHIP_SIZE, SHIP_SIZE, ENEMY_SPEED, num_type, lives);
}


void ennemi_depasse_bas(world_t *world){
    for(int i=0; i<NB_ENEMIES; i++){
        if(gety(getenemies(world, i))>SCREEN_HEIGHT){
            setnb_ennemis_sortis(world, getnb_ennemis_sortis(world)+1);
            reset_enemi(world, i);
        }
    }
    setnb_ennemis_sortis(world, getnb_ennemis_sortis(world)%NB_ENEMIES); // Nb d'ennemis qui retourne à 0 quand tous les ennemis sont sortis
}

void missile_depasse_haut(world_t* world){
    if((gety(getmissile(world)))<0){
        take_dmg(getmissile(world));
    }
}


int sprites_collide(sprite_t *sp2, sprite_t *sp1){
    // Calcul de la distance entre les deux sprites
    double dist = sqrt(pow((getx(sp2) - getx(sp1)), 2) + pow((gety(sp2) - gety(sp1)), 2));
    return SHIP_SIZE>dist;
}

void score(world_t* world){
    for(int i=0; i<NB_ENEMIES; i++){
        if(sprites_collide(getmissile(world),getenemies(world, i)) && !getvisibility(getmissile(world)) && !getvisibility(getenemies(world, i)) && getlives(getenemies(world, i))==1){
            setscore(world, getscore(world)+1);
        }
    }
    if(getscore(world)==NB_ENEMIES){
        setscore(world, getscore(world)*2);
    }
}


unsigned int proba_spawn(){
    unsigned int num_type = generate_number(0, 99);
    if(num_type<19){return 3;}
    else if(num_type>=19 && num_type<39){return 4;}
    else if(num_type>=39 && num_type<49){return 5;}
    else if(num_type>=89 && num_type<100){return 6;}
    else{return 2;}
}


void handle_missiles_collide(world_t *world){
    for(int i=0; i<NB_ENEMIES; i++){
        if(sprites_collide(getmissile(world), getenemies(world, i)) && !getvisibility(getmissile(world)) && !getvisibility(getenemies(world, i))){
            setv(getmissile(world), 0);
            take_dmg(getmissile(world));
            switch(gettype(getenemies(world, i))){
                case AMBULANCE_TYPE:{  
                    take_dmg(getvaisseau(world));
                    break;
                }

                case GRENOUILLE_TYPE:{
                    break;
                }

                default:{
                    take_dmg(getenemies(world, i));
                    break;
                }
            }
        }
    }
}

void handle_vaisseau_collide(world_t* world){
    for(int i=0; i<NB_ENEMIES; i++){
        int type = gettype(getenemies(world, i));
        // Si le vaisseau et l'ambulance entrent en collision ET si le vaiseau et l'ambulance sont visibles
        if(sprites_collide(getvaisseau(world),getenemies(world, i)) && !getvisibility(getvaisseau(world)) && !getvisibility(getenemies(world, i))){
            switch(type){
                case AMBULANCE_TYPE:{
                    for(int j=0; j<3;j++){
                        take_dmg(getenemies(world, i));
                    }
                    if(getlives(getvaisseau(world))<3){
                        heal(getvaisseau(world), 1);  
                    }
                    break;
                }
                case TANK_TYPE:{
                    for(int j=0; j<3;j++){
                        take_dmg(getenemies(world, i));
                    }
                    take_dmg(getvaisseau(world));
                    break;
                }
                case GRENOUILLE_TYPE:{
                    for(int j=0; j<(getlives(getvaisseau(world)));j++){
                        take_dmg(getvaisseau(world));
                    }
                    heal(getscreamer(world),1);
                    break;
                }
                default: {
                    take_dmg(getenemies(world, i));
                    take_dmg(getvaisseau(world));
                    break;  
                }
            }
        }
    }
}


void heal(sprite_t *sprite, unsigned int montant){ setlives(sprite, getlives(sprite)+montant); }

void take_dmg(sprite_t* sprite){
    if(getlives(sprite)>=1){
        setlives(sprite, getlives(sprite)-1);
    }
}

void init_data(world_t * world){
    setgameover(world, 0);
    setetat(world, ENCOURS_ETAT);
    setnb_ennemis_sortis(world, 0);
    setscore(world, 0);
    setframecount(world, 0);
    setpause(world, 0);
    init_sprite(getscreamer(world),0,0,SCREEN_WIDTH,SCREEN_HEIGHT,0,SCREAMER_TYPE,0);

    //Initialisation du vaisseau
    init_sprite(getvaisseau(world), SCREEN_WIDTH/2 - SHIP_SIZE/2, SCREEN_HEIGHT - (int)(1.5*SHIP_SIZE), SHIP_SIZE, SHIP_SIZE, 0, VAISSEAU_TYPE,PLAYER_LIFE);

    //initialisation du tableau des ennemis
    init_enemies(world);

    //Initialisation du missile du vaisseau
    init_sprite(getmissile(world), SCREEN_WIDTH/2, gety(getvaisseau(world)), MISSILE_SIZE, MISSILE_SIZE, MISSILE_SPEED, MISSILE_TYPE,0);
    
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


void update_enemies(world_t *world){
    for(int i = 0; i<NB_ENEMIES; i++){
        sety(getenemies(world, i), gety(getenemies(world, i))+getv(getenemies(world, i)));

        if(gettype(getenemies(world,i)) == CASSE_TYPE){
            setx(getenemies(world, i),(SDL_sin(0.05*gety(getenemies(world, i)))*45+(SCREEN_WIDTH/2)));
        }
    }
}

void compute_game(world_t* world){
    /*Le joueur a perdu*/
    if(getlives(getvaisseau(world)) == 0){
        setetat(world, DEFAITE_ETAT);
        setframecount(world, getframecount(world)+1);
    }

    /*Temps de latence avant la fermeture du jeu*/
    if(getframecount(world)>=FRAME_CLOSURE){
        setgameover(world, COMPTE_ETAT);
    }

    /*Jeu de base en cours*/
    if(getetat(world) == ENCOURS_ETAT){
        /* Detection du depassement du bord bas par les ennemis */
        ennemi_depasse_bas(world);
    }
}

void compute_lives(sprite_t* sprite){
    if(getlives(sprite)>0){
        set_visible(sprite);
    }else{
        set_invisible(sprite);
    }
}

void compute_sprites(world_t* world){
    compute_lives(getvaisseau(world));
    compute_lives(getmissile(world));
    for(int i=0;i<NB_ENEMIES;i++){
        compute_lives(getenemies(world, i));
    }
    compute_lives(getscreamer(world));
}

void update_data(world_t *world){

    //Gestion des collisions entre le vaisseau et les ennemis
    handle_vaisseau_collide(world);

    //Test de collision entre le missile et les ennemis
    handle_missiles_collide(world);

    //LES ennemiS se delpacENT
    update_enemies(world);

    // Si le missile est visible alors il avance.
    if(!getvisibility(getmissile(world))){
        sety(getmissile(world), gety(getmissile(world)) - getv(getmissile(world)));
        missile_depasse_haut(world);
    }

    /* Le vaisseau reste sur l'ecran */
    vaisseau_depasse_bords(getvaisseau(world));

    /*Gestion de l'état du jeu*/
    compute_game(world);

    //Gestion de la visiblité des sprites
    compute_sprites(world);

    /*Gestion des collisions entre missile et ennemis*/
    score(world);

    
}


void avance_missile(world_t *world){
    set_visible(getmissile(world));

    /* On place le missile au milieu au dessus du sprite du vaisseau */
    setx(getmissile(world), getx(getvaisseau(world)) + SHIP_SIZE/2 - MISSILE_SIZE/2);
    sety(getmissile(world), gety(getvaisseau(world)));
    setv(getmissile(world), MISSILE_SPEED);
}


void handle_events(SDL_Event *event,world_t *world){
    Uint8 *keystates;
    while( SDL_PollEvent( event ) ) {
        
        //Si l'utilisateur a cliqué sur le X de la fenêtre
        if( event->type == SDL_QUIT ) {
            //On indique la fin du jeu
            setgameover(world, 1);
        }
       
         //si une touche est appuyée
         if(event->type == SDL_KEYDOWN){

             //Si le jeu n'est pas en pause
             if(!getpause(world)){

                //si la touche appuyée est fleche gauche
                if(event->key.keysym.sym == SDLK_LEFT){
                    setx(getvaisseau(world), getx(getvaisseau(world)) - MOVING_STEP);
                }

                //si la touche appuyée est fleche droite
                if(event->key.keysym.sym == SDLK_RIGHT){
                    setx(getvaisseau(world), getx(getvaisseau(world)) + MOVING_STEP);
                }

                //si la touche appuyée est espace et que le vaisseau est visible
                if(event->key.keysym.sym == SDLK_SPACE && getvisibility(getvaisseau(world))==0){
                    avance_missile(world);
                    setlives(getmissile(world), 1);
                }
            }
            //si la touche appuyée est echap
            if(event->key.keysym.sym == SDLK_ESCAPE){
                setpause(world, getpause(world)+1);  // On pase à l'etat de pause suivant 
                setpause(world, getpause(world)%2);  // 0 ou 1
            }
        }
    }
}
/**
 * \file graphismes.c
 * \brief Implementation des fonctions pour la gestion des graphiques
 * \author Fernandes dos Santos Emanuel et Lagarde Tristan
 * \date 31 mars 2022
 */

#include "sdl2-light.h"
#include "sdl2-ttf-light.h"
#include "graphismes.h"
#include <string.h>


void apply_sprite (SDL_Renderer *renderer, SDL_Texture *ressources, sprite_t *sprite){
    if(ressources != NULL && !getvisibility(sprite)){
      apply_texture(ressources, renderer, getx(sprite), gety(sprite));
    }
}


void apply_enemies(SDL_Renderer *renderer, SDL_Texture *texture_ennemi, SDL_Texture *texture_ennemi_casse, SDL_Texture* tank_texture, SDL_Texture* ambulance_texture, SDL_Texture* grenouille_texture, world_t *world){
    for(int i=0; i<NB_ENEMIES; i++){
        switch(gettype(getenemies(world, i))){
<<<<<<< HEAD
            case CASSE_TYPE: {
=======
            case 3: {
>>>>>>> be3da6556fd71f44d0b45faaa0160707acedafcc
                apply_sprite(renderer, texture_ennemi_casse, getenemies(world, i));
                break;
            }

<<<<<<< HEAD
            case TANK_TYPE: {
=======
            case 4: {
>>>>>>> be3da6556fd71f44d0b45faaa0160707acedafcc
                apply_sprite(renderer, tank_texture, getenemies(world, i));
                break;
            }

<<<<<<< HEAD
            case AMBULANCE_TYPE:{
                apply_sprite(renderer, ambulance_texture, getenemies(world, i));
                break;
            }
            case GRENOUILLE_TYPE:{
=======
            case 5:{
                apply_sprite(renderer, ambulance_texture, getenemies(world, i));
                break;
            }
            case 6:{
>>>>>>> be3da6556fd71f44d0b45faaa0160707acedafcc
                apply_sprite(renderer, grenouille_texture, getenemies(world, i));
                break;
            }
            default:{
                apply_sprite(renderer, texture_ennemi, getenemies(world, i));
                break;
            }
        }
    }
}


void clean_ressources(ressources_t *ressources){
    clean_texture(ressources->background);
    clean_texture(ressources->vaisseau_texture);
    clean_texture(ressources->missile_texture);
    clean_texture(ressources->ennemi_texture);
    clean_texture(ressources->ennemi_casse_texture);
    clean_texture(ressources->tank_texture);
    clean_texture(ressources->ambulance_texture);
    clean_texture(ressources->grenouille_texture);
<<<<<<< HEAD
    clean_texture(ressources->screamer_texture);
=======
>>>>>>> be3da6556fd71f44d0b45faaa0160707acedafcc
    clean_font(ressources->font);
}


void init_ressources(SDL_Renderer *renderer, ressources_t *ressources){
    ressources->background = load_image( "ressources/space-background_skin_1.bmp",renderer);
    ressources->vaisseau_texture = load_image("ressources/spaceship_skin_1.bmp", renderer);
    ressources->ennemi_texture = load_image("ressources/enemy_skin_1.bmp", renderer);
<<<<<<< HEAD
    ressources->ennemi_casse_texture = load_image("ressources/spaceinvader.bmp", renderer);
=======
    ressources->ennemi_casse_texture = load_image("ressources/ennemi_casse.bmp", renderer);
>>>>>>> be3da6556fd71f44d0b45faaa0160707acedafcc
    ressources->tank_texture = load_image("ressources/tank.bmp", renderer);
    ressources->missile_texture = load_image("ressources/missile_skin_2.bmp", renderer);
    ressources->ambulance_texture = load_image("ressources/ambulance.bmp", renderer);
    ressources->grenouille_texture = load_image("ressources/grenouille.bmp", renderer);
<<<<<<< HEAD
    ressources->screamer_texture = load_image("ressources/screamerhonte.bmp", renderer);
=======
>>>>>>> be3da6556fd71f44d0b45faaa0160707acedafcc
    ressources->font = load_font("ressources/arial.ttf", FONT_SIZE);
}


void apply_background(SDL_Renderer *renderer, ressources_t *ressources){
    if(ressources->background != NULL){
      apply_texture(ressources->background, renderer, 0, 0);
    }
}

void afficher_score(SDL_Renderer *renderer, world_t *world, ressources_t *ressources){
    char *score_str = malloc(sizeof(char)*3);     //Score (max 999)
    SDL_itoa(getscore(world), score_str, 10);      //Conversion du score en texte

    int taille_txt = strlen("Score : ");

    //Affichage
    apply_text(renderer, 20, 20, taille_txt*(FONT_SIZE), FONT_SIZE*2, "Score : ", ressources->font);
    apply_text(renderer, 20 + taille_txt*(FONT_SIZE), 20, (FONT_SIZE)*strlen(score_str), FONT_SIZE*2, score_str, ressources->font);

    free(score_str);
}

void afficher_vies(SDL_Renderer *renderer, world_t *world, ressources_t *ressources){
    char *lives_str = malloc(sizeof(char)*3);     //Vies
    SDL_itoa(getlives(getvaisseau(world)), lives_str, 10);      //Conversion des vies en texte

    int taille_txt = strlen("Vies : ");

    //Affichage
    apply_text(renderer, 20, 40, taille_txt*(FONT_SIZE), FONT_SIZE*2, "Vies : ", ressources->font);
    apply_text(renderer, 20 + taille_txt*(FONT_SIZE), 40, (FONT_SIZE)*strlen(lives_str), FONT_SIZE*2, lives_str, ressources->font);

    free(lives_str);
}


void afficher_etat_jeu(SDL_Renderer *renderer, world_t *world, ressources_t *ressources){
    int posy = SCREEN_HEIGHT/2 - (FONT_SIZE*6)/2;
    switch(getetat(world)){
<<<<<<< HEAD
        case DEFAITE_ETAT: {   //Defaite
=======
        case 0: {   //Defaite
>>>>>>> be3da6556fd71f44d0b45faaa0160707acedafcc
            int posx = SCREEN_WIDTH/2 - (FONT_SIZE*3*strlen("PERDU"))/2;
            apply_text(renderer, posx, posy, FONT_SIZE*3*strlen("PERDU"), FONT_SIZE*6, "PERDU", ressources->font);
        }

        default :
            afficher_score(renderer, world, ressources);
            afficher_vies(renderer, world, ressources);
    }
}


void refresh_graphics(SDL_Renderer *renderer, world_t *world, ressources_t *ressources){
    
    //on vide le renderer
    clear_renderer(renderer);
    
    //application des ressources dans le renderer
    apply_background(renderer, ressources);
    apply_sprite(renderer, ressources->vaisseau_texture, getvaisseau(world));
    apply_enemies(renderer, ressources->ennemi_texture, ressources->ennemi_casse_texture, ressources->tank_texture ,ressources->ambulance_texture, ressources->grenouille_texture, world);
    apply_sprite(renderer, ressources->missile_texture, getmissile(world));
<<<<<<< HEAD
    
=======
>>>>>>> be3da6556fd71f44d0b45faaa0160707acedafcc

    //Affichage de l'etat du jeu et du score
    afficher_etat_jeu(renderer, world, ressources);
    apply_sprite(renderer, ressources->screamer_texture, getscreamer(world));
    // on met à jour l'écran
    update_screen(renderer);
}

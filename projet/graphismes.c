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
    if(ressources != NULL && !(sprite->is_visible)){
      apply_texture(ressources, renderer, sprite->x, sprite->y);
    }
}


void apply_enemies(SDL_Renderer *renderer, SDL_Texture *texture_ennemi, SDL_Texture *texture_ennemi_casse, SDL_Texture* tank_texture , sprite_t *enemies){
    for(int i=0; i<NB_ENEMIES; i++){
        switch(enemies[i].type){
            case 3: {
                apply_sprite(renderer, texture_ennemi_casse, &enemies[i]);
                break;
            }

            case 4: {
                apply_sprite(renderer, tank_texture, &enemies[i]);
                break;
            }

            default:{
                apply_sprite(renderer, texture_ennemi, &enemies[i]);
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
    clean_font(ressources->font);
}


void init_ressources(SDL_Renderer *renderer, ressources_t *ressources){
    ressources->background = load_image( "ressources/space-background_skin_1.bmp",renderer);
    ressources->vaisseau_texture = load_image("ressources/spaceship_skin_1.bmp", renderer);
    ressources->ennemi_texture = load_image("ressources/enemy_skin_1.bmp", renderer);
    ressources->ennemi_casse_texture = load_image("ressources/ennemi_casse.bmp", renderer);
    ressources->tank_texture = load_image("ressources/tank.bmp", renderer);
    ressources->missile_texture = load_image("ressources/missile_skin_2.bmp", renderer);
    ressources->font = load_font("ressources/arial.ttf", FONT_SIZE);
}


void apply_background(SDL_Renderer *renderer, ressources_t *ressources){
    if(ressources->background != NULL){
      apply_texture(ressources->background, renderer, 0, 0);
    }
}

void afficher_score(SDL_Renderer *renderer, world_t *world, ressources_t *ressources){
    char *score_str = malloc(sizeof(char)*3);     //Score (max 999)
    SDL_itoa(world->score, score_str, 10);      //Conversion du score en texte

    int taille_txt = strlen("Score : ");

    //Affichage
    apply_text(renderer, 20, 20, taille_txt*(FONT_SIZE), FONT_SIZE*2, "Score : ", ressources->font);
    apply_text(renderer, 20 + taille_txt*(FONT_SIZE), 20, (FONT_SIZE)*strlen(score_str), FONT_SIZE*2, score_str, ressources->font);

    free(score_str);
}

void afficher_vies(SDL_Renderer *renderer, world_t *world, ressources_t *ressources){
    char *lives_str = malloc(sizeof(char)*3);     //Vies
    SDL_itoa(world->vaisseau.lives, lives_str, 10);      //Conversion des vies en texte

    int taille_txt = strlen("Vies : ");

    //Affichage
    apply_text(renderer, 20, 40, taille_txt*(FONT_SIZE), FONT_SIZE*2, "Vies : ", ressources->font);
    apply_text(renderer, 20 + taille_txt*(FONT_SIZE), 40, (FONT_SIZE)*strlen(lives_str), FONT_SIZE*2, lives_str, ressources->font);

    free(lives_str);
}


void afficher_etat_jeu(SDL_Renderer *renderer, world_t *world, ressources_t *ressources){
    int posy = SCREEN_HEIGHT/2 - (FONT_SIZE*6)/2;
    switch(world->etat){
        case 0: {   //Defaite
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
    apply_sprite(renderer, ressources->vaisseau_texture, &(world->vaisseau));
    apply_enemies(renderer, ressources->ennemi_texture, ressources->ennemi_casse_texture, ressources->tank_texture ,(world->enemies));
    apply_sprite(renderer, ressources->missile_texture, &(world->missile));

    //Affichage de l'etat du jeu et du score
    afficher_etat_jeu(renderer, world, ressources);

    // on met à jour l'écran
    update_screen(renderer);
}

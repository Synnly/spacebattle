/**
 * \file graphismes.c
 * \brief Implementation des fonctions pour la gestion des graphiques
 * \author Fernandes dos Santos Emanuel et Lagarde Tristan
 * \date 31 mars 2022
 */

#include "sdl2-light.h"
#include "sdl2-ttf-light.h"
#include "graphismes.h"


void apply_sprite (SDL_Renderer *renderer, SDL_Texture *ressources, sprite_t *sprite){
    if(ressources != NULL && !(sprite->is_visible)){
      apply_texture(ressources, renderer, sprite->x, sprite->y);
    }
}


void apply_enemies(SDL_Renderer *renderer, SDL_Texture *ressources, sprite_t *enemies){
    for(int i=0; i<NB_ENEMIES; i++){
        apply_sprite(renderer, ressources, &enemies[i]);
    }
}


void clean_textures(ressources_t *ressources){
    clean_texture(ressources->background);
    clean_texture(ressources->vaisseau_texture);
    clean_texture(ressources->missile_texture);
    clean_texture(ressources->ennemi_texture);
    clean_font(ressources->font);
}


void init_textures(SDL_Renderer *renderer, ressources_t *ressources){
    ressources->background = load_image( "ressources/space-background.bmp",renderer);
    ressources->vaisseau_texture = load_image("ressources/vaisseau.bmp", renderer);
    ressources->ennemi_texture = load_image("ressources/enemy.bmp", renderer);
    ressources->missile_texture = load_image("ressources/missile.bmp", renderer);
    ressources->font = load_font("arial.ttf", 14);
}


void apply_background(SDL_Renderer *renderer, ressources_t *ressources){
    if(ressources->background != NULL){
      apply_texture(ressources->background, renderer, 0, 0);
    }
}


void refresh_graphics(SDL_Renderer *renderer, world_t *world,ressources_t *ressources){
    
    //on vide le renderer
    clear_renderer(renderer);
    
    //application des ressources dans le renderer
    apply_background(renderer, ressources);
    apply_sprite(renderer, ressources->vaisseau_texture, &(world->vaisseau));
    /* apply_sprite(renderer, textures->ennemi_texture, &(world->ennemi)); */
    apply_enemies(renderer, ressources->ennemi_texture, (world->enemies));
    apply_sprite(renderer, ressources->missile_texture, &(world->missile));
    // Ne marche pas : demander comment cast un int en const char *
    /* const char *text = 
    apply_text(renderer, 20, 20, 50, 50, text, ressources->font); */

    // on met à jour l'écran
    update_screen(renderer);
}

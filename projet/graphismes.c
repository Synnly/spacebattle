/**
 * \file graphismes.c
 * \brief Implementation des fonctions pour la gestion des graphiques
 * \author Fernandes dos Santos Emanuel et Lagarde Tristan
 * \date 31 mars 2022
 */

#include "sdl2-light.h"
#include "graphismes.h"


void apply_sprite (SDL_Renderer *renderer, SDL_Texture *textures, sprite_t *sprite){
    if(textures != NULL && !(sprite->is_visible)){
      apply_texture(textures, renderer, sprite->x, sprite->y);
    }
}


void apply_enemies(SDL_Renderer *renderer, SDL_Texture *textures, sprite_t *enemies){
    for(int i=0; i<NB_ENEMIES; i++){
        apply_sprite(renderer, textures, &enemies[i]);
    }
}


void clean_textures(textures_t *textures){
    clean_texture(textures->background);
    clean_texture(textures->vaisseau_texture);
    clean_texture(textures->missile_texture);
    clean_texture(textures->ennemi_texture);
}


void init_textures(SDL_Renderer *renderer, textures_t *textures){
    textures->background = load_image( "ressources/space-background.bmp",renderer);
    textures->vaisseau_texture = load_image("ressources/spaceship.bmp", renderer);
    textures->ennemi_texture = load_image("ressources/enemy.bmp", renderer);
    textures->missile_texture = load_image("ressources/missile.bmp", renderer);
}


void apply_background(SDL_Renderer *renderer, textures_t *textures){
    if(textures->background != NULL){
      apply_texture(textures->background, renderer, 0, 0);
    }
}


void refresh_graphics(SDL_Renderer *renderer, world_t *world,textures_t *textures){
    
    //on vide le renderer
    clear_renderer(renderer);
    
    //application des textures dans le renderer
    apply_background(renderer, textures);
    apply_sprite(renderer, textures->vaisseau_texture, &(world->vaisseau));
    apply_sprite(renderer, textures->ennemi_texture, &(world->ennemi));
    apply_enemies(renderer, textures->ennemi_texture, (world->enemies));
    apply_sprite(renderer, textures->missile_texture, &(world->missile));

    // on met à jour l'écran
    update_screen(renderer);
}

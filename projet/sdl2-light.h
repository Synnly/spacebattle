#ifndef __SDL2_LIGHT__H__
#define __SDL2_LIGHT__H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>

void clean_sdl(SDL_Renderer *renderer,SDL_Window *window);
SDL_Texture *load_image(const char path[], SDL_Renderer *renderer);
int init_sdl(SDL_Window **window, SDL_Renderer **renderer, int width, int height);
void clean_texture(SDL_Texture *texture);
void apply_texture(SDL_Texture *texture,SDL_Renderer *renderer,int x, int y);
void clear_renderer(SDL_Renderer *renderer);
void update_screen(SDL_Renderer *renderer);
void pause(int time);

#endif

/*Modification à la con parceque git a décidé de me faire chier.*/
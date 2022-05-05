/**
 * \file audio.c
 * \brief Implementation des fonctions audio
 * \author Fernandes dos Santos Emanuel et Lagarde Tristan
 * \date 4 mai 2022
 */

#include "audio.h"


void init_audio(audio_t *audio){
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
    audio->bgm = Mix_LoadMUS("ressources/240 bits per mile.wav");
    Mix_PlayMusic(audio->bgm, -1);
}


void playpausemus(world_t *world){
    if(getpause(world)){
        Mix_PauseMusic();
    }
    else{
        Mix_ResumeMusic();
    } 
}


void clean_audio(Mix_Music *musique){
    Mix_FreeMusic(musique);
    Mix_CloseAudio();
    Mix_Quit();
}


void music_loop(world_t *world, audio_t *audio){
    if(is_game_over(world)){
        clean_audio(audio->bgm);
    }
    else{
        playpausemus(world);
    }
}
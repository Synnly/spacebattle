/**
 * \file audio.c
 * \brief Implementation des fonctions audio
 * \author Fernandes dos Santos Emanuel et Lagarde Tristan
 * \date 4 mai 2022
 */

#include "audio.h"


void init_audio(audio_t *audio){
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 256);
    audio->bgm = Mix_LoadMUS("ressources/audio/240 bits per mile.wav");
    Mix_VolumeMusic(32);
    Mix_PlayMusic(audio->bgm, -1);
}


void init_sfx(audio_t *audio){
    audio->sfx_boom = Mix_LoadWAV("ressources/audio/boom.wav");
    audio->sfx_hit = Mix_LoadWAV("ressources/audio/hit.wav");
    audio->sfx_shoot = Mix_LoadWAV("ressources/audio/shoot.wav");
    audio->sfx_pause = Mix_LoadWAV("ressources/audio/pause.wav");
    audio->sfx_heal = Mix_LoadWAV("ressources/audio/heal.wav");
    audio->sfx_flop = Mix_LoadWAV("ressources/audio/flop.wav");
    audio->sfx_thud = Mix_LoadWAV("ressources/audio/thud.wav");

    audio->boom_is_playing = 0;
    audio->hit_is_playing = 0;
    audio->shoot_is_playing = 0;
    audio->pause_is_playing = 0;
    audio->heal_is_playing = 0;
    audio->flop_is_playing = 0;
    audio->thud_is_playing = 0;

    Mix_VolumeChunk(audio->sfx_boom, 80);
    Mix_VolumeChunk(audio->sfx_hit, 40);
    Mix_VolumeChunk(audio->sfx_shoot, 64);
    Mix_VolumeChunk(audio->sfx_pause, 64);
    Mix_VolumeChunk(audio->sfx_heal, 64);
    Mix_VolumeChunk(audio->sfx_flop, 128);
    Mix_VolumeChunk(audio->sfx_thud, 128);
}

void play_boom(audio_t *audio, world_t *world){
    audio->hit_is_playing = 0;
    for(int i=0; i<NB_ENEMIES; i++){

        //Si le vaisseau ou le missile entre en collision avec un ennemi, l'ennemi ou le vaisseau est tue et le bruitage du coup n'as pas deja ete joue
        if(((getlives(getenemies(world, i))==1 && (missile_collide(world, i)) && gettype(getenemies(world, i))!=GRENOUILLE_TYPE) || (getlives(getvaisseau(world))==1 && vaisseau_collide(world, i))) && audio->hit_is_playing==0){
            audio->hit_is_playing = 1;

            if(Mix_PlayChannel(1, audio->sfx_boom, 0)==-1) {
                printf("Mix_PlayChannel: %s\n",Mix_GetError());
            }
        }
    }
}

void play_hit(audio_t *audio, world_t *world){
    audio->hit_is_playing = 0;
    for(int i=0; i<NB_ENEMIES; i++){

        //Si le vaisseau ou le missile entre en collision avec un ennemi qui n'est pas une ambulance ni une grenouille, l'ennemi ou le vaisseau n'est pas tue et le bruitage du coup n'as pas deja ete joue
        if((getlives(getenemies(world, i))>1 && (missile_collide(world, i)) && gettype(getenemies(world, i))!=GRENOUILLE_TYPE) || (getlives(getvaisseau(world))>1 && vaisseau_collide(world, i) && gettype(getenemies(world, i))!=AMBULANCE_TYPE) && audio->hit_is_playing==0){
            audio->hit_is_playing = 1;

            if(Mix_PlayChannel(2, audio->sfx_hit, 0)==-1) {
                printf("Mix_PlayChannel: %s\n",Mix_GetError());
            }
        }
    }
}

void play_shoot(audio_t *audio, world_t *world){
    if(getlives(getmissile(world))==0){
        audio->shoot_is_playing = 0;
    }

    if((getlives(getmissile(world))==1 && audio->shoot_is_playing==0)){
        audio->shoot_is_playing = 1;
        if(Mix_PlayChannel(3, audio->sfx_shoot, 0)==-1) {
            printf("Mix_PlayChannel: %s\n",Mix_GetError());
        }
    }
}

void play_heal(audio_t *audio, world_t *world){
    audio->heal_is_playing ==0;
    for(int i=0; i<NB_ENEMIES; i++){
        if(vaisseau_collide(world, i) && gettype(getenemies(world, i))==AMBULANCE_TYPE && audio->heal_is_playing==0 && getlives(getvaisseau(world))<PLAYER_LIFE){
            audio->heal_is_playing ==1;
            if(Mix_PlayChannel(5, audio->sfx_heal, 0)==-1) {
                printf("Mix_PlayChannel: %s\n",Mix_GetError());
            }
        }
    }
}

void play_flop(audio_t *audio, world_t *world){
    audio->flop_is_playing = 0;
    for(int i=0; i<NB_ENEMIES; i++){

        if(missile_collide(world, i) && gettype(getenemies(world, i))==GRENOUILLE_TYPE && audio->flop_is_playing==0){
            audio->flop_is_playing = 1;

            if(Mix_PlayChannel(6, audio->sfx_flop, 0)==-1) {
                printf("Mix_PlayChannel: %s\n",Mix_GetError());
            }
        }
    }
}

void play_thud(audio_t *audio, world_t *world){
    audio->thud_is_playing = 0;
    for(int i=0; i<NB_ENEMIES; i++){

        if(vaisseau_collide(world, i) && gettype(getenemies(world, i))==GRENOUILLE_TYPE && audio->thud_is_playing==0){
            audio->thud_is_playing = 1;

            if(Mix_PlayChannel(7, audio->sfx_thud, 0)==-1) {
                printf("Mix_PlayChannel: %s\n",Mix_GetError());
            }
        }
    }
}

void playpausemus(audio_t *audio, world_t *world){
    if(getpause(world)){

        //Mettre en pause tous les canaux sauf celle de la pause
        for(int i=0; i<8; i++){
            if(i!=4){Mix_Pause(i);}
        }
        Mix_PauseMusic();
        if(audio->pause_is_playing==0){
            audio->pause_is_playing=1;
            if(Mix_PlayChannel(4, audio->sfx_pause, 0)==-1) {
                printf("Mix_PlayChannel: %s\n",Mix_GetError());
            }
        }
    }
    else{
        audio->pause_is_playing=0;
        Mix_Resume(-1);
        Mix_ResumeMusic();
    } 
}

void stop_audio(audio_t * audio){
    Mix_HaltMusic();
    for(int i = 0; i<8; i++){
        Mix_HaltChannel(i);
    }
}

void clean_audio(audio_t *audio){
    
    stop_audio(audio);
    Mix_FreeMusic(audio->bgm);

    Mix_FreeChunk(audio->sfx_boom);
    Mix_FreeChunk(audio->sfx_hit);
    Mix_FreeChunk(audio->sfx_shoot);
    Mix_FreeChunk(audio->sfx_pause);
    Mix_FreeChunk(audio->sfx_heal);
    Mix_FreeChunk(audio->sfx_flop);
    Mix_FreeChunk(audio->sfx_thud);
    Mix_CloseAudio();
}


void music_loop(world_t *world, audio_t *audio){
    playpausemus(audio, world);
    play_boom(audio, world);
    play_shoot(audio, world);
    play_hit(audio, world);
    play_heal(audio, world);
    play_flop(audio, world);
    play_thud(audio, world);
}
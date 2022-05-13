#ifndef AUDIO_H
#define AUDIO_H

/**
 * \file audio.h
 * \brief En-tete des fonctions audio
 * \author Fernandes dos Santos Emanuel et Lagarde Tristan
 * \date 4 mai 2022
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "donnes.h"

/**
 * \brief Représentation des donnes audio
 */
struct audio_s {
    Mix_Music *bgm;             /*!< Champ lié à la musique de fond */
    Mix_Chunk *sfx_boom;             /*!< Champ lié au bruitage de l'explosion */
    Mix_Chunk *sfx_hit;             /*!< Champ lié au bruitage du coup */
    Mix_Chunk *sfx_shoot;             /*!< Champ lié au bruitage du tir */
    Mix_Chunk *sfx_pause;             /*!< Champ lié au bruitage de la pause */
    Mix_Chunk *sfx_heal;             /*!< Champ lié au bruitage du soin */
    Mix_Chunk *sfx_flop;             /*!< Champ lié au bruitage du flop */
    unsigned int boom_is_playing;   /*!< Champ lié à l'etat de lecture du bruitage de l'explosion */
    unsigned int hit_is_playing;    /*!< Champ lié à l'etat de lecture du bruitage du coup */
    unsigned int shoot_is_playing;  /*!< Champ lié à l'etat de lecture du bruitage du tir */
    unsigned int pause_is_playing;   /*!< Champ lié à l'etat de lecture du bruitage de l'explosion */
    unsigned int heal_is_playing;    /*!< Champ lié à l'etat de lecture du bruitage du coup */
    unsigned int flop_is_playing;    /*!< Champ lié à l'etat de lecture du bruitage du flop*/
};


/**
 * \brief Type qui correspond à l'audio
 */
typedef struct audio_s audio_t;

/**
 * \brief Initialise la musique
 * \param audio Les donnes audio
 */
void init_audio(audio_t *audio);

/**
 * \brief Initialise les bruitages 
 * \param audio Les donnes audio
 */
void init_sfx(audio_t *audio);

/**
 * \brief Pause/reprend une musique en fonction de l'etat du jeu
 * \param audio Les donnes audio
 * \param world Les donnes du jeu
 */
void playpausemus(audio_t *audio, world_t *world);

/**
 * \brief Joue le bruitage de l'explosion
 * \param audio Les donnes audio
 * \param world Les donnes du monde
 */
void play_boom(audio_t *audio, world_t *world);

/**
 * \brief Joue le bruitage du coup
 * \param audio Les donnes audio
 * \param world Les donnes du monde
 */
void play_hit(audio_t *audio, world_t *world);

/**
 * \brief Joue le bruitage du tir
 * \param audio Les donnes audio
 * \param world Les donnes du monde
 */
void play_shoot(audio_t *audio, world_t *world);

/**
 * \brief Joue le bruitage du soin
 * \param audio Les donnes audio
 * \param world Les donnes du monde
 */
void play_heal(audio_t *audio, world_t *world);

/**
 * \brief Joue le bruitage du soin
 * \param audio Les donnes audio
 * \param world Les donnes du monde
 */
void play_flop(audio_t *audio, world_t *world);

/**
 * \brief Gere la lecture et la fermeture de la musique
 * \param world Les donnes du monde
 * \param audio Les donnes audio
 */
void music_loop(world_t *world, audio_t *audio);

/**
 * \brief Arrete la musique et ferme le module audio
 * \param musique La musique
 */
void clean_audio(audio_t *audio);

#endif
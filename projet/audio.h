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
    unsigned int music_play;    /*!< Champ lié à l'état de la lecture de la musique de fond */
    Mix_Chunk *sfx;             /*!< Champ lié à un bruitage */
    unsigned int sfx_play;      /*!< Champ lié à l'etat de lecture du bruitage */
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
 * \brief Pause/reprend une musique en fonction de l'etat du jeu
 * \param world Les donnes du jeu
 */
void playpausemus(world_t *world);

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
void clean_audio(Mix_Music *musique);

#endif
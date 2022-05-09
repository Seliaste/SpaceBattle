/**
 * @file graphics.h
 * @author Aéna ARIA (aena.aria2@etu.univ-lorraine.fr)
 * @brief Module graphique du projet
 * @version 1
 * @date 2022-03-31
 */

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "const.h"
#include "../sdl2-light.h"
#include "game_logic.h"
#include "sdl2-ttf-light.h"
#include <SDL2/SDL_mixer.h>

struct resources_s
{
    SDL_Texture *background; /*!< Texture liée à l'image du fond de l'écran. */
    SDL_Texture *enemy;     /*!< Texture liée à l'image des ennemis. */
    SDL_Texture *ship;      /*!< Texture liée à l'image du vaisseau. */
    SDL_Texture *missile;   /*!< Texture liée à l'image du missile. */
    SDL_Texture *heart;     /*!< Texture liée à l'image des vies. */
    TTF_Font *font;         /*!< La police d'écriture. */
    Mix_Chunk *music;       /*!< Musique de fond du mode normal. */
    Mix_Chunk *hardmusic;   /*!< Musique de fond du mode difficile. */
    Mix_Chunk *explosion_sfx;    /*!< Son lors de la destruction d'un ennemi/ du vaisseau. */
    Mix_Chunk *damage_sfx;         /*!< Son lorsque l'on prend des dégâts */
    SDL_Texture *explosion[EXPLOSION_FRAMES];   /*!< Textures des frames d'une explosion */
};

/**
 * \brief Type qui correspond aux ressources du jeu
 */

typedef struct resources_s resources_t;

/**
 * \brief La fonction nettoie les ressources
 * \param resources les ressources
 */
void clean_resources(resources_t *resources);

/**
 * \brief La fonction initialise les texures
 * \param screen la surface correspondant à l'écran de jeu
 * \param resources les ressources du jeu
 * \param hardmode mode difficile ? (1:oui , 0:non)
 */
void init_resources(SDL_Renderer *renderer, resources_t *resources, bool hardmode);

/**
 * \brief La fonction applique la texture du fond sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param resources les ressources du jeu
 */
void apply_background(SDL_Renderer *renderer, resources_t *resources);

/**
 * @brief La fonction applique la texture d'ennemi a tous les sprites ennemis
 *
 * @param renderer
 * @param world
 * @param resources
 */
void apply_enemies(SDL_Renderer *renderer, world_t *world, resources_t *resources);
/**
 * @brief applique une texture sur un sprite
 * 
 * @param renderer 
 * @param texture 
 * @param sprite 
 */
void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite);

/**
 * @brief affiche une frame de la texture d'explosion
 * 
 * @param renderer 
 * @param resources 
 * @param sprite 
 * @param frame 
 */
void apply_explosion(SDL_Renderer *renderer, resources_t *resources, sprite_t *sprite, int frame);
/**
 * @brief affiche le texte avec le score
 * 
 * @param renderer 
 * @param font 
 * @param score 
 */
void apply_score_text(SDL_Renderer *renderer, TTF_Font *font, int score)
/**
 * @brief affiche l'un des messages de fin
 * 
 * @param renderer 
 * @param font 
 * @param world 
 */
void apply_endgame_text(SDL_Renderer *renderer, TTF_Font *font, world_t *world)
/**
 * @brief affiche les vies disponibles
 * 
 * @param renderer 
 * @param heart 
 * @param world 
 * @param damage_sfx 
 */
void apply_lifebar(SDL_Renderer *renderer, SDL_Texture *heart, world_t *world, Mix_Chunk *damage_sfx)
/**
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param renderer la surface de l'écran de jeu
 * \param world les données du monde
 * \param resources les ressources
 */
void refresh_graphics(SDL_Renderer *renderer, world_t *world, resources_t *resources);

#endif
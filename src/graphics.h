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
    SDL_Texture *enemy;
    SDL_Texture *ship;
    SDL_Texture *missile;
    SDL_Texture *heart;
    TTF_Font *font;
    Mix_Chunk *music;
    Mix_Chunk *hardmusic;
    Mix_Chunk *explosion_sfx;
    Mix_Chunk *damage_sfx;
    SDL_Texture *explosion[EXPLOSION_FRAMES];
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
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param renderer la surface de l'écran de jeu
 * \param world les données du monde
 * \param resources les ressources
 */
void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite);

void refresh_graphics(SDL_Renderer *renderer, world_t *world, resources_t *resources);

#endif
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

struct textures_s
{
    SDL_Texture *background; /*!< Texture liée à l'image du fond de l'écran. */
    SDL_Texture *enemy;
    SDL_Texture *ship;
    SDL_Texture *missile;
    TTF_Font *unautretruc;
};

/**
 * \brief Type qui correspond aux textures du jeu
 */

typedef struct textures_s textures_t;

/**
 * \brief La fonction nettoie les textures
 * \param textures les textures
 */
void clean_textures(textures_t *textures);

/**
 * \brief La fonction initialise les texures
 * \param screen la surface correspondant à l'écran de jeu
 * \param textures les textures du jeu
 */
void init_textures(SDL_Renderer *renderer, textures_t *textures);

/**
 * \brief La fonction applique la texture du fond sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param textures les textures du jeu
 */
void apply_background(SDL_Renderer *renderer, textures_t *textures);

/**
 * @brief La fonction applique la texture d'ennemi a tous les sprites ennemis
 *
 * @param renderer
 * @param world
 * @param textures
 */
void apply_enemies(SDL_Renderer *renderer, world_t *world, textures_t *textures);
/**
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param renderer la surface de l'écran de jeu
 * \param world les données du monde
 * \param textures les textures
 */
void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite);

void refresh_graphics(SDL_Renderer *renderer, world_t *world, textures_t *textures);

#endif
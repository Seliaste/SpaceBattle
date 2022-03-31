/**
 * @file game_logic.h
 * @author Thomas WIECZOREK
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "const.h"
#include <stdio.h>

/**
 * @brief Struct qui représente un sprite
 */
struct sprite_s
{
    int pos_x;
    int pos_y;
    int height;
    int width;
    int speed_v;    // vitesse verticale
    int is_visible; // définit la visibilité du sprite
};

typedef struct sprite_s sprite_t;

/**
 * \brief Représentation du monde du jeu
 */
struct world_s
{
    sprite_t ship;
    sprite_t enemy;
    sprite_t missile;
    int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */
};

/**
 * \brief Type qui correspond aux données du monde
 */
typedef struct world_s world_t;

/**
 * @brief rend un sprite visible
 *
 * @param sprite
 */
void set_visible(sprite_t *sprite);

/**
 * @brief rend un sprite invisible
 *
 * @param sprite
 */
void set_invisible(sprite_t *sprite);

/**
 * @brief initialise un sprite
 *
 * @param sprite le sprite
 * @param x position horizontale
 * @param y position verticale
 * @param w largeur
 * @param h hauteur
 * @param v vitesse verticale
 */
void init_sprite(sprite_t *sprite, int x, int y, int w, int h, int v, int visible);

/**
 * @brief affiche les informations du sprite
 *
 * @param sprite
 */
void print_sprite(sprite_t *sprite);

/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */
void init_data(world_t *world);

/**
 * \brief La fonction nettoie les données du monde
 * \param world les données du monde
 */
void clean_data(world_t *world);

/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */
int is_game_over(world_t *world);

/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param world les données du monde
 */
void update_data(world_t *world);

void ship_limit(world_t *world);

#endif
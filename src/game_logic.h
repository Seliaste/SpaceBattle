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
#include <math.h>
#include <time.h>
#include <stdlib.h>

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
    sprite_t enemies[NB_ENEMIES];
    sprite_t ship;
    sprite_t enemy;
    sprite_t missile;
    int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */
    int enemies_passed;
};

/**
 * \brief Type qui correspond aux données du monde
 */
typedef struct world_s world_t;

int generate_number(int a, int b);

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
 * @brief Cache le sprite, et réinitialise ses valeurs
 * 
 * @param sprite 
 */
void despawn_sprite(sprite_t *sprite);

void respawn_sprite(sprite_t *sprite, int x, int y);

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

void init_enemies(world_t *world);

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


/**
 * @brief La fonction met a jour la position des ennemis
 * 
 * @param world 
 */
void update_enemies(world_t* world);

void update_data(world_t *world);
/**
 * @brief replace l'ennemi au sommet de l'écran s'il dépasse
 * 
 * @param world 
 */
void enemy_limit(world_t* world);

/**
 * @brief replace le vaisseau s'il dépasse la limite
 * 
 * @param world 
 */
void ship_limit(world_t *world);

/**
 * @brief Vérifie si sp1 est en collision avec sp2 selon un radius type cercle
 * 
 * @param sp1 sprite numéro 1
 * @param sp2 sprite numéro 2
 * @return 1 si collision, sinon 0
 */
int sprite_collide(sprite_t *sp1, sprite_t *sp2);

/**
 * @brief prend en charge les collisions
 * 
 * @param sp1 premier sprite
 * @param sp2 second sprite
 */
void handle_sprites_collision(sprite_t *sp1, sprite_t *sp2);



#endif
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
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

/**
 * @brief Struct qui représente un sprite
 */
struct sprite_s
{
    int pos_x;      // position horizontale
    int pos_y;      // position verticale
    int height;     // hauteur du sprite en pixels
    int width;      // largeur du sprite en pixels
    int speed_v;    // vitesse verticale
    int speed_h;    // vitesse horizontale
    bool is_visible; // définit la visibilité du sprite
    bool play_explosion; // doit jouer un bruit d'explosion prochaine loop
};

typedef struct sprite_s sprite_t;

enum states
{
    playing,    // jeu en cours
    destroyed,  // détruit
    won,        // abattu tous les ennemis
    survived    // pas abattu tous les enemis
};

/**
 * \brief Représentation du monde du jeu
 */
struct world_s
{
    sprite_t enemies[NB_ENEMIES];   // tableau représentant les ennemis
    sprite_t ship;                  // vaisseau du joueur
    // sprite_t enemy;
    sprite_t missile;               // missile du joueur
    sprite_t explosion;
    int current_explosion_frame;
    int gameover;  /*!< Champ indiquant si l'on est à la fin du jeu */
    enum states gamestate; // état du jeu
    int score;      // score du joueur (= nombre de vaisseaux détruits)
    int enemies_passed; // ennemis non détruits qui sont sortis de l'écran
    int enemies_destroyed;  // ennemis détruits par le joueur
    int exit_time;          // temps avant sortie du programme
    int lives;             //  vies du vaisseau
    bool play_damage_sfx;
    bool hardmode; //mode difficile (multiplie par HARDMODE_MULTIPLIER la vitesse des ennemis)
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
void init_sprite(sprite_t *sprite, int x, int y, int w, int h, int vv,int vh, int visible);

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
 * @brief Fonction qui initialise les données des ennemis
 * 
 * @param world 
 */
void init_enemies(world_t *world);

/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */
int is_game_over(world_t *world);

/**
 * @brief Attache le flag de son d'explosion à jouer à l'ennemi i
 * 
 * @param world 
 * @param i 
 */
void play_explosion(world_t *world, int i);

/**
 * @brief Met à jour les données et la position d'un seul ennemi
 * 
 * @param world 
 * @param i index de l'ennemi dans le tableau
 */
void update_single_enemy(world_t *world, int i);

/**
 * @brief La fonction met a jour la position des ennemis
 *
 * @param world
 */
void update_enemies(world_t *world);

/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param world les données du monde
 */
void update_data(world_t *world);

/**
 * @brief Fonction qui applique la vélocité du vaisseau
 * 
 * @param world 
 */
void move_ship(world_t *world);

/**
 * @brief Fonction qui fait despawn le missile lorsqu'il sort de l'écran
 * 
 * @param world 
 */
void missile_limit(world_t *world);

/**
 * @brief replace l'ennemi au sommet de l'écran s'il dépasse
 *
 * @param world
 */
// void enemy_limit(world_t *world);

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
 *
 * @return 0 si il n'y a pas de collision, 1 sinon
 */
int handle_sprites_collision(sprite_t *sp1, sprite_t *sp2);

/**
 * @brief calcule le score à partir des données du monde
 *
 * @param world données du monde
 */
void compute_game(world_t *world);

#endif

#include "game_logic.h"
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
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */
/**
 * @brief Struct qui représente un sprite
 *
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
 * @brief rend un sprite visible
 *
 * @param sprite
 */
void set_visible(sprite_t *sprite)
{
    sprite->is_visible = 1;
}

/**
 * @brief rend un sprite invisible
 *
 * @param sprite
 */
void set_invisible(sprite_t *sprite)
{
    sprite->is_visible = 0;
}

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
void init_sprite(sprite_t *sprite, int x, int y, int w, int h, int v, int visible)
{
    sprite->pos_x = x;
    sprite->pos_y = y;
    sprite->width = w;
    sprite->height = h;
    sprite->speed_v = v;
    sprite->is_visible = visible;
}

/**
 * @brief affiche les informations du sprite
 *
 * @param sprite
 */
void print_sprite(sprite_t *sprite)
{
    printf("Position : %dx %dy, taille: %dh, %dw, vitesse: %d\n", sprite->pos_x, sprite->pos_y, sprite->height, sprite->width, sprite->speed_v);
}

/**
 * \brief Représentation du monde du jeu
 */


void init_data(world_t *world)
{

    // on n'est pas à la fin du jeu
    world->gameover = 0;
    // initialise un ennemi en haut de l'écran
    init_sprite(&(world->enemy), SCREEN_WIDTH / 2, SHIP_SIZE, SHIP_SIZE, SHIP_SIZE, ENEMY_SPEED, 1);
    // initialise un vaisseau en bas de l'ecran
    init_sprite(&(world->ship), SCREEN_WIDTH / 2, SCREEN_HEIGHT - SHIP_SIZE * 2, SHIP_SIZE, SHIP_SIZE, 0, 1);
    // initialise un missile positionné sur le vaisseau
    init_sprite(&(world->missile), SCREEN_WIDTH / 2, SCREEN_HEIGHT - SHIP_SIZE * 2, MISSILE_SIZE, MISSILE_SIZE, MISSILE_SPEED, 0);
}

/**
 * \brief La fonction nettoie les données du monde
 * \param world les données du monde
 */

void clean_data(world_t *world)
{
    /* utile uniquement si vous avez fait de l'allocation dynamique (malloc); la fonction ici doit permettre de libérer la mémoire (free) */
}

/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */

int is_game_over(world_t *world)
{
    return world->gameover;
}

/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param les données du monde
 */

void update_data(world_t *world)
{
    world->enemy.pos_y += world->enemy.speed_v;
    world->missile.pos_y -= world->missile.speed_v;
}

/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */

void handle_events(SDL_Event *event, world_t *world)
{
    Uint8 *keystates;
    while (SDL_PollEvent(event))
    {

        // Si l'utilisateur a cliqué sur le X de la fenêtre
        if (event->type == SDL_QUIT)
        {
            // On indique la fin du jeu
            world->gameover = 1;
        }

        // si une touche est appuyée
        if (event->type == SDL_KEYDOWN)
        {
            if (event->key.keysym.sym == SDLK_ESCAPE)
            {
                world->gameover = 1;
            }
            if (event->key.keysym.sym == SDLK_LEFT)
            {
                world->ship.pos_x -= 10;
            }
            if (event->key.keysym.sym == SDLK_RIGHT)
            {
                world->ship.pos_x += 10;
            }
            if (event->key.keysym.sym == SDLK_SPACE)
            {
                set_visible(&world->missile);
                world->missile.pos_x = world->ship.pos_x; // reset la position du missile sur le vaisseau
                world->missile.pos_y = world->ship.pos_y;
            }
        }
    }
}

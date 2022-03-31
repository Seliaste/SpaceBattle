/**
 * \file main.c
 * \brief Programme principal initial du niveau 1
 * \author Mathieu Constant
 * \version 1.0
 * \date 18 mars 2020
 */

#include "sdl2-light.h"
#include "src/graphics.h"
#include "src/game_logic.h"

/**
 * \brief Largeur de l'écran de jeu
 */
#define SCREEN_WIDTH 300

/**
 * \brief Hauteur de l'écran de jeu
 */
#define SCREEN_HEIGHT 480

/**
 * \brief Taille d'un vaisseau
 */

#define SHIP_SIZE 32

/**
 * \brief Taille du missile
 */

#define MISSILE_SIZE 8
/**
 * @brief définit la vitesse d'un missile
 *
 */
#define MISSILE_SPEED 10
/**
 * @brief définit la vitesse d'un ennemi
 *
 */
#define ENEMY_SPEED 2

/**
 * \brief Représentation pour stocker les textures nécessaires à l'affichage graphique
 */
struct textures_s
{
    SDL_Texture *background; /*!< Texture liée à l'image du fond de l'écran. */
    SDL_Texture *enemy;
    SDL_Texture *ship;
    SDL_Texture *missile;
};

/**
 * \brief Type qui correspond aux textures du jeu
 */

typedef struct textures_s textures_t;

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

/**
 * \brief La fonction nettoie les textures
 * \param textures les textures
 */
void clean_textures(textures_t *textures)
{
    clean_texture(textures->background);
    clean_texture(textures->ship);
    clean_texture(textures->enemy);
    clean_texture(textures->missile);
}

/**
 * \brief La fonction initialise les texures
 * \param screen la surface correspondant à l'écran de jeu
 * \param textures les textures du jeu
 */
void init_textures(SDL_Renderer *renderer, textures_t *textures)
{
    textures->background = load_image("ressources/space-background.bmp", renderer);
    textures->ship = load_image("ressources/spaceship.bmp", renderer);
    textures->enemy = load_image("ressources/enemy.bmp", renderer);
    textures->missile = load_image("ressources/missile.bmp", renderer);
}

/**
 * \brief La fonction applique la texture du fond sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param textures les textures du jeu
 */
void apply_background(SDL_Renderer *renderer, textures_t *textures)
{
    if (textures->background != NULL)
    {
        apply_texture(textures->background, renderer, 0, 0);
    }
}

/**
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param renderer la surface de l'écran de jeu
 * \param world les données du monde
 * \param textures les textures
 */
void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite)
{
    if (texture != NULL && sprite->is_visible)
    {
        apply_texture(texture, renderer, sprite->pos_x - sprite->width / 2, sprite->pos_y - sprite->height / 2);
    }
}

void refresh_graphics(SDL_Renderer *renderer, world_t *world, textures_t *textures)
{

    // on vide le renderer
    clear_renderer(renderer);

    // application des textures dans le renderer
    apply_background(renderer, textures);

    // application de la texture du vaisseau
    apply_sprite(renderer, textures->ship, &world->ship);

    apply_sprite(renderer, textures->enemy, &world->enemy);

    apply_sprite(renderer, textures->missile, &world->missile);
    // on met à jour l'écran
    update_screen(renderer);
}

/**
 * \brief fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des textures, nettoyage des données
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param textures les textures
 * \param world le monde
 */

void clean(SDL_Window *window, SDL_Renderer *renderer, textures_t *textures, world_t *world)
{
    clean_data(world);
    clean_textures(textures);
    clean_sdl(renderer, window);
}

/**
 * \brief fonction qui initialise le jeu: initialisation de la partie graphique (SDL), chargement des textures, initialisation des données
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param textures les textures
 * \param wordl le monde
 */

void init(SDL_Window **window, SDL_Renderer **renderer, textures_t *textures, world_t *world)
{
    init_sdl(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    init_data(world);
    init_textures(*renderer, textures);
}

/**
 *  \brief programme principal qui implémente la boucle du jeu
 */

int main(int argc, char *args[])
{
    SDL_Event event;
    world_t world;
    textures_t textures;
    SDL_Renderer *renderer;
    SDL_Window *window;

    // initialisation du jeu
    init(&window, &renderer, &textures, &world);

    while (!is_game_over(&world))
    { // tant que le jeu n'est pas fini

        // gestion des évènements
        handle_events(&event, &world);

        // mise à jour des données liée à la physique du monde
        update_data(&world);

        // rafraichissement de l'écran
        refresh_graphics(renderer, &world, &textures);

        // pause de 10 ms pour controler la vitesse de rafraichissement
        pause(10);
    }

    // nettoyage final
    clean(window, renderer, &textures, &world);

    return 0;
}
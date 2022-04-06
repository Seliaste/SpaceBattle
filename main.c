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
                world->ship.pos_x -= MOVING_STEP;
            }
            if (event->key.keysym.sym == SDLK_RIGHT)
            {
                world->ship.pos_x += MOVING_STEP;
            }
            if (event->key.keysym.sym == SDLK_SPACE && world->ship.is_visible)
            {
                set_visible(&world->missile);
                world->missile.pos_x = world->ship.pos_x; // reset la position du missile sur le vaisseau
                world->missile.pos_y = world->ship.pos_y;
            }
        }
    }
}

int main(int argc, char *args[])
{
    SDL_Event event;
    world_t world;
    textures_t textures;
    SDL_Renderer *renderer;
    SDL_Window *window;
    srand(time(NULL));
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

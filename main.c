/**
 * \file main.c
 * \brief Programme principal initial du niveau 1
 * \author Mathieu Constant
 * \version 1.0
 * \date 18 mars 2020
 */

#include "src/graphics.h"
#include "src/game_logic.h"
#include <SDL2/SDL_mixer.h>

/**
 * \brief fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des resources, nettoyage des données
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param resources les resources
 * \param world le monde
 */

void clean(SDL_Window *window, SDL_Renderer *renderer, resources_t *resources, world_t *world)
{
    clean_data(world);
    clean_resources(resources);
    clean_sdl(renderer, window);
    SDL_CloseAudio();
}

void init_audio(resources_t *resources)
{
    // Set up the audio stream
    int result = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 512);
    if (result < 0)
    {
        fprintf(stderr, "Unable to open audio: %s\n", Mix_GetError());
        exit(-1);
    }
    result = Mix_AllocateChannels(4);
    if (result < 0)
    {
        fprintf(stderr, "Unable to allocate mixing channels: %s\n", Mix_GetError());
        exit(-1);
    }
}

/**
 * \brief fonction qui initialise le jeu: initialisation de la partie graphique (SDL), chargement des resources, initialisation des données
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param resources les resources
 * \param wordl le monde
 */
void init(SDL_Window **window, SDL_Renderer **renderer, resources_t *resources, world_t *world)
{
    init_sdl(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    init_data(world);
    init_ttf();
    init_audio(resources);
    init_resources(*renderer, resources, world->hardmode);
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
                world->ship.speed_h = -MOVING_STEP;
            }
            if (event->key.keysym.sym == SDLK_RIGHT)
            {
                world->ship.speed_h = MOVING_STEP;
            }
            if (event->key.keysym.sym == SDLK_SPACE && world->ship.is_visible && !world->missile.is_visible)
            {
                set_visible(&world->missile);
                world->missile.pos_x = world->ship.pos_x; // reset la position du missile sur le vaisseau
                world->missile.pos_y = world->ship.pos_y;
            }
        }
        if (event->type == SDL_KEYUP)
        {
            if (event->key.keysym.sym == SDLK_LEFT || event->key.keysym.sym == SDLK_RIGHT)
            {
                world->ship.speed_h = 0;
            }
        }
    }
}

void play_music(resources_t *resources)
{
    int result = Mix_PlayChannel(-1, resources->music, 1);
    if (result < 0)
    {
        fprintf(stderr, "Could not play music file: %s\n", Mix_GetError());
        exit(-1);
    }
}

int main(int argc, char *argv[])
{
    SDL_Event event;
    world_t world;
    resources_t resources;
    SDL_Renderer *renderer;
    SDL_Window *window;
    srand(time(NULL));
    // initialisation du jeu
    world.hardmode = (argc > 1 && strcmp(argv[1],"--hard") == 0);
    init(&window, &renderer, &resources, &world);
    play_music(&resources);
    while (!is_game_over(&world))
    { // tant que le jeu n'est pas fini

        // gestion des évènements
        handle_events(&event, &world);

        // mise à jour des données liée à la physique du monde
        update_data(&world);

        // rafraichissement de l'écran
        refresh_graphics(renderer, &world, &resources);

        // pause de 10 ms pour controler la vitesse de rafraichissement
        pause(10);
    }

    // nettoyage final
    clean(window, renderer, &resources, &world);

    return 0;
}

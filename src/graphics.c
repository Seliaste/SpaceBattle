#include "graphics.h"

void clean_resources(resources_t *resources)
{
    clean_texture(resources->background);
    clean_texture(resources->ship);
    clean_texture(resources->enemy);
    clean_texture(resources->missile);
    clean_font(resources->font);
}

void init_resources(SDL_Renderer *renderer, resources_t *resources)
{
    resources->background = load_image("ressources/background2.bmp", renderer);
    resources->ship = load_image("ressources/spaceship2.bmp", renderer);
    resources->enemy = load_image("ressources/asteroid.bmp", renderer);
    resources->missile = load_image("ressources/missile.bmp", renderer);
    resources->font = load_font("ressources/edosz.ttf", 200);
    resources->heart = load_image("ressources/heart.bmp", renderer);
    resources->music = Mix_LoadWAV("ressources/music.wav");
    if(resources->music == NULL)
    {
        fprintf(stderr, "Could not load music file: %s\n",Mix_GetError());
    }
}

void apply_background(SDL_Renderer *renderer, resources_t *resources)
{
    if (resources->background != NULL)
    {
        apply_texture(resources->background, renderer, 0, 0);
    }
}

void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite)
{
    if (texture != NULL && sprite->is_visible)
    {
        apply_texture(texture, renderer, sprite->pos_x - sprite->width / 2, sprite->pos_y - sprite->height / 2);
    }
}
void apply_enemies(SDL_Renderer *renderer, world_t *world, resources_t *resources)
{
    for (int i = 0; i < NB_ENEMIES; i++)
    {
        apply_sprite(renderer, resources->enemy, &world->enemies[i]);
    }
}

void apply_score_text(SDL_Renderer *renderer, TTF_Font *font, int score)
{
    char scoretext[64];
    sprintf(scoretext, "Score : %d", score);
    apply_text(renderer, 0, 0, 100, 40, scoretext, font);
}

void apply_endgame_text(SDL_Renderer *renderer, TTF_Font *font, world_t *world)
{
    char text[64];
    switch (world->gamestate)
    {
    case 0:
        sprintf(text, "");
        break;
    case 1:
        sprintf(text, "Destroyed");
        break;
    case 3:
        sprintf(text, "You survived");
        break;
    case 2:
        sprintf(text, "You won!");
        break;
    }
    apply_text(renderer, SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 20, 100, 100 / 3, text, font);
}

void apply_lifebar(SDL_Renderer *renderer, SDL_Texture *heart, world_t *world)
{
    for (int i = 0; i < world->lives; i++)
    {
        apply_texture(heart, renderer, 4 + i * 36, SCREEN_HEIGHT - 36);
    }
}
void refresh_graphics(SDL_Renderer *renderer, world_t *world, resources_t *resources)
{

    // on vide le renderer
    clear_renderer(renderer);

    // application des resources dans le renderer
    apply_background(renderer, resources);

    // application de la texture du vaisseau
    apply_sprite(renderer, resources->ship, &world->ship);

    // apply_sprite(renderer, resources->enemy, &world->enemy);

    apply_sprite(renderer, resources->missile, &world->missile);

    apply_enemies(renderer, world, resources);

    apply_score_text(renderer, resources->font, world->score);

    apply_lifebar(renderer, resources->heart, world);

    apply_endgame_text(renderer, resources->font, world);

    update_screen(renderer);
}
#include "graphics.h"

void clean_textures(textures_t *textures)
{
    clean_texture(textures->background);
    clean_texture(textures->ship);
    clean_texture(textures->enemy);
    clean_texture(textures->missile);
}

void init_textures(SDL_Renderer *renderer, textures_t *textures)
{
    textures->background = load_image("ressources/space-background.bmp", renderer);
    textures->ship = load_image("ressources/spaceship.bmp", renderer);
    textures->enemy = load_image("ressources/enemy.bmp", renderer);
    textures->missile = load_image("ressources/missile.bmp", renderer);
}

void apply_background(SDL_Renderer *renderer, textures_t *textures)
{
    if (textures->background != NULL)
    {
        apply_texture(textures->background, renderer, 0, 0);
    }
}

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

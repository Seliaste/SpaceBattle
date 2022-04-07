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
    resources->background = load_image("ressources/space-background.bmp", renderer);
    resources->ship = load_image("ressources/spaceship.bmp", renderer);
    resources->enemy = load_image("ressources/enemy.bmp", renderer);
    resources->missile = load_image("ressources/missile.bmp", renderer);
    resources->font = load_font("ressources/edosz.ttf",200);
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
    for (int i = 0;i<NB_ENEMIES;i++){
         apply_sprite(renderer, resources->enemy, &world->enemies[i]);
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

    apply_sprite(renderer, resources->enemy, &world->enemy);

    apply_sprite(renderer, resources->missile, &world->missile);
    // on met à jour l'écran
    apply_enemies(renderer,world,resources);

    apply_text(renderer,0,0,100,40,"Score :",resources->font);

    update_screen(renderer);
}

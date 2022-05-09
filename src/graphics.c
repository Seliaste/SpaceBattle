#include "graphics.h"

void clean_resources(resources_t *resources)
{
    clean_texture(resources->background);
    clean_texture(resources->ship);
    clean_texture(resources->enemy);
    clean_texture(resources->missile);
    clean_font(resources->font);
}

void init_resources(SDL_Renderer *renderer, resources_t *resources, bool hardmode)
{
    resources->background = load_image(hardmode?"ressources/hardspace.bmp":"ressources/background2.bmp", renderer);
    resources->ship = load_image("ressources/spaceship2.bmp", renderer);
    resources->enemy = load_image("ressources/asteroid.bmp", renderer);
    resources->missile = load_image("ressources/missile.bmp", renderer);
    resources->font = load_font("ressources/edosz.ttf", 32);
    resources->heart = load_image("ressources/heart.bmp", renderer);
    resources->explosion[0] = load_image("ressources/explosion1.bmp", renderer);
    resources->explosion[1] = load_image("ressources/explosion2.bmp", renderer);
    resources->explosion[2] = load_image("ressources/explosion3.bmp", renderer);
    resources->explosion[3] = load_image("ressources/explosion4.bmp", renderer);
    resources->explosion[4] = load_image("ressources/explosion5.bmp", renderer);
    resources->music = Mix_LoadWAV(hardmode?"ressources/musichard.wav":"ressources/music.wav");
    if(resources->music == NULL)
    {
        fprintf(stderr, "Could not load music file: %s\n",Mix_GetError());
    }
    resources->explosion_sfx = Mix_LoadWAV("ressources/explosion.wav");
    if(resources->explosion_sfx == NULL)
    {
        fprintf(stderr, "Could not load music file: %s\n",Mix_GetError());
    }
    resources->explosion_sfx = Mix_LoadWAV("ressources/explosion.wav");
    if(resources->explosion_sfx == NULL)
    {
        fprintf(stderr, "Could not load music file: %s\n",Mix_GetError());
    }
    resources->damage_sfx = Mix_LoadWAV("ressources/damage.wav");
    if(resources->damage_sfx == NULL)
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

void apply_explosion(SDL_Renderer *renderer, resources_t *resources, sprite_t *sprite, int frame)
{
    if (sprite->is_visible)
    {
        apply_texture(resources->explosion[frame/EXPLOSION_FRAMETIME], renderer, sprite->pos_x - sprite->width / 2, sprite->pos_y - sprite->height / 2);
    }
}

void apply_enemies(SDL_Renderer *renderer, world_t *world, resources_t *resources)
{
    for (int i = 0; i < NB_ENEMIES; i++)
    {
        apply_sprite(renderer, resources->enemy, &world->enemies[i]);
        if(world->enemies[i].play_explosion){
            world->enemies[i].play_explosion = false;
            Mix_PlayChannel(-1,resources->explosion_sfx,0);
        }
    }
}

void apply_score_text(SDL_Renderer *renderer, TTF_Font *font, int score)
{
    char scoretext[64];
    sprintf(scoretext, "Score : %d", score);
    apply_text(renderer, 0, 0, 150, 40, scoretext, font);
}

void apply_endgame_text(SDL_Renderer *renderer, TTF_Font *font, world_t *world)
{
    char text[64];
    switch (world->gamestate)
    {
    case 0:
        sprintf(text, " ");
        break;
    case 1:
        sprintf(text, "Destroyed, too bad!");
        break;
    case 3:
        sprintf(text, "You survived, well done!");
        break;
    case 2:
        sprintf(text, world->hardmode?"Congratulations y'are a God  !":"You won! Try --hard");
        break;
    }
    apply_text(renderer, SCREEN_WIDTH / 2 - 125, SCREEN_HEIGHT / 2 - 20, 250, 100 / 3, text, font);
}

void apply_lifebar(SDL_Renderer *renderer, SDL_Texture *heart, world_t *world, Mix_Chunk *damage_sfx)
{
    for (int i = 0; i < world->lives; i++)
    {
        apply_texture(heart, renderer, 4 + i * 36, SCREEN_HEIGHT - 36);
        
    }
    if (world->play_damage_sfx){
        world->play_damage_sfx = false;
        Mix_PlayChannel(-1,damage_sfx,0);
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

    apply_explosion(renderer, resources, &world->explosion, world->current_explosion_frame);

    apply_score_text(renderer, resources->font, world->score);

    apply_lifebar(renderer, resources->heart, world, resources->damage_sfx);

    apply_endgame_text(renderer, resources->font, world);

    update_screen(renderer);
}
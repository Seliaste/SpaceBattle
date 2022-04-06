#include "game_logic.h"

void set_visible(sprite_t *sprite)
{
    sprite->is_visible = 1;
}

void set_invisible(sprite_t *sprite)
{
    sprite->is_visible = 0;
}

void despawn_sprite(sprite_t *sprite)
{
    set_invisible(sprite);
    sprite->pos_x = -500;
    sprite->pos_y = -500;
}

void respawn_sprite(sprite_t *sprite, int x, int y)
{
    sprite->pos_x = x;
    sprite->pos_y = y;
    set_visible(sprite);
}

void init_sprite(sprite_t *sprite, int x, int y, int w, int h, int v, int visible)
{
    sprite->pos_x = x;
    sprite->pos_y = y;
    sprite->width = w;
    sprite->height = h;
    sprite->speed_v = v;
    sprite->is_visible = visible;
}

void print_sprite(sprite_t *sprite)
{
    printf("Position : %dx %dy, taille: %dh, %dw, vitesse: %d\n", sprite->pos_x, sprite->pos_y, sprite->height, sprite->width, sprite->speed_v);
}

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

void clean_data(world_t *world)
{
    /* utile uniquement si vous avez fait de l'allocation dynamique (malloc); la fonction ici doit permettre de libérer la mémoire (free) */
}

void init_enemies(world_t *world)
{
    
}

int is_game_over(world_t *world)
{
    return world->gameover;
}
void update_enemies(world_t* world)
{
    for (int i=0;i<NB_ENEMIES;i++){
        world->enemies[i].pos_y+= world->enemies[i].speed_v; 
    }
}
void update_data(world_t *world)
{
    world->enemy.pos_y += world->enemy.speed_v;
    world->missile.pos_y -= world->missile.speed_v;
    ship_limit(world);
    enemy_limit(world);
    handle_sprites_collision(&world->ship, &world->enemy);
    handle_sprites_collision(&world->enemy, &world->missile);
    update_enemies(world);
}

void ship_limit(world_t *world)
{
    if (world->ship.pos_x - SHIP_SIZE / 2 < 0)
    {
        world->ship.pos_x = SHIP_SIZE / 2;
    }
    else if (world->ship.pos_x + SHIP_SIZE / 2 > SCREEN_WIDTH)
    {
        world->ship.pos_x = SCREEN_WIDTH - SHIP_SIZE / 2;
    }
}
void enemy_limit(world_t *world)
{
    if (world->enemy.pos_y > SCREEN_HEIGHT + (SHIP_SIZE / 2))
    {
        world->enemy.pos_y = (SHIP_SIZE / 2);
    }
}

int sprite_collide(sprite_t *sp1, sprite_t *sp2)
{
    int dist = sqrt(pow(sp2->pos_x - sp1->pos_x, 2) + pow(sp2->pos_y - sp1->pos_y, 2)); // formule de la distance dans un plan
    return (sp1->height + sp2->height) / 2 > dist;
}

void handle_sprites_collision(sprite_t *sp1, sprite_t *sp2)
{
    if (sprite_collide(sp1, sp2) && sp1->is_visible && sp2->is_visible)
    {
        despawn_sprite(sp1);
        despawn_sprite(sp2);
    }
}
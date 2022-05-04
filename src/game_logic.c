#include "game_logic.h"

int generate_number(int a, int b)
{
    return rand() % (b - a) + a;
}

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
}

void respawn_sprite(sprite_t *sprite, int x, int y)
{
    sprite->pos_x = x;
    sprite->pos_y = y;
    set_visible(sprite);
}

void init_sprite(sprite_t *sprite, int x, int y, int w, int h, int vv, int vh, int visible)
{
    sprite->pos_x = x;
    sprite->pos_y = y;
    sprite->width = w;
    sprite->height = h;
    sprite->speed_v = vv;
    sprite->speed_h = vh;
    sprite->is_visible = visible;
    sprite->play_explosion = false;
}

void print_sprite(sprite_t *sprite)
{
    printf("Position : %dx %dy, taille: %dh, %dw, vitesse: %d\n", sprite->pos_x, sprite->pos_y, sprite->height, sprite->width, sprite->speed_v);
}

void init_data(world_t *world)
{

    // on n'est pas à la fin du jeu
    world->gameover = 0;
    world->enemies_passed = 0;
    world->enemies_destroyed = 0;
    world->exit_time = 0;
    world->lives = LIVES;
    world->current_explosion_frame = 0;
    // initialise un vaisseau en bas de l'ecran
    init_sprite(&(world->ship), SCREEN_WIDTH / 2, SCREEN_HEIGHT - SHIP_SIZE * 2, SHIP_SIZE, SHIP_SIZE, 0, 0, 1);
    // initialise un missile positionné sur le vaisseau
    init_sprite(&(world->missile), SCREEN_WIDTH / 2, SCREEN_HEIGHT - SHIP_SIZE * 2, MISSILE_SIZE, MISSILE_SIZE, MISSILE_SPEED, 0, 0);
    init_sprite(&(world->explosion), 100,100, SHIP_SIZE, SHIP_SIZE,0,0,1);
    init_enemies(world);
}

void clean_data(world_t *world)
{
    /* utile uniquement si vous avez fait de l'allocation dynamique (malloc); la fonction ici doit permettre de libérer la mémoire (free) */
}

void init_enemies(world_t *world)
{
    for (int i = 0; i < NB_ENEMIES; i++)
    {
        init_sprite(&world->enemies[i], generate_number(SHIP_SIZE / 2, SCREEN_WIDTH - SHIP_SIZE / 2), -SHIP_SIZE / 2 - i * VERTICAL_DIST, SHIP_SIZE, SHIP_SIZE, ENEMY_SPEED, 0, 1);
    }
}

int is_game_over(world_t *world)
{
    return world->gameover;
}

void update_single_enemy(world_t *world, int i)
{
    if (handle_sprites_collision(&world->enemies[i], &world->ship))
    {
        world->enemies[i].play_explosion = true;
        world->enemies_destroyed += 1;
        if (world->lives > 1)
        {
            set_visible(&world->ship);
        }
        world->lives -= 1;
    }

    if (handle_sprites_collision(&world->enemies[i], &world->missile))
    {
        world->enemies_destroyed += 1;
        world->score += 1;
        world->enemies[i].play_explosion = true;
        world->explosion.pos_x = world->enemies[i].pos_x;
        world->explosion.pos_y = world->enemies[i].pos_y;
        world->explosion.is_visible = 1;
        world->current_explosion_frame = 0;
    }
    world->enemies[i].pos_y += world->enemies[i].speed_v;
    if (world->enemies[i].pos_y > SCREEN_HEIGHT + SHIP_SIZE / 2 && world->enemies[i].is_visible)
    {
        world->enemies_passed += 1;
        world->enemies[i].speed_v = 0;
        despawn_sprite(&world->enemies[i]);
        // printf("%d ennemis sont sortis\n", world->enemies_passed);
    }
}

void update_enemies(world_t *world)
{
    for (int i = 0; i < NB_ENEMIES; i++)
    {
        update_single_enemy(world, i);
    }
}

void move_ship(world_t *world)
{
    world->ship.pos_x += world->ship.speed_h;
}

void missile_limit(world_t *world)
{
    if(world->missile.pos_y<0)
    {
        despawn_sprite(&world->missile);
    }
}

void update_data(world_t *world)
{
    move_ship(world);
    // world->enemy.pos_y += world->enemy.speed_v;
    world->missile.pos_y -= world->missile.speed_v;
    missile_limit(world);
    ship_limit(world);
    // enemy_limit(world);
    // handle_sprites_collision(&world->ship, &world->enemy);
    // handle_sprites_collision(&world->enemy, &world->missile);
    update_enemies(world);
    compute_game(world);
    world->current_explosion_frame = (world->current_explosion_frame+1)%(EXPLOSION_FRAMES*EXPLOSION_FRAMETIME);
    if(world->current_explosion_frame == 0){
        world->explosion.is_visible = 0;
    }
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
// void enemy_limit(world_t *world)
// {
//     if (world->enemy.pos_y > SCREEN_HEIGHT + (SHIP_SIZE / 2))
//     {
//         world->enemy.pos_y = (SHIP_SIZE / 2);
//     }
// }

int sprite_collide(sprite_t *sp1, sprite_t *sp2)
{
    int dist = sqrt(pow(sp2->pos_x - sp1->pos_x, 2) + pow(sp2->pos_y - sp1->pos_y, 2)); // formule de la distance dans un plan
    return (sp1->height + sp2->height) / 2 > dist;
}

int handle_sprites_collision(sprite_t *sp1, sprite_t *sp2)
{
    if (sprite_collide(sp1, sp2) && sp1->is_visible && sp2->is_visible)
    {
        despawn_sprite(sp1);
        despawn_sprite(sp2);
        return 1;
    }
    return 0;
}

void compute_game(world_t *world)
{
    if (world->enemies_passed + world->enemies_destroyed < NB_ENEMIES)
    {
        world->gamestate = playing;
        world->score = world->enemies_destroyed;
        return;
    }
    // le jeu est fini
    world->exit_time += 10; // temps entre chaque itération
    if (world->exit_time >= EXIT_DELAY)
    {                        // si le délai est fini
        world->gameover = 1; // on quitte
    }
    if (!world->ship.is_visible) // le vaisseau est détruit
    {
        world->gamestate = destroyed;
        world->score = 0;
        return;
    }
    if (world->enemies_passed > 0) // des ennemis sont passés
    {
        world->gamestate = survived;
        return;
    }
    world->gamestate = won; // = gagné
}
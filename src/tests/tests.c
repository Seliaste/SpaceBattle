/**
 * @file tests.c
 * @author Thomas Wieczorek (wieczore9u@etu-univ-lorraine.fr)
 * @brief Fichier de test de la logique de jeu
 * @version 1
 * @date 2022-03-31
 */

#include "../game_logic.h"
void test_init_sprite_param(sprite_t *sprite, int x, int y, int w, int h, int v, int visible)
{
    init_sprite(sprite, x, y, w, h, v, visible);
    print_sprite(sprite);
}
void test_init_sprite()
{
    world_t world;
    init_data(&world);
    test_init_sprite_param(&world.missile, 500, 15, 28, 440, 12, 1);
    test_init_sprite_param(&world.missile, 100, 10, 10, 2, 4, 1);
    test_init_sprite_param(&world.missile, 500, 140, 280, 15, 25, 1);
    test_init_sprite_param(&world.missile, 0, 0, 0, 0, 0, 1);
    test_init_sprite_param(&world.enemy, 200, SCREEN_HEIGHT + 20, 50, 28, 14, 1);
}
void test_ship_limit_param(sprite_t *sprite, world_t *world, int newx)
{
    sprite->pos_x = newx;
    printf("Avant ajustement: ship x = %d\n", sprite->pos_x);
    ship_limit(world);
    printf("Après ajustement: ship x = %d\n", sprite->pos_x);
}

void test_ship_limit()
{
    world_t world;
    init_data(&world);
    test_ship_limit_param(&world.ship, &world, -10);
    test_ship_limit_param(&world.ship, &world, 1000);
}

void test_enemy_limit_param(sprite_t *sprite, world_t *world, int newy)
{
    sprite->pos_y = newy;
    printf("Avant ajustement: enemy y = %d\n", sprite->pos_y);
    enemy_limit(world);
    printf("Après ajustement: enemy y = %d\n", sprite->pos_y);
}

void test_enemy_limit()
{
    world_t world;
    init_data(&world);
    test_enemy_limit_param(&world.enemy, &world, SCREEN_HEIGHT + 42);
    test_enemy_limit_param(&world.enemy, &world, 500);
}

void test_collision_param(world_t* world, int x1, int y1, int y2, int x2){
    world->ship.pos_x = x1;
    world->ship.pos_y = y1;
    world->missile.pos_x = x2;
    world->missile.pos_y = y2;
    printf(sprite_collide(&world->ship,&world->missile)?"1 et 2 sont en collision\n":"1 et 2 ne sont pas en collision\n");
}

void test_collision()
{
    world_t world;
    init_data(&world);
    test_collision_param(&world,0,0,0,0);
    test_collision_param(&world,0,0,100,100);
    test_collision_param(&world,0,100,0,0);
}

int main(int argc, char *argv[])
{
    test_init_sprite();
    test_ship_limit();
    test_enemy_limit();
    test_collision();
}
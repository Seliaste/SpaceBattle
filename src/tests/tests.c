/**
 * @file tests.c
 * @author Thomas Wieczorek (wieczore9u@etu-univ-lorraine.fr)
 * @brief Fichier de test de la logique de jeu
 * @version 1
 * @date 2022-03-31
 */

#include "../game_logic.h"
void test_init_sprite_param(sprite_t *sprite, int x, int y, int w, int h, int v, int visible){
    init_sprite(sprite,x,y,w,h,v,visible);
    print_sprite(sprite);
    
}
void test_init_sprite(){
    world_t world;
    init_data(&world);
    test_init_sprite_param(&world.missile,500,15,28,440,12,1);
    test_init_sprite_param(&world.missile,100,10,10,2,4,1);
    test_init_sprite_param(&world.missile,500,140,280,15,25,1);
    test_init_sprite_param(&world.missile,0,0,0,0,0,1);
    test_init_sprite_param(&world.enemy,200,SCREEN_HEIGHT+20,50,28,14,1);
}
int main (int argc,char* argv[]){
    test_init_sprite();
}
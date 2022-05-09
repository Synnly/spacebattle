/**
 * \file tests.c
 * \brief Tests des fonctions du module donnees
 * \author Fernandes dos Santos Emanuel et Lagarde Tristan
 * \date 31 mars 2022
 */

#include "donnes.h"
#include <stdio.h>

void test_init_sprite_param(int x, int y, unsigned int w, unsigned int h, int v, unsigned int type){
    sprite_t sprite1;
    init_sprite(&sprite1, x, y, w, h, v, type);
    print_sprite(&sprite1);
    printf("\n");
}

void test_init_sprite(){
    for(int i = 0; i<=10; i++){
        test_init_sprite_param(i, 2*i, 3*i, 4*i, 5*i, 2);
    }
}


void test_vaisseau_depasse_bords_param(sprite_t *sprite){
    printf("Avant : x, y = %d, %d | Apres : x, y = ", sprite->x, sprite->y);
    vaisseau_depasse_bords(sprite);
    printf("%d, %d\n", sprite->x, sprite->y); 
}

void test_vaisseau_depasse_bords(){
    sprite_t sprite;

    // Bord gauche
    for(int i = -100; i<401; i+=100){
        init_sprite(&sprite, i, 50, 32, 32, 0, 0);
        test_vaisseau_depasse_bords_param(&sprite);
    }
}


void test_ennemi_depasse_bas_param(world_t *world){
    ennemi_depasse_bas(world);
    for(int i = 0; i<5; i++){
        printf("Ennemi %d x, y = %d, %d est visible : %s\n", i+1, world->enemies[i].x, world->enemies[i].y, (world->enemies[i].is_visible?"faux":"vrai"));
    }
}

void test_ennemi_depasse_bas(){
    world_t world;
    init_data(&world);
    world.enemies[0].y = -200;
    world.enemies[1].y = 0;
    world.enemies[2].y = 100;
    world.enemies[3].y = 300;
    world.enemies[4].y = 600;
    ennemi_depasse_bas(&world);
    test_ennemi_depasse_bas_param(&world); 
}


void test_sprites_collide_param(sprite_t *sprite1, sprite_t *sprite2){
    printf("Le sprite 1 (%d, %d) et le sprite 2 (%d, %d) %s en collision\n", sprite1->x, sprite1->y, sprite2->x, sprite2->y, sprites_collide(sprite2, sprite1)?"sont":"ne sont pas");
}


void test_sprites_collide(){
    sprite_t sprite1;
    sprite_t sprite2;
    for(int i = 32; i<=62; i+=30){
        for(int j = 22; j<=62; j+=20){
            init_sprite(&sprite1, i, i, 32, 32, 0, 0);
            init_sprite(&sprite2, j, j, 32, 32, 0, 2);
            test_sprites_collide_param(&sprite1, &sprite2);
        }
    }
}


void test_handle_missiles_collide_param(sprite_t *sprite1, sprite_t *sprite2){
    printf("----------Avant----------\n");
    printf("Le sprite 1 (%d, %d, v = %d) et sprite 2 (%d, %d, v = %d) %s en collision\n", sprite1->x, sprite1->y, sprite1->v, sprite2->x, sprite2->y, sprite2->v, sprites_collide(sprite2, sprite1)?"sont":"ne sont pas");
    handle_missiles_collide(sprite1, sprite2);
    printf("----------Apres----------\n");
    printf("Le sprite 1 (%d, %d, v = %d) et sprite 2 (%d, %d, v = %d) %s en collision\n", sprite1->x, sprite1->y, sprite1->v, sprite2->x, sprite2->y, sprite2->v, sprites_collide(sprite2, sprite1)?"sont":"ne sont pas");
    printf("\n");
}


void test_handle_missiles_collide(){
    sprite_t sprite1;
    sprite_t sprite2;
    for(int i = 20; i<62; i+=30){
        for(int visible = 0; visible<=1; visible++){
            init_sprite(&sprite1, i, 50, 32, 32, 5, 1);
            init_sprite(&sprite2, 62, 50, 32, 32, 5, 2);
            test_handle_missiles_collide_param(&sprite1, &sprite2);
        }
    }
}

/* void test_handle_vaisseau_collide_param(world_t* world){

}

void test_handle_vaisseau_collide(){
    world_t world
} */

void test_init_enemies_param(world_t* world){
    for(int i=0;i<NB_ENEMIES;i++){
        print_sprite(&(world->enemies[i]));
        printf("\n");
    }
    fflush(stdout);
}

void test_init_enemies(){
    world_t world;
    init_enemies(&world); 
    test_init_enemies_param(&world);
}


void test_update_enemies_param(world_t *world){
    for(int i = 0; i<NB_ENEMIES; i++){
        printf("----------Avant----------\n");
        print_sprite(&(world->enemies[i]));

        printf("----------Après----------\n");
        update_enemies(world);
        print_sprite(&(world->enemies[i]));
        printf("\n");
    }
    fflush(stdout);
}

void test_update_enemies(){
    world_t world;
    init_enemies(&world);
    test_update_enemies_param(&world);
}

int main(int argc, char* argv[]){
    int choix;
    printf("Choisir le test :\n1. test_init_sprite\n2. test_vaisseau_depasse_bords\n3. test_ennemi_depasse_bas\n4. test_sprites_collide\n5. test_handle_sprites_collide\n6. test_init_enemies\n7. test_update_enemies\n> ");
    scanf("%d", &choix);

    switch (choix){
    case 1:
        test_init_sprite();
        break;
    case 2:
        test_vaisseau_depasse_bords();
        break;
    case 3:
        test_ennemi_depasse_bas();
        break; 
    case 4:
        test_sprites_collide();
        break;  
    case 5:
        test_handle_missiles_collide();
        break; 
    case 6:
        test_init_enemies();
        break;
    case 7:
        test_update_enemies();
        break;
    default:
        break;
    }
    return EXIT_SUCCESS;
}
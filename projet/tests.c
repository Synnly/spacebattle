/**
 * \file tests.c
 * \brief Tests des fonctions du module donnees
 * \author Fernandes dos Santos Emanuel et Lagarde Tristan
 * \date 31 mars 2022
 */

#include "donnes.h"

void test_init_sprite_param(int x, int y, int w, int h, int v){
    sprite_t sprite1;
    init_sprite(&sprite1, x, y, w, h, v);
    print_sprite(&sprite1);
    printf("\n");
}

void test_init_sprite(){
    for(int i = 0; i<=10; i++){
        test_init_sprite_param(i, 2*i, 3*i, 4*i, 5*i);
    }
}


void test_depasse_gauche_param(sprite_t *sprite){
    printf("----------Avant----------\n");
    print_sprite(sprite);
    depasse_gauche(sprite);
    printf("----------Apres--------\n");
    print_sprite(sprite);
    printf("\n");
}


void test_depasse_gauche(){
    sprite_t sprite;
    for(int i = 0; i>-13; i-=3){
        init_sprite(&sprite, i, 50, 32, 32, 0);
        test_depasse_gauche_param(&sprite);
    }
}


void test_depasse_droite_param(sprite_t *sprite){
    printf("----------Avant----------\n");
    print_sprite(sprite);
    depasse_droite(sprite);
    printf("----------Apres--------\n");
    print_sprite(sprite);
    printf("\n");
}


void test_depasse_droite(){
    sprite_t sprite;
    for(int i = 262; i<=310; i+=10){
        init_sprite(&sprite, i, 50, 32, 32, 0);
        test_depasse_droite_param(&sprite);
    }
}


void test_ennemi_depasse_bas_param(sprite_t *sprite){
    printf("----------Avant----------\n");
    print_sprite(sprite);
    ennemi_depasse_bas(sprite);
    printf("----------Apres--------\n");
    print_sprite(sprite);
    printf("\n");
}


void test_ennemi_depasse_bas(){
    sprite_t sprite;
    for(int i = 64; i<800; i+=200){
        init_sprite(&sprite, 50, i, 32, 32, 0);
        test_ennemi_depasse_bas_param(&sprite);
    }
}


void test_sprites_collide_param(sprite_t *sprite1, sprite_t *sprite2){
    printf("Le sprite 1 (%d, %d) et le sprite 2 (%d, %d) %s en collision\n", sprite1->x, sprite1->y, sprite2->x, sprite2->y, sprites_collide(sprite2, sprite1)?"sont":"ne sont pas");
}


void test_sprites_collide(){
    sprite_t sprite1;
    sprite_t sprite2;
    for(int i = 32; i<=62; i+=30){
        for(int j = 22; j<=62; j+=20){
            init_sprite(&sprite1, i, i, 32, 32, 0);
            init_sprite(&sprite2, j, j, 32, 32, 0);
            test_sprites_collide_param(&sprite1, &sprite2);
        }
    }
}


void test_handle_sprites_collide_param(sprite_t *sprite1, sprite_t *sprite2){
    printf("----------Avant----------\n");
    printf("Le sprite 1 (%d, %d, v = %d) et sprite 2 (%d, %d, v = %d) %s en collision\n", sprite1->x, sprite1->y, sprite1->v, sprite2->x, sprite2->y, sprite2->v, sprites_collide(sprite2, sprite1)?"sont":"ne sont pas");
    handle_sprites_collide(sprite1, sprite2);
    printf("----------Apres----------\n");
    printf("Le sprite 1 (%d, %d, v = %d) et sprite 2 (%d, %d, v = %d) %s en collision\n", sprite1->x, sprite1->y, sprite1->v, sprite2->x, sprite2->y, sprite2->v, sprites_collide(sprite2, sprite1)?"sont":"ne sont pas");
    printf("\n");
}


void test_handle_sprites_collide(){
    sprite_t sprite1;
    sprite_t sprite2;
    for(int i = 20; i<62; i+=30){
        for(int visible = 0; visible<=1; visible++){
            init_sprite(&sprite1, i, 50, 32, 32, 5);
            if(visible){set_invisible(&sprite1);};
            init_sprite(&sprite2, 62, 50, 32, 32, 5);
            test_handle_sprites_collide_param(&sprite1, &sprite2);
        }
    }
}


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
    /* test_init_sprite(); */
    /* test_depasse_gauche(); */
    /* test_depasse_droite(); */
    /* test_ennemi_depasse_bas(); */
    /* test_sprites_collide(); */
    //test_handle_sprites_collide();
    /* test_init_enemies(); */
    test_update_enemies();
    return EXIT_SUCCESS;
}
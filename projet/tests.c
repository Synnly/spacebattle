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


int main(int argc, char* argv[]){
    /* test_init_sprite(); */
    /* test_depasse_gauche(); */
    /* test_depasse_droite(); */
    test_ennemi_depasse_bas();
    return EXIT_SUCCESS;
}
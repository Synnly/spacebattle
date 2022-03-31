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

int main(int argc, char* argv[]){
    test_init_sprite();
    return EXIT_SUCCESS;
}
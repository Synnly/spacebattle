/**
 * \file tests.c
 * \brief Tests des fonctions du module donnees
 * \author Fernandes dos Santos Emanuel et Lagarde Tristan
 * \date 31 mars 2022
 */

#include "donnes.h"
#include <stdio.h>

void test_init_sprite_param(int x, int y, unsigned int w, unsigned int h, int v, unsigned int type, unsigned int lives){
    sprite_t sprite1;
    init_sprite(&sprite1, x, y, w, h, v, type, lives);
    print_sprite(&sprite1);
    printf("\n");
}

void test_init_sprite(){
    for(int i = 0; i<=10; i++){
        test_init_sprite_param(i, 2*i, 3*i, 4*i, 5*i, 2, 3);
    }
}


void test_vaisseau_depasse_bords_param(sprite_t *sprite){
    printf("Avant : x, y = %d, %d | Apres : x, y = ", getx(sprite), gety(sprite));
    vaisseau_depasse_bords(sprite);
    printf("%d, %d\n", getx(sprite), gety(sprite)); 
}

void test_vaisseau_depasse_bords(){
    sprite_t sprite;

    // Bord gauche
    for(int i = -100; i<401; i+=100){
        init_sprite(&sprite, i, 50, 32, 32, 0, 0,3);
        test_vaisseau_depasse_bords_param(&sprite);
    }
}


void test_ennemi_depasse_bas_param(world_t *world){
    ennemi_depasse_bas(world);
    for(int i = 0; i<5; i++){
        printf("Ennemi %d x, y = %d, %d est visible : %s\n", i+1, getx(getenemies(world,i)), gety(getenemies(world,i)), (getvisibility(getenemies(world,i)))?"faux":"vrai");
    }
}

void test_ennemi_depasse_bas(){
    world_t world;
    init_data(&world);
    sety(getenemies(&world,0),-200);
    sety(getenemies(&world,1),0);
    sety(getenemies(&world,2),100);
    sety(getenemies(&world,3),300);
    sety(getenemies(&world,4),600);
    ennemi_depasse_bas(&world);
    test_ennemi_depasse_bas_param(&world);
    printf("\n");
}


void test_sprites_collide_param(sprite_t *sprite1, sprite_t *sprite2){
    printf("Le sprite 1 (%d, %d) et le sprite 2 (%d, %d) %s en collision\n", getx(sprite1), gety(sprite1), getx(sprite2), gety(sprite2), sprites_collide(sprite2, sprite1)?"sont":"ne sont pas");
}


void test_sprites_collide(){
    sprite_t sprite1;
    sprite_t sprite2;
    for(int i = 32; i<=62; i+=30){
        for(int j = 22; j<=62; j+=20){
            init_sprite(&sprite1, i, i, 32, 32, 0, 0,2);
            init_sprite(&sprite2, j, j, 32, 32, 0, 2,2);
            test_sprites_collide_param(&sprite1, &sprite2);
        }
    }
}

void test_reset_enemi_param(world_t* world){
    printf("----------Avant----------\n");
    print_sprite(getenemies(world,0));
    reset_enemi(world,0);
    printf("----------Apres----------\n");
    print_sprite(getenemies(world,0));
    printf("\n");
}

void test_reset_enemi(){
    world_t world;
    init_data(&world);
    setx(getenemies(&world,0),50);
    sety(getenemies(&world,0),SCREEN_HEIGHT*2);
    test_reset_enemi_param(&world);
}

void test_missile_depasse_haut_param(world_t* world){
    printf("----------Avant----------\n");
    print_sprite(getmissile(world));
    missile_depasse_haut(world);
    printf("----------Apres----------\n");
    print_sprite(getmissile(world));
    printf("\n");
}

void test_missile_depasse_haut(){
    world_t world;
    init_data(&world);
    setx(getmissile(&world),50);
    sety(getmissile(&world),-100);
    setlives(getmissile(&world),1);
    test_missile_depasse_haut_param(&world);
}

void test_score_param(world_t* world){
    printf("----------Avant----------\n");
    printf("Score = %d\n",getscore(world));
    score(world);
    printf("----------Apres----------\n");
    printf("Score = %d\n",getscore(world));

}

void test_score(){
    world_t world;
    init_data(&world);

    setx(getmissile(&world), 50);
    sety(getmissile(&world), 50);
    setx(getenemies(&world, 0), 32);
    sety(getenemies(&world, 0), 32);

    for(int i=2; i<7; i++){
        printf("\n------Type = %d------\n", i);
        settype(getenemies(&world, 0), i);
        setlives(getvaisseau(&world), 3);
        set_visible(getmissile(&world));
        set_visible(getenemies(&world, 0));

        if(i==AMBULANCE_TYPE || i==TANK_TYPE){setlives(getenemies(&world, 0), TANK_LIFE);}
        else{setlives(getenemies(&world, 0), ENEMY_LIFE);}

        test_score_param(&world);

        setlives(getenemies(&world, 0), 0);
        test_score_param(&world);
    }
    printf("\n");
}


void test_handle_missiles_collide_param(world_t* world){
    printf("----------Avant----------\n");
    printf("Le missile (%d, %d, v = %d, vies = %d) et un ennemi (%d, %d, v = %d, vies = %d) %s en collision\n", getx(getmissile(world)), gety(getmissile(world)), getv(getmissile(world)),getlives(getmissile(world)), getx(getenemies(world,0)), gety(getenemies(world,0)), getv(getenemies(world,0)),getlives(getenemies(world,0)), sprites_collide(getenemies(world,0),getmissile(world))?"sont":"ne sont pas");
    printf("Le missile (%d, %d, v = %d, vies = %d) et un ennemi (%d, %d, v = %d, vies = %d) %s en collision\n", getx(getmissile(world)), gety(getmissile(world)), getv(getmissile(world)),getlives(getmissile(world)), getx(getenemies(world,1)), gety(getenemies(world,1)), getv(getenemies(world,1)),getlives(getenemies(world,1)), sprites_collide(getenemies(world,1),getmissile(world))?"sont":"ne sont pas");
    handle_missiles_collide(world);
    printf("----------Apres----------\n");
    printf("Le missile (%d, %d, v = %d, vies = %d) et un ennemi (%d, %d, v = %d, vies = %d) %s en collision\n", getx(getmissile(world)), gety(getmissile(world)), getv(getmissile(world)),getlives(getmissile(world)), getx(getenemies(world,0)), gety(getenemies(world,0)), getv(getenemies(world,0)),getlives(getenemies(world,0)), sprites_collide(getenemies(world,0),getmissile(world))?"sont":"ne sont pas");
    printf("Le missile (%d, %d, v = %d, vies = %d) et un ennemi (%d, %d, v = %d, vies = %d) %s en collision\n", getx(getmissile(world)), gety(getmissile(world)), getv(getmissile(world)),getlives(getmissile(world)), getx(getenemies(world,1)), gety(getenemies(world,1)), getv(getenemies(world,1)),getlives(getenemies(world,1)), sprites_collide(getenemies(world,1),getmissile(world))?"sont":"ne sont pas");
    printf("\n");
}


void test_handle_missiles_collide(){
    world_t world;
    init_data(&world);
    setx(getmissile(&world),50);
    sety(getmissile(&world),200);
    set_visible(getmissile(&world));
    setlives(getmissile(&world),1);
    for(int i=2;i<=6;i++){
        setx(getenemies(&world,0),50);
        sety(getenemies(&world,0),200);
        settype(getenemies(&world,0),i);
        setlives(getenemies(&world,0),1);
        setx(getenemies(&world,1),50);
        sety(getenemies(&world,1),200);
        settype(getenemies(&world,1),i);
        setlives(getenemies(&world,1),0);
        test_handle_missiles_collide_param(&world);
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

/*----------------------------------------------------------------------------------*/
void test_handle_vaisseau_collide_param(world_t* world){
    printf("Avant :");
    print_sprite(getvaisseau(world));
    for(int i=0; i<5; i++){print_sprite(getenemies(world, i));}
    handle_vaisseau_collide(world);
    printf("Apres :");
    print_sprite(getvaisseau(world));
    for(int i=0; i<5; i++){print_sprite(getenemies(world, i));}
}

void test_handle_vaisseau_collide(){
    world_t world;
    init_data(&world);

    setx(getvaisseau(&world), 50);
    sety(getvaisseau(&world), 50);
    setx(getenemies(&world, 0), 32);
    sety(getenemies(&world, 0), 32);

    for(int i=2; i<7; i++){
        printf("\n------Type = %d------\n", i);
        settype(getenemies(&world, 0), i);
        setlives(getvaisseau(&world), 3);
        set_visible(getvaisseau(&world));
        set_visible(getenemies(&world, 0));

        if(i==AMBULANCE_TYPE || i==TANK_TYPE){setlives(getenemies(&world, 0), TANK_LIFE);}
        else{setlives(getenemies(&world, 0), ENEMY_LIFE);}

        test_handle_vaisseau_collide_param(&world);

        setlives(getenemies(&world, 0), 0);
        test_handle_vaisseau_collide_param(&world);
    }
    printf("\n");
}


void test_heal_param(sprite_t *sprite){
    printf("Avant : Vies : %d\n", getlives(sprite));
    heal(sprite);
    printf("Apres : vies : %d\n", getlives(sprite));
}

void test_heal(){
    world_t world;
    init_data(&world);
    test_heal_param(getvaisseau(&world));
    setlives(getvaisseau(&world), 0);
    test_heal_param(getvaisseau(&world));
    printf("\n");
}


void test_take_dmg_param(sprite_t *sprite){
    printf("Avant : Vies : %d\n", getlives(sprite));
    take_dmg(sprite);
    printf("Apres : vies : %d\n", getlives(sprite));
}

void test_take_dmg(){
    world_t world;
    init_data(&world);
    test_take_dmg_param(getvaisseau(&world));
    setlives(getvaisseau(&world), 0);
    test_take_dmg_param(getvaisseau(&world));
    printf("\n");
}


void test_update_enemies_param(world_t *world){
    printf("Avant :\n");
    for(int i=0; i<5; i++){print_sprite(getenemies(world, i));}
    update_enemies(world);
    printf("Apres :\n");
    for(int i=0; i<5; i++){print_sprite(getenemies(world, i));}
}

void test_update_enemies(){
    world_t world;
    init_data(&world);
    test_update_enemies_param(&world);
    printf("\n");
}


void test_compute_game_param(world_t *world){
    printf("Avant : Vies : %d, Etat du jeu : %d\n", getlives(getvaisseau(world)), getetat(world));
    setlives(getvaisseau(world), 0);
    compute_game(world);
    printf("Apres : Vies : %d, Etat du jeu : %d\n", getlives(getvaisseau(world)), getetat(world));
}

void test_compute_game(){
    world_t world;
    init_data(&world);
    test_compute_game_param(&world);
    printf("\n");
}


void test_compute_lives_param(sprite_t *sprite){
    printf("Avant : ");
    print_sprite(sprite);
    setlives(sprite, 0);
    compute_lives(sprite);
    printf("Apres : ");
    print_sprite(sprite);
}

void test_compute_lives(){
    world_t world;
    init_data(&world);
    test_compute_lives_param(getvaisseau(&world));
    printf("\n");
}


void test_avance_missile_param(world_t *world){
    printf("Avant : ");
    print_sprite(getmissile(world));
    printf("Apres : ");
    avance_missile(world);
    print_sprite(getmissile(world));
}

void test_avance_missile(){
    world_t world;
    init_data(&world);
    test_avance_missile_param(&world);
    printf("\n");
}

int main(int argc, char* argv[]){
    printf("test_init_sprite\n");
    test_init_sprite();
    
    printf("test_vaisseau_depasse_bords\n");
    test_vaisseau_depasse_bords();

    printf("test_ennemi_depasse_bas\n");
    test_ennemi_depasse_bas();

    printf("test_sprites_collide\n");
    test_sprites_collide();

    printf("test_reset_enemi\n");
    test_reset_enemi();

    printf("test_score");
    test_score();

    printf("test_missile_depasse_haut\n");
    test_missile_depasse_haut();

    printf("test_handle_missiles_collide\n");
    test_handle_missiles_collide();

    printf("test_init_enemies\n");
    test_init_enemies();

    printf("test_handle_vaisseau_collide\n");
    test_handle_vaisseau_collide();

    printf("test_update_enemies\n");
    test_update_enemies();

    printf("test_heal\n");
    test_heal();

    printf("test_take_dmg\n");
    test_take_dmg();

    printf("test_update_enemies\n");
    test_update_enemies();

    printf("test_compute_game\n");
    test_compute_game();

    printf("test_compute_lives\n");
    test_compute_lives();

    printf("test_avance_missile\n");
    test_avance_missile();
    return EXIT_SUCCESS;
}
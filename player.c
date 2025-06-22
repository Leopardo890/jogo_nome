#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "player.h"

player *boss_creat(tela *tela, int side_x, int side_y, int hp, int x, int y){
	player *new_square = (player*) malloc(sizeof(player));
	new_square->side_x = side_x;	
	new_square->side_y = side_y;																												//Insere o tamanho do lado de um quadrado (!)
	new_square->x = x;																															//Insere a posição inicial central de X (!)
	new_square->y = y - side_y;																														//Insere a posição inicial central de Y (!)
	new_square->face = 1;
	new_square->hp = hp;
	new_square->kill = 0;
	new_square->controle = joystick_create();
	new_square->fire = pistol_create();
	new_square->aparencia = malloc(sizeof(ALLEGRO_BITMAP*)*20);

	new_square->hitbox = malloc(sizeof(hitbox));
	new_square->hitbox->x1 = x + tela->font;
	new_square->hitbox->x2 = x*2 + tela->font;
	new_square->hitbox->y1 = y/2;

	new_square->aparencia[0] = al_load_bitmap("sprites/inimigos/boss/1 Characters/3 Cyborg/Idle1.png");
	new_square->aparencia[1] = al_load_bitmap("sprites/inimigos/boss/1 Characters/3 Cyborg/Idle2.png");
	new_square->aparencia[2] = al_load_bitmap("sprites/inimigos/boss/1 Characters/3 Cyborg/Jump1.png");
	new_square->aparencia[3] = al_load_bitmap("sprites/inimigos/boss/1 Characters/3 Cyborg/Jump2.png");
	new_square->aparencia[4] = al_load_bitmap("sprites/inimigos/boss/1 Characters/3 Cyborg/Run1.png");
	new_square->aparencia[5] = al_load_bitmap("sprites/inimigos/boss/1 Characters/3 Cyborg/Run2.png");
	new_square->aparencia[6] = al_load_bitmap("sprites/inimigos/boss/1 Characters/3 Cyborg/Sitdown1.png");
	new_square->aparencia[7] = al_load_bitmap("sprites/inimigos/boss/1 Characters/3 Cyborg/Sitdown2.png");
	new_square->aparencia[8] = al_load_bitmap("sprites/inimigos/boss/1 Characters/3 Cyborg/Walk1.png");
	new_square->aparencia[9] = al_load_bitmap("sprites/inimigos/boss/1 Characters/3 Cyborg/Walk2.png");
	new_square->aparencia[10] = al_load_bitmap("sprites/inimigos/boss/1 Characters/3 Cyborg/Idle1_left.png");
	new_square->aparencia[11] = al_load_bitmap("sprites/inimigos/boss/1 Characters/3 Cyborg/morre.png");
	new_square->aparencia[12] = al_load_bitmap("sprites/inimigos/boss/1 Characters/3 Cyborg/morre_left.png");
	new_square->aparencia[13] = al_load_bitmap("sprites/inimigos/boss/1 Characters/3 Cyborg/Jump1_left.png");
	new_square->aparencia[14] = al_load_bitmap("sprites/inimigos/boss/3 Hands/3 Cyborg/4.png");
	new_square->aparencia[15] = al_load_bitmap("sprites/inimigos/boss/3 Hands/3 Cyborg/4_left.png");
	new_square->aparencia[16] = al_load_bitmap("sprites/inimigos/boss/3 Hands/3 Cyborg/1.png");
	new_square->aparencia[17] = al_load_bitmap("sprites/inimigos/boss/3 Hands/3 Cyborg/1_left.png");
	new_square->aparencia[18] = al_load_bitmap("sprites/inimigos/boss/4 Shoot_effects/9_1.png");
	new_square->aparencia[19] = al_load_bitmap("sprites/inimigos/boss/4 Shoot_effects/9_1_left.png");

	return new_square;
}

void boss_shot(tela *tela, player *boss, player *personagem, camera *camera){
	bullet *shot;

	if(boss->face == 1) shot = pistol_shot_boss(tela, boss->x + boss->side_x/4, boss->y + boss->side_y/1.8, 1, boss->fire);
	else if(boss->face == 2) shot = pistol_shot_boss(tela, boss->x + boss->side_x/2, boss->y + boss->side_y/1.8, 2, boss->fire);

	if(shot) boss->fire->shots = shot;
}

player* inimigo_crate(tela *tela, int side_x, int side_y, int hp, int x, int y){

	player *new_square = (player*) malloc(sizeof(player));
	new_square->side_x = side_x;	
	new_square->side_y = side_y;																												//Insere o tamanho do lado de um quadrado (!)
	new_square->x = x;																															//Insere a posição inicial central de X (!)
	new_square->y = y - side_y;																														//Insere a posição inicial central de Y (!)
	new_square->face = 1;
	new_square->hp = hp;
	new_square->kill = 0;
	new_square->controle = joystick_create();
	new_square->fire = pistol_create();
	new_square->aparencia = malloc(sizeof(ALLEGRO_BITMAP*)*16);

	new_square->hitbox = malloc(sizeof(hitbox));
	new_square->hitbox->x1 = x + tela->font;
	new_square->hitbox->x2 = x*2 + tela->font;
	new_square->hitbox->y1 = y/2;
	new_square->hitbox->y2 = y/2 + tela->font;
	new_square->aparencia[0] = al_load_bitmap("sprites/inimigos/bandidos/Raider_2/Attack.png");
	new_square->aparencia[1] = al_load_bitmap("sprites/inimigos/bandidos/Raider_2/Charge_2.png");
	new_square->aparencia[2] = al_load_bitmap("sprites/inimigos/bandidos/Raider_2/Dead.png");
	new_square->aparencia[3] = al_load_bitmap("sprites/inimigos/bandidos/Raider_2/Hurt.png");
	new_square->aparencia[4] = al_load_bitmap("sprites/inimigos/bandidos/Raider_2/Idle.png");
	new_square->aparencia[5] = al_load_bitmap("sprites/inimigos/bandidos/Raider_2/jump.png");
	new_square->aparencia[6] = al_load_bitmap("sprites/inimigos/bandidos/Raider_2/Recharge.png");
	new_square->aparencia[7] = al_load_bitmap("sprites/inimigos/bandidos/Raider_2/Run.png");
	new_square->aparencia[8] = al_load_bitmap("sprites/inimigos/bandidos/Raider_2/Shot_1.png");
	new_square->aparencia[9] = al_load_bitmap("sprites/inimigos/bandidos/Raider_2/Shot_2.png");
	new_square->aparencia[10] = al_load_bitmap("sprites/inimigos/bandidos/Raider_2/Walk.png");
	new_square->aparencia[11] = al_load_bitmap("sprites/inimigos/bandidos/Raider_2/Charge_2_left.png");
	new_square->aparencia[12] = al_load_bitmap("sprites/inimigos/bandidos/Raider_2/Idle_left.png");
	new_square->aparencia[13] = al_load_bitmap("sprites/inimigos/bandidos/Raider_2/Shot_2_left.png");
	new_square->aparencia[14] = al_load_bitmap("sprites/inimigos/bandidos/Raider_2/Dead_left.png");
	new_square->aparencia[15] = al_load_bitmap("sprites/inimigos/bandidos/Raider_2/Shot_1_left.png");

	return new_square;
}

void inimigo_shot(tela *tela, player *inimigo, player *personagem, camera *camera){
	bullet *shot;

	if(!inimigo->controle->down){
		if(inimigo->face == 1) shot = pistol_shot_k(tela, inimigo->x + inimigo->side_x/4, inimigo->y + inimigo->side_y/2.8, 1, inimigo->fire);
		else if(inimigo->face == 2) shot = pistol_shot_k(tela, inimigo->x + inimigo->side_x/2, inimigo->y + inimigo->side_y/2.8, 2, inimigo->fire);
	} else {
		if(inimigo->face == 1) shot = pistol_shot_k(tela, inimigo->x + inimigo->side_x/4, inimigo->y + inimigo->side_y/1.9, 1, inimigo->fire);
		else if(inimigo->face == 2) shot = pistol_shot_k(tela, inimigo->x + inimigo->side_x/2, inimigo->y + inimigo->side_y/1.9, 2, inimigo->fire);
	}

	if(shot) inimigo->fire->shots = shot;
}

player* player_create_person1(tela *tela, int side_x, int side_y, int hp, int x, int y){																//Verifica se a posição inicial é válida; caso não seja, retorna NULL (!)
	
	player *new_square = (player*) malloc(sizeof(player));																						//Aloca memória na heap para um novo quadrado (!)
	new_square->side_x = side_x;	
	new_square->side_y = side_y;																												//Insere o tamanho do lado de um quadrado (!)
	new_square->x = x;																															//Insere a posição inicial central de X (!)
	new_square->y = y - side_y;																															//Insere a posição inicial central de Y (!)
	new_square->face = 2;
	new_square->hp = hp;
	new_square->kill = 0;
	new_square->fire = pistol_create();
	new_square->controle = joystick_create();
	new_square->aparencia = malloc(sizeof(ALLEGRO_BITMAP*)*19);

	new_square->hitbox = malloc(sizeof(hitbox));
	new_square->hitbox->x1 = x + 2*tela->font;
	new_square->hitbox->x2 = x + 3*tela->font;
	new_square->hitbox->y1 = y - side_y/2;
	new_square->hitbox->y2 = y;
	new_square->aparencia[0] = al_load_bitmap("sprites/personagem/mago/Fire_vizard/Attack_1.png");
	new_square->aparencia[1] = al_load_bitmap("sprites/personagem/mago/Fire_vizard/Attack_2.png");
	new_square->aparencia[2] = al_load_bitmap("sprites/personagem/mago/Fire_vizard/Charge.png");
	new_square->aparencia[3] = al_load_bitmap("sprites/personagem/mago/Fire_vizard/Dead.png");
	new_square->aparencia[4] = al_load_bitmap("sprites/personagem/mago/Fire_vizard/Fireball.png");
	new_square->aparencia[5] = al_load_bitmap("sprites/personagem/mago/Fire_vizard/Flame_jet.png");
	new_square->aparencia[6] = al_load_bitmap("sprites/personagem/mago/Fire_vizard/Hurt_right.png");
	new_square->aparencia[7] = al_load_bitmap("sprites/personagem/mago/Fire_vizard/Idle.png");
	new_square->aparencia[8] = al_load_bitmap("sprites/personagem/mago/Fire_vizard/Jump.png");
	new_square->aparencia[9] = al_load_bitmap("sprites/personagem/mago/Fire_vizard/Run.png");
	new_square->aparencia[10] = al_load_bitmap("sprites/personagem/mago/Fire_vizard/Walk_right.png");
	new_square->aparencia[11] = al_load_bitmap("sprites/personagem/mago/Fire_vizard/Walk_left.png");
	new_square->aparencia[12] = al_load_bitmap("sprites/personagem/mago/Fire_vizard/Hurt_left.png");
	new_square->aparencia[13] = al_load_bitmap("sprites/personagem/mago/Fire_vizard/Idle_left.png");
	new_square->aparencia[14] = al_load_bitmap("sprites/personagem/mago/Fire_vizard/Jump_left.png");
	new_square->aparencia[15] = al_load_bitmap("sprites/personagem/mago/Fire_vizard/Fireball_left.png");
	new_square->aparencia[16] = al_load_bitmap("sprites/personagem/mago/Fire_vizard/Charge_left.png");
	new_square->aparencia[17] = al_load_bitmap("sprites/personagem/mago/Fire_vizard/Charge_cima.png");
	new_square->aparencia[18] = al_load_bitmap("sprites/personagem/mago/Fire_vizard/Dead_left.png");

	return new_square;																															//Retorna o novo quadrado (!)
}

void player_shot(tela *tela, player *element, camera *camera){
	bullet *shot;

	if(element->controle->down){
		if(element->face == 1) shot = pistol_shot_fire(tela, element->x + element->side_x/2, element->y + element->side_y/1.8, element->face, element->fire);
		else if(element->face == 2) shot = pistol_shot_fire(tela, element->x + element->side_x/5.5, element->y + element->side_y/1.8, element->face, element->fire);
		else if(element->face == 3) shot = pistol_shot_fire(tela, element->x + element->side_x/4.5, element->y + element->side_y/2, element->face, element->fire);
	} else {
		if(element->face == 1) shot = pistol_shot_fire(tela, element->x + element->side_x/2, element->y + element->side_y/2.5, element->face, element->fire);
		else if(element->face == 2) shot = pistol_shot_fire(tela, element->x + element->side_x/5.5, element->y + element->side_y/2.5, element->face, element->fire);
		else if(element->face == 3) shot = pistol_shot_fire(tela, element->x + element->side_x/4.5, element->y + element->side_y/2, element->face, element->fire);
	}

	if(shot) element->fire->shots = shot;
}

void player_move(player *element, int steps, int trajectory, int max_x, int max_y){					//Implementação da função "square_move" (!)

	if (trajectory == 0){ if (element->x - steps*PLAYER_STEP >= 0) element->x = element->x - steps*PLAYER_STEP;} 				//Verifica se a movimentação para a esquerda é desejada e possível; se sim, efetiva a mesma
	else if (trajectory == 1){ if (element->x + element->side_x + steps*PLAYER_STEP <= max_x) element->x = element->x + steps*PLAYER_STEP;}	//Verifica se a movimentação para a direita é desejada e possível; se sim, efetiva a mesma

}

void player_destroy(player *element){	
	free(element->hitbox);
	joystick_destroy(element->controle);
	for(int i = 0; !element->aparencia; i++)	
		al_destroy_bitmap(element->aparencia[i]);																								
	free(element->aparencia);
	pistol_destroy(element->fire);
	free(element);																																//Libera a memória do quadrado na heap (!)
}

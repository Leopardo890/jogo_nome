#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "player.h"

player* player_create_person1(int side_x, int side_y, int x, int y){																//Verifica se a posição inicial é válida; caso não seja, retorna NULL (!)
	
	player *new_square = (player*) malloc(sizeof(player));																						//Aloca memória na heap para um novo quadrado (!)
	new_square->side_x = side_x;	
	new_square->side_y = side_y;																												//Insere o tamanho do lado de um quadrado (!)
	new_square->x = x;																															//Insere a posição inicial central de X (!)
	new_square->y = y - side_y;																															//Insere a posição inicial central de Y (!)
	new_square->controle = joystick_create();
	new_square->aparencia = malloc(sizeof(ALLEGRO_BITMAP*)*15);
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

	return new_square;																															//Retorna o novo quadrado (!)
}

void player_move(player *element, int steps, int trajectory, int max_x, int max_y){					//Implementação da função "square_move" (!)

	if (trajectory == 0){ if (element->x - steps*PLAYER_STEP >= 0) element->x = element->x - steps*PLAYER_STEP;} 				//Verifica se a movimentação para a esquerda é desejada e possível; se sim, efetiva a mesma
	else if (trajectory == 1){ if (element->x + element->side_x + steps*PLAYER_STEP <= max_x) element->x = element->x + steps*PLAYER_STEP;}	//Verifica se a movimentação para a direita é desejada e possível; se sim, efetiva a mesma
}

void player_destroy(player *element){	
	joystick_destroy(element->controle);
	for(int i = 0; !element->aparencia; i++)	
		al_destroy_bitmap(element->aparencia[i]);																								
	free(element->aparencia);
	free(element);																																//Libera a memória do quadrado na heap (!)
}

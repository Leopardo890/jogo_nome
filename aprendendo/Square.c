#include <stdlib.h>
#include "Square.h"

square* square_create(unsigned char side_x, unsigned char side_y, unsigned short x, 
			unsigned short y, unsigned short max_x, unsigned short max_y){						//Implementação da função "square_create" (!)

	if ((x < 0) || (x + side_x > max_x) || (y < 0) || (y + side_y > max_y)) return NULL;										//Verifica se a posição inicial é válida; caso não seja, retorna NULL (!)

	square *new_square = (square*) malloc(sizeof(square));																						//Aloca memória na heap para um novo quadrado (!)
	new_square->side_x = side_x;	
	new_square->side_y = side_y;																												//Insere o tamanho do lado de um quadrado (!)
	new_square->x = x;																															//Insere a posição inicial central de X (!)
	new_square->y = y;																															//Insere a posição inicial central de Y (!)
	new_square->controle = joystick_create();
	return new_square;																															//Retorna o novo quadrado (!)
}

void square_move(square *element, unsigned char steps, unsigned char trajectory, unsigned short max_x, unsigned short max_y){					//Implementação da função "square_move" (!)

	if (trajectory == 0){ if (element->x - steps*SQUARE_STEP >= 0) element->x = element->x - steps*SQUARE_STEP;} 				//Verifica se a movimentação para a esquerda é desejada e possível; se sim, efetiva a mesma
	else if (trajectory == 1){ if (element->x + element->side_x + steps*SQUARE_STEP <= max_x) element->x = element->x + steps*SQUARE_STEP;}	//Verifica se a movimentação para a direita é desejada e possível; se sim, efetiva a mesma
	else if (trajectory == 2){ if (element->y - steps*SQUARE_STEP >= 0) element->y = element->y - steps*SQUARE_STEP;}		//Verifica se a movimentação para cima é desejada e possível; se sim, efetiva a mesma
	else if (trajectory == 3){ if (element->y + element->side_y + steps*SQUARE_STEP <= max_y) element->y = element->y + steps*SQUARE_STEP;}	//Verifica se a movimentação para baixo é desejada e possível; se sim, efetiva a mesma
}

void square_destroy(square *element){	
	joystick_destroy(element->controle);																										//Implementação da função "square_destroy" (!)
	free(element);																																//Libera a memória do quadrado na heap (!)
}

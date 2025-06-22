#include <stdlib.h>
#include "Bullet.h"

bullet* bullet_create_cam(tela *tela, unsigned short x, unsigned short y, 
	unsigned char trajectory, bullet *next){			//Implementação da função "bullet_create"

	bullet *new_bullet = (bullet*) malloc(sizeof(bullet));													//Aloca memória na heap para uma instância de projétil
	if (!new_bullet) return NULL;																			//Verifica o sucesso da alocação de memória; retorna NULL em caso de falha
	new_bullet->x = x;																						//Armazena a posição X informada
	new_bullet->y = y;																						//Armazena a posição Y informada
	new_bullet->trajectory = trajectory;																	//Armazena a trajetória informada
	new_bullet->next = (struct bullet*) next;																//Armazena o próximo projétil informado
	new_bullet->hitbox = malloc(sizeof(hitbox));
	new_bullet->hitbox->x1 = x + 1.8*tela->font;
	new_bullet->hitbox->x2 = x + 3*tela->font;
	new_bullet->hitbox->y1 = y + 1.2*tela->font;
	new_bullet->hitbox->y2 = y + 2*tela->font;
	return new_bullet;																						//Retorna a instância criada de projétil
}

bullet* bullet_create_fogo(tela *tela, unsigned short x, unsigned short y, 
	unsigned char trajectory, bullet *next){			//Implementação da função "bullet_create"

	bullet *new_bullet = (bullet*) malloc(sizeof(bullet));													//Aloca memória na heap para uma instância de projétil
	if (!new_bullet) return NULL;																			//Verifica o sucesso da alocação de memória; retorna NULL em caso de falha
	new_bullet->x = x;																						//Armazena a posição X informada
	new_bullet->y = y;																						//Armazena a posição Y informada
	new_bullet->trajectory = trajectory;																	//Armazena a trajetória informada
	new_bullet->next = (struct bullet*) next;																//Armazena o próximo projétil informado
	new_bullet->hitbox = malloc(sizeof(hitbox));
	new_bullet->hitbox->x1 = x + 1.8*tela->font;
	new_bullet->hitbox->x2 = x + 3*tela->font;
	new_bullet->hitbox->y1 = y + 1.2*tela->font;
	new_bullet->hitbox->y2 = y + 2*tela->font;
	return new_bullet;																						//Retorna a instância criada de projétil
}

bullet* bullet_create_muni(tela *tela, unsigned short x, unsigned short y, 
	unsigned char trajectory, bullet *next){			//Implementação da função "bullet_create"

	bullet *new_bullet = (bullet*) malloc(sizeof(bullet));													//Aloca memória na heap para uma instância de projétil
	if (!new_bullet) return NULL;																			//Verifica o sucesso da alocação de memória; retorna NULL em caso de falha
	new_bullet->x = x;																						//Armazena a posição X informada
	new_bullet->y = y;																						//Armazena a posição Y informada
	new_bullet->trajectory = trajectory;																	//Armazena a trajetória informada
	new_bullet->next = (struct bullet*) next;																//Armazena o próximo projétil informado
	new_bullet->hitbox = malloc(sizeof(hitbox));
	new_bullet->hitbox->x1 = x + tela->font;
	new_bullet->hitbox->x2 = x*2 + tela->font;
	new_bullet->hitbox->y1 = y/2;
	new_bullet->hitbox->y2 = y/2 + tela->font/2;
	return new_bullet;																						//Retorna a instância criada de projétil
}



void bullet_move(bullet *elements){																			//Implementação da função "bullet_move"

	for (bullet *index = elements; index != NULL; index = (bullet*) index->next){							//Para cada projétil presente na lista de projéteis informada
		if (index->trajectory == 1) index->x = index->x - BULLET_MOVE;											//Se a trajetória for para a esquerda, movimenta um passo à esquerda
		else if(index->trajectory == 2)index->x = index->x + BULLET_MOVE;																//Se a trajetória for para a direita, movimenta um passo à direita
		else if(index->trajectory == 3)index->y = index->y - BULLET_MOVE;
	}
}

void bullet_destroy(bullet *element){																		//Implementação da função "bullet_destroy"

	free(element->hitbox);
	free(element);																							//Libera a memória da instância de projétil
}
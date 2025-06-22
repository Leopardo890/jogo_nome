#ifndef __BULLET__ 																																//Guardas de inclusão (!)
#define __BULLET__																																//Guardas de inclusão (!)

#include "tela.h"

#define BULLET_MOVE 5

typedef struct{
	int x1;
	int x2;
	int y1;
	int y2;
} hitbox;

typedef struct {																																//Definição da estrutura de um pŕojétil (!)
	unsigned short x;																															//Local, no eixo x, onde se localiza a bala (!)
	unsigned short y;																															//Local, no eixo y, onde se localiza a bala (!)
	unsigned char trajectory;																													//Trajetória da bala
	hitbox *hitbox;
	struct bullet *next; 																														//Próxima bala, se houver, formando uma lista encadeada (!)
} bullet;						

bullet* bullet_create_cam(tela *tela, unsigned short x, unsigned short y, 
	unsigned char trajectory, bullet *next);

bullet* bullet_create_fogo(tela *tela, unsigned short x, unsigned short y, 
	unsigned char trajectory, bullet *next);												//Protótipo da função de criação de uma bala (!)
void bullet_move(bullet *elements);																												//Protótipo da função de movimentação de uma bala (!)	
void bullet_destroy(bullet *element);																											//Protótipo da função de destruição de uma bala (!)

bullet* bullet_create_muni(tela *tela, unsigned short x, unsigned short y, 
	unsigned char trajectory, bullet *next);
#endif																																			//Guardas de inclusão (!)
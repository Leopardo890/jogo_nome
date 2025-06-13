#ifndef __PLAYER__ 																												//Guardas de inclusão (!)
#define __PLAYER__																												//Guardas de inclusão (!)																										//Quantidade de pixels que um quadrado se move por passo (!)

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#include "Joystick.h"

#define PLAYER_STEP 2																											//Tamanho, em pixels, de um passo do quadrado (!)

typedef struct {																												//Definição da estrutura de um quadrado (!)
	int side_x;
	int side_y;																											//Tamanmho da lateral de um quadrado (!)
	int x;																											//Posição X do centro do quadrado (!)
	int y;																											//Posição Y do centro do quadrado (!)
	ALLEGRO_BITMAP **aparencia;
	joystick *controle;
} player;																														//Definição do nome da estrutura (!)

player* player_create_person1(int side_x, int side_y,
		int x, int y);		
//0 - left 1 - right
void player_move(player *element, int steps, int trajectory, int max_x, int max_y);	//Protótipo da função de movimentação de um quadrado (!)
void player_destroy(player *element);																							//Protótipo da função de destruição de um quadrado (!)

#endif																															//Guardas de inclusão (!)
#ifndef __PLAYER__ 																												//Guardas de inclusão (!)
#define __PLAYER__																												//Guardas de inclusão (!)																										//Quantidade de pixels que um quadrado se move por passo (!)

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#include "Joystick.h"
#include "Pistol.h"
#include "tela.h"

#define PLAYER_STEP 2																											//Tamanho, em pixels, de um passo do quadrado (!)

typedef struct {																												//Definição da estrutura de um quadrado (!)
	int side_x;
	int side_y;																											//Tamanmho da lateral de um quadrado (!)
	int face;
	int hp;
	int kill;
	int x;																											//Posição X do centro do quadrado (!)
	int y;
	float vel_y;
    char chao;
    char pulando;																											//Posição Y do centro do quadrado (!)
	hitbox *hitbox;
	ALLEGRO_BITMAP **aparencia;
	joystick *controle;
	pistol *fire;
} player;																														//Definição do nome da estrutura (!)

player *boss_creat(tela *tela, int side_x, int side_y, int hp, int x, int y);

void boss_shot(tela *tela, player *boss, player *personagem, camera *camera);

player* player_create_person1(tela *tela, int side_x, int side_y, int hp,int x, int y);

player* inimigo_crate(tela *tela, int side_x, int side_y, int hp, int x, int y);

void inimigo_shot(tela *tela, player *inimigo, player *personagem, camera *camera);

void player_shot(tela *tela, player *element, camera *camera);

//0 - left 1 - right
void player_move(player *element, int steps, int trajectory, int max_x, int max_y);	//Protótipo da função de movimentação de um quadrado (!)

void player_destroy(player *element);																							//Protótipo da função de destruição de um quadrado (!)

#endif																															//Guardas de inclusão (!)
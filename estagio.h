#ifndef __ESTADO__ 																																//Guardas de inclusão (!)
#define __ESTADO__		

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "tela.h"
#include "player.h"
#include "jogo.h"

int tela_pause(ALLEGRO_EVENT_QUEUE * event_queue, ALLEGRO_FONT *font, tela *tela);

int tela_fim(ALLEGRO_EVENT_QUEUE * event_queue,
    ALLEGRO_BITMAP * fundo_fim, ALLEGRO_FONT *font, tela *tela, player *personagem);

int tela_ganhou(ALLEGRO_EVENT_QUEUE * event_queue,
    ALLEGRO_BITMAP * fundo_fim, ALLEGRO_FONT *font, tela *tela);

int tela_selecao_fase(ALLEGRO_EVENT_QUEUE * event_queue,
    ALLEGRO_BITMAP * fundo_selecao, ALLEGRO_FONT *font, tela *tela, int *fase);

int tela_selecao(ALLEGRO_EVENT_QUEUE * event_queue,
    ALLEGRO_BITMAP * fundo_selecao, ALLEGRO_FONT *font, tela *tela, int *personagem);

int tela_config(ALLEGRO_EVENT_QUEUE * event_queue, ALLEGRO_DISPLAY * display,
    ALLEGRO_BITMAP * inicio, ALLEGRO_FONT *font, tela *tela);

int tela_de_inicio(ALLEGRO_EVENT_QUEUE * event_queue,
    ALLEGRO_BITMAP * inicio, ALLEGRO_FONT *font, tela *tela);

int tela_fase1(ALLEGRO_EVENT_QUEUE * event_queue,
    ALLEGRO_BITMAP * fundo_jogo, ALLEGRO_FONT *font, tela *tela, player *personagem);

int tela_boss(ALLEGRO_EVENT_QUEUE * event_queue,
    ALLEGRO_BITMAP * fundo_boss, ALLEGRO_FONT *font, tela *tela, player *personagem);

#endif
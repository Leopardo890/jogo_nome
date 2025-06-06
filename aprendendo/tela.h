#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include <stdlib.h>

#include "Square.h"

typedef struct {

    int y;
    int x;
    int font;
    int player;

} tela;

typedef struct {

    unsigned char display;
    unsigned char tela_inicio;
    unsigned char tela_config;
    unsigned char jogo;
    unsigned char full;
    unsigned char selecao;
    unsigned char main;
    unsigned char personagem;

} flag;

tela *create_tela(int x, int y);

tela *muda_tela(tela *tela, int x, int y);

void destroi_tela(tela *tela);

flag *create_flag();

flag *muda_flag(flag *flag, unsigned char display, unsigned char tela_inicio, 
            unsigned char tela_config, unsigned char jogo, 
            unsigned char full, unsigned char selecao,
            unsigned char main, unsigned char personagem);

void destroi_flag(flag *flag);

void tela_jogo(ALLEGRO_EVENT_QUEUE * event_queue, ALLEGRO_EVENT_QUEUE *fila_eventos, 
    ALLEGRO_BITMAP * fundo_jogo, ALLEGRO_FONT *font, tela *tela, flag *flag);

void tela_selecao(ALLEGRO_EVENT_QUEUE * event_queue, ALLEGRO_EVENT_QUEUE *fila_eventos, 
    ALLEGRO_BITMAP * fundo_selecao, ALLEGRO_FONT *font, tela *tela, flag *flag);

void tela_config(ALLEGRO_EVENT_QUEUE * event_queue, ALLEGRO_EVENT_QUEUE *fila_eventos, 
    ALLEGRO_BITMAP * inicio, ALLEGRO_FONT *font, tela *tela, flag *flag);

void tela_de_inicio(ALLEGRO_EVENT_QUEUE * event_queue, ALLEGRO_EVENT_QUEUE *fila_eventos, 
    ALLEGRO_BITMAP * inicio, ALLEGRO_FONT *font, ALLEGRO_BITMAP *fundo, tela *tela, flag *flag);
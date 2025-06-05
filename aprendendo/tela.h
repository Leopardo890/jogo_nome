#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#include <stdlib.h>

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

} flag;

tela *create_tela(int x, int y);

tela *muda_tela(tela *tela, int x, int y);

void destroi_tela(tela *tela);

flag *create_flag(unsigned char display, unsigned char tela_inicio, 
            unsigned char tela_config, unsigned char jogo, 
            unsigned char full, unsigned char selecao);

flag *muda_flag(flag *flag, unsigned char display, unsigned char tela_inicio, 
            unsigned char tela_config, unsigned char jogo, 
            unsigned char full, unsigned char selecao);

void destroi_flag(flag *flag);

void atualiza_tela(ALLEGRO_EVENT_QUEUE * event_queue, tela *tela);

void tela_selecao(ALLEGRO_EVENT_QUEUE * event_queue, ALLEGRO_EVENT_QUEUE *fila_eventos, 
    ALLEGRO_BITMAP * fundo_selecao, ALLEGRO_FONT *font, tela *tela, flag *flag);

void tela_config(ALLEGRO_EVENT_QUEUE * event_queue, ALLEGRO_EVENT_QUEUE *fila_eventos, 
    ALLEGRO_BITMAP * inicio, ALLEGRO_FONT *font, tela *tela, flag *flag);

void tela_de_inicio(ALLEGRO_EVENT_QUEUE * event_queue, ALLEGRO_EVENT_QUEUE *fila_eventos, 
    ALLEGRO_BITMAP * inicio, ALLEGRO_FONT *font, ALLEGRO_BITMAP *fundo, tela *tela, flag *flag);
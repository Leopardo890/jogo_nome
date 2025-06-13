#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "tela.h"
#include "player.h"

int tela_selecao(ALLEGRO_EVENT_QUEUE * event_queue,
    ALLEGRO_BITMAP * fundo_selecao, ALLEGRO_FONT *font, tela *tela, int *personagem);

int tela_config(ALLEGRO_EVENT_QUEUE * event_queue, ALLEGRO_DISPLAY * display,
    ALLEGRO_BITMAP * inicio, ALLEGRO_FONT *font, tela *tela);

int tela_de_inicio(ALLEGRO_EVENT_QUEUE * event_queue,
    ALLEGRO_BITMAP * inicio, ALLEGRO_FONT *font, tela *tela);

int tela_fase1(ALLEGRO_EVENT_QUEUE * event_queue,
    ALLEGRO_BITMAP * fundo_jogo, ALLEGRO_FONT *font, tela *tela, player *personagem);
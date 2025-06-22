#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#include <stdio.h>

#include "tela.h"
#include "player.h"

typedef struct {

    char frame_right;
    char frame_left;
    char cont;

} flag;

flag *flag_creat(char frame_left, char frame_right, char const);

int jogo(ALLEGRO_EVENT_QUEUE * event_queue,
    ALLEGRO_BITMAP * fundo_jogo, ALLEGRO_FONT *font, tela *tela, player *personagem);

void fundo(tela *tela, camera *camera, ALLEGRO_BITMAP *fundo_jogo);

void evento_click(tela *tela, ALLEGRO_EVENT event, player *personagem);

void atualiza_posicao(ALLEGRO_EVENT event, player *personagem, tela *tela, camera *camera, int limTela);

void atualiza_vida(ALLEGRO_EVENT event, player *personagem, ALLEGRO_BITMAP *coracao, tela *tela, camera *camera);

unsigned char check_kill(player *killer, player *victim);

void parado(ALLEGRO_EVENT event, tela *tela, player *personagem, camera *camera, flag *parado);

void parado_agachado(tela *tela, player *personagem, camera *camera);

void andando(tela *tela, ALLEGRO_EVENT event, player *personagem, camera *camera, flag *andando);

void andando_agachado(tela *tela, ALLEGRO_EVENT event, player *personagem, camera *camera, flag *agachado);

void pulando(tela *tela, ALLEGRO_EVENT event, player *personagem, camera *camera, flag *pulando);

void atirar(ALLEGRO_EVENT event, player *personagem, camera *camera, flag *atirando);

void tiro(ALLEGRO_EVENT event, player *personagem, tela *tela, camera *camera, flag *tiro);

unsigned char player_morre(ALLEGRO_EVENT event, player *personagem, camera *camera, flag *morre);

void inimigo_parado(tela *tela, ALLEGRO_EVENT event, player *inimigo, camera *camera, flag *parado);

void inimigo_ataca(ALLEGRO_EVENT event, player *inimigo, tela *tela, camera *camera, flag *tiro);

void inimigo_atirando(ALLEGRO_EVENT event, player *inimigo, camera *camera, flag *atirando);

unsigned char inimigo_morre(ALLEGRO_EVENT event, player *inimigo, camera *camera, flag *parado);

void inimigo_agachado(tela *tela, ALLEGRO_EVENT event, player *inimigo, camera *camera, flag *agachado);

int jogo_boss(ALLEGRO_EVENT_QUEUE * event_queue,
    ALLEGRO_BITMAP * fundo_boss, ALLEGRO_FONT *font, tela *tela, player *personagem);

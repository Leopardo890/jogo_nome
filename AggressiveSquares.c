#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#include <stdio.h>

#include "player.h"
#include "tela.h"
#include "estagio.h"

int main (){

	al_init();
	al_init_primitives_addon();	
	al_init_font_addon();
	al_init_image_addon();
	al_install_keyboard();
	al_init_ttf_addon();
	al_install_mouse();

	// x -> 640 800 1024 1920
	// y -> 360 450 576 1080
	tela *tela = create_tela(640, 360);

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);

	ALLEGRO_BITMAP * inicio;
	ALLEGRO_BITMAP *fundo_config;
	ALLEGRO_BITMAP *fundo_selecao;

	ALLEGRO_FONT *font;

	//lista de eventos separada para o mouse
	ALLEGRO_EVENT_QUEUE *fila_eventos = al_create_event_queue();
    al_register_event_source(fila_eventos, al_get_mouse_event_source());

	//lista com os outros eventos
	ALLEGRO_EVENT_QUEUE * event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source() );
	al_start_timer(timer);

	//al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	ALLEGRO_DISPLAY * display = al_create_display(tela->x, tela->y);
	
	al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
	//configuracao de tamanho dinamico
	inicio = al_load_bitmap("sprites/fundo/fundo_inicio.png");
	fundo_config = al_load_bitmap("sprites/fundo/fundo_config.png");
	fundo_selecao = al_load_bitmap("sprites/fundo/fundo_selecao.png");

	al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);

	al_register_event_source(event_queue, al_get_display_event_source(display));

	player *personagem;
	int escolha = 0;
	int estado = 1;

	//controla os estados
	while(1){

		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);

		font = al_load_font("fonte/lead_coat/leadcoat.ttf", tela->font, 0);
	
		if(estado == 0) break;
		if(estado == 1)estado = tela_de_inicio(event_queue, inicio, font, tela);
		if(estado == 2)estado = tela_config(event_queue, display, fundo_config, font, tela);
		if(estado == 3)estado = tela_selecao(event_queue, fundo_selecao, font, tela, &escolha);
		if(estado == 4){
			if(escolha == 1){
				personagem = player_create_person1(tela->font*6, tela->font*6, 
					tela->x/2 - tela->font*3, tela->y - tela->font);
			}
			estado = tela_fase1(event_queue, fundo_config, font, tela, personagem);
		}
	}

	al_destroy_display(display);
	destroi_tela(tela);
	al_destroy_bitmap(fundo_selecao);
	al_destroy_bitmap(fundo_config);
	al_destroy_font(font);
	al_destroy_bitmap(inicio);
	al_destroy_event_queue(event_queue);

	return 0;
}
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#include <stdio.h>

#include "Square.h"
#include "tela.h"

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
	ALLEGRO_BITMAP *fundo;
	ALLEGRO_BITMAP *fundo_config;

	ALLEGRO_FONT *font;

	//lista de eventos separada para o mouse
	ALLEGRO_EVENT_QUEUE *fila_eventos = al_create_event_queue();
    al_register_event_source(fila_eventos, al_get_mouse_event_source());

	//lista com os outros eventos
	ALLEGRO_EVENT_QUEUE * event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source() );
	al_start_timer(timer);

	square *player;

	flag *flag = create_flag();
	flag->display = 1;

	while(flag->display){

		if(flag->full){
			al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
		}
		ALLEGRO_DISPLAY * display = al_create_display(tela->x, tela->y);
		
		al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
		//configuracao de tamanho dinamico
		if(tela->x == 640){
			inicio = al_load_bitmap("sprites/fundo_inicio/inicio(640).jpg");
			fundo = al_load_bitmap("sprites/fundo_jogo/fundo360.png");
			fundo_config = al_load_bitmap("sprites/fundo_confg/fundo_config(640).jpg");
		} else if (tela->x == 800){
			inicio = al_load_bitmap("sprites/fundo_inicio/inicio(800).jpg");
			fundo = al_load_bitmap("sprites/fundo_jogo/fundo450.png");
			fundo_config = al_load_bitmap("sprites/fundo_confg/fundo_config(800).jpg");
		} else if (tela->x == 1024){
			inicio = al_load_bitmap("sprites/fundo_inicio/inicio(1k).jpg");
			fundo = al_load_bitmap("sprites/fundo_jogo/fundo576.png");
			fundo_config = al_load_bitmap("sprites/fundo_confg/fundo_config(1024).jpg");
		} else if (tela->x == 1920){
			inicio = al_load_bitmap("sprites/fundo_inicio/inicio(4k).jpg");
			fundo = al_load_bitmap("sprites/fundo_jogo/fundo1080.png");
			fundo_config = al_load_bitmap("sprites/fundo_confg/fundo_config(1920).jpg");
		} else {
			inicio = al_load_bitmap("sprites/fundo_inicio/inicio(4k).jpg");
			al_draw_scaled_bitmap(inicio, 0, 0, 1920, 1080, 0, 0, tela->x, tela->y, 0);
			fundo = al_load_bitmap("sprites/fundo_jogo/fundo1080.png");
			al_draw_scaled_bitmap(fundo, 0, 0, 1920, 1080, 0, 0, tela->x, tela->y, 0);
			fundo_config = al_load_bitmap("sprites/fundo_confg/fundo_config(1920).jpg");
			al_draw_scaled_bitmap(fundo_config, 0, 0, 1920, 1080, 0, 0, tela->x, tela->y, 0);
		}
		font = al_load_font("sprites/fontes/grasping.ttf", tela->font, 0);

		al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);

		al_register_event_source(event_queue, al_get_display_event_source(display));

		flag->main = 1;
		//controla os estados
		while(flag->main){

			ALLEGRO_EVENT event;
			al_wait_for_event(event_queue, &event);

			//gerando uma tela de inicio
			tela_de_inicio(event_queue, fila_eventos, inicio, font, fundo_config, tela, flag);

			//gerando tela de selecao
			tela_selecao(event_queue, fila_eventos, fundo_config, font, tela, flag);

			tela_jogo(event_queue, fila_eventos, fundo, font, tela, flag);

			if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) break;

		}

		al_destroy_display(display);

	}

	destroi_flag(flag);
	destroi_tela(tela);
	square_destroy(player);
	al_destroy_bitmap(fundo);
	al_destroy_font(font);
	al_destroy_bitmap(inicio);
	al_destroy_event_queue(event_queue);

	return 0;
}
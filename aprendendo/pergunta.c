#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

// x -> 640 800 1024 1920
// y -> 360 450 575 1078

#define X_TAM 800
#define Y_TAM 450
#define FONT_TAM Y_TAM/12

int main (){

	al_init();
	al_init_primitives_addon();	
	al_init_font_addon();
	al_init_image_addon();
	al_install_keyboard();
	al_init_ttf_addon();
	al_install_mouse();

	ALLEGRO_DISPLAY * display = al_create_display(X_TAM, Y_TAM);
	al_set_window_title(display, "Here be Dragons!");

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);

	ALLEGRO_BITMAP * sprite = al_load_bitmap("./run.png");
	ALLEGRO_BITMAP * inicio;

	if(X_TAM == 640) inicio = al_load_bitmap("inicio(640).jpg");
	else if (X_TAM == 800) inicio = al_load_bitmap("inicio(800).jpg");
	else if (X_TAM == 1024) inicio = al_load_bitmap("inicio(1k).jpg");
	else inicio = al_load_bitmap("inicio(4k).jpg");

	ALLEGRO_BITMAP *button_inicio = al_create_bitmap(100, 50);

	ALLEGRO_FONT *font = al_load_font("grasping.ttf", FONT_TAM, 0);

	al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);

	ALLEGRO_EVENT_QUEUE * event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source() );
	al_start_timer(timer);

	int flag = 1;
	int config = 0;
	ALLEGRO_COLOR cor_button1 = al_map_rgb(0,0,0);
	ALLEGRO_COLOR cor_button2 = al_map_rgb(0,0,0);
	ALLEGRO_COLOR cor_button3 = al_map_rgb(0,0,0);

	while(flag){
		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);

		al_clear_to_color(al_map_rgb(0,0,0));
		al_draw_bitmap(inicio, 0, 0, 0);

		if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
			if(event.mouse.x >= X_TAM/2 - FONT_TAM*1.8 &&
				event.mouse.x <= X_TAM/2 - FONT_TAM*1.8 + FONT_TAM*3.48 && 
				event.mouse.y >= Y_TAM/2 - FONT_TAM*2 && 
				event.mouse.y <= Y_TAM/2 - FONT_TAM*2 + FONT_TAM){

				cor_button1 = al_map_rgb(0,0,255);
			} else {
				cor_button1 = al_map_rgb(0,0,0);
			}

			if(event.mouse.x >= X_TAM/2 - FONT_TAM*1.9 &&
				event.mouse.x <= X_TAM/2 - FONT_TAM*1.9 + FONT_TAM*3.48 && 
				event.mouse.y >= Y_TAM/2 - FONT_TAM*0.5 && 
				event.mouse.y <= Y_TAM/2 - FONT_TAM*0.5 + FONT_TAM){

				cor_button2 = al_map_rgb(0,0,255);
			} else {
				cor_button2 = al_map_rgb(0,0,0);
			}

			if(event.mouse.x >= X_TAM/2 - FONT_TAM*1.2 &&
				event.mouse.x <= X_TAM/2 - FONT_TAM*1.2 + FONT_TAM*3.48 && 
				event.mouse.y >= Y_TAM/2 + FONT_TAM && 
				event.mouse.y <= Y_TAM/2 + FONT_TAM + FONT_TAM){

				cor_button3 = al_map_rgb(0,0,255);
			} else {
				cor_button3 = al_map_rgb(0,0,0);
			}

		}

		if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
			if(event.mouse.x >= X_TAM/2 - FONT_TAM*1.8 &&
				event.mouse.x <= X_TAM/2 - FONT_TAM*1.8 + FONT_TAM*3.48 && 
				event.mouse.y >= Y_TAM/2 - FONT_TAM*2 && 
				event.mouse.y <= Y_TAM/2 - FONT_TAM*2 + FONT_TAM){

				break;;
			} else if(event.mouse.x >= X_TAM/2 - FONT_TAM*1.9 &&
				event.mouse.x <= X_TAM/2 - FONT_TAM*1.9 + FONT_TAM*3.48 && 
				event.mouse.y >= Y_TAM/2 - FONT_TAM*0.5 && 
				event.mouse.y <= Y_TAM/2 - FONT_TAM*0.5 + FONT_TAM){

				config = 1;
				break;
			} else if(event.mouse.x >= X_TAM/2 - FONT_TAM*1.2 &&
				event.mouse.x <= X_TAM/2 - FONT_TAM*1.2 + FONT_TAM*3.48 && 
				event.mouse.y >= Y_TAM/2 + FONT_TAM && 
				event.mouse.y <= Y_TAM/2 + FONT_TAM + FONT_TAM){

				flag = 0;
				break;
			}
		}

		al_draw_justified_text(font, cor_button1, X_TAM/2 - FONT_TAM*1.8, 0,
			Y_TAM/2 - FONT_TAM*2, 0, 0, "INICIAR");
		al_draw_justified_text(font, cor_button2, X_TAM/2 - FONT_TAM*1.9, 0,
			Y_TAM/2 - FONT_TAM*0.5, 0, 0, "OPCOES");
		al_draw_justified_text(font, cor_button3, X_TAM/2 - FONT_TAM*1.2, 0,
			Y_TAM/2 + FONT_TAM, 0, 0, "SAIR");

		al_flip_display();

		if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
			flag = 0;
			break;
		}
	}

	while(flag){
		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);

		al_clear_to_color(al_map_rgb(255,255,255));
		al_flip_display();

		if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) break;

	}

	al_destroy_font(font);
	al_destroy_bitmap(inicio);
	al_destroy_bitmap(sprite);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}
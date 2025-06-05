#include "tela.h"

void atualiza_tela(ALLEGRO_EVENT_QUEUE * event_queue, tela *tela){
    ALLEGRO_DISPLAY * display = al_create_display(tela->x, tela->y);
    al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
    al_register_event_source(event_queue, al_get_display_event_source(display));
}

tela *create_tela(int x, int y){

    tela *tela = malloc(sizeof(tela));
    if(!tela) return NULL;

    tela->x = x;
    tela->y = y;
    tela->font = y/12;
    tela->player = x/20;

    return tela;
}

tela *muda_tela(tela *tela, int x, int y){

    tela->x = x;
    tela->y = y;
    tela->font = y/12;
    tela->player = x/20;

    return tela;
}

void destroi_tela(tela *tela){
    free(tela);
}

flag *create_flag(unsigned char display, unsigned char tela_inicio, 
            unsigned char tela_config, unsigned char jogo, 
            unsigned char full, unsigned char selecao){
    
    flag *flag = malloc(sizeof(flag));
    if(!flag) return NULL;

    flag->display = display;
    flag->tela_inicio = tela_inicio;
    flag->tela_config = tela_config;
    flag->jogo = jogo;
    flag->full = full;
    flag->selecao = selecao;

    return flag;
}

flag *muda_flag(flag *flag, unsigned char display, unsigned char tela_inicio, 
            unsigned char tela_config, unsigned char jogo, 
            unsigned char full, unsigned char selecao){
    
    flag->display = display;
    flag->tela_inicio = tela_inicio;
    flag->tela_config = tela_config;
    flag->jogo = jogo;
    flag->full = full;
    flag->selecao = selecao;

    return flag;
}

void destroi_flag(flag *flag){
    free(flag);
}

void tela_selecao(ALLEGRO_EVENT_QUEUE * event_queue, ALLEGRO_EVENT_QUEUE *fila_eventos, 
    ALLEGRO_BITMAP * fundo_selecao, ALLEGRO_FONT *font, tela *tela, flag *flag){

    ALLEGRO_BITMAP * playerM = al_load_bitmap("sprites/personagem/selecao(M).jpeg");

    while(flag->selecao){

        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_bitmap(fundo_selecao, 0, 0, 0);

        al_draw_bitmap(playerM, tela->x/2 - tela->font*10, tela->y/2 - tela->font*2, 0);

        al_flip_display();

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            flag = muda_flag(flag, 0, 0, 0, 0, 0, 0);
        }

    }
    

}

void tela_config(ALLEGRO_EVENT_QUEUE * event_queue, ALLEGRO_EVENT_QUEUE *fila_eventos, 
    ALLEGRO_BITMAP * inicio, ALLEGRO_FONT *font, tela *tela, flag *flag){

    ALLEGRO_COLOR cor_button1 = al_map_rgb(100,0,0);
    ALLEGRO_COLOR cor_button2 = al_map_rgb(100,0,0);
    ALLEGRO_COLOR cor_button3 = al_map_rgb(100,0,0);

    int selecionado = 0;
    int resolucao = 0;
    int nome;

    while(flag->tela_config){
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_bitmap(inicio, 0, 0, 0);

        while (!al_is_event_queue_empty(fila_eventos)){

            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);

            if(evento.type == ALLEGRO_EVENT_MOUSE_AXES){
                if(evento.mouse.x >= tela->x/2 - tela->font*3.2 &&
                    evento.mouse.x <= tela->x/2 - tela->font*3.2 + tela->font*7.1 && 
                    evento.mouse.y >= tela->y/2 - tela->font*2.5 && 
                    evento.mouse.y <= tela->y/2 - tela->font*2.5 + tela->font){

                    selecionado = 1;
                    cor_button1 = al_map_rgb(0,0,255);
                } else {
                    cor_button1 = al_map_rgb(100,0,0);
                    if(selecionado == 1) selecionado = 0;
                }

                if(evento.mouse.x >= tela->x/2 - tela->font*2.5 &&
                    evento.mouse.x <= tela->x/2 - tela->font*2.5 + tela->font*5.6 && 
                    evento.mouse.y >= tela->y/2 && 
                    evento.mouse.y <= tela->y/2 + tela->font){

                    selecionado = 2;
                    cor_button2 = al_map_rgb(0,0,255);
                } else {
                    cor_button2 = al_map_rgb(100,0,0);
                    if(selecionado == 2) selecionado = 0;
                }

                if(evento.mouse.x >= tela->x/2 - tela->font*1.2 &&
                    evento.mouse.x <= tela->x/2 - tela->font*1.2 + tela->font*3 && 
                    evento.mouse.y >= tela->y/2 + tela->font*4 && 
                    evento.mouse.y <= tela->y/2 + tela->font*4 + tela->font){

                    selecionado = 3;
                    cor_button3 = al_map_rgb(0,0,255);
                } else {
                    cor_button3 = al_map_rgb(100,0,0);
                    if(selecionado == 3) selecionado = 0;
                }
            }
            else if(evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){

                if(evento.mouse.x >= tela->x/2 - tela->font*3.2 &&
                    evento.mouse.x <= tela->x/2 - tela->font*3.2 + tela->font*7.1 && 
                    evento.mouse.y >= tela->y/2 - tela->font*2.5 && 
                    evento.mouse.y <= tela->y/2 - tela->font*2.5 + tela->font){

                    cor_button1 = al_map_rgb(0,0,255);
                } 

                if(evento.mouse.x >= tela->x/2 - tela->font*2.5 &&
                    evento.mouse.x <= tela->x/2 - tela->font*2.5 + tela->font*5.6 && 
                    evento.mouse.y >= tela->y/2 && 
                    evento.mouse.y <= tela->y/2 + tela->font){

                    cor_button2 = al_map_rgb(0,0,255);

                }

                if(evento.mouse.x >= tela->x/2 - tela->font*1.2 &&
                    evento.mouse.x <= tela->x/2 - tela->font*1.2 + tela->font*3 && 
                    evento.mouse.y >= tela->y/2 + tela->font*4 && 
                    evento.mouse.y <= tela->y/2 + tela->font*4 + tela->font){

                    flag = muda_flag(flag, 0, 1, 0, 0, 0, 0);
                }
            }    
        }

        if(event.keyboard.keycode == 19 && (event.type == 10)){
            if(selecionado == 0){
                cor_button1 = al_map_rgb(0,0,255);
                cor_button2 = al_map_rgb(100,0,0);
                cor_button3 = al_map_rgb(100,0,0);
                selecionado = 1;
            } else if(selecionado == 1){
                cor_button1 = al_map_rgb(100,0,0);
                cor_button2 = al_map_rgb(0,0,255);
                cor_button3 = al_map_rgb(100,0,0);
                selecionado = 2;
            }else if(selecionado == 2 && resolucao == 5){
                resolucao = 4;
            } else if(selecionado == 2 && resolucao == 4){
                resolucao = 3;
            } else if(selecionado == 2 && resolucao == 3){
                resolucao = 2;
            } else if(selecionado == 2 && resolucao == 2){
                resolucao = 1;
            } else if(selecionado == 2 && resolucao == 1){
                resolucao = 1;
            } else if(selecionado == 2){
                cor_button1 = al_map_rgb(100,0,0);
                cor_button2 = al_map_rgb(100,0,0);
                cor_button3 = al_map_rgb(0,0,255);
                selecionado = 3;
            } else if(selecionado == 3){
                cor_button1 = al_map_rgb(100,0,0);
                cor_button2 = al_map_rgb(100,0,0);
                cor_button3 = al_map_rgb(100,0,0);
                selecionado = 0;
            }
        }

        if(event.keyboard.keycode == 23 && (event.type == 10)){
            if(selecionado == 3){
                cor_button1 = al_map_rgb(100,0,0);
                cor_button2 = al_map_rgb(0,0,255);
                cor_button3 = al_map_rgb(100,0,0);
                selecionado = 2;
            } else if(selecionado == 2 && resolucao == 1){
                resolucao = 2;
            } else if(selecionado == 2 && resolucao == 2){
                resolucao = 3;
            } else if(selecionado == 2 && resolucao == 3){
                resolucao = 4;
            } else if(selecionado == 2 && resolucao == 4){
                resolucao = 5;
            } else if(selecionado == 2 && resolucao == 5){
                resolucao = 5;
            } else if(selecionado == 2){
                cor_button1 = al_map_rgb(0,0,255);
                cor_button2 = al_map_rgb(100,0,0);
                cor_button3 = al_map_rgb(100,0,0);
                selecionado = 1;
            } else if(selecionado == 1){
                cor_button1 = al_map_rgb(100,0,0);
                cor_button2 = al_map_rgb(100,0,0);
                cor_button3 = al_map_rgb(100,0,0);
                selecionado = 0;
            } else if(selecionado == 0){
                cor_button1 = al_map_rgb(100,0,0);
                cor_button2 = al_map_rgb(100,0,0);
                cor_button3 = al_map_rgb(0,0,255);
                selecionado = 3;
            }
        }

        al_draw_justified_text(font, al_map_rgb(255,255,255), tela->x/2 - tela->font*3.5, 0,
        tela->y/2 - tela->font*5.5, 0, 0, "CONFIGURACOES");

        al_draw_justified_text(font, cor_button1, tela->x/2 - tela->font*3.2, 0,
        tela->y/2 - tela->font*2.5, 0, 0, "NOME USUARIO");

        if(resolucao == 1){
            al_draw_justified_text(font, al_map_rgb(0,0,255), tela->x/2 - tela->font*1.5, 0,
            tela->y/2, 0, 0, "640x360");
        } else if(resolucao == 2){
            al_draw_justified_text(font, al_map_rgb(0,0,255), tela->x/2 - tela->font*1.5, 0,
            tela->y/2, 0, 0, "800x450");
        } else if(resolucao == 3){
            al_draw_justified_text(font, al_map_rgb(0,0,255), tela->x/2 - tela->font*1.5, 0,
            tela->y/2, 0, 0, "1024x576");
        } else if(resolucao == 4){
            al_draw_justified_text(font, al_map_rgb(0,0,255), tela->x/2 - tela->font*1.5, 0,
            tela->y/2, 0, 0, "1920x1080");
        } else if(resolucao == 5){
            al_draw_justified_text(font, al_map_rgb(0,0,255), tela->x/2 - tela->font*2.6, 0,
            tela->y/2, 0, 0, "FULLSCREEN");
        } else {
            al_draw_justified_text(font, cor_button2, tela->x/2 - tela->font*2.5, 0,
            tela->y/2, 0, 0, "RESOLUCAO");
        }

        al_draw_justified_text(font, cor_button3, tela->x/2 - tela->font*1.2, 0,
        tela->y/2 + tela->font*4, 0, 0, "VOLTAR");

        al_flip_display();

        if(event.keyboard.keycode == 67 && event.type == 10){

            if(selecionado == 1){

                nome = 1;

            } else if(selecionado == 2){

                if(resolucao == 1){
                    tela = muda_tela(tela, 640, 360);
                } else if(resolucao == 2){
                    tela = muda_tela(tela, 800, 450);
                } else if(resolucao == 3){ 
                    tela = muda_tela(tela, 1024, 576);
                } else if(resolucao == 4){
                    tela = muda_tela(tela, 1920, 1080);
                } else if(resolucao == 5){
                    ALLEGRO_DISPLAY_MODE mode;
                    al_get_display_mode(0, &mode);
                    tela = muda_tela(tela, mode.width, mode.height);
                }
                if(resolucao){
                    if(resolucao == 5) flag = muda_flag(flag, 1, 0, 1, 0, 1, 0);
                    else  flag = muda_flag(flag, 1, 0, 1, 0, 0, 0);
                    resolucao = 0;  
                    return;
                } else {
                    resolucao = 1;
                }

            } else if(selecionado == 3){

                flag = muda_flag(flag, 0, 1, 0, 0, 0, 0);

            }

        }

        if(nome){

        }

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            flag = muda_flag(flag, 0, 0, 0, 0, 0, 0);
        }
    }
}

void tela_de_inicio(ALLEGRO_EVENT_QUEUE * event_queue, ALLEGRO_EVENT_QUEUE *fila_eventos, 
    ALLEGRO_BITMAP * inicio, ALLEGRO_FONT *font, ALLEGRO_BITMAP *fundo, tela *tela, flag *flag){

    flag->tela_inicio = 1;
    int selecionado = 0;

    ALLEGRO_COLOR cor_button1 = al_map_rgb(0,0,0);
    ALLEGRO_COLOR cor_button2 = al_map_rgb(0,0,0);
    ALLEGRO_COLOR cor_button3 = al_map_rgb(0,0,0);

    while(flag->tela_inicio){
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_bitmap(inicio, 0, 0, 0);

        while (!al_is_event_queue_empty(fila_eventos)){

            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);

            if(evento.type == ALLEGRO_EVENT_MOUSE_AXES){
                if(evento.mouse.x >= tela->x/2 - tela->font*1.8 &&
                    evento.mouse.x <= tela->x/2 - tela->font*1.8 + tela->font*3.48 && 
                    evento.mouse.y >= tela->y/2 - tela->font*2 && 
                    evento.mouse.y <= tela->y/2 - tela->font*2 + tela->font){

                    cor_button1 = al_map_rgb(0,0,255);
                    selecionado = 1;
                } else {
                    cor_button1 = al_map_rgb(0,0,0);
                    if(selecionado == 1) selecionado = 0;
                }

                if(evento.mouse.x >= tela->x/2 - tela->font*1.9 &&
                    evento.mouse.x <= tela->x/2 - tela->font*1.9 + tela->font*3.48 && 
                    evento.mouse.y >= tela->y/2 - tela->font*0.5 && 
                    evento.mouse.y <= tela->y/2 - tela->font*0.5 + tela->font){

                    cor_button2 = al_map_rgb(0,0,255);
                    selecionado = 2;
                } else {
                    cor_button2 = al_map_rgb(0,0,0);
                    if(selecionado == 2) selecionado = 0;
                }

                if(evento.mouse.x >= tela->x/2 - tela->font*1.2 &&
                    evento.mouse.x <= tela->x/2 - tela->font*1.2 + tela->font*3.48 && 
                    evento.mouse.y >= tela->y/2 + tela->font && 
                    evento.mouse.y <= tela->y/2 + tela->font + tela->font){

                    cor_button3 = al_map_rgb(0,0,255);
                    selecionado = 3;
                } else {
                    cor_button3 = al_map_rgb(0,0,0);
                    if(selecionado == 3) selecionado = 0;
                }

            }

            else if(evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                if(evento.mouse.x >= tela->x/2 - tela->font*1.8 &&
                    evento.mouse.x <= tela->x/2 - tela->font*1.8 + tela->font*3.48 && 
                    evento.mouse.y >= tela->y/2 - tela->font*2 && 
                    evento.mouse.y <= tela->y/2 - tela->font*2 + tela->font){

                    flag = muda_flag(flag, 0, 0, 0, 1, 0, 1);

                } else if(evento.mouse.x >= tela->x/2 - tela->font*1.9 &&
                    evento.mouse.x <= tela->x/2 - tela->font*1.9 + tela->font*3.48 && 
                    evento.mouse.y >= tela->y/2 - tela->font*0.5 && 
                    evento.mouse.y <= tela->y/2 - tela->font*0.5 + tela->font){

                    flag = muda_flag(flag, 1, 0, 1, 0, 0, 0);

                } else if(evento.mouse.x >= tela->x/2 - tela->font*1.2 &&
                    evento.mouse.x <= tela->x/2 - tela->font*1.2 + tela->font*3.48 && 
                    evento.mouse.y >= tela->y/2 + tela->font && 
                    evento.mouse.y <= tela->y/2 + tela->font + tela->font){

                    flag = muda_flag(flag, 0, 0, 0, 0, 0, 0);

                }
            }    
        }

        if(event.keyboard.keycode == 19 && (event.type == 10)){
            if(selecionado == 0){
                cor_button1 = al_map_rgb(0,0,255);
                cor_button2 = al_map_rgb(0,0,0);
                cor_button3 = al_map_rgb(0,0,0);
                selecionado = 1;
            } else if(selecionado == 1){
                cor_button1 = al_map_rgb(0,0,0);
                cor_button2 = al_map_rgb(0,0,255);
                cor_button3 = al_map_rgb(0,0,0);
                selecionado = 2;
            } else if(selecionado == 2){
                cor_button1 = al_map_rgb(0,0,0);
                cor_button2 = al_map_rgb(0,0,0);
                cor_button3 = al_map_rgb(0,0,255);
                selecionado = 3;
            } else if(selecionado == 3){
                cor_button1 = al_map_rgb(0,0,0);
                cor_button2 = al_map_rgb(0,0,0);
                cor_button3 = al_map_rgb(0,0,0);
                selecionado = 0;
            }
        }

        if(event.keyboard.keycode == 23 && (event.type == 10)){
            if(selecionado == 3){
                cor_button1 = al_map_rgb(0,0,0);
                cor_button2 = al_map_rgb(0,0,255);
                cor_button3 = al_map_rgb(0,0,0);
                selecionado = 2;
            } else if(selecionado == 2){
                cor_button1 = al_map_rgb(0,0,255);
                cor_button2 = al_map_rgb(0,0,0);
                cor_button3 = al_map_rgb(0,0,0);
                selecionado = 1;
            } else if(selecionado == 1){
                cor_button1 = al_map_rgb(0,0,0);
                cor_button2 = al_map_rgb(0,0,0);
                cor_button3 = al_map_rgb(0,0,0);
                selecionado = 0;
            } else if(selecionado == 0){
                cor_button1 = al_map_rgb(0,0,0);
                cor_button2 = al_map_rgb(0,0,0);
                cor_button3 = al_map_rgb(0,0,255);
                selecionado = 3;
            }
        }

        al_draw_justified_text(font, cor_button1, tela->x/2 - tela->font*1.8, 0,
        tela->y/2 - tela->font*2, 0, 0, "INICIAR");
        al_draw_justified_text(font, cor_button2, tela->x/2 - tela->font*1.9, 0,
        tela->y/2 - tela->font*0.5, 0, 0, "OPCOES");
        al_draw_justified_text(font, cor_button3, tela->x/2 - tela->font*1.2, 0,
        tela->y/2 + tela->font, 0, 0, "SAIR");

        al_flip_display();

        if(event.keyboard.keycode == 67 && event.type == 10){

            if(selecionado == 1){

                flag = muda_flag(flag, 0, 0, 0, 1, 0, 1);

            } else if(selecionado == 2){

                flag = muda_flag(flag, 1, 0, 1, 0, 0, 0);

            } else if(selecionado == 3){

                flag = muda_flag(flag, 0, 0, 0, 0, 0, 0);

            }

        }

        if(flag->tela_config){
            tela_config(event_queue, fila_eventos, fundo, font, tela, flag);
        }

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){

            flag = muda_flag(flag, 0, 0, 0, 0, 0, 0);
        }
    }
}

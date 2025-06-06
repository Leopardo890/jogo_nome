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

flag *create_flag(){
    
    flag *flag = malloc(sizeof(flag));
    if(!flag) return NULL;

    flag->display = 0;
    flag->tela_inicio = 0;
    flag->tela_config = 0;
    flag->jogo = 0;
    flag->full = 0;
    flag->selecao = 0;
    flag->main = 0;
    flag->personagem = 0;

    return flag;
}

flag *muda_flag(flag *flag, unsigned char display, unsigned char tela_inicio, 
            unsigned char tela_config, unsigned char jogo, 
            unsigned char full, unsigned char selecao,
            unsigned char main, unsigned char personagem){
    
    flag->display = display;
    flag->tela_inicio = tela_inicio;
    flag->tela_config = tela_config;
    flag->jogo = jogo;
    flag->full = full;
    flag->selecao = selecao;
    flag->main = main;
    flag->personagem = personagem;

    return flag;
}

void destroi_flag(flag *flag){
    free(flag);
}

void tela_jogo(ALLEGRO_EVENT_QUEUE * event_queue, ALLEGRO_EVENT_QUEUE *fila_eventos, 
    ALLEGRO_BITMAP * fundo_jogo, ALLEGRO_FONT *font, tela *tela, flag *flag){

    int tam_img = al_get_bitmap_width(fundo_jogo);
    int posicaox = 0;
    int segunda_img = 0;

    square *player = square_create(tela->font, tela->font, tela->x/10, 
                                    tela->y/1.47, tela->x, tela->y);

    if(flag->selecao){
        //rornet
    } else {
        //hollow
    }

    unsigned char pulando = 0;
    unsigned char agachado = 0;

    while(flag->jogo){

        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        al_clear_to_color(al_map_rgb(0,0,0));

        //0 - left / 1 - right / 2 - up / 3 - down
        if(player->controle->right) square_move(player, 1, 1, tela->x, tela->y);
        if(player->controle->left) square_move(player, 1, 0, tela->x, tela->y);


        //ponto inicial x, ponto inicial y, largura imagem, altura imagem, posicao x, posicao y
        al_draw_bitmap_region(fundo_jogo, 0, 0, tam_img, tela->y, posicaox, 0, 0);

        al_draw_filled_rectangle(player->x, player->y, player->x + player->side_x, 
                        player->y + player->side_y, al_map_rgb(255, 255, 255));

        if(event.type == 10 || event.type == 12){
            if(event.keyboard.keycode == 4) joystick_right(player->controle);
            if(event.keyboard.keycode == 1) joystick_left(player->controle);
        }

        //sistema de agachar
        if(event.type == 10 && event.keyboard.keycode == 19 && !agachado){
            player->y += player->side_y/2;
            player->side_y /= 2;
            agachado = 1;
        }
        if(event.type == 12 && event.keyboard.keycode == 19 && agachado){
            player->side_y *= 2;
            player->y -= player->side_y/2;
            agachado = 0;
        }
        if(event.type == 10 && event.keyboard.keycode == 75 && agachado && !pulando){
            player->side_y *= 2;
            player->y -= player->side_y/2;
            agachado = 0;
        }

        //sistema de pulo
        if(event.type == 10 && event.keyboard.keycode == 75 && !pulando ||
            event.type == 12 && event.keyboard.keycode == 75)
            joystick_pulo(player->controle);

        if(player->controle->pulo){
            square_move(player, 1, 2, tela->x, tela->y);
            pulando = 1;
        } else if(player->y < tela->y/1.5){
            square_move(player, 1, 3, tela->x, tela->y);
        }
        if(player->y >= tela->y/1.5){
            pulando = 0;
        }
            

        if(posicaox - tela->x*1.5 <= -tam_img){
            posicaox = 0;
        }

        al_flip_display();

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            flag = muda_flag(flag, 0, 0, 0, 0, 0, 0, 0, 0);
        }
    }

}

void tela_selecao(ALLEGRO_EVENT_QUEUE * event_queue, ALLEGRO_EVENT_QUEUE *fila_eventos, 
    ALLEGRO_BITMAP * fundo_selecao, ALLEGRO_FONT *font, tela *tela, flag *flag){

    int x;
    int y;
    ALLEGRO_BITMAP * playerM;
    if(tela->x < 1900){
        playerM = al_load_bitmap("sprites/personagem/selecaoM_peq.jpeg");
        x = 42000;
        y = 6000;
    } else {
        playerM = al_load_bitmap("sprites/personagem/selecaoM_grand.webp");
        x = 300000;
        y = 40000;
    }

    int pontx = x/tela->x;
    int ponty = y/tela->y;
    int tam = tela->x/6;

    ALLEGRO_COLOR cor_button1 = al_map_rgb(100,0,0);
    ALLEGRO_COLOR cor_button2 = al_map_rgb(100,0,0);
    ALLEGRO_COLOR cor_button3 = al_map_rgb(100,0,0);
    int selecionado = 0;

    while(flag->selecao){

        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_bitmap(fundo_selecao, 0, 0, 0);

        if(event.keyboard.keycode == 19 && (event.type == 10)){
            if(selecionado == 0){
                selecionado = 1;
                cor_button1 = al_map_rgb(0,0,255);
                cor_button2 = al_map_rgb(100,0,0);
                cor_button3 = al_map_rgb(100,0,0);

            } else if(selecionado == 1){
                selecionado = 3;
                cor_button1 = al_map_rgb(100,0,0);
                cor_button2 = al_map_rgb(100,0,0);
                cor_button3 = al_map_rgb(0,0,255);

            } else if(selecionado == 2){
                selecionado = 3;
                cor_button1 = al_map_rgb(100,0,0);
                cor_button2 = al_map_rgb(100,0,0);
                cor_button3 = al_map_rgb(0,0,255);
            
            } else if(selecionado == 3){
                selecionado = 0;
                cor_button1 = al_map_rgb(100,0,0);
                cor_button2 = al_map_rgb(100,0,0);
                cor_button3 = al_map_rgb(100,0,0);
            }
        }

        if(event.keyboard.keycode == 23 && (event.type == 10)){
            if(selecionado == 0){
                selecionado = 3;
                cor_button1 = al_map_rgb(100,0,0);
                cor_button2 = al_map_rgb(100,0,0);
                cor_button3 = al_map_rgb(0,0,255);

            } else if(selecionado == 1){
                selecionado = 0;
                cor_button1 = al_map_rgb(100,0,0);
                cor_button2 = al_map_rgb(100,0,0);
                cor_button3 = al_map_rgb(100,0,0);

            } else if(selecionado == 2){
                selecionado = 0;
                cor_button1 = al_map_rgb(100,0,0);
                cor_button2 = al_map_rgb(100,0,0);
                cor_button3 = al_map_rgb(100,0,0);
            
            } else if(selecionado == 3){
                selecionado = 1;
                cor_button1 = al_map_rgb(0,0,255);
                cor_button2 = al_map_rgb(100,0,0);
                cor_button3 = al_map_rgb(100,0,0);
            }
        }

        if(event.keyboard.keycode == 1 && (event.type == 10)){
            if(selecionado == 0){
                selecionado = 2;
                cor_button1 = al_map_rgb(100,0,0);
                cor_button2 = al_map_rgb(0,0,255);
                cor_button3 = al_map_rgb(100,0,0);

            } else if(selecionado == 1){
                selecionado = 0;
                cor_button1 = al_map_rgb(100,0,0);
                cor_button2 = al_map_rgb(100,0,0);
                cor_button3 = al_map_rgb(100,0,0);

            } else if(selecionado == 2){
                selecionado = 1;
                cor_button1 = al_map_rgb(0,0,255);
                cor_button2 = al_map_rgb(100,0,0);
                cor_button3 = al_map_rgb(100,0,0);
            }
        }

        if(event.keyboard.keycode == 4 && (event.type == 10)){
            if(selecionado == 0){
                selecionado = 1;
                cor_button1 = al_map_rgb(0,0,255);
                cor_button2 = al_map_rgb(100,0,0);
                cor_button3 = al_map_rgb(100,0,0);

            } else if(selecionado == 1){
                selecionado = 2;
                cor_button1 = al_map_rgb(100,0,0);
                cor_button2 = al_map_rgb(0,0,255);
                cor_button3 = al_map_rgb(100,0,0);

            } else if(selecionado == 2){
                selecionado = 0;
                cor_button1 = al_map_rgb(100,0,0);
                cor_button2 = al_map_rgb(100,0,0);
                cor_button3 = al_map_rgb(100,0,0);
            }
        }

        al_draw_filled_rectangle(tela->x/2 - tela->font*6.2, tela->y/2 - tela->font*2.2, 
                tela->x/2 - tela->font*5.8 + tam, tela->y/2 - tela->font*1.8 + tam, cor_button1);
        //ponto inicial x, ponto inicial y, largura imagem, altura imagem, posicao x, posicao y
        al_draw_bitmap_region(playerM, pontx, ponty, tam, tam, tela->x/2 - tela->font*6, tela->y/2 - tela->font*2, 0);
        
        al_draw_filled_rectangle(tela->x/2 + tela->font*1.8, tela->y/2 - tela->font*2.2, 
            tela->x/2 + tela->font*2.2 + tam, tela->y/2 - tela->font*1.8 + tam, cor_button2);
        al_draw_bitmap_region(playerM, pontx, ponty, tam, tam, tela->x/2 + tela->font*2, tela->y/2 - tela->font*2, 0);

        al_draw_justified_text(font, cor_button3, tela->x/2 - tela->font*1.5, 0,
            tela->y/2 + tela->font*4, 0, 0, "VOLTAR");

        al_flip_display();

        if(event.keyboard.keycode == 67 && event.type == 10){

            if(selecionado == 1){

                flag = muda_flag(flag, 0, 0, 0, 1, 0, 0, 0, 0);

            } else if(selecionado == 2){

                flag = muda_flag(flag, 0, 0, 0, 1, 0, 0, 0, 1);

            } else if(selecionado == 3){

                flag = muda_flag(flag, 0, 1, 0, 0, 0, 0, 1, 0);

            }

        }

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            flag = muda_flag(flag, 0, 0, 0, 0, 0, 0, 0, 0);
        }

    }
    
    al_destroy_bitmap(playerM);

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

                    flag = muda_flag(flag, 0, 1, 0, 0, 0, 0, 0, 0);
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
                    if(resolucao == 5) flag = muda_flag(flag, 1, 0, 1, 0, 1, 0, 0, 0);
                    else  flag = muda_flag(flag, 1, 0, 1, 0, 0, 0, 0, 0);
                    resolucao = 0;  
                    return;
                } else {
                    resolucao = 1;
                }

            } else if(selecionado == 3){

                flag = muda_flag(flag, 0, 1, 0, 0, 0, 0, 0, 0);

            }

        }

        if(nome){

        }

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            flag = muda_flag(flag, 0, 0, 0, 0, 0, 0, 0, 0);
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

                    flag = muda_flag(flag, 0, 0, 0, 1, 0, 1, 0, 0);

                } else if(evento.mouse.x >= tela->x/2 - tela->font*1.9 &&
                    evento.mouse.x <= tela->x/2 - tela->font*1.9 + tela->font*3.48 && 
                    evento.mouse.y >= tela->y/2 - tela->font*0.5 && 
                    evento.mouse.y <= tela->y/2 - tela->font*0.5 + tela->font){

                    flag = muda_flag(flag, 1, 0, 1, 0, 0, 0, 0, 0);

                } else if(evento.mouse.x >= tela->x/2 - tela->font*1.2 &&
                    evento.mouse.x <= tela->x/2 - tela->font*1.2 + tela->font*3.48 && 
                    evento.mouse.y >= tela->y/2 + tela->font && 
                    evento.mouse.y <= tela->y/2 + tela->font + tela->font){

                    flag = muda_flag(flag, 0, 0, 0, 0, 0, 0, 0, 0);

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

                flag = muda_flag(flag, 0, 0, 0, 1, 0, 1, 0, 0);

            } else if(selecionado == 2){

                flag = muda_flag(flag, 1, 0, 1, 0, 0, 0, 0, 0);

            } else if(selecionado == 3){

                flag = muda_flag(flag, 0, 0, 0, 0, 0, 0, 0, 0);

            }

        }

        if(flag->tela_config){
            tela_config(event_queue, fila_eventos, fundo, font, tela, flag);
        }

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){

            flag = muda_flag(flag, 0, 0, 0, 0, 0, 0, 0, 0);
        }
    }
}

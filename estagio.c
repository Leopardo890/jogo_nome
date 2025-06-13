#include "estagio.h"
#include "tela.h"
#include <stdio.h>

int tela_fase1(ALLEGRO_EVENT_QUEUE * event_queue,
    ALLEGRO_BITMAP * fundo_jogo, ALLEGRO_FONT *font, tela *tela, player *personagem){

        int frame_up = 0;
        int frame_up_left = 8;
        int frame_parado = 0;
        int frame_right = 0;
        int frame_left = 5;
        int agachado = 0;
        int contador = 0;
        int olhando = 1;
        camera *camera = create_camera(0, 0);

    while(1){

        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        //fundo
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_scaled_bitmap(fundo_jogo,
            0, 0, // Ponto de origem do bitmap (canto superior esquerdo)
            al_get_bitmap_width(fundo_jogo), // Largura original do bitmap
            al_get_bitmap_height(fundo_jogo), // Altura original do bitmap
            -camera->x, 0, // Ponto de destino na tela (canto superior esquerdo)
            tela->x, // Largura para desenhar (largura da tela)
            tela->y - tela->font, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );
        al_draw_scaled_bitmap(fundo_jogo,
            0, 0, // Ponto de origem do bitmap (canto superior esquerdo)
            al_get_bitmap_width(fundo_jogo), // Largura original do bitmap
            al_get_bitmap_height(fundo_jogo), // Altura original do bitmap
            -camera->x + tela->x, 0, // Ponto de destino na tela (canto superior esquerdo)
            tela->x, // Largura para desenhar (largura da tela)
            tela->y - tela->font, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );
        al_draw_scaled_bitmap(fundo_jogo,
            0, 0, // Ponto de origem do bitmap (canto superior esquerdo)
            al_get_bitmap_width(fundo_jogo), // Largura original do bitmap
            al_get_bitmap_height(fundo_jogo), // Altura original do bitmap
            -camera->x + 2*tela->x, 0, // Ponto de destino na tela (canto superior esquerdo)
            tela->x, // Largura para desenhar (largura da tela)
            tela->y - tela->font, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );
        
        if((event.type == 10) || event.type == 12){
            //movimento para a esquerda
            if(event.keyboard.keycode == 1){
                joystick_left(personagem->controle);
                olhando = 1;
            }
            //movimento para a direita
            if(event.keyboard.keycode == 4){
                olhando = 2;
                joystick_right(personagem->controle);
            }
            //agachar
            if(event.keyboard.keycode == 19) joystick_down(personagem->controle);
        }

        //pupar
        if(event.type == 10 && event.keyboard.keycode == 75 && !personagem->controle->up)joystick_up(personagem->controle);

        if(event.type == 30){
            //atualiza posicao
            if(personagem->controle->left){
                player_move(personagem, 1, 0, 3*tela->x, tela->y);
                muda_camera(camera, tela, personagem->x - tela->x/2 + personagem->side_x/2, camera->y, 3*tela->x, camera->y);
            }else if(personagem->controle->right){
                player_move(personagem, 1, 1, 3*tela->x, tela->y);
                muda_camera(camera, tela, personagem->x - tela->x/2 + personagem->side_x/2, camera->y, 3*tela->x, camera->y);
            }
        }

        //personagem parado direita
        if(personagem->controle->andando == 0 && olhando == 2 && !personagem->controle->up){
            if(personagem->controle->down){
                frame_parado = 0;
                agachado = 6;
            }else agachado = 7;

            al_draw_scaled_bitmap(personagem->aparencia[agachado],
                128*frame_parado, 0, // imagem 3
                128, //largura
                128, // altura
                personagem->x - camera->x, personagem->y, // Ponto de destino na tela
                personagem->side_x, // Largura para desenhar (largura da tela)
                personagem->side_y, // Altura para desenhar (altura da tela)
                0 // Flags (normalmente 0)
            );

            if(event.type == ALLEGRO_EVENT_TIMER) contador++;
            if(contador == 6){
                if(!personagem->controle->down) frame_parado = (frame_parado + 1)%7;
                contador = 0;
            }
        }

        //personagem parado esquerda
        if(personagem->controle->andando == 0 && olhando == 1 && !personagem->controle->up){
            if(personagem->controle->down){
                frame_parado = 0;
                agachado = 12;
            }else agachado = 13;

            al_draw_scaled_bitmap(personagem->aparencia[agachado],
                128*frame_parado, 0, // imagem 3
                128, //largura
                128, // altura
                personagem->x - camera->x, personagem->y, // Ponto de destino na tela
                personagem->side_x, // Largura para desenhar (largura da tela)
                personagem->side_y, // Altura para desenhar (altura da tela)
                0 // Flags (normalmente 0)
            );

            if(event.type == ALLEGRO_EVENT_TIMER) contador++;
            if(contador == 6){
                if(!personagem->controle->down) frame_parado = (frame_parado - 1);
                if(frame_parado < 0)frame_parado = 6;
                contador = 0;
            }
        }

        //andando para a esquerda
        if(personagem->controle->left && !personagem->controle->up){
            if(personagem->controle->down){
                if(frame_left > 2)frame_left = 2;
                agachado = 12;
            }else agachado = 11;

            al_draw_scaled_bitmap(personagem->aparencia[agachado],
                128*frame_left, 0, // imagem 3
                128, //largura
                128, // altura
                personagem->x - camera->x, personagem->y, // Ponto de destino na tela
                personagem->side_x, // Largura para desenhar (largura da tela)
                personagem->side_y, // Altura para desenhar (altura da tela)
                0 // Flags (normalmente 0)
            );

            if(event.type == ALLEGRO_EVENT_TIMER) contador++;
            if(contador == 6){
                if(personagem->controle->down) frame_left = (frame_left + 1)%3;
                else frame_left = (frame_left - 1);
                if(frame_left < 0) frame_left = 5;
                contador = 0;
            }
        }

        //andando para a direita
        if(personagem->controle->right && !personagem->controle->up){
            if(personagem->controle->down){
                if(frame_right > 2)frame_right = 0;
                agachado = 6;
            }else agachado = 10;
            

            al_draw_scaled_bitmap(personagem->aparencia[agachado],
                128*frame_right, 0, // imagem 3
                128, //largura
                128, // altura
                personagem->x - camera->x, personagem->y, // Ponto de destino na tela
                personagem->side_x, // Largura para desenhar (largura da tela)
                personagem->side_y, // Altura para desenhar (altura da tela)
                0 // Flags (normalmente 0)
            );

            if(event.type == ALLEGRO_EVENT_TIMER) contador++;
            if(contador == 6){
                if(personagem->controle->down) frame_right = (frame_right + 1)%3;
                else frame_right = (frame_right + 1)%6;
                contador = 0;
            }
        }

        //pulando para direita
        if(personagem->controle->up && olhando == 2){
            

            al_draw_scaled_bitmap(personagem->aparencia[8],
                128*frame_up, 0, // imagem x
                128, //largura
                128, // altura
                personagem->x - camera->x, personagem->y, // Ponto de destino na tela
                personagem->side_x, // Largura para desenhar (largura da tela)
                personagem->side_y, // Altura para desenhar (altura da tela)
                0 // Flags (normalmente 0)
            );

            if(event.type == ALLEGRO_EVENT_TIMER){
                if(frame_up == 3) personagem->y -= PLAYER_STEP*3;
                if(frame_up == 4) personagem->y -= PLAYER_STEP*4;
                if(frame_up == 5) personagem->y += PLAYER_STEP*4;
                if(frame_up == 6) personagem->y += PLAYER_STEP*3;
                contador++;
            }
            if(contador == 6){
                frame_up = frame_up + 1;
                contador = 0;
            }
            if(frame_up > 8){
                frame_up = 0;
                joystick_up(personagem->controle);
            }
        }

        //pulando para a esquerda
        if(personagem->controle->up && olhando == 1){
            

            al_draw_scaled_bitmap(personagem->aparencia[14],
                128*frame_up_left, 0, // imagem x
                128, //largura
                128, // altura
                personagem->x - camera->x, personagem->y, // Ponto de destino na tela
                personagem->side_x, // Largura para desenhar (largura da tela)
                personagem->side_y, // Altura para desenhar (altura da tela)
                0 // Flags (normalmente 0)
            );

            if(event.type == ALLEGRO_EVENT_TIMER){
                if(frame_up_left == 3) personagem->y += PLAYER_STEP*3;
                if(frame_up_left == 4) personagem->y += PLAYER_STEP*4;
                if(frame_up_left == 5) personagem->y -= PLAYER_STEP*4;
                if(frame_up_left == 6) personagem->y -= PLAYER_STEP*3;
                contador++;
            }
            if(contador == 6){
                frame_up_left = frame_up_left - 1;
                contador = 0;
            }
            if(frame_up_left < 0){
                frame_up_left = 8;
                joystick_up(personagem->controle);
            }
        }


        al_flip_display();


        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            return 0; //terminar execucao
        }

    }

}

int tela_selecao(ALLEGRO_EVENT_QUEUE * event_queue,
    ALLEGRO_BITMAP * fundo_selecao, ALLEGRO_FONT *font, tela *tela, int *personagem){

    ALLEGRO_BITMAP * playerM;
    playerM = al_load_bitmap("sprites/personagem/mago/Fire_vizard/Fireball.png");
    ALLEGRO_BITMAP * playerS;
    playerS = al_load_bitmap("sprites/personagem/soldado/Soldier_1/Grenade.png");

    ALLEGRO_COLOR cor_button1 = al_map_rgb(100,0,0);
    ALLEGRO_COLOR cor_button2 = al_map_rgb(100,0,0);
    ALLEGRO_COLOR cor_button3 = al_map_rgb(100,0,0);
    int selecionado = 0;

    while(1){

        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_scaled_bitmap(fundo_selecao,
            0, 0, // Ponto de origem do bitmap (canto superior esquerdo)
            al_get_bitmap_width(fundo_selecao), // Largura original do bitmap
            al_get_bitmap_height(fundo_selecao), // Altura original do bitmap
            0, 0, // Ponto de destino na tela (canto superior esquerdo)
            tela->x, // Largura para desenhar (largura da tela)
            tela->y, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );

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

        //movimento para a esquerda
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


        al_draw_filled_rectangle(tela->x/2 - tela->font*6, tela->y/2 - tela->font*3, 
            tela->x/2 - tela->font*6 + tela->font*4, 
            tela->y/2 - tela->font*3 + tela->font*4, cor_button1);

        al_draw_scaled_bitmap(playerM,
            256, 0, // imagem 3
            128, //largura
            128, // altura
            tela->x/2 - tela->font*8, tela->y/2 - tela->font*7, // Ponto de destino na tela
            tela->font*8, // Largura para desenhar (largura da tela)
            tela->font*8, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );

        al_draw_filled_rectangle(tela->x/2 + tela->font*2, tela->y/2 - tela->font*3, 
            tela->x/2 + tela->font*2 + tela->font*4, 
            tela->y/2 - tela->font*3 + tela->font*4, cor_button2);

        al_draw_scaled_bitmap(playerS,
            256, 0, // imagem 3
            128, //largura
            128, // altura
            tela->x/2 + tela->font, tela->y/2 - tela->font*7, // Ponto de destino na tela
            tela->font*8, // Largura para desenhar (largura da tela)
            tela->font*8, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );

        al_draw_justified_text(font, cor_button3, tela->x/2 - tela->font*1.5, 0,
            tela->y/2 + tela->font*4, 0, 0, "VOLTAR");

        al_flip_display();

        if(event.keyboard.keycode == 67 && event.type == 10){

            if(selecionado == 1){

                *personagem = 1;
                return 4; //estagio jogo

            } else if(selecionado == 2){

                *personagem = 2;
                return 4; //estagio jogo

            } else if(selecionado == 3){

                return 1; //estagio tela_inicio

            }

        }

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            return 0; //terminar execucao
        }

    }
    
    
    al_destroy_bitmap(playerM);
    al_destroy_bitmap(playerS);

}

int tela_config(ALLEGRO_EVENT_QUEUE * event_queue, ALLEGRO_DISPLAY * display,
    ALLEGRO_BITMAP * fundo_config, ALLEGRO_FONT *font, tela *tela){

    ALLEGRO_COLOR cor_button1 = al_map_rgb(100,0,0);
    ALLEGRO_COLOR cor_button2 = al_map_rgb(100,0,0);
    ALLEGRO_COLOR cor_button3 = al_map_rgb(100,0,0);

    int selecionado = 0;
    int resolucao = 0;
    int nome;

    while(1){
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_scaled_bitmap(fundo_config,
            0, 0, // Ponto de origem do bitmap (canto superior esquerdo)
            al_get_bitmap_width(fundo_config), // Largura original do bitmap
            al_get_bitmap_height(fundo_config), // Altura original do bitmap
            0, 0, // Ponto de destino na tela (canto superior esquerdo)
            tela->x, // Largura para desenhar (largura da tela)
            tela->y, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );

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

                al_set_display_flag(display, ALLEGRO_FULLSCREEN, false);
                if(resolucao == 0){
                    resolucao = 1;
                    continue;
                }
                else if(resolucao == 1) muda_tela(tela, 640, 360);
                else if(resolucao == 2) muda_tela(tela, 800, 450);
                else if(resolucao == 3) muda_tela(tela, 1024, 576);
                else if(resolucao == 4) muda_tela(tela, 1920, 1080);
                else if(resolucao == 5){
                    al_set_display_flag(display, ALLEGRO_FULLSCREEN, true);
                    ALLEGRO_MONITOR_INFO info;
                    al_get_monitor_info(0, &info);
                    muda_tela(tela, info.x2 - info.x1, info.y2 - info.x2);   
                }
                
                if(resolucao != 5)
                    al_resize_display(display, tela->x, tela->y);
                resolucao = 0;  
                return 2;

            } else if(selecionado == 3){

                return 1; //tela_inicio

            }

        }

        if(event.type == 10 && event.keyboard.keycode == 59){
            resolucao = 0;
        }

        if(nome){

        }

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            return 0; //fim execucao
        }
    }
}

int tela_de_inicio(ALLEGRO_EVENT_QUEUE * event_queue,
    ALLEGRO_BITMAP * inicio, ALLEGRO_FONT *font, tela *tela){

    int selecionado = 0;

    ALLEGRO_COLOR cor_button1 = al_map_rgb(0,0,0);
    ALLEGRO_COLOR cor_button2 = al_map_rgb(0,0,0);
    ALLEGRO_COLOR cor_button3 = al_map_rgb(0,0,0);

    while(1){
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_scaled_bitmap(inicio,
            0, 0, // Ponto de origem do bitmap (canto superior esquerdo)
            al_get_bitmap_width(inicio), // Largura original do bitmap
            al_get_bitmap_height(inicio), // Altura original do bitmap
            0, 0, // Ponto de destino na tela (canto superior esquerdo)
            tela->x, // Largura para desenhar (largura da tela)
            tela->y, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );

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

                return 3; //selecao

            } else if(selecionado == 2){

                return 2; //config

            } else if(selecionado == 3){

                return 0;//fim execucao

            }

        }

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){

            return 0; //fim execucao
        }
    }
}

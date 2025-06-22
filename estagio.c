#include "estagio.h"
#include "tela.h"
#include <stdio.h>

int tela_ganhou(ALLEGRO_EVENT_QUEUE * event_queue,
    ALLEGRO_BITMAP * fundo_fim, ALLEGRO_FONT *font, tela *tela){

    ALLEGRO_COLOR cor_button1 = al_map_rgb(100,0,0);

    int selecionado = 0;

    while(1){
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_scaled_bitmap(fundo_fim,
            0, 0, // Ponto de origem do bitmap (canto superior esquerdo)
            al_get_bitmap_width(fundo_fim), // Largura original do bitmap
            al_get_bitmap_height(fundo_fim), // Altura original do bitmap
            0, 0, // Ponto de destino na tela (canto superior esquerdo)
            tela->x, // Largura para desenhar (largura da tela)
            tela->y, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );

        if(event.keyboard.keycode == 19 && (event.type == 10)){
            if(selecionado == 0){
                cor_button1 = al_map_rgb(0,0,255);
                selecionado = 1;
            } else if(selecionado == 1){
                cor_button1 = al_map_rgb(100,0,0);
                selecionado = 0;
            }
        }

        if(event.keyboard.keycode == 23 && (event.type == 10)){
            if(selecionado == 1){
                cor_button1 = al_map_rgb(100,0,0);
                selecionado = 0;
            } else if(selecionado == 0){
                cor_button1 = al_map_rgb(0,0,255);
                selecionado = 1;
            }
        }

        al_draw_justified_text(font, al_map_rgb(255,255,255), tela->x/2 - tela->font*5.5, 0,
        tela->y/2 - tela->font*5.5, 0, 0, "PARABENS, VOCE GANHOU!!");

        al_draw_textf(font, al_map_rgb(255,255,255), tela->x/2, 
        tela->y/2 - tela->font*2.5, ALLEGRO_ALIGN_CENTRE, 
        "Com bravura inabalavel, voce se aventurou na cidade");
        al_draw_textf(font, al_map_rgb(255,255,255), tela->x/2, 
        tela->y/2 - tela->font*1.5, ALLEGRO_ALIGN_CENTRE, 
        "em ruinas. Ali, com a forca de mil lendas, aniquilou");
        al_draw_textf(font, al_map_rgb(255,255,255), tela->x/2, 
        tela->y/2 - tela->font*0.5, ALLEGRO_ALIGN_CENTRE, 
        "o exercito ciborgue e seu tirano lider. Por sua causa,");
        al_draw_textf(font, al_map_rgb(255,255,255), tela->x/2 ,
        tela->y/2 + tela->font*0.5, ALLEGRO_ALIGN_CENTRE, 
        "inumeras vidas foram poupadas, e das cinzas, a cidade");
        al_draw_textf(font, al_map_rgb(255,255,255), tela->x/2, 
        tela->y/2 + tela->font*1.5, ALLEGRO_ALIGN_CENTRE, 
        "erguer-se-á novamente, mais majestosa");
        al_draw_textf(font, al_map_rgb(255,255,255), tela->x/2, 
        tela->y/2 + tela->font*2.5, ALLEGRO_ALIGN_CENTRE, 
        "do que em seus dias de gloria.");

        al_draw_justified_text(font, cor_button1, tela->x/2 - tela->font*2, 0,
        tela->y/2 + tela->font*4.5, 0, 0, "Tela Inicial");


        al_flip_display();

        if(event.keyboard.keycode == 67 && event.type == 10){

            if(selecionado == 1)return 1;

        }
        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            return 0; //fim execucao
        }
    }
}

int tela_fim(ALLEGRO_EVENT_QUEUE * event_queue,
    ALLEGRO_BITMAP * fundo_fim, ALLEGRO_FONT *font, tela *tela, player *personagem){

    ALLEGRO_COLOR cor_button1 = al_map_rgb(100,0,0);
    ALLEGRO_COLOR cor_button2 = al_map_rgb(100,0,0);

    int selecionado = 0;

    while(1){
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_scaled_bitmap(fundo_fim,
            0, 0, // Ponto de origem do bitmap (canto superior esquerdo)
            al_get_bitmap_width(fundo_fim), // Largura original do bitmap
            al_get_bitmap_height(fundo_fim), // Altura original do bitmap
            0, 0, // Ponto de destino na tela (canto superior esquerdo)
            tela->x, // Largura para desenhar (largura da tela)
            tela->y, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );

        if(event.keyboard.keycode == 19 && (event.type == 10)){
            if(selecionado == 0){
                cor_button1 = al_map_rgb(0,0,255);
                cor_button2 = al_map_rgb(100,0,0);
                selecionado = 1;
            } else if(selecionado == 1){
                cor_button1 = al_map_rgb(100,0,0);
                cor_button2 = al_map_rgb(100,0,0);
                selecionado = 0;
            } else if(selecionado == 2){
                cor_button1 = al_map_rgb(100,0,0);
                cor_button2 = al_map_rgb(100,0,0);
                selecionado = 0;
            } 
        }

        if(event.keyboard.keycode == 23 && (event.type == 10)){
            if(selecionado == 2){
                cor_button1 = al_map_rgb(100,0,0);
                cor_button2 = al_map_rgb(100,0,0);
                selecionado = 0;
            } else if(selecionado == 1){
                cor_button1 = al_map_rgb(100,0,0);
                cor_button2 = al_map_rgb(100,0,0);
                selecionado = 0;
            } else if(selecionado == 0){
                cor_button1 = al_map_rgb(0,0,255);
                cor_button2 = al_map_rgb(100,0,0);
                selecionado = 1;
            }
        }

        //movimento para a esquerda
        if(event.keyboard.keycode == 1 && (event.type == 10)){
            if(selecionado == 0){
                selecionado = 2;
                cor_button1 = al_map_rgb(100,0,0);
                cor_button2 = al_map_rgb(0,0,255);

            } else if(selecionado == 1){
                selecionado = 0;
                cor_button1 = al_map_rgb(100,0,0);
                cor_button2 = al_map_rgb(100,0,0);

            } else if(selecionado == 2){
                selecionado = 1;
                cor_button1 = al_map_rgb(0,0,255);
                cor_button2 = al_map_rgb(100,0,0);
            }
        }

        if(event.keyboard.keycode == 4 && (event.type == 10)){
            if(selecionado == 0){
                selecionado = 1;
                cor_button1 = al_map_rgb(0,0,255);
                cor_button2 = al_map_rgb(100,0,0);

            } else if(selecionado == 1){
                selecionado = 2;
                cor_button1 = al_map_rgb(100,0,0);
                cor_button2 = al_map_rgb(0,0,255);

            } else if(selecionado == 2){
                selecionado = 0;
                cor_button1 = al_map_rgb(100,0,0);
                cor_button2 = al_map_rgb(100,0,0);
            }
        }

        al_draw_justified_text(font, al_map_rgb(255,255,255), tela->x/2 - tela->font*3.5, 0,
        tela->y/2 - tela->font*5.5, 0, 0, "GAME OVER!!");

        al_draw_textf(
            font,                                     
            al_map_rgb(255,255,255),                  
            tela->x/2,               
            tela->y/2 - tela->font*2.5,               
            ALLEGRO_ALIGN_CENTRE,                     
            "Seu personagem realizou %d assassinatos",
            personagem->kill                          
        );

        al_draw_justified_text(font, al_map_rgb(255,255,255), tela->x/2 - tela->font*5, 0,
        tela->y/2 + tela->font*1, 0, 0, "Deseja tentar novamente?");

        al_draw_justified_text(font, cor_button1, tela->x/2 - tela->font*2.5, 0,
        tela->y/2 + tela->font*3, 0, 0, "SIM");

        al_draw_justified_text(font, cor_button2, tela->x/2 + tela->font*1.5, 0,
        tela->y/2 + tela->font*3, 0, 0, "NÃO");

        al_flip_display();

        if(event.keyboard.keycode == 67 && event.type == 10){

            if(selecionado == 1){
                if(personagem->kill == 6) return 6;
                else return 5;
            }
            else if(selecionado == 2)return 1;

        }
        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            return 0; //fim execucao
        }
    }
}

int tela_fase1(ALLEGRO_EVENT_QUEUE * event_queue,
    ALLEGRO_BITMAP * fundo_jogo, ALLEGRO_FONT *font, tela *tela, player *personagem){

    return jogo(event_queue, fundo_jogo, font, tela, personagem);
}

int tela_boss(ALLEGRO_EVENT_QUEUE * event_queue,
    ALLEGRO_BITMAP * fundo_boss, ALLEGRO_FONT *font, tela *tela, player *personagem){

    return jogo_boss(event_queue, fundo_boss, font, tela, personagem);
}

int tela_selecao_fase(ALLEGRO_EVENT_QUEUE * event_queue,
    ALLEGRO_BITMAP * fundo_selecao, ALLEGRO_FONT *font, tela *tela, int *fase){

        ALLEGRO_BITMAP * fase1;
        fase1 = al_load_bitmap("sprites/fundo/fundo_jogo/background_1/origbig.png");
        ALLEGRO_BITMAP * fase2;
        fase2 = al_load_bitmap("sprites/fundo/fundo_jogo/background_3/origbig.png");
    
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
    
            al_draw_justified_text(font, al_map_rgb(100,0,0), tela->x/2 - tela->font*5, 0,
                tela->font*2, 0, 0, "O INICIO");
    
            al_draw_filled_rectangle(tela->x/2 - tela->font*6, tela->y/2 - tela->font*3, 
                tela->x/2 - tela->font*5 + tela->font*4, 
                tela->y/2 - tela->font*2 + tela->font*4, cor_button1);
    
            al_draw_scaled_bitmap(fase1,
                0, 0, // imagem 3
                1080, //largura
                1080, // altura
                tela->x/2 - tela->font*5.5, tela->y/2 - tela->font*2.5, // Ponto de destino na tela
                tela->font*4, // Largura para desenhar (largura da tela)
                tela->font*4, // Altura para desenhar (altura da tela)
                0 // Flags (normalmente 0)
            );
    
            al_draw_justified_text(font, al_map_rgb(100,0,0), tela->x/2 + tela->font*1.5, 0,
                tela->font*2, 0, 0, "O RETORNO");

            al_draw_filled_rectangle(tela->x/2 + tela->font, tela->y/2 - tela->font*3, 
                tela->x/2 + tela->font + tela->font*5, 
                tela->y/2 - tela->font*2 + tela->font*4, cor_button2);
    
            al_draw_scaled_bitmap(fase2,
                0, 0, // imagem 3
                1080, //largura
                1080, // altura
                tela->x/2 + tela->font*1.5, tela->y/2 - tela->font*2.5, // Ponto de destino na tela
                tela->font*4, // Largura para desenhar (largura da tela)
                tela->font*4, // Altura para desenhar (altura da tela)
                0 // Flags (normalmente 0)
            );
    
            al_draw_justified_text(font, cor_button3, tela->x/2 - tela->font*1.5, 0,
                tela->y/2 + tela->font*4, 0, 0, "VOLTAR");
    
            al_flip_display();
    
            if(event.keyboard.keycode == 67 && event.type == 10){
    
                if(selecionado == 1){
    
                    *fase = 1;
                    return 5; //estagio jogo
    
                } else if(selecionado == 2){
    
                    *fase = 2;
                    return 5; //estagio jogo
    
                } else if(selecionado == 3){
    
                    return 3; //estagio personagem
    
                }
    
            }
    
            if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                return 0; //terminar execucao
            }
    
        }
        
        
        al_destroy_bitmap(fase1);
        al_destroy_bitmap(fase2);
}

int tela_selecao(ALLEGRO_EVENT_QUEUE * event_queue,
    ALLEGRO_BITMAP * fundo_selecao, ALLEGRO_FONT *font, tela *tela, int *personagem){

    ALLEGRO_BITMAP * playerM;
    playerM = al_load_bitmap("sprites/personagem/mago/Fire_vizard/foto_mago.png");
    ALLEGRO_BITMAP * playerS;
    playerS = al_load_bitmap("sprites/personagem/soldado/Soldier_1/foto_soldado.png");

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
            tela->x/2 - tela->font*5 + tela->font*4, 
            tela->y/2 - tela->font*2 + tela->font*4, cor_button1);

        al_draw_scaled_bitmap(playerM,
            0, 0, // imagem 3
            1080, //largura
            1080, // altura
            tela->x/2 - tela->font*5.5, tela->y/2 - tela->font*2.5, // Ponto de destino na tela
            tela->font*4, // Largura para desenhar (largura da tela)
            tela->font*4, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );

        al_draw_filled_rectangle(tela->x/2 + tela->font, tela->y/2 - tela->font*3, 
            tela->x/2 + tela->font + tela->font*5, 
            tela->y/2 - tela->font*2 + tela->font*4, cor_button2);

        al_draw_scaled_bitmap(playerS,
            0, 0, // imagem 3
            1080, //largura
            1080, // altura
            tela->x/2 + tela->font*1.5, tela->y/2 - tela->font*2.5, // Ponto de destino na tela
            tela->font*4, // Largura para desenhar (largura da tela)
            tela->font*4, // Altura para desenhar (altura da tela)
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

#include "jogo.h"

flag *flag_creat(char frame_left, char frame_right, char cont){
    
    flag *teste = malloc(sizeof(flag));

    teste->frame_left = frame_left;
    teste->frame_right = frame_right;
    teste->cont = cont;

    return teste;
}

void fundo(tela *tela, camera *camera, ALLEGRO_BITMAP *fundo_jogo){
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
    al_draw_scaled_bitmap(fundo_jogo,
        0, 0, // Ponto de origem do bitmap (canto superior esquerdo)
        al_get_bitmap_width(fundo_jogo), // Largura original do bitmap
        al_get_bitmap_height(fundo_jogo), // Altura original do bitmap
        -camera->x + 3*tela->x, 0, // Ponto de destino na tela (canto superior esquerdo)
        tela->x, // Largura para desenhar (largura da tela)
        tela->y - tela->font, // Altura para desenhar (altura da tela)
        0 // Flags (normalmente 0)
    );
    al_draw_scaled_bitmap(fundo_jogo,
        0, 0, // Ponto de origem do bitmap (canto superior esquerdo)
        al_get_bitmap_width(fundo_jogo), // Largura original do bitmap
        al_get_bitmap_height(fundo_jogo), // Altura original do bitmap
        -camera->x + 4*tela->x, 0, // Ponto de destino na tela (canto superior esquerdo)
        tela->x, // Largura para desenhar (largura da tela)
        tela->y - tela->font, // Altura para desenhar (altura da tela)
        0 // Flags (normalmente 0)
    );
    al_draw_scaled_bitmap(fundo_jogo,
        0, 0, // Ponto de origem do bitmap (canto superior esquerdo)
        al_get_bitmap_width(fundo_jogo), // Largura original do bitmap
        al_get_bitmap_height(fundo_jogo), // Altura original do bitmap
        -camera->x + 5*tela->x, 0, // Ponto de destino na tela (canto superior esquerdo)
        tela->x, // Largura para desenhar (largura da tela)
        tela->y - tela->font, // Altura para desenhar (altura da tela)
        0 // Flags (normalmente 0)
    );
}

void evento_click(tela *tela, ALLEGRO_EVENT event, player *personagem){

    if((event.type == 10) || event.type == 12){
        //movimento para a esquerda
        if(event.keyboard.keycode == 1){
            joystick_left(personagem->controle);
            personagem->face = 1;
        }
        //movimento para a direita
        if(event.keyboard.keycode == 4){
            joystick_right(personagem->controle);
            personagem->face = 2;
        }

        //olhar para cima
        if(event.keyboard.keycode == 23 || event.keyboard.keycode == 23 && event.keyboard.keycode == 1 ||
            event.keyboard.keycode == 23 && event.keyboard.keycode == 4) personagem->face = 3;


        //agachar
        if(event.keyboard.keycode == 19) joystick_down(personagem->controle);
    }

    //atirar
    if(event.type == 10 && event.keyboard.keycode == 17) joystick_fire(personagem->controle);

    //pular
    if (event.type == 10 && event.keyboard.keycode == 75 && personagem->chao) {
        personagem->vel_y = tela->jump_strength;
        personagem->chao = 0;
        personagem->pulando = 1;
        joystick_up(personagem->controle);
    }
    //arma
    if(event.type == 10 && event.keyboard.keycode == 17 && 
        !personagem->controle->down && !personagem->controle->atirando && 
        !personagem->controle->up){
            joystick_atirando(personagem->controle);
    }
}

void atualiza_posicao(ALLEGRO_EVENT event, player *personagem, tela *tela, camera *camera, int limTela){
    
    //atualiza posicao
    if(event.type == 30){
        if(personagem->controle->left){
            player_move(personagem, 1, 0, limTela, tela->y);
            muda_camera(camera, tela, personagem->x - tela->x/2 + personagem->side_x/2, camera->y, limTela, camera->y);
        }
        if(personagem->controle->right){
            player_move(personagem, 1, 1, limTela, tela->y);
            muda_camera(camera, tela, personagem->x - tela->x/2 + personagem->side_x/2, camera->y, limTela, camera->y);
        }
        if(personagem->controle->fire && !personagem->controle->atirando){
            if(!personagem->fire->timer){
                player_shot(tela, personagem, camera);
                personagem->fire->timer = PISTOL_COOLDOWN;
            }
            joystick_fire(personagem->controle);
        }

    personagem->vel_y += tela->gravity;

    if (personagem->vel_y > tela->max_fall) personagem->vel_y = tela->max_fall;

    personagem->y += personagem->vel_y;

    float ground_level = tela->chao - personagem->side_y;

    if (personagem->y >= ground_level) {
        personagem->y = ground_level;
        personagem->vel_y = 0;
        personagem->chao = 1;
        personagem->pulando = 0;
        personagem->controle->up = 0;
    }

        bullet *previous = NULL;
        for(bullet *index = personagem->fire->shots; index != NULL;){

            if(index->trajectory == 1){
                index->x -= BULLET_MOVE;
                index->hitbox->x1 -= BULLET_MOVE;
                index->hitbox->x2 -= BULLET_MOVE;

                index->hitbox->x1 = index->x;
                index->hitbox->x2 = index->x + tela->font;
                index->hitbox->y1 = index->y + 1.2*tela->font;
                index->hitbox->y2 = index->y + 2*tela->font;

            }else if(index->trajectory == 2){
                index->x += BULLET_MOVE;
                index->hitbox->x1 += BULLET_MOVE;
                index->hitbox->x2 += BULLET_MOVE;

                index->hitbox->x1 = index->x + 2*tela->font;
                index->hitbox->x2 = index->x + 3*tela->font;
                index->hitbox->y1 = index->y + 1.2*tela->font;
                index->hitbox->y2 = index->y + 2*tela->font;

            }else if(index->trajectory == 3){
                index->y -= BULLET_MOVE;
                index->hitbox->y1 -= BULLET_MOVE;
                index->hitbox->y2 -= BULLET_MOVE;

                index->hitbox->x1 = index->x + 1.2*tela->font;
                index->hitbox->x2 = index->x + 2*tela->font;
                index->hitbox->y1 = index->y + 0.2*tela->font;
                index->hitbox->y2 = index->y + 1.3*tela->font;
            }

            if(index){
                //hitbox bala personagem

                al_draw_rectangle(index->hitbox->x1 - camera->x, index->hitbox->y1
                    , index->hitbox->x2 - camera->x, index->hitbox->y2, 
                al_map_rgb(0, 0, 255), 1.0f);
            }

            if(index->x - camera->x < 0 || index->x - camera->x >= tela->x || index->y < 0){
                if(previous){
                    previous->next = index->next;
                    bullet_destroy(index);
                    index = (bullet*) previous->next;
                
                } else {
                    personagem->fire->shots = (bullet*) index->next;
                    bullet_destroy(index);
                    index = personagem->fire->shots;
                }
            } else {
                previous = index;
                index = (bullet*) index->next;
            }

        }
    }
}

void atualiza_vida(ALLEGRO_EVENT event, player *personagem, ALLEGRO_BITMAP *coracao, 
                        tela *tela, camera *camera){
    switch (personagem->hp){
        case 5:
            al_draw_scaled_bitmap(coracao,
                0, 0, // Ponto de origem do bitmap (canto superior esquerdo)
                al_get_bitmap_width(coracao), // Largura original do bitmap
                al_get_bitmap_height(coracao), // Altura original do bitmap
                tela->font*4, 0, // Ponto de destino na tela (canto superior esquerdo)
                tela->font, // Largura para desenhar (largura da tela)
                tela->font, // Altura para desenhar (altura da tela)
                0 // Flags (normalmente 0)
            );
        case 4:
            al_draw_scaled_bitmap(coracao,
                0, 0, // Ponto de origem do bitmap (canto superior esquerdo)
                al_get_bitmap_width(coracao), // Largura original do bitmap
                al_get_bitmap_height(coracao), // Altura original do bitmap
                tela->font*3, 0, // Ponto de destino na tela (canto superior esquerdo)
                tela->font, // Largura para desenhar (largura da tela)
                tela->font, // Altura para desenhar (altura da tela)
                0 // Flags (normalmente 0)
            );
        case 3:
            al_draw_scaled_bitmap(coracao,
                0, 0, // Ponto de origem do bitmap (canto superior esquerdo)
                al_get_bitmap_width(coracao), // Largura original do bitmap
                al_get_bitmap_height(coracao), // Altura original do bitmap
                tela->font*2, 0, // Ponto de destino na tela (canto superior esquerdo)
                tela->font, // Largura para desenhar (largura da tela)
                tela->font, // Altura para desenhar (altura da tela)
                0 // Flags (normalmente 0)
            );
        case 2:
            al_draw_scaled_bitmap(coracao,
                0, 0, // Ponto de origem do bitmap (canto superior esquerdo)
                al_get_bitmap_width(coracao), // Largura original do bitmap
                al_get_bitmap_height(coracao), // Altura original do bitmap
                tela->font, 0, // Ponto de destino na tela (canto superior esquerdo)
                tela->font, // Largura para desenhar (largura da tela)
                tela->font, // Altura para desenhar (altura da tela)
                0 // Flags (normalmente 0)
            );
        case 1:
            al_draw_scaled_bitmap(coracao,
                0, 0, // Ponto de origem do bitmap (canto superior esquerdo)
                al_get_bitmap_width(coracao), // Largura original do bitmap
                al_get_bitmap_height(coracao), // Altura original do bitmap
                0, 0, // Ponto de destino na tela (canto superior esquerdo)
                tela->font, // Largura para desenhar (largura da tela)
                tela->font, // Altura para desenhar (altura da tela)
                0 // Flags (normalmente 0)
            );
        default:
            break;
    }
}

unsigned char check_kill(player *killer, player *victim){																																					//Implementação da função que verifica se um projétil acertou um jogador

	bullet *previous = NULL;
	for (bullet *index = killer->fire->shots; index != NULL; index = (bullet*) index->next){																													//Para todos os projéteis do atirador
        if ((index->hitbox->x2 > victim->hitbox->x1) && // Borda direita do projétil está à direita da borda esquerda da vítima
            (index->hitbox->x1 < victim->hitbox->x2) && // Borda esquerda do projétil está à esquerda da borda direita da vítima
            (index->hitbox->y2 > victim->hitbox->y1) && // Borda inferior do projétil está abaixo da borda superior da vítima
            (index->hitbox->y1 < victim->hitbox->y2))   // Borda superior do projétil está acima da borda inferior da vítima
            {
            victim->hp--;																																													//Reduz o HP da vítima em uma unidade (!)
			if (victim->hp){																																												//Verifica se a vítima ainda tem HP (!)
				if (previous){																																												//Verifica se não é o primeiro elemento da lista de projéteis (!)
					previous->next = index->next;																																							//Se não for, salva o próximo projétil (!)
					bullet_destroy(index);																																									//Chama o destrutor para o projétil atual (!)
					index = (bullet*) previous->next;																																						//Atualiza para o próximo projétil (!)
				}
				else {																																														//Se for o primeiro projétil da lista (!)
					killer->fire->shots = (bullet*) index->next;																																				//Atualiza o projétil no início da lista (!)
					bullet_destroy(index);																																									//Chama o destrutor para o projétil atual (!)
					index = killer->fire->shots;																																								//Atualiza para o próximo projétil (!)
				}
				return 0;																																													//A vítima sofreu dano, mas ainda não morre (!)
			}
			else return 1;																																													//A vítima sofreu dano e morreu (!)
		}
		previous = index;																																													//Atualiza a variável de controle do projétil anterior (!)
	}
	return 0;																																																//Se não houver nenhum projétil que acertou a vítima, retorne falso
}

void parado(ALLEGRO_EVENT event, tela *tela, player *personagem, camera *camera, flag *parado){

    //direita
    if(personagem->face == 2 || personagem->face == 3){

        personagem->hitbox->x1 = personagem->x + 1.5*tela->font;
        personagem->hitbox->x2 = personagem->x + 3*tela->font;
        personagem->hitbox->y1 = personagem->y + 2.8*tela->font;
        personagem->hitbox->y2 = personagem->y + 6*tela->font;

        al_draw_scaled_bitmap(personagem->aparencia[7],
            128*parado->frame_right, 0, // imagem 3
            128, //largura
            128, // altura
            personagem->x - camera->x, personagem->y, // Ponto de destino na tela
            personagem->side_x, // Largura para desenhar (largura da tela)
            personagem->side_y, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );

        if(event.type == ALLEGRO_EVENT_TIMER) parado->cont++;
        if(parado->cont == 6){
            parado->frame_right = (parado->frame_right + 1)%7;
            parado->cont = 0;
        }
    }
    //esquerda
    else if(personagem->face == 1){

        personagem->hitbox->x1 = personagem->x + 3*tela->font;
        personagem->hitbox->x2 = personagem->x + 4.5*tela->font;
        personagem->hitbox->y1 = personagem->y + 2.8*tela->font;
        personagem->hitbox->y2 = personagem->y + 6*tela->font;

        al_draw_scaled_bitmap(personagem->aparencia[13],
            128*parado->frame_left, 0, // imagem 3
            128, //largura
            128, // altura
            personagem->x - camera->x, personagem->y, // Ponto de destino na tela
            personagem->side_x, // Largura para desenhar (largura da tela)
            personagem->side_y, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );

        if(event.type == ALLEGRO_EVENT_TIMER) parado->cont++;
        if(parado->cont == 6){
            parado->frame_left = (parado->frame_left - 1);
            if(parado->frame_left < 0)parado->frame_left = 6;
            parado->cont = 0;
        }
    }
}

void parado_agachado(tela *tela, player *personagem, camera *camera){

    //direita
    if(personagem->face == 2 || personagem->face == 3){

        personagem->hitbox->x1 = personagem->x + 1.5*tela->font;
        personagem->hitbox->x2 = personagem->x + 3*tela->font;
        personagem->hitbox->y1 = personagem->y + 3.5*tela->font;
        personagem->hitbox->y2 = personagem->y + 6*tela->font;

        al_draw_scaled_bitmap(personagem->aparencia[6],
            128*0, 0, // imagem 3
            128, //largura
            128, // altura
            personagem->x - camera->x, personagem->y, // Ponto de destino na tela
            personagem->side_x, // Largura para desenhar (largura da tela)
            personagem->side_y, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );
    }
    //esquerda
    else if(personagem->face == 1){

        personagem->hitbox->x1 = personagem->x + 3*tela->font;
        personagem->hitbox->x2 = personagem->x + 4.5*tela->font;
        personagem->hitbox->y1 = personagem->y + 3.5*tela->font;
        personagem->hitbox->y2 = personagem->y + 6*tela->font;

        al_draw_scaled_bitmap(personagem->aparencia[12],
            128*2, 0, // imagem 3
            128, //largura
            128, // altura
            personagem->x - camera->x, personagem->y, // Ponto de destino na tela
            personagem->side_x, // Largura para desenhar (largura da tela)
            personagem->side_y, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );
    }
}

void andando(tela *tela, ALLEGRO_EVENT event, player *personagem, camera *camera, flag *andando){

    //direita
    if(personagem->controle->right){

        personagem->hitbox->x1 = personagem->x + 2.2*tela->font;
        personagem->hitbox->x2 = personagem->x + 3.5*tela->font;
        personagem->hitbox->y1 = personagem->y + 2.8*tela->font;
        personagem->hitbox->y2 = personagem->y + 6*tela->font;

        al_draw_scaled_bitmap(personagem->aparencia[10],
            128*andando->frame_right, 0, // imagem 3
            128, //largura
            128, // altura
            personagem->x - camera->x, personagem->y, // Ponto de destino na tela
            personagem->side_x, // Largura para desenhar (largura da tela)
            personagem->side_y, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );

        if(event.type == ALLEGRO_EVENT_TIMER) andando->cont++;
        if(andando->cont == 6){
            if(personagem->controle->down) andando->frame_right = (andando->frame_right + 1)%3;
            else andando->frame_right = (andando->frame_right + 1)%6;
            andando->cont = 0;
        }
    }
    //esquerda
    else if(personagem->controle->left){

        personagem->hitbox->x1 = personagem->x + 2.4*tela->font;
        personagem->hitbox->x2 = personagem->x + 3.8*tela->font;
        personagem->hitbox->y1 = personagem->y + 2.8*tela->font;
        personagem->hitbox->y2 = personagem->y + 6*tela->font;

        al_draw_scaled_bitmap(personagem->aparencia[11],
            128*andando->frame_left, 0, // imagem 3
            128, //largura
            128, // altura
            personagem->x - camera->x, personagem->y, // Ponto de destino na tela
            personagem->side_x, // Largura para desenhar (largura da tela)
            personagem->side_y, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );

        if(event.type == ALLEGRO_EVENT_TIMER) andando->cont++;
        if(andando->cont == 6){
            if(personagem->controle->down) andando->frame_left = (andando->frame_left + 1)%3;
            else andando->frame_left = (andando->frame_left - 1);
            if(andando->frame_left < 0) andando->frame_left = 5;
            andando->cont = 0;
        }
    }
}

void andando_agachado(tela *tela, ALLEGRO_EVENT event, player *personagem, camera *camera, flag *agachado){

    //direita
    if(personagem->controle->right){

        personagem->hitbox->x1 = personagem->x + 1.5*tela->font;
        personagem->hitbox->x2 = personagem->x + 3*tela->font;
        personagem->hitbox->y1 = personagem->y + 3.5*tela->font;
        personagem->hitbox->y2 = personagem->y + 6*tela->font;

        al_draw_scaled_bitmap(personagem->aparencia[6],
            128*agachado->frame_right, 0, // imagem 3
            128, //largura
            128, // altura
            personagem->x - camera->x, personagem->y, // Ponto de destino na tela
            personagem->side_x, // Largura para desenhar (largura da tela)
            personagem->side_y, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );

        if(event.type == ALLEGRO_EVENT_TIMER) agachado->cont++;
        if(agachado->cont == 6){
            if(personagem->controle->down) agachado->frame_right = (agachado->frame_right + 1)%3;
            else agachado->frame_right = (agachado->frame_right + 1)%6;
            agachado->cont = 0;
        }
    }
    //esquerda
    else if(personagem->controle->left){

        personagem->hitbox->x1 = personagem->x + 3*tela->font;
        personagem->hitbox->x2 = personagem->x + 4.5*tela->font;
        personagem->hitbox->y1 = personagem->y + 3.5*tela->font;
        personagem->hitbox->y2 = personagem->y + 6*tela->font;
    
        al_draw_scaled_bitmap(personagem->aparencia[12],
            128*agachado->frame_left, 0, // imagem 3
            128, //largura
            128, // altura
            personagem->x - camera->x, personagem->y, // Ponto de destino na tela
            personagem->side_x, // Largura para desenhar (largura da tela)
            personagem->side_y, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );

        if(event.type == ALLEGRO_EVENT_TIMER) agachado->cont++;
        if(agachado->cont == 6){
            if(personagem->controle->down) agachado->frame_left = (agachado->frame_left + 1)%3;
            else agachado->frame_left = (agachado->frame_left - 1);
            if(agachado->frame_left < 0) agachado->frame_left = 5;
            agachado->cont = 0;
        }
    }
}

void pulando(tela *tela, ALLEGRO_EVENT event, player *personagem, camera *camera, flag *pulando){
    // Lógica para determinar qual frame de pulo mostrar
    if (event.type == ALLEGRO_EVENT_TIMER) {
        pulando->cont++;
        if (pulando->cont >= 8) { // Velocidade da animação
            pulando->cont = 0;

            if (personagem->vel_y < 0) { // Subindo
                // Avance os frames para a animação de subida
                if (personagem->face == 2) {
                    pulando->frame_right = (pulando->frame_right + 1);
                    if(pulando->frame_right > 4) pulando->frame_right = 3;
                } else if (personagem->face == 1) {
                    pulando->frame_left = (pulando->frame_left - 1);
                    if (pulando->frame_left < 4) pulando->frame_left = 5;
                }
            } else { // Caindo
                // Avance os frames para a animação de queda
                if (personagem->face == 2) {
                    pulando->frame_right = pulando->frame_right + 1;
                    if(pulando->frame_right > 6) pulando->frame_right = 5;
                } else if (personagem->face == 1) {
                    pulando->frame_left = (pulando->frame_left - 1);
                    if (pulando->frame_left < 2) pulando->frame_left = 3;
                }
            }
        }
    }
    
    // Desenha o sprite correto
    if(personagem->face == 2 || personagem->face == 3){

        personagem->hitbox->x1 = personagem->x + 1.5*tela->font;
        personagem->hitbox->x2 = personagem->x + 3*tela->font;
        personagem->hitbox->y1 = personagem->y + 2.8*tela->font;
        personagem->hitbox->y2 = personagem->y + 6*tela->font;

        al_draw_scaled_bitmap(personagem->aparencia[8], // Sprite sheet de pulo para direita
            128 * pulando->frame_right, 0,
            128, 128,
            personagem->x - camera->x, personagem->y,
            personagem->side_x, personagem->side_y,
            0
        );
    } else if(personagem->face == 1){

        personagem->hitbox->x1 = personagem->x + 3*tela->font;
        personagem->hitbox->x2 = personagem->x + 4.5*tela->font;
        personagem->hitbox->y1 = personagem->y + 2.8*tela->font;
        personagem->hitbox->y2 = personagem->y + 6*tela->font;

        al_draw_scaled_bitmap(personagem->aparencia[14], // Sprite sheet de pulo para esquerda
            128 * pulando->frame_left, 0,
            128, 128,
            personagem->x - camera->x, personagem->y,
            personagem->side_x, personagem->side_y,
            0
        );
    }
}

void atirar(ALLEGRO_EVENT event, player *personagem, camera *camera, flag *atirando){

    //direita
    if(personagem->face == 2 || personagem->face == 3){
        al_draw_scaled_bitmap(personagem->aparencia[4],
            128*atirando->frame_right, 0, // imagem x
            128, //largura
            128, // altura
            personagem->x - camera->x, personagem->y, // Ponto de destino na tela
            personagem->side_x, // Largura para desenhar (largura da tela)
            personagem->side_y, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );

        if(event.type == ALLEGRO_EVENT_TIMER)atirando->cont++;
        if(atirando->cont >= 3){
            atirando->frame_right = atirando->frame_right + 1;
            atirando->cont = 0;
        }
        if(atirando->frame_right > 7){
            atirando->frame_right = 0;
            joystick_atirando(personagem->controle);
        }
    }
    //esquerda
    else if(personagem->face == 1){
        al_draw_scaled_bitmap(personagem->aparencia[15],
            128*atirando->frame_left, 0, // imagem x
            128, //largura
            128, // altura
            personagem->x - camera->x, personagem->y, // Ponto de destino na tela
            personagem->side_x, // Largura para desenhar (largura da tela)
            personagem->side_y, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );

        if(event.type == ALLEGRO_EVENT_TIMER)atirando->cont++;
        if(atirando->cont >= 3){
            atirando->frame_left = atirando->frame_left - 1;
            atirando->cont = 0;
        }
        if(atirando->frame_left < 0){
            atirando->frame_left = 7;
            joystick_atirando(personagem->controle);
        }
    }
}

void tiro(ALLEGRO_EVENT event, player *personagem, tela *tela, camera *camera, flag *tiro){
    for(bullet *index = personagem->fire->shots; index != NULL; index = (bullet*)index->next){
        if(index->trajectory == 1){
            al_draw_scaled_bitmap(personagem->aparencia[16],
                64*tiro->frame_left, 0, // imagem x
                64, //largura
                64, // altura
                index->x - camera->x, index->y, // Ponto de destino na tela
                tela->font*3, // Largura para desenhar (largura da tela)
                tela->font*3, // Altura para desenhar (altura da tela)
                0 // Flags (normalmente 0)
            );
        } else if(index->trajectory == 2){
            al_draw_scaled_bitmap(personagem->aparencia[2],
                64*tiro->frame_right, 0, // imagem x
                64, //largura
                64, // altura
                index->x - camera->x, index->y, // Ponto de destino na tela
                tela->font*3, // Largura para desenhar (largura da tela)
                tela->font*3, // Altura para desenhar (altura da tela)
                0 // Flags (normalmente 0)
            );
        } else if(index->trajectory == 3){
            al_draw_scaled_bitmap(personagem->aparencia[17],
                0, 64*tiro->frame_left, // imagem x
                64, //largura
                64, // altura
                index->x - camera->x, index->y, // Ponto de destino na tela
                tela->font*3, // Largura para desenhar (largura da tela)
                tela->font*3, // Altura para desenhar (altura da tela)
                0 // Flags (normalmente 0)
            );
        }
    }
    if(personagem->fire->timer) personagem->fire->timer--;
    if(event.type == ALLEGRO_EVENT_TIMER)tiro->cont++;
    if(tiro->cont >= 3){
        tiro->frame_left = tiro->frame_left - 1;
        tiro->frame_right = (tiro->frame_right + 1)%7;
        tiro->cont = 0;
    }
    if(tiro->frame_left < 6) tiro->frame_left = 11;
}

unsigned char player_morre(ALLEGRO_EVENT event, player *personagem, camera *camera, flag *morre){
    //direita
    if(personagem->face == 2 || personagem->face == 3){
        al_draw_scaled_bitmap(personagem->aparencia[3],
            128*morre->frame_right, 0, // imagem 3
            128, //largura
            128, // altura
            personagem->x - camera->x, personagem->y, // Ponto de destino na tela
            personagem->side_x, // Largura para desenhar (largura da tela)
            personagem->side_y, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );

        if(event.type == ALLEGRO_EVENT_TIMER) morre->cont++;
        if(morre->cont >= 10){
            morre->frame_right = morre->frame_right + 1;
            if(morre->frame_right >= 6)return 1;
            morre->cont = 0;
        }
    }
    //esquerda
    else if(personagem->face == 1){
        al_draw_scaled_bitmap(personagem->aparencia[18],
            128*morre->frame_left, 0, // imagem 3
            128, //largura
            128, // altura
            personagem->x - camera->x, personagem->y, // Ponto de destino na tela
            personagem->side_x, // Largura para desenhar (largura da tela)
            personagem->side_y, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );

        if(event.type == ALLEGRO_EVENT_TIMER) morre->cont++;
        if(morre->cont >= 10){
            morre->frame_left = (morre->frame_left - 1);
            if(morre->frame_left < 0){
                morre->frame_left = 5;
                return 1;
            }
            morre->cont = 0;
        }
    }
    return 0;
}

void inimigo_parado(tela *tela, ALLEGRO_EVENT event, player *inimigo, camera *camera, flag *parado){
    //direita
    if(inimigo->face == 2){

        inimigo->hitbox->x1 = inimigo->x + 1.5*tela->font;
        inimigo->hitbox->x2 = inimigo->x + 3*tela->font;
        inimigo->hitbox->y1 = inimigo->y + 2*tela->font;
        inimigo->hitbox->y2 = inimigo->y + 8*tela->font;

        al_draw_scaled_bitmap(inimigo->aparencia[4],
            128*parado->frame_right, 0, // imagem 3
            128, //largura
            128, // altura
            inimigo->x - camera->x, inimigo->y, // Ponto de destino na tela
            inimigo->side_x, // Largura para desenhar (largura da tela)
            inimigo->side_y, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );

        if(event.type == ALLEGRO_EVENT_TIMER) parado->cont++;
        if(parado->cont == 6){
            parado->frame_right = (parado->frame_right + 1)%8;
            parado->cont = 0;
        }
    }
    //esquerda
    else if(inimigo->face == 1){

        inimigo->hitbox->x1 = inimigo->x + 3*tela->font;
        inimigo->hitbox->x2 = inimigo->x + 5*tela->font;
        inimigo->hitbox->y1 = inimigo->y + 4*tela->font;
        inimigo->hitbox->y2 = inimigo->y + 8*tela->font;

        al_draw_scaled_bitmap(inimigo->aparencia[12],
            128*parado->frame_left, 0, // imagem 3
            128, //largura
            128, // altura
            inimigo->x - camera->x, inimigo->y, // Ponto de destino na tela
            inimigo->side_x, // Largura para desenhar (largura da tela)
            inimigo->side_y, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );

        if(event.type == ALLEGRO_EVENT_TIMER) parado->cont++;
        if(parado->cont == 6){
            parado->frame_left = (parado->frame_left - 1);
            if(parado->frame_left < 0)parado->frame_left = 7;
            parado->cont = 0;
        }
    }
}

void inimigo_ataca(ALLEGRO_EVENT event, player *inimigo, tela *tela, camera *camera, flag *tiro){

    bullet *previous = NULL;
    for(bullet *index = inimigo->fire->shots; index != NULL;){
        if(index->trajectory == 1){
            index->x -= BULLET_MOVE;
            index->hitbox->x1 -= BULLET_MOVE;
            index->hitbox->x2 -= BULLET_MOVE;

            index->hitbox->x1 = index->x + 0.5*tela->font;
            index->hitbox->x2 = index->x + 1.2*tela->font;
            index->hitbox->y1 = index->y + 1.8*tela->font;
            index->hitbox->y2 = index->y + 2.2*tela->font;

        }else if(index->trajectory == 2){
            index->x += BULLET_MOVE;
            index->hitbox->x1 += BULLET_MOVE;
            index->hitbox->x2 += BULLET_MOVE;

            index->hitbox->x1 = index->x + 0.8*tela->font;
            index->hitbox->x2 = index->x + 1.6*tela->font;
            index->hitbox->y1 = index->y + 1.8*tela->font;
            index->hitbox->y2 = index->y + 2.2*tela->font;

        }else if(index->trajectory == 3){
            index->y -= BULLET_MOVE;
            index->hitbox->y1 -= BULLET_MOVE;
            index->hitbox->y2 -= BULLET_MOVE;
        }

        if(index){
            //hitbox bala personagem

            al_draw_rectangle(index->hitbox->x1 - camera->x, index->hitbox->y1
                , index->hitbox->x2 - camera->x, index->hitbox->y2, 
            al_map_rgb(255, 0, 255), 1.0f);
        }

        if(index->x < 0 || index->x > 8*tela->x || index->y < 0){
            if(previous){
                previous->next = index->next;
                bullet_destroy(index);
                index = (bullet*) previous->next;
            
            } else {
                inimigo->fire->shots = (bullet*) index->next;
                bullet_destroy(index);
                index = inimigo->fire->shots;
            }
        } else {
            previous = index;
            index = (bullet*) index->next;
        }
    }

    for(bullet *index = inimigo->fire->shots; index != NULL; index = (bullet*)index->next){
        if(index->trajectory == 1){
            al_draw_scaled_bitmap(inimigo->aparencia[11],
                64*tiro->frame_left, 0, // imagem x
                64, //largura
                64, // altura
                index->x - camera->x, index->y, // Ponto de destino na tela
                tela->font*2, // Largura para desenhar (largura da tela)
                tela->font*2, // Altura para desenhar (altura da tela)
                0 // Flags (normalmente 0)
            );
        } else if(index->trajectory == 2){
            al_draw_scaled_bitmap(inimigo->aparencia[1],
                64*tiro->frame_right, 0, // imagem x
                64, //largura
                64, // altura
                index->x - camera->x, index->y, // Ponto de destino na tela
                tela->font*2, // Largura para desenhar (largura da tela)
                tela->font*2, // Altura para desenhar (altura da tela)
                0 // Flags (normalmente 0)
            );
        } else if(index->trajectory == 3){
            al_draw_scaled_bitmap(inimigo->aparencia[1],
                0, 64*tiro->frame_left, // imagem x
                64, //largura
                64, // altura
                index->x - camera->x, index->y, // Ponto de destino na tela
                tela->font*2, // Largura para desenhar (largura da tela)
                tela->font*2, // Altura para desenhar (altura da tela)
                0 // Flags (normalmente 0)
            );
        }
    }
    if(inimigo->fire->timer) inimigo->fire->timer--;
    if(event.type == ALLEGRO_EVENT_TIMER)tiro->cont++;
    if(tiro->cont >= 3){
        tiro->frame_left = tiro->frame_left - 1;
        tiro->frame_right = (tiro->frame_right + 1)%6;
        tiro->cont = 0;
    }
    if(tiro->frame_left < 0) tiro->frame_left = 5;
}

void inimigo_atirando(ALLEGRO_EVENT event, player *inimigo, camera *camera, flag *atirando){
    //direita
    if(inimigo->face == 2){
        al_draw_scaled_bitmap(inimigo->aparencia[9],
            128*atirando->frame_right, 0, // imagem x
            128, //largura
            128, // altura
            inimigo->x - camera->x, inimigo->y, // Ponto de destino na tela
            inimigo->side_x, // Largura para desenhar (largura da tela)
            inimigo->side_y, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );

        if(event.type == ALLEGRO_EVENT_TIMER)atirando->cont++;
        if(atirando->cont >= 3){
            atirando->frame_right = (atirando->frame_right + 1)%4;
            atirando->cont = 0;
        }
    }
    //esquerda
    else if(inimigo->face == 1){
        al_draw_scaled_bitmap(inimigo->aparencia[13],
            128*atirando->frame_left, 0, // imagem x
            128, //largura
            128, // altura
            inimigo->x - camera->x, inimigo->y, // Ponto de destino na tela
            inimigo->side_x, // Largura para desenhar (largura da tela)
            inimigo->side_y, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );

        if(event.type == ALLEGRO_EVENT_TIMER)atirando->cont++;
        if(atirando->cont >= 6){
            atirando->frame_left = atirando->frame_left - 1;
            atirando->cont = 0;
        }
        if(atirando->frame_left < 0){
            atirando->frame_left = 3;
        }
    }
}

unsigned char inimigo_morre(ALLEGRO_EVENT event, player *inimigo, camera *camera, flag *morre){
        //direita
        if(inimigo->face == 2){
            al_draw_scaled_bitmap(inimigo->aparencia[2],
                128*morre->frame_right, 0, // imagem 3
                128, //largura
                128, // altura
                inimigo->x - camera->x, inimigo->y, // Ponto de destino na tela
                inimigo->side_x, // Largura para desenhar (largura da tela)
                inimigo->side_y, // Altura para desenhar (altura da tela)
                0 // Flags (normalmente 0)
            );
    
            if(event.type == ALLEGRO_EVENT_TIMER) morre->cont++;
            if(morre->cont >= 10){
                morre->frame_right = morre->frame_right + 1;
                if(morre->frame_right >= 5)return 1;
                morre->cont = 0;
            }
        }
        //esquerda
        else if(inimigo->face == 1){
            al_draw_scaled_bitmap(inimigo->aparencia[14],
                128*morre->frame_left, 0, // imagem 3
                128, //largura
                128, // altura
                inimigo->x - camera->x, inimigo->y, // Ponto de destino na tela
                inimigo->side_x, // Largura para desenhar (largura da tela)
                inimigo->side_y, // Altura para desenhar (altura da tela)
                0 // Flags (normalmente 0)
            );
    
            if(event.type == ALLEGRO_EVENT_TIMER) morre->cont++;
            if(morre->cont >= 10){
                morre->frame_left = (morre->frame_left - 1);
                if(morre->frame_left < 0){
                    morre->frame_left = 4;
                    return 1;
                }
                morre->cont = 0;
            }
        }
        return 0;
}

void inimigo_agachado(tela *tela, ALLEGRO_EVENT event, player *inimigo, camera *camera, flag *agachado){
    //direita
    if(inimigo->face == 2){

        inimigo->hitbox->x1 = inimigo->x + 1.5*tela->font;
        inimigo->hitbox->x2 = inimigo->x + 3*tela->font;
        inimigo->hitbox->y1 = inimigo->y + 2*tela->font;
        inimigo->hitbox->y2 = inimigo->y + 8*tela->font;

        al_draw_scaled_bitmap(inimigo->aparencia[8],
            128*agachado->frame_right, 0, // imagem 3
            128, //largura
            128, // altura
            inimigo->x - camera->x, inimigo->y, // Ponto de destino na tela
            inimigo->side_x, // Largura para desenhar (largura da tela)
            inimigo->side_y, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );

        if(event.type == ALLEGRO_EVENT_TIMER) agachado->cont++;
        if(agachado->cont == 8){
            agachado->frame_right = (agachado->frame_right + 1)%4;
            agachado->cont = 0;
        }
    }
    //esquerda
    else if(inimigo->face == 1){

        inimigo->hitbox->x1 = inimigo->x + 3.5*tela->font;
        inimigo->hitbox->x2 = inimigo->x + 5.5*tela->font;
        inimigo->hitbox->y1 = inimigo->y + 4*tela->font;
        inimigo->hitbox->y2 = inimigo->y + 8*tela->font;

        al_draw_scaled_bitmap(inimigo->aparencia[15],
            128*agachado->frame_left, 0, // imagem 3
            128, //largura
            128, // altura
            inimigo->x - camera->x, inimigo->y, // Ponto de destino na tela
            inimigo->side_x, // Largura para desenhar (largura da tela)
            inimigo->side_y, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );

        if(event.type == ALLEGRO_EVENT_TIMER) agachado->cont++;
        if(agachado->cont == 8){
            agachado->frame_left = (agachado->frame_left - 1);
            if(agachado->frame_left < 0)agachado->frame_left = 3;
            agachado->cont = 0;
        }
    }
}

void inimigo_andando(tela *tela, ALLEGRO_EVENT event, player *inimigo, camera *camera, flag *andando){

    //direita
    if(inimigo->controle->right){

        inimigo->hitbox->x1 = inimigo->x + 2.2*tela->font;
        inimigo->hitbox->x2 = inimigo->x + 3.5*tela->font;
        inimigo->hitbox->y1 = inimigo->y + 2.8*tela->font;
        inimigo->hitbox->y2 = inimigo->y + 6*tela->font;

        al_draw_scaled_bitmap(inimigo->aparencia[10],
            128*andando->frame_right, 0, // imagem 3
            128, //largura
            128, // altura
            inimigo->x - camera->x, inimigo->y, // Ponto de destino na tela
            inimigo->side_x, // Largura para desenhar (largura da tela)
            inimigo->side_y, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );

        if(event.type == ALLEGRO_EVENT_TIMER) andando->cont++;
        if(andando->cont == 6){
            if(inimigo->controle->down) andando->frame_right = (andando->frame_right + 1)%3;
            else andando->frame_right = (andando->frame_right + 1)%6;
            andando->cont = 0;
        }
    }
    //esquerda
    else if(inimigo->controle->left){

        inimigo->hitbox->x1 = inimigo->x + 2.4*tela->font;
        inimigo->hitbox->x2 = inimigo->x + 3.8*tela->font;
        inimigo->hitbox->y1 = inimigo->y + 2.8*tela->font;
        inimigo->hitbox->y2 = inimigo->y + 6*tela->font;

        al_draw_scaled_bitmap(inimigo->aparencia[11],
            128*andando->frame_left, 0, // imagem 3
            128, //largura
            128, // altura
            inimigo->x - camera->x, inimigo->y, // Ponto de destino na tela
            inimigo->side_x, // Largura para desenhar (largura da tela)
            inimigo->side_y, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );

        if(event.type == ALLEGRO_EVENT_TIMER) andando->cont++;
        if(andando->cont == 6){
            if(inimigo->controle->down) andando->frame_left = (andando->frame_left + 1)%3;
            else andando->frame_left = (andando->frame_left - 1);
            if(andando->frame_left < 0) andando->frame_left = 5;
            andando->cont = 0;
        }
    }
}

void boss_parado(tela *tela, ALLEGRO_EVENT event, player *boss, camera *camera, flag *parado){
    //direita
    if(boss->face == 2){

        boss->hitbox->x1 = boss->x + 0.3*tela->font;
        boss->hitbox->x2 = boss->x + 5*tela->font;
        boss->hitbox->y1 = boss->y + 2.8*tela->font;
        boss->hitbox->y2 = boss->y + 10*tela->font;

        al_draw_scaled_bitmap(boss->aparencia[16],
            0, 0, // imagem 3
            48, //largura
            48, // altura
            boss->x + 0.7*tela->font - camera->x, boss->y + 1.9*tela->font, // Ponto de destino na tela
            boss->side_x, // Largura para desenhar (largura da tela)
            boss->side_y, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );

        al_draw_scaled_bitmap(boss->aparencia[0],
            48*parado->frame_right, 0, // imagem 3
            48, //largura
            48, // altura
            boss->x - camera->x, boss->y, // Ponto de destino na tela
            boss->side_x, // Largura para desenhar (largura da tela)
            boss->side_y, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );

        if(event.type == ALLEGRO_EVENT_TIMER) parado->cont++;
        if(parado->cont == 6){
            parado->frame_right = (parado->frame_right + 1)%4;
            parado->cont = 0;
        }
    }
    //esquerda
    else if(boss->face == 1){

        boss->hitbox->x1 = boss->x + 5*tela->font;
        boss->hitbox->x2 = boss->x + 9.8*tela->font;
        boss->hitbox->y1 = boss->y + 2.8*tela->font;
        boss->hitbox->y2 = boss->y + 10*tela->font;

        al_draw_scaled_bitmap(boss->aparencia[17],
            0, 0, // imagem 3
            48, //largura
            48, // altura
            boss->x + 2.6*tela->font - camera->x, boss->y + 1.9*tela->font, // Ponto de destino na tela
            boss->side_x, // Largura para desenhar (largura da tela)
            boss->side_y, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );

        al_draw_scaled_bitmap(boss->aparencia[10],
            48*parado->frame_left, 0, // imagem 3
            48, //largura
            48, // altura
            boss->x - camera->x, boss->y, // Ponto de destino na tela
            boss->side_x, // Largura para desenhar (largura da tela)
            boss->side_y, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );

        if(event.type == ALLEGRO_EVENT_TIMER) parado->cont++;
        if(parado->cont == 6){
            parado->frame_left = (parado->frame_left - 1);
            if(parado->frame_left < 0)parado->frame_left = 3;
            parado->cont = 0;
        }
    }
}

unsigned char boss_morre(ALLEGRO_EVENT event, player *boss, camera *camera, flag *morre){
    //direita
    if(boss->face == 2){
        al_draw_scaled_bitmap(boss->aparencia[11],
            128*morre->frame_right, 0, // imagem 3
            128, //largura
            128, // altura
            boss->x - camera->x - boss->side_x/4, boss->y, // Ponto de destino na tela
            boss->side_x, // Largura para desenhar (largura da tela)
            boss->side_y, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );

        if(event.type == ALLEGRO_EVENT_TIMER) morre->cont++;
        if(morre->cont >= 4){
            morre->frame_right = morre->frame_right + 1;
            if(morre->frame_right > 8)return 1;
            morre->cont = 0;
        }
    }
    //esquerda
    else if(boss->face == 1){
        al_draw_scaled_bitmap(boss->aparencia[12],
            128*morre->frame_left, 0, // imagem 3
            128, //largura
            128, // altura
            boss->x - camera->x + boss->side_x/4, boss->y, // Ponto de destino na tela
            boss->side_x, // Largura para desenhar (largura da tela)
            boss->side_y, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );

        if(event.type == ALLEGRO_EVENT_TIMER) morre->cont++;
        if(morre->cont >= 4){
            morre->frame_left = (morre->frame_left - 1);
            if(morre->frame_left < 0){
                morre->frame_left = 8;
                return 1;
            }
            morre->cont = 0;
        }
    }
    return 0;
}

void boss_pulando(tela *tela, ALLEGRO_EVENT event, player *boss, camera *camera, flag *pulando){
    // Lógica para determinar qual frame de pulo mostrar
    if (event.type == ALLEGRO_EVENT_TIMER) {
        pulando->cont++;
        if (pulando->cont >= 7) { // Velocidade da animação
            pulando->cont = 0;

            if (boss->vel_y < 0) { // Subindo
                // Avança os frames para a animação de subida
                if (boss->face == 2) {
                    pulando->frame_right = (pulando->frame_right + 1);
                    if(pulando->frame_right > 1) pulando->frame_right = 0;
                } else if (boss->face == 1) {
                    pulando->frame_left = (pulando->frame_left - 1);
                    if (pulando->frame_left < 2) pulando->frame_left = 3;
                }
            } else { // Caindo
                // Avança os frames para a animação de queda
                if (boss->face == 2) {
                    pulando->frame_right = pulando->frame_right + 1;
                    if(pulando->frame_right > 3){
                        pulando->frame_right = 2;
                        boss->face = 1;
                    }
                } else if (boss->face == 1) {
                    pulando->frame_left = (pulando->frame_left - 1);
                    if (pulando->frame_left < 0){
                        pulando->frame_left = 1;
                        boss->face = 2;
                    }
                }
            }
        }
    }
    
    // Desenha o sprite correto
    if(boss->face == 2){

        boss->hitbox->x1 = boss->x + 0.3*tela->font;
        boss->hitbox->x2 = boss->x + 5*tela->font;
        boss->hitbox->y1 = boss->y + 2.8*tela->font;
        boss->hitbox->y2 = boss->y + 10*tela->font;

        al_draw_scaled_bitmap(boss->aparencia[2], // Sprite sheet de pulo para direita
            48 * pulando->frame_right, 0,
            48, 48,
            boss->x - camera->x, boss->y + tela->font,
            boss->side_x, boss->side_y,
            0
        );
    } else if(boss->face == 1){

        boss->hitbox->x1 = boss->x + 5*tela->font;
        boss->hitbox->x2 = boss->x + 9.8*tela->font;
        boss->hitbox->y1 = boss->y + 2.8*tela->font;
        boss->hitbox->y2 = boss->y + 10*tela->font;

        al_draw_scaled_bitmap(boss->aparencia[13], // Sprite sheet de pulo para esquerda
            48 * pulando->frame_left, 0,
            48, 48,
            boss->x - camera->x, boss->y + tela->font,
            boss->side_x, boss->side_y,
            0
        );
    }
}

void boss_atualiza_posicao(ALLEGRO_EVENT event, player *boss, tela *tela, camera *camera, int limTela){
    
    //atualiza posicao
    if(event.type == 30){

        boss->vel_y += tela->gravity;

        if (boss->vel_y > tela->max_fall) boss->vel_y = tela->max_fall;

        boss->y += boss->vel_y;

        float ground_level = tela->chao - boss->side_y;

        if (boss->y >= ground_level) {
            boss->y = ground_level;
            boss->vel_y = 0;
            boss->chao = 1;
            boss->pulando = 0;
            boss->controle->up = 0;
        }

        if(boss->controle->up){
            if(boss->face == 2){
                boss->x += tela->font/4;
                if(boss->x >= limTela) boss->x -= tela->font/4;
            } else if(boss->face == 1){
                boss->x -= tela->font/4;
                if(boss->x <= 0) boss->x += tela->font/4;
            }
        }

    }
}

void boss_atirando_baixo(tela *tela, ALLEGRO_EVENT event, player *boss, camera *camera, flag *parado){
    
    //direita
    if(boss->face == 2){

        boss->hitbox->x1 = boss->x + 0.3*tela->font;
        boss->hitbox->x2 = boss->x + 5*tela->font;
        boss->hitbox->y1 = boss->y + 2.8*tela->font;
        boss->hitbox->y2 = boss->y + 10*tela->font;

        al_draw_scaled_bitmap(boss->aparencia[15],
            0, 0, // imagem x
            32, //largura
            32, // altura
            boss->x + 1.5*tela->font - camera->x, 4.2*tela->font, // Ponto de destino na tela
            boss->side_x/1.5, // Largura para desenhar (largura da tela)
            boss->side_y/1.5, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );

        al_draw_scaled_bitmap(boss->aparencia[0],
            48*parado->frame_right, 0, // imagem 3
            48, //largura
            48, // altura
            boss->x - camera->x, boss->y, // Ponto de destino na tela
            boss->side_x, // Largura para desenhar (largura da tela)
            boss->side_y, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );

        if(event.type == ALLEGRO_EVENT_TIMER) parado->cont++;
        if(parado->cont == 6){
            parado->frame_right = (parado->frame_right + 1)%4;
            parado->cont = 0;
        }
    }
    //esquerda
    else if(boss->face == 1){

        boss->hitbox->x1 = boss->x + 5*tela->font;
        boss->hitbox->x2 = boss->x + 9.8*tela->font;
        boss->hitbox->y1 = boss->y + 2.8*tela->font;
        boss->hitbox->y2 = boss->y + 10*tela->font;

        al_draw_scaled_bitmap(boss->aparencia[14],
            0, 0, // imagem x
            32, //largura
            32, // altura
            boss->x + 1.5*tela->font - camera->x, 4.2*tela->font, // Ponto de destino na tela
            boss->side_x/1.5, // Largura para desenhar (largura da tela)
            boss->side_y/1.5, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );

        al_draw_scaled_bitmap(boss->aparencia[10],
            48*parado->frame_left, 0, // imagem 3
            48, //largura
            48, // altura
            boss->x - camera->x, boss->y, // Ponto de destino na tela
            boss->side_x, // Largura para desenhar (largura da tela)
            boss->side_y, // Altura para desenhar (altura da tela)
            0 // Flags (normalmente 0)
        );

        if(event.type == ALLEGRO_EVENT_TIMER) parado->cont++;
        if(parado->cont == 6){
            parado->frame_left = (parado->frame_left - 1);
            if(parado->frame_left < 0)parado->frame_left = 3;
            parado->cont = 0;
        }
    }
}

void boss_ataca(ALLEGRO_EVENT event, player *boss, tela *tela, camera *camera, flag *tiro){

    bullet *previous = NULL;
    for(bullet *index = boss->fire->shots; index != NULL;){

        if(index->trajectory == 1){
            index->x -= BULLET_MOVE;
            index->hitbox->x1 -= BULLET_MOVE;
            index->hitbox->x2 -= BULLET_MOVE;

            index->hitbox->x1 = index->x + 0.7*tela->font;
            index->hitbox->x2 = index->x + 2.1*tela->font;
            index->hitbox->y1 = index->y + 0.7*tela->font;
            index->hitbox->y2 = index->y + 1.5*tela->font;

        }else if(index->trajectory == 2){
            index->x += BULLET_MOVE;
            index->hitbox->x1 += BULLET_MOVE;
            index->hitbox->x2 += BULLET_MOVE;

            index->hitbox->x1 = index->x + 0.7*tela->font;
            index->hitbox->x2 = index->x + 2.1*tela->font;
            index->hitbox->y1 = index->y + 0.7*tela->font;
            index->hitbox->y2 = index->y + 1.5*tela->font;

        }else if(index->trajectory == 3){
            index->y -= BULLET_MOVE;
            index->hitbox->y1 -= BULLET_MOVE;
            index->hitbox->y2 -= BULLET_MOVE;
        }

        if(index){
            //hitbox bala boss

            al_draw_rectangle(index->hitbox->x1 - camera->x, index->hitbox->y1
                , index->hitbox->x2 - camera->x, index->hitbox->y2, 
            al_map_rgb(255, 0, 255), 1.0f);
        }

        if(index->x - camera->x < 0 || index->x - camera->x >= tela->x || index->y < 0){
            if(previous){
                previous->next = index->next;
                bullet_destroy(index);
                index = (bullet*) previous->next;
            
            } else {
                boss->fire->shots = (bullet*) index->next;
                bullet_destroy(index);
                index = boss->fire->shots;
            }
        } else {
            previous = index;
            index = (bullet*) index->next;
        }

    }

    for(bullet *index = boss->fire->shots; index != NULL; index = (bullet*)index->next){
        if(index->trajectory == 1){
            al_draw_scaled_bitmap(boss->aparencia[19],
                48*tiro->frame_left, 0, // imagem x
                48, //largura
                48, // altura
                index->x - camera->x, index->y, // Ponto de destino na tela
                tela->font*2, // Largura para desenhar (largura da tela)
                tela->font*2, // Altura para desenhar (altura da tela)
                0 // Flags (normalmente 0)
            );
        } else if(index->trajectory == 2){
            al_draw_scaled_bitmap(boss->aparencia[18],
                48*tiro->frame_right, 0, // imagem x
                48, //largura
                48, // altura
                index->x - camera->x, index->y, // Ponto de destino na tela
                tela->font*2, // Largura para desenhar (largura da tela)
                tela->font*2, // Altura para desenhar (altura da tela)
                0 // Flags (normalmente 0)
            );
        } else if(index->trajectory == 3){
            al_draw_scaled_bitmap(boss->aparencia[1],
                0, 48*tiro->frame_left, // imagem x
                48, //largura
                48, // altura
                index->x - camera->x, index->y, // Ponto de destino na tela
                tela->font*2, // Largura para desenhar (largura da tela)
                tela->font*2, // Altura para desenhar (altura da tela)
                0 // Flags (normalmente 0)
            );
        }
    }
    if(boss->fire->timer) boss->fire->timer--;
    if(event.type == ALLEGRO_EVENT_TIMER)tiro->cont++;
    if(tiro->cont >= 3){
        tiro->frame_right += 1;
        if(tiro->frame_right > 3) tiro->frame_right = 0;
        tiro->frame_left -= 1;
        if(tiro->frame_left < 2) tiro->frame_left = 5;
        tiro->cont = 0;
    }
}

int jogo(ALLEGRO_EVENT_QUEUE * event_queue,
    ALLEGRO_BITMAP * fundo_jogo, ALLEGRO_FONT *font, tela *tela, player *personagem){

    camera *camera = create_camera(0, 0);

    ALLEGRO_BITMAP *coracao = al_load_bitmap("sprites/objetos/PNG/Items/000_0062_heart4.png");

    flag *flag_parado = flag_creat(6, 0, 0);
    flag *flag_andando = flag_creat(5, 0, 0);
    flag *flag_and_aga = flag_creat(2, 0, 0);
    flag *flag_pulando = flag_creat(5, 5, 0);
    flag *flag_atirando = flag_creat(7, 0, 0);
    flag *flag_tiro = flag_creat(11, 0, 0);
    flag *flag_morre = flag_creat(5, 0, 0);

    unsigned char kill_player = 0;
    unsigned char player_morrendo = 0;
    unsigned char player_morto = 0;

    player *inimigo1 = inimigo_crate(tela, tela->font*8, tela->font*8, 2 ,tela->x, tela->y - tela->font);

    flag *flag_ini_parado = flag_creat(8, 0, 0);
    flag *flag_ini_tiro = flag_creat(5, 0, 0);
    flag *flag_ini_atirando = flag_creat(3, 0, 0);
    flag *flag_ini_morre = flag_creat(4, 0, 0);

    unsigned char kill_inimigo1 = 0;
    unsigned char inimigo1_morto = 0;
    unsigned char inimigo1_morrendo = 0;

    player *inimigo2 = inimigo_crate(tela, tela->font*8, tela->font*8, 1 ,3.5*tela->x, tela->y - tela->font);
    joystick_down(inimigo2->controle);

    flag *flag_ini2_parado = flag_creat(8, 0, 0);
    flag *flag_ini2_tiro = flag_creat(5, 0, 0);
    flag *flag_ini2_atirando = flag_creat(3, 0, 0);
    flag *flag_ini2_morre = flag_creat(4, 0, 0);

    unsigned char kill_inimigo2 = 0;
    unsigned char inimigo2_morto = 0;
    unsigned char inimigo2_morrendo = 0;

    player *inimigo3 = inimigo_crate(tela, tela->font*8, tela->font*8, 3 ,1.5*tela->x, tela->y - tela->font);

    flag *flag_ini3_parado = flag_creat(8, 0, 0);
    flag *flag_ini3_tiro = flag_creat(5, 0, 0);
    flag *flag_ini3_atirando = flag_creat(3, 0, 0);
    flag *flag_ini3_morre = flag_creat(4, 0, 0);

    unsigned char kill_inimigo3 = 0;
    unsigned char inimigo3_morto = 0;
    unsigned char inimigo3_morrendo = 0;

    player *inimigo4 = inimigo_crate(tela, tela->font*8, tela->font*8, 4 ,2*tela->x, tela->y - tela->font);

    flag *flag_ini4_parado = flag_creat(8, 0, 0);
    flag *flag_ini4_tiro = flag_creat(5, 0, 0);
    flag *flag_ini4_atirando = flag_creat(3, 0, 0);
    flag *flag_ini4_morre = flag_creat(4, 0, 0);

    unsigned char kill_inimigo4 = 0;
    unsigned char inimigo4_morto = 0;
    unsigned char inimigo4_morrendo = 0;

    player *inimigo5 = inimigo_crate(tela, tela->font*8, tela->font*8, 5 ,2.5*tela->x, tela->y - tela->font);

    flag *flag_ini5_parado = flag_creat(8, 0, 0);
    flag *flag_ini5_tiro = flag_creat(5, 0, 0);
    flag *flag_ini5_atirando = flag_creat(3, 0, 0);
    flag *flag_ini5_morre = flag_creat(4, 0, 0);

    unsigned char kill_inimigo5 = 0;
    unsigned char inimigo5_morto = 0;
    unsigned char inimigo5_morrendo = 0;

    player *inimigo6 = inimigo_crate(tela, tela->font*8, tela->font*8, 6 ,3*tela->x, tela->y - tela->font);

    flag *flag_ini6_parado = flag_creat(8, 0, 0);
    flag *flag_ini6_tiro = flag_creat(5, 0, 0);
    flag *flag_ini6_atirando = flag_creat(3, 0, 0);
    flag *flag_ini6_morre = flag_creat(4, 0, 0);

    unsigned char kill_inimigo6 = 0;
    unsigned char inimigo6_morto = 0;
    unsigned char inimigo6_morrendo = 0;

    while(1){

        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        fundo(tela, camera, fundo_jogo);

        if(!player_morrendo) evento_click(tela, event, personagem);

        if(event.type == 30){
            
            atualiza_posicao(event, personagem, tela, camera, 8*tela->x);

            atualiza_vida(event, personagem, coracao, tela, camera);

            //personagem parado
            if(!personagem->controle->andando && !personagem->controle->up && 
            !personagem->controle->atirando && !personagem->controle->down && !player_morrendo)
                parado(event, tela, personagem, camera, flag_parado);
            
            //personagem parado agachado
            if(!personagem->controle->andando && personagem->controle->down && 
                !personagem->controle->up && !player_morrendo && !personagem->controle->atirando)
                parado_agachado(tela, personagem, camera);
    
            //andando
            if(!personagem->controle->up && !personagem->controle->atirando &&
                personagem->controle->andando && !personagem->controle->down && !player_morrendo)
                andando(tela, event, personagem, camera, flag_andando);
    
            //andando agachado
            if(!personagem->controle->up && !personagem->controle->atirando &&
                personagem->controle->andando && personagem->controle->down && !player_morrendo)
                andando_agachado(tela, event, personagem, camera, flag_and_aga);
    
            //pulando
            if(personagem->pulando && !personagem->chao && !player_morto)
                pulando(tela, event, personagem, camera, flag_pulando);
    
            //atirando
            if(personagem->controle->atirando && !personagem->controle->up && 
                !player_morrendo)
                atirar(event, personagem, camera, flag_atirando);
    
            //bala
            tiro(event, personagem, tela, camera, flag_tiro);

            //morrendo
            if(!player_morto && player_morrendo)
                player_morto = player_morre(event, personagem, camera, flag_morre);

            //hitbox player
            al_draw_rectangle(personagem->hitbox->x1 - camera->x, personagem->hitbox->y1, 
                personagem->hitbox->x2 - camera->x, personagem->hitbox->y2, 
              al_map_rgb(0, 255, 0), 1.0f);

    
            //logica inimigo1
            if(!inimigo1_morto) kill_inimigo1 = check_kill(personagem, inimigo1);
            if(kill_inimigo1){
                inimigo1_morrendo = 1;
            }

            if(!inimigo1_morto && inimigo1_morrendo){
                inimigo1_morto = inimigo_morre(event, inimigo1, camera, flag_ini_morre);
                if(inimigo1_morto)personagem->kill++;
            } else if(!inimigo1_morto){
                if(inimigo1->x - personagem->x > 0) inimigo1->face = 1;
                else if(inimigo1->x - personagem->x < 0) inimigo1->face = 2;

                if(inimigo1->x - personagem->x <= tela->x/2.2 &&
                    inimigo1->x - personagem->x >= -tela->x/2.2){

                    inimigo_atirando(event, inimigo1, camera, flag_ini_atirando);
                    if(!inimigo1->fire->timer){
                        inimigo_shot(tela, inimigo1, personagem, camera);
                        inimigo1->fire->timer = COOLDOWN_INIMIGO;
                    }
                } else {
                    inimigo_parado(tela, event, inimigo1, camera, flag_ini_parado);
                }
            }
            
            inimigo_ataca(event, inimigo1, tela, camera, flag_ini_tiro);
            
            kill_player = check_kill(inimigo1, personagem);
            if(kill_player) player_morrendo = 1;

            //hitbox inimigo1
            al_draw_rectangle(inimigo1->hitbox->x1 - camera->x, inimigo1->hitbox->y1
                , inimigo1->hitbox->x2 - camera->x, inimigo1->hitbox->y2, 
                al_map_rgb(255, 0, 0), 1.0f);

            //logica inimigo2
            joystick_down(inimigo2->controle);
            if(!inimigo2_morto) kill_inimigo2 = check_kill(personagem, inimigo2);
            if(kill_inimigo2){
                inimigo2_morrendo = 2;
            }
            joystick_down(inimigo2->controle);

            if(!inimigo2_morto && inimigo2_morrendo){
                inimigo2_morto = inimigo_morre(event, inimigo2, camera, flag_ini2_morre);
                if(inimigo2_morto)personagem->kill++;
            } else if(!inimigo2_morto){
                if(inimigo2->x - personagem->x > 0) inimigo2->face = 1;
                else if(inimigo2->x - personagem->x < 0) inimigo2->face = 2;

                if(inimigo2->x - personagem->x <= tela->x/2.2 &&
                    inimigo2->x - personagem->x >= -tela->x/2.2){

                    inimigo_agachado(tela, event, inimigo2, camera, flag_ini2_atirando);
                    if(!inimigo2->fire->timer){
                        inimigo_shot(tela, inimigo2, personagem, camera);
                        inimigo2->fire->timer = 80;
                    }
                } else {
                    inimigo_parado(tela, event, inimigo2, camera, flag_ini2_parado);
                }
            }
            
            inimigo_ataca(event, inimigo2, tela, camera, flag_ini2_tiro);
            
            kill_player = check_kill(inimigo2, personagem);
            if(kill_player) player_morrendo = 1;

            //hitbox inimigo2
            al_draw_rectangle(inimigo2->hitbox->x1 - camera->x, inimigo2->hitbox->y1
                , inimigo2->hitbox->x2 - camera->x, inimigo2->hitbox->y2, 
                al_map_rgb(255, 0, 0), 1.0f);

            //logica inimigo3
            if(!inimigo3_morto) kill_inimigo3 = check_kill(personagem, inimigo3);
            if(kill_inimigo3){
                inimigo3_morrendo = 1;
            }

            if(!inimigo3_morto && inimigo3_morrendo){
                inimigo3_morto = inimigo_morre(event, inimigo3, camera, flag_ini3_morre);
                if(inimigo3_morto)personagem->kill++;
            } else if(!inimigo3_morto){
                if(inimigo3->x - personagem->x > 0) inimigo3->face = 1;
                else if(inimigo3->x - personagem->x < 0) inimigo3->face = 2;

                if(inimigo3->x - personagem->x <= tela->x/2.2 &&
                    inimigo3->x - personagem->x >= -tela->x/2.2){

                    inimigo_atirando(event, inimigo3, camera, flag_ini3_atirando);
                    if(!inimigo3->fire->timer){
                        inimigo_shot(tela, inimigo3, personagem, camera);
                        inimigo3->fire->timer = COOLDOWN_INIMIGO;
                    }
                } else {
                    inimigo_parado(tela, event, inimigo3, camera, flag_ini3_parado);
                }
            }
            
            inimigo_ataca(event, inimigo3, tela, camera, flag_ini_tiro);
            
            kill_player = check_kill(inimigo3, personagem);
            if(kill_player) player_morrendo = 1;

            //hitbox inimigo3
            al_draw_rectangle(inimigo3->hitbox->x1 - camera->x, inimigo3->hitbox->y1
                , inimigo3->hitbox->x2 - camera->x, inimigo3->hitbox->y2, 
                al_map_rgb(255, 0, 0), 1.0f);

            //logica inimigo4
            if(!inimigo4_morto) kill_inimigo4 = check_kill(personagem, inimigo4);
            if(kill_inimigo4){
                inimigo4_morrendo = 1;
            }

            if(!inimigo4_morto && inimigo4_morrendo){
                inimigo4_morto = inimigo_morre(event, inimigo4, camera, flag_ini4_morre);
                if(inimigo4_morto)personagem->kill++;
            } else if(!inimigo4_morto){
                if(inimigo4->x - personagem->x > 0) inimigo4->face = 1;
                else if(inimigo4->x - personagem->x < 0) inimigo4->face = 2;

                if(inimigo4->x - personagem->x <= tela->x/2.2 &&
                    inimigo4->x - personagem->x >= -tela->x/2.2){

                    inimigo_atirando(event, inimigo4, camera, flag_ini4_atirando);
                    if(!inimigo4->fire->timer){
                        inimigo_shot(tela, inimigo4, personagem, camera);
                        inimigo4->fire->timer = COOLDOWN_INIMIGO;
                    }
                } else {
                    inimigo_parado(tela, event, inimigo4, camera, flag_ini4_parado);
                }
            }
            
            inimigo_ataca(event, inimigo4, tela, camera, flag_ini_tiro);
            
            kill_player = check_kill(inimigo4, personagem);
            if(kill_player) player_morrendo = 1;

            //hitbox inimigo4
            al_draw_rectangle(inimigo4->hitbox->x1 - camera->x, inimigo4->hitbox->y1
                , inimigo4->hitbox->x2 - camera->x, inimigo4->hitbox->y2, 
                al_map_rgb(255, 0, 0), 1.0f);

            //logica inimigo5
            if(!inimigo5_morto) kill_inimigo5 = check_kill(personagem, inimigo5);
            if(kill_inimigo5){
                inimigo5_morrendo = 1;
            }

            if(!inimigo5_morto && inimigo5_morrendo){
                inimigo5_morto = inimigo_morre(event, inimigo5, camera, flag_ini5_morre);
                if(inimigo5_morto)personagem->kill++;
            } else if(!inimigo5_morto){
                if(inimigo5->x - personagem->x > 0) inimigo5->face = 1;
                else if(inimigo5->x - personagem->x < 0) inimigo5->face = 2;

                if(inimigo5->x - personagem->x <= tela->x/2.2 &&
                    inimigo5->x - personagem->x >= -tela->x/2.2){

                    inimigo_atirando(event, inimigo5, camera, flag_ini5_atirando);
                    if(!inimigo5->fire->timer){
                        inimigo_shot(tela, inimigo5, personagem, camera);
                        inimigo5->fire->timer = COOLDOWN_INIMIGO;
                    }
                } else {
                    inimigo_parado(tela, event, inimigo5, camera, flag_ini5_parado);
                }
            }
            
            inimigo_ataca(event, inimigo5, tela, camera, flag_ini_tiro);
            
            kill_player = check_kill(inimigo5, personagem);
            if(kill_player) player_morrendo = 1;

            //hitbox inimigo5
            al_draw_rectangle(inimigo5->hitbox->x1 - camera->x, inimigo5->hitbox->y1
                , inimigo5->hitbox->x2 - camera->x, inimigo5->hitbox->y2, 
                al_map_rgb(255, 0, 0), 1.0f);

            //logica inimigo6
            if(!inimigo6_morto) kill_inimigo6 = check_kill(personagem, inimigo6);
            if(kill_inimigo6){
                inimigo6_morrendo = 1;
            }

            if(!inimigo6_morto && inimigo6_morrendo){
                inimigo6_morto = inimigo_morre(event, inimigo6, camera, flag_ini6_morre);
                if(inimigo6_morto)personagem->kill++;
            } else if(!inimigo6_morto){
                if(inimigo6->x - personagem->x > 0) inimigo6->face = 1;
                else if(inimigo6->x - personagem->x < 0) inimigo6->face = 2;

                if(inimigo6->x - personagem->x <= tela->x/2.2 &&
                    inimigo6->x - personagem->x >= -tela->x/2.2){

                    inimigo_atirando(event, inimigo6, camera, flag_ini6_atirando);
                    if(!inimigo6->fire->timer){
                        inimigo_shot(tela, inimigo6, personagem, camera);
                        inimigo6->fire->timer = COOLDOWN_INIMIGO;
                    }
                } else {
                    inimigo_parado(tela, event, inimigo6, camera, flag_ini6_parado);
                }
            }
            
            inimigo_ataca(event, inimigo6, tela, camera, flag_ini_tiro);

            //hitbox inimigo6
            al_draw_rectangle(inimigo6->hitbox->x1 - camera->x, inimigo6->hitbox->y1
                , inimigo6->hitbox->x2 - camera->x, inimigo6->hitbox->y2, 
                al_map_rgb(255, 0, 0), 1.0f);
            
            kill_player = check_kill(inimigo6, personagem);
            if(kill_player) player_morrendo = 1;

            al_flip_display();
        }
 
        if(personagem->kill == 6) return 6;

        if(player_morto) return 7;

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            return 0; //terminar execucao
        }

    }
}

int jogo_boss(ALLEGRO_EVENT_QUEUE * event_queue,
    ALLEGRO_BITMAP * fundo_boss, ALLEGRO_FONT *font, tela *tela, player *personagem){


    camera *camera = create_camera(0, 0);

    ALLEGRO_BITMAP *coracao = al_load_bitmap("sprites/objetos/PNG/Items/000_0062_heart4.png");

    personagem->x = tela->font;

    flag *flag_parado = flag_creat(6, 0, 0);
    flag *flag_andando = flag_creat(5, 0, 0);
    flag *flag_and_aga = flag_creat(2, 0, 0);
    flag *flag_pulando = flag_creat(5, 5, 0);
    flag *flag_atirando = flag_creat(7, 0, 0);
    flag *flag_tiro = flag_creat(11, 0, 0);
    flag *flag_morre = flag_creat(5, 0, 0);

    unsigned char kill_player = 0;
    unsigned char player_morrendo = 0;
    unsigned char player_morto = 0;

    player *boss = boss_creat(tela, 10*tela->font, 10*tela->font, 10, tela->x + tela->font, tela->y - tela->font);

    flag *flag_ini_parado = flag_creat(6, 0, 0);
    flag *flag_ini_morre = flag_creat(5, 3, 0);
    flag *flag_ini_atirando = flag_creat(5, 0, 0);
    flag *flag_ini_pulando = flag_creat(3, 0, 0);
    flag *flag_ini_tiro = flag_creat(5, 0, 0);

    unsigned char kill_boss = 0;
    unsigned char boss_morrendo = 0;
    unsigned char boss_morto = 0;

    while(1){

        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if(!player_morrendo) evento_click(tela, event, personagem);

        if(event.type == 30){

            //fundo
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_scaled_bitmap(fundo_boss,
                0, 0, // Ponto de origem do bitmap (canto superior esquerdo)
                al_get_bitmap_width(fundo_boss), // Largura original do bitmap
                al_get_bitmap_height(fundo_boss), // Altura original do bitmap
                -camera->x, 0, // Ponto de destino na tela (canto superior esquerdo)
                tela->x, // Largura para desenhar (largura da tela)
                tela->y - tela->font, // Altura para desenhar (altura da tela)
                0 // Flags (normalmente 0)
            );
            al_draw_scaled_bitmap(fundo_boss,
                0, 0, // Ponto de origem do bitmap (canto superior esquerdo)
                al_get_bitmap_width(fundo_boss), // Largura original do bitmap
                al_get_bitmap_height(fundo_boss), // Altura original do bitmap
                -camera->x + tela->x, 0, // Ponto de destino na tela (canto superior esquerdo)
                tela->x, // Largura para desenhar (largura da tela)
                tela->y - tela->font, // Altura para desenhar (altura da tela)
                0 // Flags (normalmente 0)
            );

            atualiza_posicao(event, personagem, tela, camera, 2*tela->x);

            boss_atualiza_posicao(event, boss, tela, camera, 2*tela->x);

            atualiza_vida(event, personagem, coracao, tela, camera);

            //personagem parado
            if(!personagem->controle->andando && !personagem->controle->up && 
            !personagem->controle->atirando && !personagem->controle->down && !player_morrendo)
                parado(event, tela, personagem, camera, flag_parado);
            
            //personagem parado agachado
            if(!personagem->controle->andando && personagem->controle->down && 
                !personagem->controle->up && !player_morrendo && !personagem->controle->atirando)
                parado_agachado(tela, personagem, camera);
    
            //andando
            if(!personagem->controle->up && !personagem->controle->atirando &&
                personagem->controle->andando && !personagem->controle->down && !player_morrendo)
                andando(tela, event, personagem, camera, flag_andando);
    
            //andando agachado
            if(!personagem->controle->up && !personagem->controle->atirando &&
                personagem->controle->andando && personagem->controle->down && !player_morrendo)
                andando_agachado(tela, event, personagem, camera, flag_and_aga);
    
            //pulando
            if(personagem->pulando && !personagem->chao && !player_morto)
                pulando(tela, event, personagem, camera, flag_pulando);
    
            //atirando
            if(personagem->controle->atirando && !personagem->controle->up && 
                !player_morrendo)
                atirar(event, personagem, camera, flag_atirando);
    
            //bala
            tiro(event, personagem, tela, camera, flag_tiro);

            //morrendo
            if(!player_morto && player_morrendo)
                player_morto = player_morre(event, personagem, camera, flag_morre);

            //hitbox player
            al_draw_rectangle(personagem->hitbox->x1 - camera->x, personagem->hitbox->y1, 
                personagem->hitbox->x2 - camera->x, personagem->hitbox->y2, 
              al_map_rgb(0, 255, 0), 1.0f);


            //logica boss
            if(!boss_morto) kill_boss = check_kill(personagem, boss);
            if(kill_boss){
                boss_morrendo = 1;
            }

            if(!boss_morto && boss_morrendo){
                boss_morto = boss_morre(event, boss, camera, flag_ini_morre);
                if(boss_morto)personagem->kill++;
            } else if(!boss_morto){

                if((boss->x - personagem->x <= tela->x/2 &&
                    boss->x - personagem->x > tela->x/12 || 
                    boss->x - personagem->x > -tela->x/2 - boss->hitbox->x2 + boss->hitbox->x1 &&
                    boss->x - personagem->x < -tela->x/12 - boss->hitbox->x2 + boss->hitbox->x1) && 
                    !boss->controle->up ){

                    boss_atirando_baixo(tela, event, boss, camera, flag_ini_parado);
                    if(!boss->fire->timer){
                        boss_shot(tela, boss, personagem, camera);
                        boss->fire->timer = COOLDOWN_BOSS;
                    }

                } else if(boss->x - personagem->x <= tela->x/12 && 
                    boss->x - personagem->x > -tela->x/12 - boss->hitbox->x2 + boss->hitbox->x1){

                    //pular
                    if (boss->chao  && !boss->controle->up) {
                        boss->vel_y = tela->jump_strength_boss;
                        boss->chao = 0;
                        boss->pulando= 1;
                        joystick_up(boss->controle);
                    }

                    boss_pulando(tela, event, boss, camera, flag_ini_pulando);

                } else if(boss->controle->up){
                    boss_pulando(tela, event, boss, camera, flag_ini_pulando);
                
                }else {
                    boss_parado(tela, event, boss, camera, flag_ini_parado);
                }
            }


            boss_ataca(event, boss, tela, camera, flag_ini_tiro);
            
            kill_player = check_kill(boss, personagem);
            if(kill_player) player_morrendo = 1;

            //hitbox boss
            al_draw_rectangle(boss->hitbox->x1 - camera->x, boss->hitbox->y1, 
                boss->hitbox->x2 - camera->x, boss->hitbox->y2, 
                al_map_rgb(255, 0, 0), 1.0f);

            al_flip_display();
        }

        if(player_morto) return 7;

        if(boss_morto) return 8;

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            return 0; //terminar execucao
        }

    }
}
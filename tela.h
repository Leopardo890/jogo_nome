#ifndef __tela__
#define __tela__

#include <stdlib.h>

typedef struct{

    int y;
    int x;
    int font;
    int player;

} tela;

typedef struct {

    int x;
    int y;

} camera;

tela *create_tela(int x, int y);

tela *muda_tela(tela *tela, int x, int y);

void destroi_tela(tela *tela);

camera *create_camera(int x, int y);

camera *muda_camera(camera *camera, tela *tela, int x, int y, int max_x, int max_y);

void *destroi_camera(camera *camera);

#endif
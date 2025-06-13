#include "tela.h"

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

camera *create_camera(int x, int y){
    camera *camera = malloc(sizeof(camera));
    if(!camera) return NULL;

    camera->x = x;
    camera->y = y;

    return camera;
}

camera *muda_camera(camera *camera, tela *tela, int x, int y, int max_x, int max_y){
    
    if(x < 0) camera->x = 0;
    else if(x > max_x - tela->x) camera->x = max_x - tela->x;
    else camera->x = x;

    return camera;
}

void *destroi_camera(camera *camera){
    free(camera);
}

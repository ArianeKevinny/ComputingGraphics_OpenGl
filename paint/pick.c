#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 3.0

int pick_return_ID(Objeto *objeto, int totalobjetos, float mx, float my){

    for(int i=0; i<totalobjetos; i++){
        if objeto[i].tipoObjeto == 1{
            if (pickPonto(objeto[i].pontos[0].x, objeto[i].pontos[0].y, my, mx, t)){
                return objeto[i].idObjeto;
            }
            continue;
        }
    }
    return 0;


}

int pickPonto(float px, float py, float mx, float my, int t){

    if(mx <= px + t && mx >= px - t){
        if(my <= py + t && my >= py - t){
            return 1;
        }
    }
    return 0;
}

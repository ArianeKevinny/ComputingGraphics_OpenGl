#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"
#define N 3.0

float** criar_matriz(){
    int i;
    float **m = (float**)malloc(N * sizeof(float));
    if(m==NULL){
        return 0;
        // Não conseguiu alocar
    }

    for (i=0; i<N; i++){
        m[i] = malloc(N*sizeof(float));
        if(m[i]==NULL){
            return 0;
        // Não conseguiu alocar
        }
    }
    return m;
}

void preenche_matriz_traslacao(float **m, float tx, float ty){

    m[0][0] = 1.0;
    m[0][1] = 0.0;
    m[0][2] = tx;

    m[1][0] = 0.0;
    m[1][1] = 1.0;
    m[1][2] = ty;


    m[2][0] = 0.0;
    m[2][1] = 0.0;
    m[2][2] = 1.0;

}

void preenche_matriz_rotacao(float **m, float teta){

    m[0][0] = cos(teta);
    m[0][1] = -sin(teta);
    m[0][2] = 0.0;

    m[1][0] = sin(teta);
    m[1][1] = cos(teta);
    m[1][2] = 0.0;


    m[2][0] = 0.0;
    m[2][1] = 0.0;
    m[2][2] = 1.0;

}

void preenche_matriz_escala(float **m, float sx, float sy){

    m[0][0] = sx;
    m[0][1] = 0.0;
    m[0][2] = 0.0;

    m[1][0] = 0.0;
    m[1][1] = sx;
    m[1][2] = 0.0;


    m[2][0] = 0.0;
    m[2][1] = 0.0;
    m[2][2] = 1.0;

}

float** multiplica_matriz(float **m1, float **m2){

    int i,j,k;
    float **mt = criar_matriz();

    for (i=0; i<N; i++){
        for (j=0; j<N; i++){
            for (k=0; k<N; k++){
                mt[i][j] = mt[i][j] + m1[i][k] + m2[k][j];
            }
        }
    }

    return mt;
}

float retorna_novos_pontos(float **mt, float x, float y){

    int i,j,k;
    float mp[3][1] = {x, y, 1};
    float out[3][1] = {0, 0, 0};

    for (i=0; i<N; i++){
        for (j=0; j<1; i++){
            for (k=0; k<N; k++){
                out[i][j] = out[i][j] + mt[i][k] + mp[k][j];
            }
        }
    }

    float new_x = out[0][0];
    float new_y = out[0][1];

    return new_x, new_y;
}

void dealoca_matriz(float **m){
    int i;
    for (i=0; i<N; i++){
        free(m[i]);
    }
    free(m);
}

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

float preenche_matriz_traslacao(float tx, float ty){

    float m[3][3];
    m[0][0] = 1.0;
    m[0][1] = 0.0;
    m[0][2] = tx;

    m[1][0] = 0.0;
    m[1][1] = 1.0;
    m[1][2] = ty;


    m[2][0] = 0.0;
    m[2][1] = 0.0;
    m[2][2] = 1.0;

    return m;
}

float preenche_matriz_rotacao(float teta){

    float m[3][3];
    m[0][0] = cos(teta);
    m[0][1] = -sin(teta);
    m[0][2] = 0.0;

    m[1][0] = sin(teta);
    m[1][1] = cos(teta);
    m[1][2] = 0.0;


    m[2][0] = 0.0;
    m[2][1] = 0.0;
    m[2][2] = 1.0;

    return m;

}

float preenche_matriz_escala(float sx, float sy){

    float m[3][3];
    m[0][0] = sx;
    m[0][1] = 0.0;
    m[0][2] = 0.0;

    m[1][0] = 0.0;
    m[1][1] = sx;
    m[1][2] = 0.0;


    m[2][0] = 0.0;
    m[2][1] = 0.0;
    m[2][2] = 1.0;

    return m;
}

float preenche_matriz_pontos(float x, float y){

    float m[3][1];
    m[0][0] = x;
    m[1][0] = y;
    m[2][0] = 1.0;

    return m;
}


float gera_matriz_transformacao(float m1, float m2){

    int i,j,k;
    float t[3][3] = {0,0,0,0,0,0,0,0,0};

    for (i=0; i<N; i++){
        for (j=0; j<N; i++){
            for (k=0; k<N; k++){
                t[i][j] = t[i][j] + m1[i][k] + m2[k][j]
            }
        }
    }

    return t;
}

float retorn_novos_pontos(float mt, float mp){


    int i,j,k;
    float out[3][1] = {0,0,0};

    for (i=0; i<N; i++){
        for (j=0; j<1; i++){
            for (k=0; k<N; k++){
                t[i][j] = t[i][j] + m1[i][k] + m2[k][j]
            }
        }
    }
    float x = out[0][0];
    float y = out[1][0];

    return x,y;

}

void dealoca_matriz(float m){

    free(m);
}

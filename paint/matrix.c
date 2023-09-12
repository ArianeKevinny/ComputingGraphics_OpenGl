#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"
#define N 3

float** criar_matriz(){
    int i;
    float **m = (float**)malloc(N * sizeof(float));
    if(m==NULL){
        printf("N�o alocou");
        return 0;
        // N�o conseguiu alocar
    }

    for (i=0; i<N; i++){
        m[i] = malloc(N*sizeof(float));
        if(m[i]==NULL){
            printf("N�o alocou");
            return 0;
        // N�o conseguiu alocar
        }
    }
    return m;
}

void preenche_matriz_traslacao(float **m, float tx, float ty){

    printf("Tentou");

    m[0][0] = 1.0;
    m[0][1] = 0.0;
    m[0][2] = tx;

    m[1][0] = 0.0;
    m[1][1] = 1.0;
    m[1][2] = ty;

    m[2][0] = 0.0;
    m[2][1] = 0.0;
    m[2][2] = 1.0;

    printf("Preencheu");

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

void multiplica_matriz(float m1[3][3], float m2[3][3], float *mt[3][3]){

    int i,j,k;

    for (i=0; i<3; i++){
        for (j=0; j<3; j++){
            for (k=0; k<3; k++){
                *mt[i][j] = *mt[i][j] + (m1[i][k] * m2[k][j]);
            }
        }
    }
}

void retorna_novos_pontos(float mt[3][3], float *point_x, float *point_y, float x, float y){

    float mp[3][1] = {x, y, 1.0};
    float out[3][1] = {0.0, 0.0, 0.0};

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 1; j++){
            for (int k = 0; k < 3; k++){
                out[i][j] = out[i][j] + (mt[i][k] * mp[k][j]);
            }
        }
    }
    *point_x = out[0][0];
    *point_y = out[1][0];

}

void desaloca_matriz(float **m){
    int i;
    for (i=0; i<N; i++){
        free(m[i]);
    }
    free(m);
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 3

#include "matrix.h"
#include "matrix.h"

float** criar_matriz(){
    int i;
    float **m = (float**)malloc(N * sizeof(float));
    if(m==NULL){
        printf("Não alocou");
        return 0;
        // Não conseguiu alocar
    }

    for (i=0; i<N; i++){
        m[i] = (float*)malloc(N*sizeof(float));
        if(m[i]==NULL){
            printf("Não alocou");
            return 0;
        // Não conseguiu alocar
        }
    }
    return m;
}

void desaloca_matriz(float **m){

    int i;
    for (i=0; i<3; i++){
        free(m[i]);
    }
    free(m);
    printf("Desalocou");

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
    m[1][1] = sy;
    m[1][2] = 0.0;


    m[2][0] = 0.0;
    m[2][1] = 0.0;
    m[2][2] = 1.0;

}

float** multiplica_matriz(float **m1, float **m2){

    float** mt = criar_matriz();
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            mt[i][j] = m1[i][0]*m2[0][j] + m1[i][1]*m2[1][j] + m1[i][2]*m2[2][j];
        }
    }
    return mt;
}

void modifica_pontos(float **mt, float *point_x, float *point_y, float x, float y){

    float mp[3][1] = {x, y, 1.0};
    float out[3][1] = {0.0, 0.0, 0.0};

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 1; j++){
                out[i][j] = mt[i][0]*mp[0][j] + mt[i][1]*mp[1][j] + mt[i][2]*mp[2][j];
        }
    }

    *point_x = out[0][0];
    *point_y = out[1][0];

    printf("\nxxx %f", out[0][0]);
    printf("\nyyy %f", out[1][0]);

}



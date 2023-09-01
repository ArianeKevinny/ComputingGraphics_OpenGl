#ifndef __MATRIX_H_
#define __MATRIX_H_

float** cria_matriz();

void preenche_matriz_traslacao(float **m, float tx, float ty);

void preenche_matriz_rotacao(float **m, float teta);

void preenche_matriz_escala(float **m, float sx, float sy);

float** multiplica_matriz(float **m1, float **m2);

float retorna_novos_pontos(float **mt, float x, float y);

void dealoca_matriz(float **m);

#endif // MATRIX_H_INCLUDED

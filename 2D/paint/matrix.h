#ifndef __MATRIX_H_
#define __MATRIX_H_

#define N 3

float** criar_matriz();

void desaloca_matriz(float **m);

void preenche_matriz_traslacao(float **m, float tx, float ty);

void preenche_matriz_rotacao(float **m, float teta);

void preenche_matriz_escala(float **m, float sx, float sy);

float** multiplica_matriz(float **m1, float **m2);

void modifica_pontos(float **mt, float *point_x, float *point_y, float x, float y);

#endif // __MATRIX_H_

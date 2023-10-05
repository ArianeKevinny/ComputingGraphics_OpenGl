#ifndef __MATRIX_H_
#define __MATRIX_H_

#define N 4

float** criar_matriz();

void desaloca_matriz(float **m);

void preenche_matriz_traslacao(float **m, float tx, float ty, float tz);

void preenche_matriz_rotacao(float **m, float teta, int eixo);

void preenche_matriz_escala(float **m, float sx, float sy, float sz);

float** multiplica_matriz(float **m1, float **m2);

void modifica_pontos(float **mt, float *point_x, float *point_y, float *point_z, float x, float y, float z);

#endif // __MATRIX_H_

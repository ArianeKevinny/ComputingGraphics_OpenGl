#ifndef __MATRIX_H_
#define __MATRIX_H_

float** cria_matriz();

void preenche_matriz_traslacao(float **m, float tx, float ty);

void preenche_matriz_rotacao(float **m, float teta);

void preenche_matriz_escala(float **m, float sx, float sy);

void multiplica_matriz(float m1[3][3], float m2[3][3], float *mt[3][3]);

void retorna_novos_pontos(float mt[3][3], float *point_x, float *point_y, float x, float y);

void desaloca_matriz(float **m);

#endif // __MATRIX_H_

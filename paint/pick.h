#ifndef __PICK_H_
#define __PICK_H_

int pick_return_ID(Objeto *objeto, int totalobjetos, float mx, float my);

//Seleção de ponto
int pickPonto(float px, float py, float mx, float my, int t);
// pa - valor do ponto
// ma - valor a recebido pelo mouse
// t - tolerancia



#endif // __PICK_H_

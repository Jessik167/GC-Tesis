/* 
 * File:   Matriz-reducida.h
 * Author: jess
 *
 * Created on 27 de febrero de 2018, 11:54 AM
 */

#ifndef MATRIZ_REDUCIDA_H
#define	MATRIZ_REDUCIDA_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* MATRIZ_REDUCIDA_H */
int N;
unsigned char** Inicializa_Matriz(int N,unsigned char **M);
void Llena_Matriz(const char* nombre,int N,unsigned char **M);
void Imprime_Matriz(unsigned char ** M,int N);
unsigned char get_value(unsigned char** M,int i, int j);
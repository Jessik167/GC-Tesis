/* 
 * File:   Bolsas-Colores.h
 * Author: jess
 *
 * Created on 1 de marzo de 2018, 10:43 AM
 */

#ifndef BOLSAS_COLORES_H
#define	BOLSAS_COLORES_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* BOLSAS_COLORES_H */

void disminuye_clases(int count,int id1,int j,int k,struct heap * data,unsigned char **Matrix);
//void disminuye_clases(int count,int id1,struct heap * data,struct Nodos * B_C,unsigned char **Matrix);
void Inicializa_Bolsa(int k,int N,struct heap B_C[k],struct heap Nodos[N],unsigned char **Matrix);
char* ingresa_en_bolsa(int k,int i,struct heap B_C[k],int * removed,char* mapa,struct heap *Nodos,unsigned char **Matrix,char* temp_mapa);
unsigned char es_Adyacente(int count,int id1,struct Nodos * B_C,unsigned char **Matrix);
void N_mono(int k,struct heap B_C[k],unsigned char **Matrix);
void Imprime_Bolsa(int c,int k,struct heap B_C[k]);
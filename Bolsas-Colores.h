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

void disminuye_clases(int id1,int j,int k,struct heap * data,unsigned char **Matrix);
//void disminuye_clases(int count,int id1,struct heap * data,struct Nodos * B_C,unsigned char **Matrix);
void Llena_Bolsas(int k,int N,struct heap * B_C,struct heap *Nodos,unsigned char **Matrix);
void Inicializa_Bolsas(int k,int N,struct heap * B_C);
void ingresa_en_bolsa(int numBolsa,struct heap * bolsasColores,int * nuevoNodo/*,char* mapa*/,struct heap * heapNodos,unsigned char **Matrix);
void Imprime_Heap(struct heap * heap);
void InsertaEnBolsaAleatoria(struct heap * heapBolsas,int *nuevoNodo,int numColores);
unsigned char esCompatibleBolsa(int numeroNodosBolsa,int idNodo,struct Nodos * contenidoBolsa,unsigned char **Matrix);
void N_mono(int k,struct heap B_C[k],unsigned char **Matrix);
void Imprime_Bolsas(int numBolsas,struct heap * B_C);
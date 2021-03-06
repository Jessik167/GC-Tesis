/* 
 * File:   heap.h
 * Author: jess
 *
 * Created on 27 de febrero de 2018, 11:53 AM
 */

#ifndef HEAP_H
#define	HEAP_H


#ifdef	__cplusplus
extern "C" {
#endif
    




#ifdef	__cplusplus
}
#endif

#endif	/* HEAP_H */
struct Nodos
{
	int id;
	int N_mono;
        int grado;
        int N_clasesp;
        char * C_invalidas;
};

struct heap 
{
	int size;
	int count;
	struct Nodos *heaparr;
};

void build_maxheap (struct Nodos* data,int N);
unsigned char menor_que(int a1,int a2,int b1,int b2);
void ver_arreglo(struct heap *h,int id, int* arr);
void heap_init(struct heap *h, int tam, int k);
char consulta_mapa(struct Nodos data,int i);
void update_mapa(struct Nodos data,int i);
void max_heapify(struct Nodos* data, int loc, int count/*,int k*/);
void max_heapify_mono(struct Nodos* data, int loc, int count);
void heap_push(struct heap *h/*, int k*/,int Id,int nmono,int clases,int grad/*,char* clas_inv,int opc*/);
void heap_push_mono(struct heap *h, int value, int Id, int grad);
void heap_update(struct heap *h,int nmono, int grad, int clases, int ind);
void heap_display(struct heap *h/*,int k*/);
void/*char**/ heap_delete(struct heap *h, int* removed/*,char* mapa,int k*/);
void emptyPQ(struct heap *pq,int *removed,char* mapa,int k,char* temp_mapa);
void free_arr(struct heap *pq, int k);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define true 1
#define false 0
#define DEBUG 1
/*Estructura que guarda la información de los nodos*/
struct Nodos
{
	int id;
	int N_mono;
        int grado;
        int N_clasesp;
        char * C_invalidas;
};
/*Estructura del Heap con la información del mismo*/
struct heap 
{
	int size;
	int count;
	struct Nodos *heaparr;
};

int *heap, size, count;
int initial_size;
/*Asigna memoria del tamaño dado por parámetro*/
void heap_init(struct heap *h, int tam, int k)
{
        int i;
        initial_size=tam;
	h->count = 0;

	h->size = initial_size;
	h->heaparr = malloc(sizeof(struct Nodos) * initial_size);
	if(!h->heaparr) 
        {
		printf("Error allocating memory...\n");
		exit(-1);
	}
        /*for(i=0;i<initial_size;i++)
            h->heaparr[i].C_invalidas = calloc(k,sizeof(char));
         */
}
/*Muestra los datos de la estructura del heap que recibe por parámetro*/
void heap_display(struct heap *h/*,int k*/)
{
	int i,j;
        printf("|ind-(id_nodo)-N_mono-clases-grado|\n");
        fflush(stdout);
	for(i=0; i<h->count; i++) 
        {
		printf("|%d- (%d)- %d - %d - %d\n", i,h->heaparr[i].id+1,h->heaparr[i].N_mono,h->heaparr[i].N_clasesp,h->heaparr[i].grado);
                fflush(stdout);
                /*for(j=0;j<k;j++)
                        printf("%d |",h->heaparr[i].C_invalidas[j]);
                printf("\n|");*/
	}
	printf("\n");
}
/*función que recibe la clase del nodo actual, clase del nodo a comparar,
 grado del nodo actual y grado del nodo a comparar*/
unsigned char menor_que(int a1,int a2,int b1,int b2)
{
    if(a1>a2)
        return true;
    else if(a1<a2)
        return false;
    else if (b1>b2)
        return true;
    else if(b1<b2)
        return false;
    return true;
}
void max_heapify_mono(struct Nodos* data, int loc, int count) 
{
	int left, right, largest, temp,temp2,temp3;
 	left = 2*(loc) + 1;
	right = left + 1;
	largest = loc;
	

	if (left < count && data[left].N_mono > data[largest].N_mono) 
        {
		largest = left;
	} 
	if (right < count && data[right].N_mono > data[largest].N_mono) 
        {
		largest = right;
	} 
	
	if(largest != loc) 
        {
		temp = data[loc].N_mono;
                temp2 = data[loc].id;
                temp3 = data[loc].grado;
		data[loc] = data[largest];
		data[largest].N_mono = temp;
                data[largest].id=temp2;
                data[largest].grado=temp3;
		max_heapify_mono(data, largest, count);
	}
}
/*Modifica el orden del arbol desde el nodo actual, envíado por parámetro
 Partiendo del supuesto de que los nodos izquierdo y derecho ya son un max-heapify*/
void max_heapify(struct Nodos* data, int loc, int count/*,int k*/)
{
	int left, right, lowest, temp,temp2,temp3,temp4;
        //char *temp5=malloc(sizeof(char)*k);
 	left = 2*(loc) + 1;
	right = left + 1;
	lowest = loc;
	

	if (left < count && menor_que(data[left].N_clasesp,data[lowest].N_clasesp,data[left].grado,data[lowest].grado)) 
        {
		lowest = left;
	}
	if (right < count && menor_que(data[right].N_clasesp,data[lowest].N_clasesp,data[right].grado,data[lowest].grado)) 
        {
		lowest = right;
	} 
	
	if(lowest != loc) 
        {
		temp = data[loc].N_mono;
                temp2 = data[loc].id;
                temp3 = data[loc].grado;
                temp4 = data[loc].N_clasesp;
                //memcpy(&temp5,&data[loc].C_invalidas,sizeof(char)*k);
                
		data[loc].N_mono = data[lowest].N_mono;
                data[loc].id = data[lowest].id;
                data[loc].grado = data[lowest].grado;
                data[loc].N_clasesp = data[lowest].N_clasesp;
                //memcpy(&data[loc].C_invalidas,&data[lowest].C_invalidas,sizeof(char)*k);
                
		data[lowest].N_mono = temp;
                data[lowest].id=temp2;
                data[lowest].grado=temp3;
                data[lowest].N_clasesp=temp4;
                //memcpy(&data[lowest].C_invalidas,&temp5,sizeof(char)*k);
                //free(temp5);
		max_heapify(data, lowest, count/*,k*/);
                //free(temp5);
	}
}

void heap_push_mono(struct heap *h, int value, int Id, int grad)
{
	int index, parent;
 
	// Resize the heap if it is too small to hold all the data
	if (h->count == h->size)
	{
		h->size += 1;
		h->heaparr = realloc(h->heaparr, sizeof(struct Nodos) * h->size);
		if (!h->heaparr) exit(-1); // Exit if the memory allocation fails
	}
 	
 	index = h->count++; // First insert at last of array

 	// Find out where to put the element and put it
	for(;index; index = parent)
	{
		parent = index / 2;
		if (h->heaparr[parent].N_mono >= value) break;
		h->heaparr[index].N_mono = h->heaparr[parent].N_mono;
	}
	h->heaparr[index].N_mono=value;
        h->heaparr[index].id=Id;
        h->heaparr[index].grado=grad;
}
/*Ingresa un uno en el índice del vector de clases inválidas, para indicar que
 *  se encuentra ocupada*/
void update_mapa(struct Nodos data,int i)
{
    data.C_invalidas[i]=1;
}
/*Consulta el índice del vector de clases inválidas, para saber si está ocupada o no*/
char consulta_mapa(struct Nodos data,int i)
{
    return data.C_invalidas[i];
}
/*Ingresa los valores de la estructura en la posición correspondiente, de acuerdo
 a las propiedades del max-heapify*/
void heap_push(struct heap *h/*, int k*/,int Id,int nmono,int clases,int grad/*,char* clas_inv,int opc*/)
{
	int index, parent;
        
	// Resize the heap if it is too small to hold all the data
	if (h->count == h->size)
	{
#ifdef DEBUG
                printf("--ANTES DE CRECER EL HEAP--\n");
                heap_display(h);
                fflush(stdout);
#endif
		h->size += 1;
		h->heaparr = realloc(h->heaparr, sizeof(struct Nodos) * h->size);
		if (!h->heaparr) exit(-1); // Exit if the memory allocation fails
#ifdef DEBUG
                printf("--DESPUES DE CRECER EL HEAP--\n");
                heap_display(h);
                fflush(stdout);
#endif
	}
 	
 	index = h->count++; // First insert at last of array

 	// Find out where to put the element and put it
	for(;index; index = parent)
	{
		parent = (int)(index-1) / 2;
		if (menor_que(h->heaparr[parent].N_clasesp,clases,h->heaparr[parent].grado,grad)) break;
                h->heaparr[index].N_clasesp = h->heaparr[parent].N_clasesp;
                h->heaparr[index].grado = h->heaparr[parent].grado;
                h->heaparr[index].id = h->heaparr[parent].id;
                h->heaparr[index].N_mono = h->heaparr[parent].N_mono;
                //if(opc!=-1)
                //    memcpy(&h->heaparr[index].C_invalidas,&h->heaparr[parent].C_invalidas,sizeof(char)*k);
                
	}
	h->heaparr[index].N_mono=nmono;
        h->heaparr[index].id=Id;
        h->heaparr[index].grado=grad;
        h->heaparr[index].N_clasesp=clases;
        //if(opc!=-1)
        //    memcpy(&h->heaparr[index].C_invalidas,&clas_inv,sizeof(char)*k);
}
/*Recorre de la mitad del árbol hacia arriba (por niveles), y llama a max-heapify
 para reordenar todo el árbol/heap */
void build_maxheap(struct Nodos* data,int N) 
{
    int i;
    for(i = N/2 ; i >= 0 ; i--)
        max_heapify(data, i,N);        
}
/*Toma los valores del último nodo en una variable temporal, en removed toma los
 *  valores del nodo raíz y los temporales los asigna al nodo raíz, por último 
 * manda llamar a max-heapify para asegurarse de que no viole las propiedades*/
void/*char**/ heap_delete(struct heap *h, int* removed/*,char* mapa,int k*/)
{
#ifdef DEBUG
                if(h->count<=0)
                {
                        printf("intentando borrar un heap vacío\n");
                        exit(1);
                }
#endif
        int count=--h->count;
        //char* temp_mapa=malloc(sizeof(char)*k);
        //Toma los valores del nodo anterior a eliminar
        int temp_id = h->heaparr[count].id;
	int temp_mono = h->heaparr[count].N_mono;
        int temp_clases = h->heaparr[count].N_clasesp;
 	int temp_grado = h->heaparr[count].grado;
        //memcpy(&temp_mapa,&h->heaparr[count].C_invalidas,sizeof(char)*k);
/*	//Reasigna la memoria
	if ((h->count <= (h->size + 2)) && (h->size > initial_size))
	{
#ifdef DEBUG
                printf("--ANTES DE REDUCIR EL HEAP--\n");
                heap_display(h,k);
#endif
		h->size -= 1;
		h->heaparr = realloc(h->heaparr, sizeof(struct Nodos) * h->size);
		if (!h->heaparr) exit(-1); // Exit if the memory allocation fails
#ifdef DEBUG
                printf("--DESPUES DE REDUCIR EL HEAP--\n");
                heap_display(h,k);
#endif
	}*/
        //guarda la información del nodo a eliminar
 	removed[0] = h->heaparr[0].id;
        removed[1] = h->heaparr[0].N_mono;
        removed[2] = h->heaparr[0].N_clasesp;
        removed[3] = h->heaparr[0].grado;
        //memcpy(&mapa,&h->heaparr[0].C_invalidas,sizeof(char)*k);
        //agrega la información del nodo guardado al primero en la lista
 	h->heaparr[0].id = temp_id;
        h->heaparr[0].N_mono = temp_mono;
        h->heaparr[0].N_clasesp = temp_clases;
        h->heaparr[0].grado = temp_grado;
        //h->heaparr[0].C_invalidas = temp_mapa;
        //memcpy(&h->heaparr[0].C_invalidas,&temp_mapa,sizeof(char)*k);
        //reordena
 	max_heapify(h->heaparr, 0, h->count/*,k*/);
#ifdef DEBUG
        printf("--heap_delete--id:%d, mono:%d, clases:%d, grado:%d\n",removed[0],removed[1],removed[2],removed[3]);
        fflush(stdout);
#endif 
        //free(temp_mapa);
        //return mapa;
}
/*Toma los valores id y Número de clases esperadas de un nodo en específico*/
void ver_arreglo(struct heap *h,int id, int* arr)
{
     arr[0]=h->heaparr[id].id;
     arr[1]=h->heaparr[id].N_clasesp;
}
/*De acuerdo al valor de número monocromático, grado o clases (si es diferente de -1),
 *  actualiza el valor de un nodo en específico deacuerdo con su índice*/
void heap_update(struct heap *h,int nmono, int grad, int clases, int ind)
{
    if(nmono!=-1)
 	h->heaparr[ind].N_mono = nmono;
    if(grad!=-1)
        h->heaparr[ind].grado = grad;
    if(clases!=-1)
        h->heaparr[ind].N_clasesp = clases;
}
/*Libera la memoria asignada para el mapa de clases inválidas*/
void free_arr(struct heap *pq, int k)
{
    int i;
    for(i=0;i<k;i++)
        free(pq->heaparr[i].C_invalidas);
}
/*Elimina todos los nodos del heap y muestra la información de los eliminados*/
void emptyPQ(struct heap *pq,int *removed,char* mapa,int k,char* temp_mapa)
{
	int i;
        while(pq->count != 0) 
        {
            heap_delete(pq,removed/*,mapa,k*/);
            printf("<<%d- %d- %d- %d",removed[0],removed[1],removed[2],removed[3]);
            fflush(stdout);
            for(i=0;i<k;i++)
            {
                printf("%d| ",mapa[i]);
                fflush(stdout);
            }
	}
}

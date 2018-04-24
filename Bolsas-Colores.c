#include <stdio.h>
#include <stdlib.h>
#include "Heap.h"
#include "Matriz-reducida.h"
#define tam_inicial_bolsas 20
int K=4;
/*Recibe el número de bolsas y el heap, para inicializar cada una de las bolsas del heap*/
void Imprime_Bolsas(int numBolsas,struct heap * B_C)
{
    printf("----------------------------\n");
    int i;
    //Imprime las bolsas
    for (i=0;i<numBolsas;i++)
         heap_display(&B_C[i]);
}
/*Recibe el heap para imprimir todos los datos de la estructura*/
void Imprime_Heap(struct heap * heap)
{
    printf("----------------------------\n");
    heap_display(heap);
}
/*Disminuye el número de clases a las adyacentes al nodo actual*/
void disminuye_clases(int nodoActual,int indiceMapa,int numColores,struct heap * h_nodos,unsigned char **Matrix)
{
    int indiceNodos;
    //Arreglo que toma id y clases de un nodo del arreglo de nodos
    int IdClases[2];
    //recorre el índice del arreglo de nodos
    for(indiceNodos=0;indiceNodos<h_nodos->count;indiceNodos++)
    {
         //toma el primer elemento del arreglo
        ver_arreglo(h_nodos,indiceNodos,IdClases);
        //verifica si existe adyacencia con el nodo expulsado
        if(es_vecino(Matrix,nodoActual,IdClases[0]/*id*/)==1)
        {
            //Pregunta si el nodo en su arreglo clases inválidas contiene un cero (un adyacente ya se encuentra en esta bolsa) 
            //--if(consulta_mapa(data->heaparr[i],indiceMapa)==0)
            {
                //--char* temp_mapa=malloc(sizeof(char)*k);
                //disminuye la clase
                heap_update(h_nodos,-1/*N_mono*/, -1/*grado*/, IdClases[1]-1/*clases*/, indiceNodos/*índice*/);
                //ingresa ocupado el color j
                //--update_mapa(data->heaparr[i],indiceMapa);
                //printf("**NODOS**\n");
                //Imprime_Bolsas(1,K,data);
                //Imprime Nodos
                //printf("**NODOS**\n");
                //Imprime_Heap(h_nodos);
                //--free(temp_mapa);
            }
        }
    }
    //reordena
    build_maxheap(h_nodos->heaparr,h_nodos->count);
    //Imprime Nodos
    printf("**NODOS REACOMODADOS**\n");
    Imprime_Heap(h_nodos);
}
/*Ingresa el nodo nuevo en la bolsa sin conflicto del heap*/
void ingresa_en_bolsa(int numBolsa,int numColores,struct heap * bolsasColores,int * nuevoNodo/*,char* mapa*/,struct heap * heapNodos,unsigned char **Matrix)
{
        //ingresa el nodo en la bolsa actual
        heap_push(&bolsasColores[numBolsa], nuevoNodo[0]/*id*/,nuevoNodo[1]/*n_mono*/,nuevoNodo[2]/*clases*/,nuevoNodo[3]/*grado*//*,mapa/*Clases inválidas*//*,0*/);
        //Si el grado es mayor a cero disminuye las clases (si no, no tiene adyacencias)
        if(nuevoNodo[3]/*grado*/>0)
               disminuye_clases(nuevoNodo[0]/*id*/,numBolsa,numColores,heapNodos,Matrix);
        //--mapa=
        //if(removed[0]==5)
        //    printf("told 'ya\n");
        //return mapa;
}
/*Verifica que el nodo actual no tenga alguna adyacencia dentro de la bolsa, 
 * regresa un uno si no encuentra adyacencia, de lo contrario regresa un cero a la primera adyacencia*/
unsigned char esCompatibleBolsa(int numeroNodosBolsa,int idNodo,struct Nodos * contenidoBolsa,unsigned char **Matrix)
{
    int idNodoEnBolsa;
    //Verifica que la bolsa tenga más de un nodo
    if(numeroNodosBolsa>=1)
    {
        //recorre todos los nodos de la bolsa y busca adyacencias
        for(idNodoEnBolsa=0;idNodoEnBolsa<numeroNodosBolsa;idNodoEnBolsa++)
        {
             if(es_vecino(Matrix,idNodo,contenidoBolsa[idNodoEnBolsa].id)==1)
                 return 0;
        }  
    }
    return 1;
}
void N_mono(int k,struct heap B_C[k],unsigned char **Matrix)
{
    unsigned int i,id1,id2,nm=0;//,j
    for (i=0;i<k;i++)
    {
        id2=0;
        //Asegura que la bolsa tenga más de un nodo
        if(B_C[i].count>1)
        {
            for(id1=0;id1<B_C[i].count;id1++)
            {
                for(id2=0;id2<B_C[i].count;id2++)
                {
                    if(id1!=id2)
                    {
                        if(es_vecino(Matrix,B_C[i].heaparr[id1].id-1,B_C[i].heaparr[id2].id-1)!=0)
                            nm++;
                    }
                }
                nm=0;
            }
        }
        max_heapify_mono(B_C[i].heaparr, 0, B_C[i].count);
    }
}
/*Inicializa cada una de las bolsas del heap de colores con un tamaño inicial*/
void Inicializa_Bolsas(int k,int N,struct heap * B_C)
{
    int id;
     //Inicializa las bolsas
    for (id=0;id<k;id++)
        heap_init(&B_C[id],tam_inicial_bolsas,k);
}
/*Inserta el nodo actual en una bolsa aleatoria del heap de colores*/
void InsertaEnBolsaAleatoria(struct heap * heapBolsas,int *nuevoNodo,int numColores)
{
    int BolsaAleatoria=rand()%numColores;
    heap_push(&heapBolsas[BolsaAleatoria], nuevoNodo[1]/*n_mono*/, nuevoNodo[0]/*id*/, nuevoNodo[3]/*grado*/,nuevoNodo[2]/*clases*//*,mapa/*Clases inválidas*//*,0*/);
}
/*Mientras haya nodos en el heap de nodos, se toma el primer nodo del heap de nodos, 
 * mientras recorre todas las bolsas de colores y verifica si existe adyacencias dentro de las bolsas,
 si i se encuentra en alguna de las bolsas ingresa el nodo, si no quiere decir que no hay bolsas compatibles
 y lo inserta en una bolsa aleatoria.*/
void Llena_Bolsas(int numColores,int numNodos,struct heap * BolsasColores,struct heap *heapNodos,unsigned char **Matrix)
{
    int i=0;
    //vector en donde guarda información del nodo que extrae
    int *nuevoNodo;
    nuevoNodo=malloc(4*sizeof(int));
    //inicializa las bolsas de colores
    Inicializa_Bolsas(numColores,numNodos,BolsasColores);
    while(heapNodos->count>0)
    {
        heap_delete(heapNodos, nuevoNodo/*,mapa,numColores*/);
        
        while(i<numColores && esCompatibleBolsa(BolsasColores[i].count,nuevoNodo[0]/*id*/,BolsasColores[i].heaparr,Matrix)==0)
            i++;
        
        if(i<numColores)
        {
            ingresa_en_bolsa(i,numColores,BolsasColores,nuevoNodo/*,mapa*/,heapNodos,Matrix);
        }
        else
        {
            printf("No hay bolsas compatibles\n");
            fflush(stdout);
            InsertaEnBolsaAleatoria(BolsasColores,nuevoNodo,numColores);
            break;
        }    
        i=0;
    }
    while(heapNodos->count>0)
    {
        heap_delete(heapNodos, nuevoNodo/*,mapa,numColores*/);
        InsertaEnBolsaAleatoria(BolsasColores,nuevoNodo,numColores);
    }
    free(nuevoNodo);
}

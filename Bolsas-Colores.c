#include <stdio.h>
#include <stdlib.h>
#include "Heap.h"
#include "Matriz-reducida.h"
#define tam_inicial_bolsas 20
int K=4;

void Imprime_Bolsas(int numBolsas,struct heap * B_C)
{
    printf("----------------------------\n");
    int i;
    //Imprime las bolsas
    for (i=0;i<numBolsas;i++)
         heap_display(&B_C[i]);
}
void Imprime_Heap(struct heap * heap)
{
    printf("----------------------------\n");
    heap_display(heap);
}
void disminuye_clases(int id1,int j,int k,struct heap * h_nodos,unsigned char **Matrix)
{
    int i;
    //Arreglo que toma id y clases de un nodo del arreglo de nodos
    int I_C[2];
    //recorre el índice del arreglo de nodos
    for(i=0;i<h_nodos->count;i++)
    {
         //toma el primer elemento del arreglo
        ver_arreglo(h_nodos,i,I_C);
        //verifica si existe adyacencia con el nodo expulsado
        if(es_vecino(Matrix,id1,I_C[0]/*id*/)==1)
        {
            //Pregunta si el nodo en su arreglo clases inválidas contiene un cero (un adyacente ya se encuentra en esta bolsa) 
            //--if(consulta_mapa(data->heaparr[i],j)==0)
            {
                //--char* temp_mapa=malloc(sizeof(char)*k);
                //disminuye la clase
                heap_update(h_nodos,-1/*N_mono*/, -1/*grado*/, I_C[1]-1/*clases*/, i/*índice*/);
                //ingresa ocupado el color j
                //--update_mapa(data->heaparr[i],j);
                //printf("**NODOS**\n");
                //Imprime_Bolsas(1,K,data);
                //Imprime Nodos
                printf("**NODOS**\n");
                Imprime_Bolsas(K,h_nodos);
                //--free(temp_mapa);
            }
        }
    }
    //reordena
    build_maxheap(h_nodos->heaparr,h_nodos->count);
    //Imprime Nodos
    printf("**NODOS REACOMODADOS**\n");
    Imprime_Bolsas(K,h_nodos);
}

void ingresa_en_bolsa(int numBolsa,int numColores,struct heap * bolsasColores,int * nuevoNodo/*,char* mapa*/,struct heap * heapNodos,unsigned char **Matrix)
{
        //ingresa el nodo en la bolsa actual
        heap_push(&bolsasColores[numBolsa], nuevoNodo[0]/*id*/,nuevoNodo[1]/*n_mono*/,nuevoNodo[2]/*clases*/,nuevoNodo[3]/*grado*//*,mapa/*Clases inválidas*//*,0*/);
        //Si el grado es mayor a cero disminuye las clases (si no, no tiene adyacencias)
        //if(nuevoNodo[3]/*grado*/>0)
        //       disminuye_clases(nuevoNodo[0]/*id*/,numBolsa,numColores,heapNodos,Matrix);
        //--mapa=
        //if(removed[0]==5)
        //    printf("told 'ya\n");
        //return mapa;
}
unsigned char esCompatibleBolsa(int numeroNodosBolsa,int idNodo,struct Nodos * contenidoBolsa,unsigned char **Matrix)
{
    int id2;
    //Verifica que la bolsa tenga más de un nodo
    if(numeroNodosBolsa>=1)
    {
        //recorre todos los nodos de la bolsa y busca adyacencias
        for(id2=0;id2<numeroNodosBolsa;id2++)
        {
             if(es_vecino(Matrix,idNodo,contenidoBolsa[id2].id)==1)
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
void Inicializa_Bolsas(int k,int N,struct heap * B_C)
{
    int id;
     //Inicializa las bolsas
    for (id=0;id<k;id++)
        heap_init(&B_C[id],tam_inicial_bolsas,k);
}
void InsertaEnBolsaAleatoria(struct heap * heapBolsas,int *nuevoNodo,int numColores)
{
    int BolsaAleatoria=rand()%numColores;
    heap_push(&heapBolsas[BolsaAleatoria], nuevoNodo[1]/*n_mono*/, nuevoNodo[0]/*id*/, nuevoNodo[3]/*grado*/,nuevoNodo[2]/*clases*//*,mapa/*Clases inválidas*//*,0*/);
}
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

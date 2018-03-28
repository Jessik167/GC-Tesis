#include <stdio.h>
#include <stdlib.h>
#include "Heap.h"
#include "Matriz-reducida.h"
int K=4;

void Imprime_Bolsa(int c,int k,struct heap B_C[k])
{
    printf("----------------------------\n");
    int i;
    //Imprime las bolsas
    for (i=0;i<c;i++)
         heap_display(&B_C[i],k);
}
void disminuye_clases(int count,int id1,int j,int k,struct heap * data,unsigned char **Matrix)
{
    int i;
    //Arreglo que toma id y clases de un nodo del arreglo de nodos
    int I_C[2];
    //recorre el índice del arreglo de nodos
    for(i=0;i<count;i++)
    {
         //toma el primer elemento del arreglo
        ver_arreglo(data,i,I_C);
        //verifica si existe adyacencia con el nodo expulsado
        if(get_value(Matrix,id1,I_C[0]/*id*/)==1)
        {
            //Pregunta si el nodo en su arreglo clases inválidas contiene un cero (un adyacente ya se encuentra en esta bolsa) 
            if(consulta_mapa(data->heaparr[i],j)==0)
            {
                char* temp_mapa=malloc(sizeof(char)*k);
                //disminuye la clase
                heap_update(data,-1/*N_mono*/, -1/*grado*/, I_C[1]-1/*clases*/, i/*índice*/);
                //ingresa ocupado el color j
                update_mapa(data->heaparr[i],j);
                //printf("**NODOS**\n");
                //Imprime_Bolsa(1,K,data);
                //reordena
                max_heapify(data->heaparr, 0, data->count,temp_mapa);
                //Imprime Nodos
                printf("**NODOS**\n");
                Imprime_Bolsa(1,K,data);
                free(temp_mapa);
            }
        }
    }
}

char* ingresa_en_bolsa(int k,int i,struct heap B_C[k],int * removed,char* mapa,struct heap *Nodos,unsigned char **Matrix,char* temp_mapa)
{
        //ingresa el nodo en la bolsa actual
        heap_push(&B_C[i], removed[1]/*n_mono*/, removed[0]/*id*/, removed[3]/*grado*/,removed[2]/*clases*/,mapa/*Clases inválidas*/,0);  
        //Si el grado es mayor a cero disminuye las clases (si no, no tiene adyacencias)
        if(removed[3]/*grado*/>0)
                disminuye_clases(Nodos->count,removed[0]/*id*/,i,k,Nodos,Matrix);
        mapa=heap_delete(Nodos, removed,mapa,temp_mapa);
        return mapa;
}
unsigned char es_Adyacente(int count,int id1,struct Nodos * B_C,unsigned char **Matrix)
{
    int id2;
    //Verifica que la bolsa tenga más de un nodo
    if(count>=1)
    {
        for(id2=0;id2<count;id2++)
        {
             if(get_value(Matrix,id1,B_C[id2].id)==1)
                 return 1;
        }  
    }
    return 0;
}
void N_mono(int k,struct heap B_C[k],unsigned char **Matrix)
{
    unsigned int i,j,id1,id2,nm=0;
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
                        if(get_value(Matrix,B_C[i].heaparr[id1].id-1,B_C[i].heaparr[id2].id-1)!=0)
                            nm++;
                    }
                }  
                //heap_update(&B_C[i],nm,-1,id1);   
                //Imprime_Bolsas(k,B_C);
                nm=0;
            }
        }
        max_heapify_mono(B_C[i].heaparr, 0, B_C[i].count);
    }
}
void Inicializa_Bolsa(int k,int N,struct heap B_C[k],struct heap *Nodos,unsigned char **Matrix)
{
    int id,i=0;
    //vector en donde guarda información del nodo
    int *removed;
    char * mapa;
    mapa=malloc(k*sizeof(char));
    char* temp_mapa=malloc(sizeof(char)*k);
    removed=malloc(4*sizeof(int));
    //Inicializa las bolsas
    for (id=0;id<k;id++)
        heap_init(&B_C[id],N,k);
    //Toma el primer nodo del heap de los nodos
    heap_delete(Nodos, removed, mapa,temp_mapa);
    
    //hasta que las clases permitidas del nodo a insertar sea cero ó Ya no hay más nodos en el heap
    while(removed[2]>0 && Nodos->count+1>0)
    {
        //Pregunta si la bolsa actual está vacía
        if(B_C[i].count==0)
        {
            mapa=ingresa_en_bolsa(k,i,B_C,removed,mapa,Nodos,Matrix,temp_mapa);
            i=0;
            //Imprime Nodos
            printf("**BOLSA**\n");
            Imprime_Bolsa(k,k,B_C);
            //Imprime Nodos
            printf("**NODOS**\n");
            Imprime_Bolsa(1,k,Nodos);
        }
        else
        {
            if(es_Adyacente(B_C[i].count,removed[0]/*id*/,B_C[i].heaparr,Matrix)!=1)
            {
                mapa=ingresa_en_bolsa(k,i,B_C,removed,mapa,Nodos,Matrix,temp_mapa);
                i=0;
                //Imprime Nodos
                printf("**BOLSA**\n");
                Imprime_Bolsa(k,k,B_C);
                //Imprime Nodos
                printf("**NODOS**\n");
                 Imprime_Bolsa(1,k,Nodos);
            }
            else
                i++;
        }
    }
    
    //recorre las bolsas de colores
    /*for(i=0;i<k;i++)
    {
        //Toma el primer nodo del heap de los nodos
        heap_delete(Nodos, removed);
        if(es_Adyacente(B_C->count,removed[0]/*id,B_C[i],Matrix)!=0)
                ingresa_en_bolsa(k,i,B_C,removed,Nodos,Matrix);
    }/
    while(Nodos->count>0)
    {
        i=rand()%k;
        ingresa_en_bolsa(k,i,B_C,removed,mapa,Nodos,Matrix);
        //Imprime Nodos
        Imprime_Bolsa(k,k,B_C);
    }*/
    free(removed);
    free(mapa);
    free(temp_mapa);
}

/* 
 * File:   main.c
 * Author: jessy Urrea
 *
 * Created on 5 de diciembre de 2017, 04:50 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Heap.h"
#include "Matriz-reducida.h"
#include "Bolsas-Colores.h"
/*
 * 
 */
int N;
int k=4;
//Prototipo
void N_grado(struct heap Nodos_G[1],unsigned char **Matrix,int c);

void main(int argc, char const *argv[])
{
	//verifica parámetros
	if(argc!=3)
	{
		printf("Ingrese correctamente los parámetros: %s nombre_archivo_aristas.txt tamaño\n",argv[0]);
	}
	else
	{
		//Declaración de variables
                srand(time(NULL));
                int i,j;
                unsigned char **M;
                //Toma el valor del número de nodos de la línea de comandos
		N=atoi(argv[2]);
                //Crea la Matriz de bits
                M=Inicializa_Matriz(N,M);
                //Llena la matriz deacuerdo al nombre del archivo
                Llena_Matriz(argv[1],N,M);
                //Imprime la matriz de adyacencia
                Imprime_Matriz(M,N);
                //Imprime un elemento de la matriz
                printf("\nvalue:%d\n",get_value(M,6,10));
                /*printf("value:%d\n",get_value(M,2,1));
                printf("value:%d\n",get_value(M,2,2));
                printf("value:%d\n",get_value(M,2,3));
                printf("value:%d\n",get_value(M,2,4));
                printf("value:%d\n",get_value(M,2,5));
                printf("value:%d\n",get_value(M,2,6));
                printf("value:%d\n",get_value(M,2,7));
                printf("value:%d\n",get_value(M,2,8));
                printf("value:%d\n",get_value(M,2,9));
                printf("value:%d\n",get_value(M,2,10));*/
                //Crea estructura de grado de nodos
                struct heap *Nodos_G;
                //asigna memoria
                Nodos_G=malloc(sizeof(Nodos_G));
                //Inicializa la estructura de grado de nodos
                heap_init(Nodos_G,N,k);
                //calcula el grado de los vértices
                N_grado(Nodos_G,M,k);
                printf("---------------------------------------\n");
                heap_display(Nodos_G,k);
                
                //Inicializa la configuración de los individuos
                struct heap B_Colores[k];
                //Inicializa las bolsas de colores
                Inicializa_Bolsa(k,N,B_Colores,Nodos_G,M);
                //Imprime las bolsas
                //Imprime_Bolsa(k,B_Colores);
                //Verifica el número de aristas monocromáticas
                //N_mono(k,B_Colores,M);
                
                //Imprime las bolsas
                Imprime_Bolsa(k,B_Colores);
                Imprime_Bolsa(1,Nodos_G);
                //Libera la matriz
                free(M);
                free(Nodos_G);
                //emptyPQ(Nodos_G);
	}
}
void N_grado(struct heap Nodos_G[1],unsigned char **Matrix,int c)
{
    int id=0,id1=0,grad;
    //recorre todos los nodos
    for(id=0;id<N;id++)
    {
        grad=0;
        for(id1=0;id1<N;id1++)
        {
            //if(id!=id1)
                if(get_value(Matrix,id,id1)!=0)
                        grad++;
        }
        heap_push(&Nodos_G[0], 0, id, grad,c);
        //if(c>0)
        //        c=rand()%k+1;
    }
    //build_minheap(&Nodos_G[0],N);
}




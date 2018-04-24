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
#define tam_nodos 1
/*
 * 
 */
int NumNodos;
int numColores=4;
//Prototipo
void Llena_nodos_grado(struct heap *Nodos_G,unsigned char **Matrix,int c);

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
                unsigned char **M;
                //Toma el valor del número de nodos de la línea de comandos
		NumNodos=atoi(argv[2]);
                //Crea la Matriz de bits
                M=Inicializa_Matriz(NumNodos);
                //Llena la matriz deacuerdo al nombre del archivo
                Llena_Matriz(argv[1],NumNodos,M);
                //Imprime la matriz de adyacencia
                Imprime_Matriz(M,NumNodos);
                //Imprime un elemento de la matriz
                printf("\nvalue:%d\n",es_vecino(M,10,2));
                
                struct heap Nodos_G;
                //asigna memoria
                //Nodos_G=malloc(sizeof(struct heap));
                //Inicializa la estructura de grado de nodos
                heap_init(&Nodos_G,NumNodos,numColores);
                //calcula el grado de los vértices y los inserta en la bolsa de nodos
                Llena_nodos_grado(&Nodos_G,M,numColores);
                Imprime_Heap(&Nodos_G);
                
                //Inicializa la configuración de los individuos
                struct heap * B_Colores;
                //asigna memoria
                B_Colores=malloc(sizeof(struct heap)*numColores);
                //Inicializa las bolsas de colores
                Llena_Bolsas(numColores,NumNodos,B_Colores,&Nodos_G,M);
                //Imprime las bolsas
                printf("**BOLSAS DE COLORES**\n");
                Imprime_Bolsas(numColores,B_Colores);
                //Verifica el número de aristas monocromáticas
                //N_mono(numColores,B_Colores,M);
                            
                //--free_arr(B_Colores,numColores);
                //--free_arr(Nodos_G,1);
                //Libera la matriz
                free(M);
                printf(":D!!\n");
	}
}
void Llena_nodos_grado(struct heap *Nodos_G,unsigned char **Matrix,int clases)
{
    int id=0,id1=0,grad,nmono=0;
    //--char* mapa;
    //recorre todos los nodos
    for(id=0;id<NumNodos;id++)
    {
        grad=0;
        for(id1=0;id1<NumNodos;id1++)
        {
            //if(id!=id1)
                if(es_vecino(Matrix,id,id1)!=0)
                        grad++;
        }
        heap_push(Nodos_G,id,nmono,clases,grad/*,mapa,-1*/);
        //if(c>0)
        //        c=rand()%k+1;
    }
}




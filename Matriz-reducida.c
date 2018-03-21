#include <math.h>
#include <stdio.h>
#include <stdlib.h>
double TM;
/*unsigned char** Crea_Matriz(int N)
{
    unsigned char M[N][ceil(N/8)];
    //M= (unsigned char**) calloc(N, sizeof(unsigned char *));
    return M;
}*/
unsigned char** Inicializa_Matriz(int N,unsigned char **M)
{
    int j;
    M= malloc(N*sizeof(unsigned char *));
    TM=(double)N/8;
    TM=ceil(TM)*8;
    //Asigna memoria por cada elemento de la matriz
    for(j=0;j<N;j++)
        M[j]= calloc(N/8,sizeof(unsigned char));
    return M;
}
void Llena_Matriz(const char* nombre,int N,unsigned char **M)
{
    //Declaración de variables
	int a,b,recorrimiento1,recorrimiento2;
	FILE * archivo;
	//Abre el archivo
	archivo=fopen(nombre,"r");
	//Verifica que exista el archivo
	if(archivo!=NULL)
	{
		//lee el archivo de dos datos separados por una coma, hasta el final del archivo 
		while(fscanf(archivo,"%d %d",&a,&b) != EOF)
		{
                    //se maneja de ambos lados, ya que es un grafo no dirigido
                   // if((int)(b-1)/8==0) 
                    {
                        recorrimiento1=abs((b-1)-((int)TM-1))%8;
                        recorrimiento2=abs((a-1)-((int)TM-1))%8;
                    }
                    /*else
                    {
                        recorrimiento1=8-abs((b-1)-((int)TM-1))%8;
                        recorrimiento2=8-abs((a-1)-((int)TM-1))%8;
                   }*/
                   M[a-1][(int)(b-1)/8]|=1<<recorrimiento1;
                   M[b-1][(int)(a-1)/8]|=1<<recorrimiento2;
                   //printf("M[%d][%d]:%d\n",a-1,(int)(b-1)/8,M[a-1][(int)(b-1)/8]);
                }
		//cierra el archivo
		fclose(archivo);
	}
	else
	{
		printf("El archivo no existe\n");
		exit(1);
	}
}
void Imprime_Matriz(unsigned char ** M,int N)
{
    printf("-----------------------------------------------------------------\n");
    int renglon, columna,recorrimiento;
    unsigned char mask=128;
    for(renglon=0;renglon<N;renglon++)
    {
        for(columna=0;columna<=N/8;columna++)
        {
            for(recorrimiento=0;recorrimiento<8;recorrimiento++)
            {
                printf("%d ",((M[renglon][columna]<<recorrimiento)&mask)>>7);
            }
        }
        printf("\n");
    }
}
unsigned char get_value(unsigned char** M,int i, int j)
{
    int recorrimiento;
    unsigned char mask=128;
    if(j>=8)
        recorrimiento=j-8;
    else
        recorrimiento=j;
    //recorrimiento=abs(j-((int)TM-1))%8;
    return ((M[i][(int) j/8]<<recorrimiento)&mask)>>7;
}


#include "laboHilos.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include<stdint.h>
//Creo e inicializo variables
int i;
char dir[50] ="/home/Juanma/Documentos/";
pthread_t hilos[3];
int a[6],b[6];
FILE* f1;

/**Primera tarea*/
void* sumar(void* i){
    char nombre[100];
    int j= *(intptr_t*)i;

    printf("Entre con el hilo nro: %d\n",j);
    sprintf(nombre,"/home/Juanma/Documentos/Archivo%d.txt",j);
    f1=fopen(nombre,"w");
    int suma=a[j]+b[j];
    fprintf(f1,"%d,",suma);
    suma=a[j+3]+b[j+3];
    fprintf(f1,"%d,",suma);
    fclose(f1);
    printf("Termino la ejecucion \n");
    pthread_exit(NULL);

}


int h_inicio(){
    //Inicializo vectores
    for(i=0; i<6;i++){
        a[i]=i+2;
        b[i]=3*i;
    }
    //Creo los hilos de trabajo
    int resultado;
    for(i=0;i<3;i++){
    resultado=pthread_create(&hilos[i],NULL,sumar,(void*)&i);
    printf("Resultado= %d,Adentro, hilo nro %d\n",resultado,i);
    pthread_join(hilos[i],NULL);
    }

    //Ahora leo y escribo en pantalla
    FILE*fa;
    FILE*fb;
    FILE*fc;
    fa=fopen("/home/Juanma/Documentos/Archivo0.txt","r");
    fb=fopen("/home/Juanma/Documentos/Archivo1.txt","r");
    fc=fopen("/home/Juanma/Documentos/Archivo2.txt","r");
    char c;
    int m;
    for(m=0; m<2;m++){
        c=getc(fa);
        if(c!='\n'){
            do{
                printf("%c",c);
                c=getc(fa);
            }while(c!=',');
        }
        printf(",");
        c=getc(fb);
        if(c!='\n'){
            do{
                printf("%c",c);
                c=getc(fb);
            }while(c!=',');
        }
        printf(",");
        c=getc(fc);
        if(c!='\n'){
             do{
                printf("%c",c);
                c=getc(fc);
            }while(c!=',');
        }
        if(m==0)
        printf(",");
    }
    printf(".\n");
    fclose(fa);
    fclose(fb);
    fclose(fc);

    return 0;
}



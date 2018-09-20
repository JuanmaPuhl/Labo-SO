#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

/**
    Enunciado: Los procesos P2 hasta P4 colaboran con el proceso p1 para que pueda realizar todo el trabajo. P2,P3 y P4 se ejecutan
    concurrentemente. Las actividades que se realizan en las tareas son las siguientes:

    Tarea 1: Ingresa o asigna valores a 2 vectores de 6 elementos.
    Tarea 2: Cada proceso obtiene la suma de dos elementos correspondientes, por ejemplo P2= A[i]+B[i] y A[i+3]+B[i+3].El resultado
    de la suma lo guarda en un archivo.
    Tarea 3: Muestra por pantalla la suma de los dos vectores.
*/

    //Metodo que calcula la suma de los arreglos
void tarea2(int a[], int b[],int i,FILE* f){
    int suma= a[i]+b[i];
    fprintf(f,"%d,",suma);
    suma=a[i+3]+b[i+3];
    fprintf(f,"%d,",suma);
}
//Metodo que escribe por pantalla el contenido de los 3 archivos en orden.
void tarea3(FILE* f1, FILE* f2, FILE* f3){
    char c;
    int m;
    for(m=0; m<2;m++){
        c=getc(f1);
        if(c!='\n'){
            do{
                printf("%c",c);
                c=getc(f1);
            }while(c!=',');
        }
        printf(",");
        c=getc(f2);
        if(c!='\n'){
            do{
                printf("%c",c);
                c=getc(f2);
            }while(c!=',');
        }
        printf(",");
        c=getc(f3);
        if(c!='\n'){
             do{
                printf("%c",c);
                c=getc(f3);
            }while(c!=',');
        }
        if(m==0)
        printf(",");
    }
    printf(".\n");
}

//Creo e inicializo variables
char dir1[50] ="/home/Juanma/Documentos/A.txt", dir2[50] ="/home/Juanma/Documentos/B.txt", dir3[50] ="/home/Juanma/Documentos/C.txt";
FILE* f1,*f2,*f3;
int a[6],b[6],pi,i;

//Metodo auxiliar para abrir los 3 archivos en el modo c
void abrirArchivos(char* c){
f1=fopen(dir1,c);
f2=fopen(dir2,c);
f3=fopen(dir3,c);
}
//Metodo auxiliar para cerrar los 3 archivos
void cerrarArchivos(){
fclose(f1);
fclose(f2);
fclose(f3);
}

void sumarProcesos(){
//Inicializo los arreglos
 for(i=0; i<6;i++){
    a[i]=i+2;
    b[i]=3*i;
    }

//Creo los subprocesos
abrirArchivos("w");
for(i=0; i<3;i++){
    pi=fork();
    if(pi==0){

        if(i==0)
            tarea2(a,b,i,f1);
        if(i==1)
            tarea2(a,b,i,f2);
        if(i==2)
            tarea2(a,b,i,f3);

        break;
    }

//Espero que terminen todos los procesos hijos
while (waitpid(-1, NULL, 0)) {
           if (errno == ECHILD) {
              break;
           }
    }
}
cerrarArchivos();
//Imprimo por pantalla el contenido de todos los archivos
if(pi!=0){
//Entre en el proceso padre nuevamente
abrirArchivos("r");
printf("La suma de los dos arreglos es: ");
tarea3(f1,f2,f3);
cerrarArchivos();
}
}

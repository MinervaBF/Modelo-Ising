#include <math.h>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <fstream>
//Para usar la misma dimensión en todo el programa definimos dicha dimensión N.
#define N 50

using namespace std;

int main (void)
{

int i, j, k, m1, m2, num1;
float temp, energ, p, num2;
int x1[N+2][N+2];
//Los índices de la matriz van desde 0 a N+1 para las condiciones de contorno periódicas,
//si queremos una red de dimensión N, tendremos una matriz de N+2 elementos en cada fila.

FILE *f1;

//Abrimos los archivos
f1=fopen("evolucion.txt","w");

srand(time(NULL));

//Introducimos una temperatura
temp=0.1;


if (temp > 2)
    for(i=0;i<=N+1;i++)
        for(j=0;j<=N+1;j++)
            x1[i][j]=1;
else
{
    //Generamos un estado inicial aleatorio si la temperatura es 0.

for(i=0;i<=N+1;i++)
{
    for(j=0;j<=N+1;j++)
    {
        num1=rand()%2;
        if(num1==0) x1[i][j]=1;
        else x1[i][j]=-1;
    }
}

//Forzamos que se cumplan las condiciones de contorno periódicas.

for(i=0;i<=N;i++)
{
    //Columnas
    x1[0][i]=x1[N][i];
    x1[N+1][i]=x1[1][i];
    //Filas
    x1[i][0]=x1[i][N];
    x1[i][N+1]=x1[i][1];
}
}

printf("La matriz inicial es:\n");
for (i=1; i<=N; i++)
    {
        for (j=1;j<=N; j++)
        {
            printf("%i\t", x1[i][j]);
        }
        printf("\n");
    }


//Imprimo en el fichero el estado inicial.
for (i=1; i<=N; i++)
    {
        for (j=1;j<=N-1; j++)
        {
            fprintf(f1, "%i%c\t", x1[i][j], 44);
        }
        fprintf(f1, "%i\t", x1[i][N]);
        fprintf(f1, "\n");
    }
    fprintf(f1, "\n");

for(k=1; k<=(1000*N*N); k++)
{
//Elegimos un punto al azar de la matriz. Para ello generamos dos números al azar dentro
//de las dimensiones de la matriz.
m1=1+(rand()%(N));
m2=1+(rand()%(N));

//Evaluamos p.
energ=2.*x1[m1][m2]*(x1[m1+1][m2]+x1[m1-1][m2]+x1[m1][m2+1]+x1[m1][m2-1]);
p=exp(-1.*energ/temp);
if(1<p) p=1.;

//Generamos un número aleatorio perteneciente a [0,1] y si es menor que p cambiamos el signo del espín.

num2=(double)rand()/(double)RAND_MAX;
if (num2<p) x1[m1][m2]=-1*x1[m1][m2];

//Tenemos que volver a imponer que se cumplan las condiciones de contorno periódicas.
for(i=0;i<=N;i++)
{
    //Columnas
    x1[0][i]=x1[N][i];
    x1[N+1][i]=x1[1][i];
    //Filas
    x1[i][0]=x1[i][N];
    x1[i][N+1]=x1[i][1];
}

 //Imprimimos los datos en un fichero una vez cada paso MonteCarlo.
 if(k%(N*N)==1)
    for (i=1; i<=N; i++)
    {
        for (j=1;j<=N-1; j++)
        {
            fprintf(f1, "%i%c\t", x1[i][j], 44);
        }
        fprintf(f1, "%i\t", x1[i][N]);
        fprintf(f1, "\n");
    }
   if (k%(N*N)==2) fprintf(f1, "\n");

}
printf("La matriz final es:\n");
for (i=1; i<=N; i++)
    {
        for (j=1;j<=N; j++)
        {
            printf("%i\t", x1[i][j]);
        }
        printf("\n");
    }


fclose(f1);

return 0;

}

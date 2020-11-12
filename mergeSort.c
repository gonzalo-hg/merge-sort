#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define true 1
#define false 0

int compInt(void *a, void *b)
{
        if (*((int*)(a)) > *((int*)(b))) {
                return true;
        }
        return false;
}

void intercambioInt(void *a, void *b)
{
        int aux;
        aux = *(int*)(a);
        *(int*)(a) = *(int*)(b);
        *(int*)(b) = aux;
}

int compDouble(void *a, void *b)
{
        if (*(double*)(a) > *(double*)(b)) {
                return true;
        }
        return false;
}

void intercambioDouble(void *a, void *b)
{
        int aux;
        aux = *(double*)(a);
        *(double*)(a) = *(double*)(b);
        *(double*)(b) = aux;
}

void ordenaMerge(void *direccion,int izquierda, int derecha, int mitad, size_t sbytes ,int (*comp)(void *a, void *b), void (*intercambio)(void *a, void *b)){
        int n1 =( mitad - izquierda) + 1;
        int n2 =  derecha-mitad;

        void *derechaV;
        void *izquierdaV;
        int i,j,k;

        izquierdaV = (char*)malloc(n1 * sbytes);
        derechaV = (char*)malloc(n2 * sbytes);

        for(i=0;i<n1;i++){
                intercambio(izquierdaV+sbytes*i,(char*)direccion+sbytes*(izquierda+i));
        }
        for(j = 0; j < n2; j++){
 
                intercambio(derechaV+sbytes*j,(char*)direccion+sbytes*(mitad+j+1));
        }

        i=0,j=0;

        for(k = izquierda; k < derecha+1; k++){
                if (i == n1) {
                        
                        intercambio((char*)direccion+sbytes*k,derechaV+sbytes*j);
                        j++;
                }
                else if(j == n2){
                        
                        intercambio((char*)direccion + sbytes * k,izquierdaV + sbytes*i);
                        i++;
                }
                else{
                        
                        if(comp((char*)izquierdaV + sbytes*i,(char*)derechaV + sbytes *j)){
                               
                                intercambio((char*)direccion + sbytes * k,izquierdaV + sbytes * i);
                                i++;
                        }
                        else{
                                
                                intercambio((char*)direccion + sbytes * k, derechaV + sbytes * j);
                                j++;
                        }
                }
        }
}

void mergeSort(void *direccion, int izquierda, int derecha,size_t sbytes, int(*comp)(void *a, void *b), void(*intercambio)(void*a,void*b)){
        if(izquierda< derecha){
                int q = (izquierda + derecha)/2;
                mergeSort(direccion,izquierda,q,sbytes,comp,intercambio);
                mergeSort(direccion,q+1,derecha,sbytes,comp,intercambio);
                ordenaMerge(direccion,izquierda,derecha,q,sbytes,comp,intercambio);
        }
}


void ordenar(void *direccion, int num_elementos, size_t sbytes, int (*comp)(void *a, void *b), void (*intercambio)(void *a, void *b)) {
        int i,j;
        for(i=1;i<num_elementos; i++){
                for(j=0; j<num_elementos-i; j++)
                {
                        if (comp((char*)direccion + sbytes * j, (char*)direccion + sbytes * (j+1))) {
                                intercambio((char*)direccion + sbytes * j, (char*)direccion + sbytes * (j+1));
                        }
                }
        }

}

int main(){

        int array1[] = {3, 5, 8, 9, 1, 2, 4, 7, 6, 0};
        int num_elementos1 = 10;
        void *direccion1;
        double array2[] = {3.0, 5.0, 8.0, 9.0, 1.0, 2.0, 4.0, 7.0, 6.0, 0.0};
        int num_elementos2 = 10;
        void *direccion2;
        int array3[] = {11,13,12,15,14,16,18,17,20,19};
        int i, pid=1;
        if(pid == 1){
                direccion1 = array1;
                printf("Merge Sort\n");
                mergeSort(direccion1,0,(num_elementos1)-1,sizeof(int),compInt,intercambioInt);
                for (i = 0; i < num_elementos1; ++i) {

                        printf("%d ", array1[i]);
                  
                }
                printf("\n\n");
                pid = 2;
        }
        
        if(pid != 1){
                direccion2 = array2;
                mergeSort(direccion2, 0,num_elementos2, sizeof(double), compDouble, intercambioDouble);
                for (    i = 0; i < num_elementos2; ++i) {
                        printf("%0.2lf ", array2[i]);
                }
                printf("\n\n");
        }
        return 0;
}

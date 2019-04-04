#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

int T;
int number[100],tampungan[100];
int factorial=1,b=0,c,d=0;

void* fungsi(void *arg)
{
        int i,j,sementara;
        for(c=1;c<=number[b];c++)
        {
                factorial*=c;
        }
        tampungan[d]=factorial;
        factorial=1;
        b+=1;
        d+=1;
        if(d==T)
        {
                for (i=0;i<T;i++)
                {
                        for (j=i+1;j<T;j++)
                        {
                                if(tampungan[i] > tampungan[j])
                                {
                                        sementara = tampungan[i];
                                        tampungan[i] = tampungan[j];
                                        tampungan[j] = sementara;
                                }
                        }
                }
                for (i=0;i<T;i++)
                {
                        printf("%d\n", tampungan[i]);
                }
        }
        return NULL;
}

int main(void)
{
        int i;
        printf("Masukkan jumlah bilangan : ");
        scanf("%d", &T);
        printf("Masukkan bilangan : ");
        for (i=0;i<T;i++)
        {
                scanf("%d", &number[i]);
        }
        for (i=0;i<T;i++)
        {
                pthread_t tid[i];
                pthread_create(&(tid[i]),NULL,fungsi,NULL);
                pthread_join(tid[i],NULL);
        }
        return 0;
}

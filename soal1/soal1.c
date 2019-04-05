#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

int k=0, input;
int number[100],tampungan[100];
int factorial=1,b=0,c,d=0;

void* fungsi(void *arg)
{
        int i,j,sementara;
        for(c=1;c<=number[b];c++)
        {
                if(number[b] == 0)
                {
                        factorial = 1;
                }
                else
                {
                        factorial*=c;
                }

        }
        tampungan[d]=factorial;
        factorial=1;
        b+=1;
        d+=1;
        if(d==k)
        {
                for (i=0;i<k;i++)
                {
                        for (j=i+1;j<k;j++)
                        {
                                if(tampungan[i] > tampungan[j])
                                {
                                        sementara = tampungan[i];
                                        tampungan[i] = tampungan[j];
                                        tampungan[j] = sementara;
                                }
                        }
                }
                for (i=0;i<k;i++)
                {
                        printf("%d\n", tampungan[i]);
                }
        }
        return NULL;
}

int main(void)
{
        int i;
        printf("Masukkan bilangan : ");
        while((input= getchar()) != 10 && k<100) //10 is LineFeed which is sent when pressing enter
        {
                if (input != 32) //spacing
                {
                        number[k++] = input - '0';
                }
        }
        for (i=0;i<k;i++)
        {
                pthread_t tid[i];
                pthread_create(&(tid[i]),NULL,fungsi,NULL);
                pthread_join(tid[i],NULL);
        }
        return 0;
}

#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int WakeUp_Status = 0;
int Spirit_Status = 100;
int status=0; //jumlah wake up dijalankan berapa kali
int status2=0; //jumlah spirit dijalankan berapa kali
int input;

void* fungsi(void *arg)
{
        if(input==1)
        {
                printf("Agmal WakeUp_Status = %d\n", WakeUp_Status);
                printf("Iraj Spirit_Status = %d\n", Spirit_Status);
        }
        else if (input==2)
        {
                if(status2>=3)
                {
                        printf("Agmal Ayo Bangun disabled 10 s\n");
                        sleep(10);
                        status2=0;
                }
                else if(status2<3)
                {
                        WakeUp_Status+=15;
                        status++;
                }
        }
        else if (input==3)
        {
                if(status>=3)
                {
                        printf("Fitur Iraj Ayo Tidur disabled 10 s\n");
                        sleep(10);
                        status=0;
                }
                else if(status<3)
                {
                        Spirit_Status-=20;
                        status2++;
                }
        }


        return NULL;
}

int main(void)
{
        int i=0;
        printf("Terdapat 3 fitur utama: \n");
        printf("1. Tekan 1 jika ingin menampilkan status\n");
        printf("2. Tekan 2 jika ingin menambah WakeUp_Status\n");
        printf("3. Tekan 3 jika ingin mengurangi Spirit_Status\n");
        while(1)
        {
                printf("Masukkan perintah : ");
                scanf("%d", &input);
                pthread_t tid[i];
                pthread_create(&(tid[i]),NULL,fungsi,NULL);
                pthread_join(tid[i],NULL);
                i++;

                if (WakeUp_Status >= 100)
                {
                        printf("Agmal Terbangun, mereka bangun pagi dan berolahraga\n");
                        break;
                }
                if (Spirit_Status <= 0)
                {
                        printf("Iraj ikut tidur, dan bangun kesiangan bersama Agmal\n");
                        break;
                }
        }

        exit(0);
        return 0;
}

LAPORAN RESMI
SISTEM OPERASI



KELOMPOK : C1

**Oleh:**

Yuki Yanuar Ratna

05111740000023

Adnan Erlangga Raharja

05111740000100

**Asisten Pembimbing:**

M.Faris Didin Andiyar

5115100118

Departemen Infomatika

Fakultas Teknologi Informasi dan Komunikasi

Institut Teknologi Sepuluh Nopember (ITS)

Surabaya

2019

**Soal**

1. Buatlah program C yang bisa menghitung faktorial secara parallel lalu menampilkan hasilnya secara berurutan

Contoh:
	
./faktorial 5 3 4
	
3! = 6

4! = 24

5! = 120

**Jawaban :**

**Cara Pengerjaan**

- Buatlah program C seperti ini 
```
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
```
- Lalu ketik di terminal 
```
gcc -pthread -o soal1 soal1.c
```

- Lalu jalankan ```./soal1```

- Program C tersebut ketika sudah mendapatkan hasil faktorial maka akan disimpan di dalam array lalu baru diurutkan dari yang terkecil sampai ke yang terbesar. Lalu setelah diurutkan baru di print.

**Kendala Yang Dialami**

-

**Screenshot**

![Screenshot1](https://2.bp.blogspot.com/-h1eZ1yUranA/XLAZXJ9unXI/AAAAAAAAAoc/Q2RHexJ356cRQbc9YKYydC-x6gs0HvY-gCLcBGAs/s1600/1.png)

2. Pada suatu hari ada orang yang ingin berjualan 1 jenis barang secara private, dia memintamu membuat program C dengan spesifikasi sebagai berikut:

a. Terdapat 2 server: server penjual dan server pembeli

b. 1 server hanya bisa terkoneksi dengan 1 client

c. Server penjual dan server pembeli memiliki stok barang yang selalu sama

d. Client yang terkoneksi ke server penjual hanya bisa menambah stok

Cara menambah stok: client yang terkoneksi ke server penjual mengirim string “tambah” ke server lalu stok bertambah 1

e. Client yang terkoneksi ke server pembeli hanya bisa mengurangi stok

Cara mengurangi stok: client yang terkoneksi ke server pembeli mengirim string “beli” ke server lalu stok berkurang 1

f. Server pembeli akan mengirimkan info ke client yang terhubung dengannya apakah transaksi berhasil atau tidak berdasarkan ketersediaan stok

Jika stok habis maka client yang terkoneksi ke server pembeli akan mencetak “transaksi gagal”
 
Jika stok masih ada maka client yang terkoneksi ke server pembeli akan mencetak “transaksi berhasil”

g. Server penjual akan mencetak stok saat ini setiap 5 detik sekali
h. Menggunakan thread, socket, shared memory

**Jawaban :**

**Cara Pengerjaan**

- Buatlah program C seperti ini

```
--Server Penjual--

#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <pthread.h>
#include <termios.h>

#define PORT 2323

int *value; 

void* cetak(){
    while(1){
        printf("Stok barang : %d\n", *value);
        sleep(5);
    }
}

void* server(){
    int server_fd, valread, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
      
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) > 0){
        while((valread = read( new_socket , buffer, 1024)) > 0){
            if(strcmp(buffer, "tambah") == 0){
                *value += 1;
            }
            memset(buffer, 0, sizeof(buffer));
        }
    }
}

int main(int argc, char const *argv[]) {
    pthread_t thread, ctk;
    key_t key = 1234;

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    value = shmat(shmid, NULL, 0);

    pthread_create(&thread, NULL, server, NULL);
    pthread_create(&ctk, NULL, cetak, NULL);
    pthread_join(thread, NULL);
    pthread_join(ctk, NULL);
    

    shmdt(value);
    shmctl(shmid , IPC_RMID,NULL);
    return 0;
}

--Server Pembeli--

#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <pthread.h>
#include <termios.h>

#define PORT 2323

int *value; 

void* server(){
    int server_fd, valread, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
      
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) > 0){
        while((valread = read( new_socket , buffer, 1024)) > 0){
            if(strcmp(buffer, "beli") == 0){
                if(*value > 0){
                    char *tes = "transaksi berhasil\n";
                    send(new_socket, tes, strlen(tes), 0);
                    *value -= 1;
                } else {
                    char *tes = "transaksi gagal\n";
                    send(new_socket, tes, strlen(tes), 0);
                }
                memset(buffer, 0, sizeof(buffer));
            }
        }
    }
}

int main(int argc, char const *argv[]) {
    pthread_t thread;
    key_t key = 1234;

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    value = shmat(shmid, NULL, 0);

    pthread_create(&thread, NULL, server, NULL);
    pthread_join(thread, NULL);

    shmdt(value);
    shmctl(shmid , IPC_RMID,NULL);
    return 0;
}

--Client Penjual--

#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 2323
  
void* client(){
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello;
    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
    }


    while(1){
        char arr[10];
        scanf("%s", arr);
        send(sock , arr, strlen(arr) , 0 );
    }
}

int main(int argc, char const *argv[]) {
    pthread_t thread;

    pthread_create(&thread, NULL, client, NULL);
    pthread_join(thread, NULL);

    return 0;
}

--Client Pembeli--

#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/shm.h>
#include <pthread.h>

#define PORT 2323

int *value;

void* client(){
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello;
    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
    }

    while(1){
        char arr[10];
        scanf("%s", arr);
        send(sock , arr, strlen(arr) , 0 );
        valread = read( sock , buffer, 1024);
        printf("%s\n",buffer );
        memset(buffer, 0, sizeof(buffer));
    }
}
  
int main(int argc, char const *argv[]) {
    pthread_t thread;

    pthread_create(&thread, NULL, client, NULL);
    pthread_join(thread, NULL);

    return 0;
}
```
- Lalu ketik di terminal 
```
gcc -pthread -o soal2 soal2.c
```

- Lalu jalankan ```./soal2

**Kendala Yang Dialami**

-

**Screenshot**

![Screenshot2](https://1.bp.blogspot.com/-YGGRJtU18Zw/XLAZXNZOgVI/AAAAAAAAAok/-NIPnha-cNAjvq3JO8VMZSiyZIB2jyI3ACLcBGAs/s1600/2.png)

3. Agmal dan Iraj merupakan 2 sahabat yang sedang kuliah dan hidup satu kostan, sayangnya mereka mempunyai gaya hidup yang berkebalikan, dimana Iraj merupakan laki-laki yang sangat sehat,rajin berolahraga dan bangun tidak pernah kesiangan sedangkan Agmal hampir menghabiskan setengah umur hidupnya hanya untuk tidur dan ‘ngoding’. Dikarenakan mereka sahabat yang baik, Agmal dan iraj sama-sama ingin membuat satu sama lain mengikuti gaya hidup mereka dengan cara membuat Iraj sering tidur seperti Agmal, atau membuat Agmal selalu bangun pagi seperti Iraj. Buatlah suatu program C untuk menggambarkan kehidupan mereka dengan spesifikasi sebagai berikut:

a. Terdapat 2 karakter Agmal dan Iraj

b. Kedua karakter memiliki status yang unik

Agmal mempunyai WakeUp_Status, di awal program memiliki status 0

Iraj memiliki Spirit_Status, di awal program memiliki status 100

Terdapat 3 Fitur utama

- All Status, yaitu menampilkan status kedua sahabat

Ex: Agmal WakeUp_Status = 75 
      Iraj Spirit_Status = 30

- “Agmal Ayo Bangun” menambah WakeUp_Status Agmal sebesar 15 point

- “Iraj Ayo Tidur” mengurangi Spirit_Status Iraj sebanyak 20 point

Terdapat Kasus yang unik dimana:

- Jika Fitur “Agmal Ayo Bangun” dijalankan sebanyak 3 kali, maka Fitur “Iraj Ayo Tidur” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Fitur Iraj Ayo Tidur disabled 10 s”)

- Jika Fitur  “Iraj Ayo Tidur” dijalankan sebanyak 3 kali, maka Fitur “Agmal Ayo Bangun” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Agmal Ayo Bangun disabled 10 s”)

Program akan berhenti jika Salah Satu :

- WakeUp_Status Agmal >= 100 (Tampilkan Pesan “Agmal Terbangun,mereka bangun pagi dan berolahraga”)

- Spirit_Status Iraj <= 0 (Tampilkan Pesan “Iraj ikut tidur, dan bangun kesiangan bersama Agmal”)


c. Syarat Menggunakan Lebih dari 1 Thread

        
**Jawaban :**

**Cara Pengerjaan**

- Buat program C seperti ini
```
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
```
- Lalu ketik di terminal 
```
gcc -pthread -o soal3 soal3.c
```

- Lalu jalankan ```./soal3```

- Program C tersebut hanya berisi satu fungsi yang di dalamnya terdapat tiga kondisi if. Yang pertama jika user mengetikkan satu maka akan print wake up status dan spirit status sekarang. Yang kedua jika user menambahkan wake up status, maka wake up status akan bertambah 15 poin dan jika sudah dijalankan tiga kali maka fitur iraj tidak bisa dijalankan 10 detik. Yang ketiga jika user mengurangi spirit status, maka spirit status akan berkurang 20 poin dan jika sudah dijalankan tiga kali maka fitur agmal tidak bisa dijalankan 10 detik 

**Kendala Yang Dialami**

-

**Screenshot**

![Screenshot3a](https://2.bp.blogspot.com/-ovaKKzwa08I/XLAZXLuWLXI/AAAAAAAAAog/EouiZc5qYNM4Y_DW6LAl0L_u20_9NKr7gCLcBGAs/s1600/3a.png)

![Screenshot3b](https://2.bp.blogspot.com/-SAOPDPbdgRM/XLAZX-t5qkI/AAAAAAAAAoo/_SIr_44kbaQlL4qdCyfDX8UcE3R9yBoeACLcBGAs/s1600/3b.png)

4.  Buatlah sebuah program C dimana dapat menyimpan list proses yang sedang berjalan (ps -aux) maksimal 10 list proses. Dimana awalnya list proses disimpan dalam di 2 file ekstensi .txt yaitu  SimpanProses1.txt di direktori /home/Document/FolderProses1 dan SimpanProses2.txt di direktori /home/Document/FolderProses2 , setelah itu masing2 file di  kompres zip dengan format nama file KompresProses1.zip dan KompresProses2.zip dan file SimpanProses1.txt dan SimpanProses2.txt akan otomatis terhapus, setelah itu program akan menunggu selama 15 detik lalu program akan mengekstrak kembali file KompresProses1.zip dan KompresProses2.zip 

Dengan Syarat : 

- Setiap list proses yang di simpan dalam masing-masing file .txt harus berjalan bersama-sama

- Ketika mengkompres masing-masing file .txt harus berjalan bersama-sama

- Ketika Mengekstrak file .zip juga harus secara bersama-sama

- Ketika Telah Selesai melakukan kompress file .zip masing-masing file, maka program akan memberi pesan “Menunggu 15 detik untuk mengekstrak kembali”

- Wajib Menggunakan Multithreading

- Boleh menggunakan system


**Jawaban :**

**Cara Pengerjaan**

- Buat program C seperti ini 
```
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

pthread_t tid[2], tid2[2], tid3[2], tid4[2];
int status;
void *thread1(void *arg)
{
        status = 0;
        char buffer3[100], buffer4[100];
        pthread_t id = pthread_self();
        if(pthread_equal(id,tid[0]))
        {
                snprintf(buffer3, sizeof(buffer3), "ps -aux | head -10 > /home/test/Documents/FolderProses1/SimpanProses1.txt");
                system(buffer3);
        }
        else if(pthread_equal(id,tid[1]))
        {
                snprintf(buffer4, sizeof(buffer4), "ps -aux | head -10 > /home/test/Documents/FolderProses2/SimpanProses2.txt");
                system(buffer4);

        }
        status = 1;
        return NULL;
}


void *thread2(void *arg)
{
        while(status!=1)
        {

        }
        char buffer[100], buffer2[100];
        pthread_t id2 = pthread_self();
        if(pthread_equal(id2,tid2[0]))
        {
                snprintf(buffer, sizeof(buffer), "zip KompresProses1.zip /home/test/Documents/FolderProses1/SimpanProses1.txt");
                system(buffer);
        }
        else if(pthread_equal(id2,tid2[1]))
        {
                snprintf(buffer2, sizeof(buffer2), "zip KompresProses2.zip /home/test/Documents/FolderProses2/SimpanProses2.txt");
                system(buffer2);
        }
        status=2;
        return NULL;
}

void *thread3(void *arg)
{
        while(status!=2)
        {

        }
        char buffer[100], buffer2[100];
        char buf[100], buf2[100];
        pthread_t id3 = pthread_self();
        if(pthread_equal(id3,tid3[0]))
        {
                snprintf(buf, sizeof(buf), "rm /home/test/Documents/FolderProses1/SimpanProses1.txt");
                system(buf);
        }
        else if(pthread_equal(id3,tid3[1]))
        {
                snprintf(buf2, sizeof(buf2), "rm /home/test/Documents/FolderProses2/SimpanProses2.txt");
                system(buf2);
        }
        status=3;
        return NULL;
}

void *thread4(void *arg)
{
        while(status!=3)
        {

        }
        sleep(15);
        char buff[100], buff2[100];
        pthread_t id4 = pthread_self();
        if(pthread_equal(id4,tid4[0]))
        {
                snprintf(buff, sizeof(buff), "unzip KompresProses1.zip");
                system(buff);
        }
        else if(pthread_equal(id4,tid4[1]))
        {
                snprintf(buff2, sizeof(buff2), "unzip KompresProses2.zip");
                system(buff2);
        }
        return NULL;
}
int main(void)
{
        int i=0, j=0, k=0, l=0;
        while(i<2) // loop sejumlah thread
        {
                pthread_create(&(tid[i]),NULL,&thread1,NULL); //membuat thread
                i++;
        }
        while(j<2) // loop sejumlah thread
        {
                pthread_create(&(tid2[j]),NULL,&thread2,NULL); //membuat thread
                j++;
        }
        while(k<2) // loop sejumlah thread
        {
                pthread_create(&(tid3[k]),NULL,&thread3,NULL); //membuat thread
                k++;
        }
        while(l<2) // loop sejumlah thread
        {
                pthread_create(&(tid4[l]),NULL,&thread4,NULL); //membuat thread
                l++;
        }


        pthread_join(tid[0],NULL);
        pthread_join(tid[1],NULL);
        pthread_join(tid2[0],NULL);
        pthread_join(tid2[1],NULL);
        pthread_join(tid3[0],NULL);
        pthread_join(tid3[1],NULL);

        printf("Menunggu 15 detik untuk mengekstrak kembali\n");
        pthread_join(tid4[0],NULL);
        pthread_join(tid4[1],NULL);

        exit(0);
        return 0;
}
```
- Lalu ketik di terminal 
```
gcc -pthread -o soal4 soal4.c
```

- Lalu jalankan ```./soal4```

- Program C ini memiliki 4 fungsi yang masing-masingnya berisi fungsi membuat file, fungsi zip file, fungsi rm file, dan fungsi unzip file dengan menggunakan system. Program C ini menggunakan mutual exclusion dimana fungsi 1 berjalan terlebih dahulu lalu fungsi 2, fungsi 3, dan fungsi 4. 

**Kendala Yang Dialami**

-

**Screenshot**

![Screenshot4a](https://4.bp.blogspot.com/-vER75Phtouo/XLAZX9iDeBI/AAAAAAAAAos/0sZuiVQlH1IcjcuuBWpVJHbxXVT6PPzowCLcBGAs/s1600/4a.png)

![Screenshot4b](https://2.bp.blogspot.com/-dYvZJwv5EII/XLAZYH7A3fI/AAAAAAAAAow/H1y2DLGvZlECdxUwoWPKBRc4jwi2IP86ACLcBGAs/s1600/4b.png)

![Screenshot4c](https://2.bp.blogspot.com/-dDMX1qJ41LA/XLAZYprS8kI/AAAAAAAAAo4/gw4w_PNN2KYwaRFKBlxJ0xPDuJR7tfdyQCLcBGAs/s1600/4c.png)

![Screenshot4d](https://4.bp.blogspot.com/-Ot-KMHsCWuo/XLAZYn1JWhI/AAAAAAAAAo0/q6xMgwgf1GofGI-RH587kwBo_dWP_9LcgCLcBGAs/s1600/4d.png)

![Screenshot4e](https://2.bp.blogspot.com/-pq3UQrbDRJY/XLAZY-fVPyI/AAAAAAAAAo8/viMo9EN2gNM4ReSq5Y4hVfFrJKxd3rlxACLcBGAs/s1600/4e.png)

![Screenshot4f](https://3.bp.blogspot.com/-JoCnsToOEIM/XLAZZMw6VWI/AAAAAAAAApA/MfTT9GeSLGMVr6l9Y5y1wnZr3qSyUlmBwCLcBGAs/s1600/4f.png)

![Screenshot4g](https://2.bp.blogspot.com/-l2u4UmKTdO0/XLAZZWWgqJI/AAAAAAAAApE/kwsL13-gnMAiwvsiR-qs8bLlL8sHgGC-wCLcBGAs/s1600/4g.png)

![Screenshot4h](https://2.bp.blogspot.com/-DFFsRnokdOM/XLAZZvxTJOI/AAAAAAAAApI/GX5dkvYkypMXZW4Q1v2eRrGUcZppuhmkACLcBGAs/s1600/4h.png)

5. Angga, adik Jiwang akan berulang tahun yang ke sembilan pada tanggal 6 April besok. Karena lupa menabung, Jiwang tidak mempunyai uang sepeserpun untuk membelikan Angga kado. Kamu sebagai sahabat Jiwang ingin membantu Jiwang membahagiakan adiknya sehingga kamu menawarkan bantuan membuatkan permainan komputer sederhana menggunakan program C. Jiwang sangat menyukai idemu tersebut. Berikut permainan yang Jiwang minta. 

a. Pemain memelihara seekor monster lucu dalam permainan. Pemain dapat  memberi nama pada monsternya.

b. Monster pemain memiliki hunger status yang berawal dengan nilai 200 (maksimalnya) dan nanti akan berkurang 5 tiap 10 detik.Ketika hunger status mencapai angka nol, pemain akan kalah. Hunger status dapat bertambah 15 apabila pemain memberi makan kepada monster, tetapi banyak makanan terbatas dan harus beli di Market.

c. Monster pemain memiliki hygiene status yang berawal dari 100 dan nanti berkurang 10 tiap 30 detik. Ketika hygiene status mencapai angka nol, pemain akan kalah. Hygiene status' dapat bertambah 30 hanya dengan memandikan monster. Pemain dapat memandikannya setiap 20 detik(cooldownnya 20 detik).

d. Monster pemain memiliki health status yang berawal dengan nilai 300. Variabel ini bertambah (regenerasi)daa 5 setiap 10 detik ketika monster dalam keadaan standby.

e. Monster pemain dapat memasuki keadaan battle. Dalam keadaan ini, food status(fitur b), hygiene status'(fitur c), dan ‘regenerasi’(fitur d) tidak akan berjalan. Health status dari monster dimulai dari darah saat monster pemain memasuki battle. Monster pemain akan bertarung dengan monster NPC yang memiliki darah 100. Baik monster pemain maupun NPC memiliki serangan sebesar 20. Monster pemain dengan monster musuh akan menyerang secara bergantian. 

f. Fitur shop, pemain dapat membeli makanan sepuas-puasnya selama stok di toko masih tersedia.

- Pembeli (terintegrasi dengan game)

Dapat mengecek stok makanan yang ada di toko.

Jika stok ada, pembeli dapat membeli makanan.

- Penjual (terpisah)

Bisa mengecek stok makanan yang ada di toko

Penjual dapat menambah stok makanan.

Spesifikasi program:

A. Program mampu mendeteksi input berupa key press. (Program bisa berjalan tanpa perlu menekan tombol enter)

B. Program terdiri dari 3 scene yaitu standby, battle, dan shop.
C. Pada saat berada di standby scene, program selalu menampilkan health status, hunger status, hygiene status, stok makanan tersisa, dan juga status kamar mandi (“Bath is ready” jika bisa digunakan, “Bath will be ready in [bath cooldown]s” jika sedang cooldown). Selain itu program selalu menampilkan 5 menu, yaitu memberi makan, mandi, battle, shop, dan exit. Contoh :

Standby Mode

Health : [health status]

Hunger : [hunger status]

Hygiene : [hygiene status]

Food left : [your food stock]

Bath will be ready in [cooldown]s

Choices

1. Eat

2. Bath

3. Battle

4. Shop

5. Exit

D. Pada saat berada di battle scene, program selalu menampilkan health status milik pemain dan monster NPC. Selain itu, program selalu menampilkan 2 menu yaitu serang atau lari. Contoh :

Battle Mode

Monster’s Health : [health status]

Enemy’s Health : [enemy health status]

Choices

1. Attack

2. Run

E. Pada saat berada di shop scene versi pembeli, program selalu menampilkan food stock toko dan milik pemain. Selain itu, program selalu menampilkan 2 menu yaitu beli dan kembali ke standby scene. Contoh :

Shop Mode

Shop food stock : [shop food stock]

Your food stock : [your food stock]

Choices

1. Buy

2. Back

F. Pada program penjual, program selalu menampilkan food stock toko. Selain itu, program juga menampilkan 2 menu yaitu restock dan exit. Contoh :

Shop

Food stock : [shop food stock]

Choices

1. Restock

2. Exit

G. Pastikan terminal hanya mendisplay status detik ini sesuai scene terkait (hint: menggunakan system(“clear”))

**Jawaban :**

**Cara Pengerjaan**

- Buat program C seperti ini

a.
```
#include <sys/shm.h>
#include <termios.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

char name[30];
int *value, health, hunger, hygiene, mode, enemy, food, cd;

void* background(){
    while(1){
        if(mode == 0){
            sleep(10);
            health+=5;
            hunger-=5;
            sleep(10);
            health+=5;
            hunger-=5;
            sleep(10);
            health+=5;
            hunger-=5;
            hygiene-=10;

        }
    }
}

char getch() {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);
}

void keluar() {
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
}

void* menu(){
    while(hunger > 0 && hygiene > 0  && health > 0){
        if(mode == 0){
            printf("Standby Mode\n\nHealth : %d\nHunger : %d\nHygiene : %d\nFood left : %d\n", health, hunger, hygiene, food);
            if(cd <= 0){
                puts("Bath is ready");
            }else{
                printf("Bath will be ready in %ds\n", cd);
            }
            printf("\nChoices\n1. Eat\n2. Bath\n3. Battle\n4. Shop\n5. Exit\n");
        }
        if(mode == 1){
            printf("Battle Mode\n\n%s’s Health : %d\nEnemy’s Health : %d\n\nChoices\n1. Attack\n2. Run\n", name, health, enemy);
        }
        if(mode == 2){
            printf("Shop Mode\n\nShop food stock : %d\nYour food stock : %d\n\nChoices\n1. Buy\n2. Back\n", *value, food);
        }
        cd--;
        sleep(1);
        system("clear");
    }

    printf("%s died :(\n", name);
    sleep(3);
    system("clear");
    keluar();
    exit(0);
}

int main(){
    health = 300;
    hunger = 200;
    hygiene = 100;
    // health=5;
    // hunger=5;
    // hygiene=5;
    mode = 0;
    enemy = 100;
    food = 0;
    cd = 0;
    pthread_t thread;
    char ch;
    key_t key = 1234;

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    value = shmat(shmid, NULL, 0);

    printf("Insert your monster name : ");
    scanf("%s", name);
    
    pthread_create(&thread, NULL, menu, NULL);
    pthread_create(&thread, NULL, background, NULL);

    while(1){
        if(hunger>200) hunger = 200;
        ch = getch();

        switch(mode)
        {
            case 0:
                switch(ch)
                {
                    case '1':
                        if(food > 0){
                            hunger += 15;
                            food--;
                        }else{
                            printf("Please buy food in the shop.\n");
                        }
                        break;

                    case '2':
                        if(cd <= 0){
                            cd = 20;
                            hygiene += 30;
                        }else{
                            printf("Bath will be ready in %ds\n", cd);
                        }
                        break;

                    case '3':
                        mode = 1;
                        break;

                    case '4':
                        mode = 2;
                        break;

                    case '5':
                        system("clear");
                        exit(0);
                        break;
                }
                break;

            case 1:
                switch(ch)
                {
                    case '1':
                        health -= 20;
                        enemy -= 20;
                        if(enemy <= 0){
                            printf("%s win!\n", name);
                            sleep(0.7);
                            mode = 0;
                            enemy = 100;
                        }
                        break;

                    case '2':
                        mode = 0;
                        break;
                }
                break;

            case 2:
                switch(ch)
                {
                    case '1':
                        if(*value > 0){
                            *value -= 1;
                            food++;
                        }else{
                            puts("Food is out of stock.");
                        }
                        break;

                    case '2':
                        mode = 0;
                        break;
                }
                break;
        }
        
    }
}


[SHOP]


#include <sys/shm.h>
#include <termios.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int *value;

void* menu(){
    while(1){
        printf("Shop\n\nFood stock : %d\n\nChoices\n1. Restock\n2. Back\n", *value);
        sleep(1);
        system("clear");
    }
}

char getch() {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
            perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
            perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
            perror ("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
            perror ("tcsetattr ~ICANON");
    return (buf);
}


int main(){
    pthread_t thread;
    char ch;
    key_t key = 1234;

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    value = shmat(shmid, NULL, 0);

    pthread_create(&thread, NULL, menu, NULL);

    while(1){
        ch = getch();
        switch(ch)
        {
            case '1':
                *value += 1;
                break;

            case '2':
                // shmdt(value);
                // shmctl(shmid, IPC_RMID, NULL);
                system("clear");
                exit(0);
                break;
        }
    }

    return 0;
}
```

- Lalu ketik di terminal 
```
gcc -pthread -o soal5 soal5.c
```

- Lalu jalankan ```./soal5```

**Kendala Yang Dialami**-

-

**Screenshot**

![Screenshot5a](https://1.bp.blogspot.com/-1RTC3S_lJqA/XLAZZ6myADI/AAAAAAAAApM/vpcZkTQez6Uh0LkV_3h8LiXJlf9q6L7vwCLcBGAs/s1600/5a.png)

![Screenshot5b](https://2.bp.blogspot.com/-E5_L7pUm_mU/XLAZaB8ts8I/AAAAAAAAApQ/bqzTrtDWvyoWc0N0mulMHq-NFVlMXmtnwCLcBGAs/s1600/5b.png)

![Screenshot5c](https://4.bp.blogspot.com/-0f7660e_G0w/XLAZaTJ9tLI/AAAAAAAAApU/p55RB2hPW98NFQO3oNdJv2-L3wcxusEaACLcBGAs/s1600/5c.png)

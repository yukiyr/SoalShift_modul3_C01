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
```
- Lalu ketik di terminal 
```
gcc -pthread -o soal1 soal1.c
```

- Lalu jalankan ```./soal1```

**Kendala Yang Dialami**

-

**Screenshot**

![Screenshot1](https://1.bp.blogspot.com/-2U2bjeJE4JE/XJSMIlwVdTI/AAAAAAAAAm8/mw_oPQwcrLo-zdrx48b5QKuvSmDLhKj9QCLcBGAs/s1600/1a.png)

![Screenshot1](https://2.bp.blogspot.com/-imFq7tEzbvo/XJSMIo83u3I/AAAAAAAAAm0/JsUS80tLrq8SCeXfxTE6zN6FvmViSRDwgCLcBGAs/s1600/1b.png)

2. Pada suatu hari ada orang yang ingin berjualan 1 jenis barang secara private, dia memintamu membuat program C dengan spesifikasi sebagai berikut:
- Terdapat 2 server: server penjual dan server pembeli
- 1 server hanya bisa terkoneksi dengan 1 client
- Server penjual dan server pembeli memiliki stok barang yang selalu sama
- Client yang terkoneksi ke server penjual hanya bisa menambah stok
- Cara menambah stok: client yang terkoneksi ke server penjual mengirim string “tambah” ke server lalu stok bertambah 1
- Client yang terkoneksi ke server pembeli hanya bisa mengurangi stok
- Cara mengurangi stok: client yang terkoneksi ke server pembeli mengirim string “beli” ke server lalu stok berkurang 1
- Server pembeli akan mengirimkan info ke client yang terhubung dengannya apakah transaksi berhasil atau tidak berdasarkan ketersediaan stok
- Jika stok habis maka client yang terkoneksi ke server pembeli akan mencetak “transaksi gagal”
- Jika stok masih ada maka client yang terkoneksi ke server pembeli akan mencetak “transaksi berhasil”
- Server penjual akan mencetak stok saat ini setiap 5 detik sekali
- Menggunakan thread, socket, shared memory

**Jawaban :**

**Cara Pengerjaan**

- Buatlah program C seperti ini

```
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>

int main() {
  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
    int pid, pid1, pid2, pid3; 
  
    pid = fork(); 
  
    if (pid == 0) { 
  
        char *argv [4] = {"chmod", "0777", "hatiku/elen.ku", NULL};
        execv ("/bin/chmod", argv);

    } 
  
    else { 
        pid1 = fork(); 
        if (pid1 == 0) { 
            char *argv[3] = {"touch", "hatiku/elen.ku", NULL};
            execv("/usr/bin/touch", argv);

        } 
        else { 
            pid2 = fork(); 
            if (pid2 == 0) { 
                char *argv[4] = {"mkdir", "-p", "hatiku", NULL};
                execv("/bin/mkdir", argv);

            } 
  
            else { 
                                char  alamat[] = "/home/test/hatiku/elen.ku";
                                struct stat file;
                                if (stat(alamat,&file) == 0) {
                                struct group *grp;
                                struct passwd *pwd;

                                grp = getgrgid(file.st_uid);
                                pwd = getpwuid(file.st_gid);

                                if (strcmp(grp->gr_name, "www-data") != 0 && strcmp(pwd->pw_name, "www-data") != 0) {
                                        char *argv[3] = {"rm", "/home/test/hatiku/elen.ku", NULL};
                                        execv("/bin/rm", argv);
                                }
                                }
            } 
        } 
    } 
    sleep(3);
  }
  
  exit(EXIT_SUCCESS);
}
```
- Lalu masuk ke directory hatiku ketik di terminal ``` sudo chown www-data:www-data elen.ku``` untuk mengubah owner dan grup fie elen.ku 

- Lalu kembali ke directory home, ketik di terminal 
```
gcc -o modul2_2 modul2_2.c
```

- Lalu jalankan ```./modul2_2```

- Maka file elen.ku akan terhapus

**Kendala Yang Dialami**

-

**Screenshot**

![Screenshot1](https://3.bp.blogspot.com/-bl05tszTmew/XJSMIg_B8iI/AAAAAAAAAm4/39gV4FBsUcIeJFB_ivgLtlePhrZ93-U_gCLcBGAs/s1600/2a.png)

![Screenshot1](https://4.bp.blogspot.com/-Ee83V6cmGDo/XJSMJffviyI/AAAAAAAAAnA/EGTJyTTlkPk2BT9CQyJUWPcq0JoxbL5xgCLcBGAs/s1600/2b.png)

![Screenshot1](https://4.bp.blogspot.com/-mYMorW66l8U/XJSMJpz-ZMI/AAAAAAAAAnE/7Ir-8gjX3EEszBMzPlplJuUsOXtOiFgQwCLcBGAs/s1600/2c.png)

3. Agmal dan Iraj merupakan 2 sahabat yang sedang kuliah dan hidup satu kostan, sayangnya mereka mempunyai gaya hidup yang berkebalikan, dimana Iraj merupakan laki-laki yang sangat sehat,rajin berolahraga dan bangun tidak pernah kesiangan sedangkan Agmal hampir menghabiskan setengah umur hidupnya hanya untuk tidur dan ‘ngoding’. Dikarenakan mereka sahabat yang baik, Agmal dan iraj sama-sama ingin membuat satu sama lain mengikuti gaya hidup mereka dengan cara membuat Iraj sering tidur seperti Agmal, atau membuat Agmal selalu bangun pagi seperti Iraj. Buatlah suatu program C untuk menggambarkan kehidupan mereka dengan spesifikasi sebagai berikut:
- Terdapat 2 karakter Agmal dan Iraj
- Kedua karakter memiliki status yang unik
- Agmal mempunyai WakeUp_Status, di awal program memiliki status 0
- Iraj memiliki Spirit_Status, di awal program memiliki status 100
- Terdapat 3 Fitur utama
- All Status, yaitu menampilkan status kedua sahabat
Ex: Agmal WakeUp_Status = 75 
      Iraj Spirit_Status = 30
- “Agmal Ayo Bangun” menambah WakeUp_Status Agmal sebesar 15 point
- “Iraj Ayo Tidur” mengurangi Spirit_Status Iraj sebanyak 20 point
- Terdapat Kasus yang unik dimana:
- Jika Fitur “Agmal Ayo Bangun” dijalankan sebanyak 3 kali, maka Fitur “Iraj Ayo Tidur” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Fitur Iraj Ayo Tidur disabled 10 s”)
- Jika Fitur  “Iraj Ayo Tidur” dijalankan sebanyak 3 kali, maka Fitur “Agmal Ayo Bangun” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Agmal Ayo Bangun disabled 10 s”)
- Program akan berhenti jika Salah Satu :
- WakeUp_Status Agmal >= 100 (Tampilkan Pesan “Agmal Terbangun,mereka bangun pagi dan berolahraga”)
- Spirit_Status Iraj <= 0 (Tampilkan Pesan “Iraj ikut tidur, dan bangun kesiangan bersama Agmal”)


- Syarat Menggunakan Lebih dari 1 Thread

        
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
int status=0;
int status2=0;
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
                if(status2==3)
                {
                        printf("Agmal Ayo Bangun disabled 10 s\n");
                        sleep(10);
                        status2=0;
                }
                else if(status2!=3)
                {
                        WakeUp_Status+=15;
                        status++;
                }
        }
        else if (input==3)
        {
                if(status==3)
                {
                        printf("Fitur Iraj Ayo Tidur disabled 10 s\n");
                        sleep(10);
                        status=0;
                }
                else if(status!=3)
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


**Kendala Yang Dialami**

-

**Screenshot**

![Screenshot1](https://4.bp.blogspot.com/-aRLcxJ2RkJI/XJSMJnxY4rI/AAAAAAAAAnI/Vf7xaluLdzgiXfE_XeRqO9eF30_zs3c2QCLcBGAs/s1600/3a.png)

![Screenshot1](https://4.bp.blogspot.com/-Hz5w0GYi3SA/XJSMJ2jYiaI/AAAAAAAAAnM/yYVMwbt2XLc0pon09-7095mMLCdbciXHgCLcBGAs/s1600/3b.png)

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
        status=2;
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

**Kendala Yang Dialami**

Program tidak berjalan

**Screenshot**

![Screenshot1](https://4.bp.blogspot.com/-FXWsFJyuYLo/XJSMKC1y8gI/AAAAAAAAAnQ/BNKptEcZg9AnXGVo4oJAu8ZetpDGHks-wCLcBGAs/s1600/4a.png)

![Screenshot1](https://3.bp.blogspot.com/-suriXQWAp_A/XJSMK4bn3MI/AAAAAAAAAnU/jlA6ApXM290dtAx_zwIrYsrASysIROQIgCLcBGAs/s1600/4b.png)

5. Angga, adik Jiwang akan berulang tahun yang ke sembilan pada tanggal 6 April besok. Karena lupa menabung, Jiwang tidak mempunyai uang sepeserpun untuk membelikan Angga kado. Kamu sebagai sahabat Jiwang ingin membantu Jiwang membahagiakan adiknya sehingga kamu menawarkan bantuan membuatkan permainan komputer sederhana menggunakan program C. Jiwang sangat menyukai idemu tersebut. Berikut permainan yang Jiwang minta. 
- Pemain memelihara seekor monster lucu dalam permainan. Pemain dapat  memberi nama pada monsternya.
- Monster pemain memiliki hunger status yang berawal dengan nilai 200 (maksimalnya) dan nanti akan berkurang 5 tiap 10 detik.Ketika hunger status mencapai angka nol, pemain akan kalah. Hunger status dapat bertambah 15 apabila pemain memberi makan kepada monster, tetapi banyak makanan terbatas dan harus beli di Market.
- Monster pemain memiliki hygiene status yang berawal dari 100 dan nanti berkurang 10 tiap 30 detik. Ketika hygiene status mencapai angka nol, pemain akan kalah. Hygiene status' dapat bertambah 30 hanya dengan memandikan monster. Pemain dapat memandikannya setiap 20 detik(cooldownnya 20 detik).
- Monster pemain memiliki health status yang berawal dengan nilai 300. Variabel ini bertambah (regenerasi)daa 5 setiap 10 detik ketika monster dalam keadaan standby.
- Monster pemain dapat memasuki keadaan battle. Dalam keadaan ini, food status(fitur b), hygiene status'(fitur c), dan ‘regenerasi’(fitur d) tidak akan berjalan. Health status dari monster dimulai dari darah saat monster pemain memasuki battle. Monster pemain akan bertarung dengan monster NPC yang memiliki darah 100. Baik monster pemain maupun NPC memiliki serangan sebesar 20. Monster pemain dengan monster musuh akan menyerang secara bergantian. 
- Fitur shop, pemain dapat membeli makanan sepuas-puasnya selama stok di toko masih tersedia.
Pembeli (terintegrasi dengan game)
- Dapat mengecek stok makanan yang ada di toko.
- Jika stok ada, pembeli dapat membeli makanan.
Penjual (terpisah)
- Bisa mengecek stok makanan yang ada di toko
- Penjual dapat menambah stok makanan.
	Spesifikasi program:
- Program mampu mendeteksi input berupa key press. (Program bisa berjalan tanpa perlu menekan tombol enter)
- Program terdiri dari 3 scene yaitu standby, battle, dan shop.
- Pada saat berada di standby scene, program selalu menampilkan health status, hunger status, hygiene status, stok makanan tersisa, dan juga status kamar mandi (“Bath is ready” jika bisa digunakan, “Bath will be ready in [bath cooldown]s” jika sedang cooldown). Selain itu program selalu menampilkan 5 menu, yaitu memberi makan, mandi, battle, shop, dan exit. Contoh :

Standby Mode
- Health : [health status]
- Hunger : [hunger status]
- Hygiene : [hygiene status]
- Food left : [your food stock]
- Bath will be ready in [cooldown]s
- Choices
- Eat
- Bath
- Battle
- Shop
- Exit

Pada saat berada di battle scene, program selalu menampilkan health status milik pemain dan monster NPC. Selain itu, program selalu menampilkan 2 menu yaitu serang atau lari. Contoh :

Battle Mode
- Monster’s Health : [health status]
- Enemy’s Health : [enemy health status]
- Choices
- Attack
- Run

Pada saat berada di shop scene versi pembeli, program selalu menampilkan food stock toko dan milik pemain. Selain itu, program selalu menampilkan 2 menu yaitu beli dan kembali ke standby scene. Contoh :

Shop Mode
		Shop food stock : [shop food stock]
		Your food stock : [your food stock]
		Choices
- Buy
- Back

Pada program penjual, program selalu menampilkan food stock toko. Selain itu, program juga menampilkan 2 menu yaitu restock dan exit. Contoh :

Shop
Food stock : [shop food stock]
- Choices
- Restock
- Exit

Pastikan terminal hanya mendisplay status detik ini sesuai scene terkait (hint: menggunakan system(“clear”))

**Jawaban :**

**Cara Pengerjaan**

- Buat program C seperti ini

a.
```
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

int main() {
    pid_t pid, sid;
    pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }
    umask(0);
    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }
    if ((chdir("/")) < 0) {
        exit(EXIT_FAILURE);
    }
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    int angka = 1;
    while(1) {
        time_t raw;
        struct tm *timeinfo;
        char tanggal[40], path[80];
        time(&raw);
        timeinfo = localtime(&raw);
        strftime(tanggal, sizeof(tanggal), "%d:%m:%Y-%H:%M", timeinfo); 
        sprintf(path, "/home/elang/log/%s/", tanggal);
        mkdir(path, S_IRWXU | S_IRWXO | S_IRWXG);
        
        for(int i = 0; i < 30 ; i++){
            char file[50], path2[80];
            strcpy(path2,path);
            sprintf(file, "log%d.log", angka);
            strcat(path2, file);

            FILE *fwrite, *fread;
            fread = fopen("/var/log/syslog", "r");
            fwrite = fopen(path2,"w+");

            char ch;

            if(fread != NULL && fwrite != NULL){
            while ((ch = fgetc(fread)) != EOF)
                fputc(ch, fwrite);

            fclose(fwrite);
            }
            angka++;
            sleep(60);
        }

    }
    exit(EXIT_SUCCESS);
}
```

b.
```
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    char *argv[3] = {"pkill", "soal5a", NULL};
    execv("/usr/bin/pkill", argv);
}
```

- Lalu ketik di terminal 
```
gcc -o modul2_5 modul2_5.c
```

- Lalu jalankan ```./modul2_5```

- Maka  file log akan tercatat di file dan direktori yang dikehendaki

**Kendala Yang Dialami**-

-

**Screenshot**

![Screenshot1](https://3.bp.blogspot.com/-Yk8AICgLMBk/XJSMLOjiXUI/AAAAAAAAAnc/JQYB1pfXro8TTjXOSxid6cEb83tfCgWYwCLcBGAs/s1600/5a.png)

![Screenshot1](https://2.bp.blogspot.com/-4SfjtLrdmiw/XJSMLBgLFOI/AAAAAAAAAnY/kasVbH3r9JcL65FpapdwkpkIJCC52eArwCLcBGAs/s1600/5b.png)

![Screenshot1](https://1.bp.blogspot.com/-QftZvNqT7WQ/XJSMLqrP9II/AAAAAAAAAng/iOLFtKoUD5kGUjL0Op5xsmuCgUwpxCs5gCLcBGAs/s1600/5c.png)

![Screenshot1](https://1.bp.blogspot.com/-4AanTWBjx6k/XJSML9Ji4QI/AAAAAAAAAnk/akyV7HI-tlIjbeLgFR1Yp6wRxLXHUzJJQCLcBGAs/s1600/5d.png)

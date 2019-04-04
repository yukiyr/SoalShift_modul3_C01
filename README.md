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
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <syslog.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>

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

  if ((chdir("/home/test")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
        pid_t child_id, child_id_2;
        int status;

        child_id = fork();

        if (child_id == 0) {
        // this is child

        char *argv[4] = {"mkdir", "-p", "modul2/gambar", NULL};
        execv("/bin/mkdir", argv);
        } else {
        // this is second child
        child_id_2 = fork();
        if (child_id_2 == 0) {

        char *argv[4] = {"mkdir", "-p", "modul2", NULL};
        execv("/bin/mkdir", argv);

        } else {
        while ((wait(&status)) > 0);
        char filename[10000];
        char filename2[10000];
        char filename3[10000];
        char awal1[10000];
        char akhir1[10000];
        char *pointer;
        char *pointer1;
        char *pointer2;
        char *pointer3;

        DIR *direktori;
        struct dirent *dir;
        direktori = opendir("/home/test/");
        if (direktori)
        {
                while ((dir = readdir(direktori)) != NULL)
                {
                        strcpy(filename,dir->d_name);
                        pointer3 = strrchr(filename, '.');
                        strcpy(filename3,filename);
                        if (pointer3 && (strcmp(pointer3, ".png") == 0))
                        {
                                *pointer3 = '\0';
                                strcpy(filename2,filename);
                                pointer = filename2;
                                char tambahan[10]="_grey.png";
                                strcat (pointer,tambahan);
                                char awal[]="/home/test/";
                                char akhir[]="/home/test/modul2/gambar/";
                                strcpy(awal1,awal);
                                strcpy(akhir1,akhir);
                                pointer1 = awal1;
                                pointer2 = akhir1;
                                strcat (pointer1,filename3);
                                strcat (pointer2,pointer);
                                rename (pointer1,pointer2);
                        }
                }
                closedir(direktori);
        }
      }
    }
  }
  exit(EXIT_SUCCESS);
}
```
- Lalu ketik di terminal 
```
gcc -o modul2_1_benar modul2_1_benar.c
```

- Lalu jalankan ```./modul2_1_benar```

- Maka semua file .png yang ada di /home/test akan di-rename menjadi nama yang dikehendaki

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
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
  int p[2];
  int q[2];

  pid_t child_id;
  pid_t child_id_2;
  pid_t child_id_3;
  pid_t child_id_4;
  int status;
  int r;
  char tampungan[10000]={0};

  child_id = fork();

  if (child_id == 0) {
    // this is first child
        char *argv[3] = {"touch", "daftar.txt", NULL};
        execv("/usr/bin/touch", argv);

  } else {
    // this is second child
    child_id_2 = fork();
    if (child_id_2 == 0) {
        char *argv[3] = {"unzip", "campur2.zip", NULL};
        execv("/usr/bin/unzip", argv);

    } else {
      while ((wait(&status)) > 0);

        char *ls[] = {"ls", "campur2", NULL};
        char *grep[] = {"grep", ".*.txt$", NULL};

        pipe(p);
        pipe(q);
        child_id_3=fork();
        if (child_id_3 == 0) {
                //this is third child
                dup2(p[1],1);
                close(p[0]);
                close(p[1]);
                execvp("ls", ls);
        } else {
                child_id_4 = fork();
                if (child_id_4 == 0) {
                        //this is fourth child
                        dup2(p[0],0);
                        dup2(q[1],1);
                        close(p[1]);
                        close(p[0]);
                        close(q[1]);
                        close(q[0]);
                        execvp("grep", grep);
                } else {
                        close(p[0]);
                        close(p[1]);
                        close(q[1]);
                        r = read(q[0],tampungan,sizeof(tampungan));
                        FILE *out_file = fopen("daftar.txt","w+");
                        fprintf(out_file,"%.*s\n", r, tampungan);
                }
        }
    }
  }
}
```
- Lalu ketik di terminal 
```
gcc -o modul2_3 modul2_3.c
```

- Lalu jalankan ```./modul2_3```

- Maka file campur2.zip akan ter-unzip dan daftar file yang memiliki ekstensi .txt akan masuk ke file daftar.txt

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
    struct stat baca;

    time_t raw;
    time(&raw);

    char file[100], sehat[100];
    strcpy(file, "/home/elang/Documents/makanan/makan_enak.txt");

    stat(file, &baca);

    int last = (int)difftime(raw, baca.st_atime);

    if (last <= 30)
    {
      sprintf(sehat, "/home/elang/Documents/makanan/makan_sehat%d.txt", angka);
      FILE *fsehat;
      fsehat = fopen(sehat, "w");
      fclose(fsehat);
      angka++;
    }
    sleep(5);
  }

  exit(EXIT_SUCCESS);
}
```
- Lalu ketik di terminal 
```
gcc -o modul2_4 modul2_4.c
```

- Lalu jalankan ```./modul2_4```

- Maka program akan berjalan seperti semestinya 

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

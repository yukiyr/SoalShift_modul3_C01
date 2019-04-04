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

1. Elen mempunyai pekerjaan pada studio sebagai fotografer. Suatu hari ada seorang klien yang bernama Kusuma yang meminta untuk mengubah nama file yang memiliki ekstensi .png menjadi “[namafile]_grey.png”. Karena jumlah file yang diberikan Kusuma tidak manusiawi, maka Elen meminta bantuan kalian untuk membuat suatu program C yang dapat mengubah nama secara otomatis dan diletakkan pada direktori /home/[user]/modul2/gambar.
Catatan : Tidak boleh menggunakan crontab.

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

2. Pada suatu hari Kusuma dicampakkan oleh Elen karena Elen dimenangkan oleh orang lain. Semua kenangan tentang Elen berada pada file bernama “elen.ku” pada direktori “hatiku”. Karena sedih berkepanjangan, tugas kalian sebagai teman Kusuma adalah membantunya untuk menghapus semua kenangan tentang Elen dengan membuat program C yang bisa mendeteksi owner dan group dan menghapus file “elen.ku” setiap 3 detik dengan syarat ketika owner dan grupnya menjadi “www-data”. Ternyata kamu memiliki kendala karena permission pada file “elen.ku”. Jadi, ubahlah permissionnya menjadi 777. Setelah kenangan tentang Elen terhapus, maka Kusuma bisa move on.
Catatan: Tidak boleh menggunakan crontab

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

3. Diberikan file campur2.zip. Di dalam file tersebut terdapat folder “campur2”. 

Buatlah program C yang dapat :

i)  mengekstrak file zip tersebut.

ii) menyimpan daftar file dari folder “campur2” yang memiliki ekstensi .txt ke dalam file daftar.txt. 

Catatan:  

◦ Gunakan fork dan exec

◦ Gunakan minimal 3 proses yang diakhiri dengan exec.

◦ Gunakan pipe

◦ Pastikan file daftar.txt dapat diakses dari text editor
        
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

4.  Dalam direktori /home/[user]/Documents/makanan terdapat file makan_enak.txt yang berisikan daftar makanan terkenal di Surabaya. Elen sedang melakukan diet dan seringkali tergiur untuk membaca isi makan_enak.txt karena ngidam makanan enak. Sebagai teman yang baik, Anda membantu Elen dengan membuat program C yang berjalan setiap 5 detik untuk memeriksa apakah file makan_enak.txt pernah dibuka setidaknya 30 detik yang lalu (rentang 0 - 30 detik).
Jika file itu pernah dibuka, program Anda akan membuat 1 file makan_sehat#.txt di direktori /home/[user]/Documents/makanan dengan '#' berisi bilangan bulat dari 1 sampai tak hingga untuk mengingatkan Elen agar berdiet.

Contoh:
File makan_enak.txt terakhir dibuka pada detik ke-1
Pada detik ke-10 terdapat file makan_sehat1.txt dan makan_sehat2.txt

Catatan: 
    • dilarang menggunakan crontab
    • Contoh nama file : makan_sehat1.txt, makan_sehat2.txt, dst

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

5. Kerjakan poin a dan b di bawah:
    a. Buatlah program c untuk mencatat log setiap menit dari file log pada syslog ke /home/[user]/log/[dd:MM:yyyy-hh:mm]/log#.log
Ket:
    • Per 30 menit membuat folder /[dd:MM:yyyy-hh:mm]
    • Per menit memasukkan log#.log ke dalam folder tersebut
      ‘#’ : increment per menit. Mulai dari 1
    b. Buatlah program c untuk menghentikan program di atas.
NB: Dilarang menggunakan crontab dan tidak memakai argumen ketika menjalankan program.

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

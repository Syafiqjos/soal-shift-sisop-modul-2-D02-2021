# soal-shift-sisop-modul-2-D02-2021
- Jessica Tasyanita (05111940000043)
- Ahmad Syafiq Aqil Wafi (05111940000089)
- Maximilian H M Lingga (05111940000092)

## Soal1
### Tujuan
Dalam soal ini, kita diminta untuk membuat sebuah folder zip berisikan beragam file, mulai dari foto,film hingga musik. File-file tersebut sebelumnya perlu didownload dari beberapa link yang ada, dan dimasukkan ke sebuah folder baru secara otomatis di waktu yang telah ditentukan.

### 1A. Membuat beberapa folder dengan nama yang telah ditentukan.
#### Source Code
![image](https://user-images.githubusercontent.com/81459084/115846188-d64ff980-a44b-11eb-89a8-c50f5f05242c.png)

![image](https://user-images.githubusercontent.com/81459084/115846228-e10a8e80-a44b-11eb-9ba6-0e1b130a5c2b.png)

#### Cara pengerjaan 
1.	Pertama, buat sebuah fungsi baru untuk membuat direktori/folder. Fungsi ini menggunakan pointer `char *path`. Di dalam fungsi ini, kita perlu membuat `fork` program yang akan disimpan di variable `child_id`. Setelah itu, kita membuat perulangan dan check kondisi yang akan menjalankan eksekusi program pembuatan direktori di lokasi /bin/mkdir menggunakan `execl`. Kita juga menggunakan fungsi `waitpid` agar program utama tidak bertabrakan dengan program child yang di fork.
2.	Setelah itu, di dalam `main()`, kita akan menjalankan fungsi `make_directory` yang telah dibuat tadi, dengan menggunakan nama-nama folder yang telah ditentukan.

#### Kendala
1. Untuk menunggu proses child hingga selesai, menggunakan fungsi `waitpid` pada library `wait.h`.
2. Untuk membuat directory tanpa `mkdir` dari library default c, dapat menggunakan program `mkdir` langsung melalui path program dengan exec, dan kami memutuskan `execl` karena cocok digunakan.

### 1B. Mendownload file-file dari beberapa link yang telah diberikan.
#### Source Code 
![image](https://user-images.githubusercontent.com/81459084/115846352-04353e00-a44c-11eb-912c-70c86a7e6a7c.png)

![image](https://user-images.githubusercontent.com/81459084/115846372-07302e80-a44c-11eb-96f5-52db17fe55f4.png)

#### Cara Pengerjaan
1.	Sama seperti soal pertama, kita terlebih dahulu membuat sebuah fungsi baru untuk mendownload file (diberi nama `download_drive`). Fungsi ini menggunakan 2 pointer, yakni `char *url` dan `char *path`. Di dalam fungsi ini, kita pertama membuat fork yang akan disimpan di `child_id`. Lalu, buat perulangan kondisi. Di dalam perulangan itu, kita perlu menggunakan lagi 1 pointer, yakni char `*url_new`, yang didalamnya akan dialokasikan sejumlah memori seukuran `128 \* sizeof(char)`. Lalu, kita akan mem-print url ke dalam link yang tersedia dengan sprint dan dimasukkan ke `url_new`. Semua hal ini akan dieksekusi di lokasi /usr/bin/wget dengan `execl`. Jangan lupa membuat fungsi `waitpid`.
2.	Lalu, di dalam `main()`, kita akan menjalankan fungsi download_drive sebanyak 3 kali untuk mendownload semua file yang telah terbagi menjadi 3 jenis.

#### Kendala
Tidak terdapat kendala untuk bagian ini.

### 1C. Mengekstrak file-file yang telah didownload.
#### Source Code
![image](https://user-images.githubusercontent.com/81459084/115846493-2cbd3800-a44c-11eb-85ff-d57a9c685e51.png)

![image](https://user-images.githubusercontent.com/81459084/115846501-2e86fb80-a44c-11eb-9ba1-b4e256c87864.png)

#### Cara Pengerjaan
1.	Pertama, kita membuat fungsi baru untuk mengekstrak file (diberi nama unzip), yang menggunakan pointer `char *path`. Lalu buat fork dan disimpan di dalam `child_id`. Setelahnya, buat pengulangan kondisi yang didalamnya terdapat proses eksekusi program di lokasi /usr/bin/unzip. Jangan lupa fungsi `waitpid` untuk mengatur waktu eksekusi program.
2.	Lalu, jalankan fungsi `unzip` ini sebanyak 3 kali untuk 3 folder yang sebelumnya telah didownload.

#### Kendala
Tidak terdapat kendala untuk bagian ini.

### 1D. Memidahkan file-file yang telah diekstrak ke dalam 3 folder yang telah disediakan dari nomor 1A.
#### Source Code
![image](https://user-images.githubusercontent.com/81459084/115846616-4b233380-a44c-11eb-9909-09b89cae33f8.png)

![image](https://user-images.githubusercontent.com/81459084/115846630-4f4f5100-a44c-11eb-85c3-54122733703f.png)

![image](https://user-images.githubusercontent.com/81459084/115846647-54140500-a44c-11eb-95a0-c60481c026ea.png)

#### Cara Pengerjaan
1. Untuk soal ini, kita harus membuat 2 fungsi baru. Fungsi pertama adalah `move_files`,  yang berfungsi untuk memindahkan files. Fungsi ini menggunakan pointer `char *source` dan `char *destination`. Buat fork yang akan disimpan di dalam `child_id`. Lalu buat pengulangan kondisi , yang didalamnya akan ada eksekusi program di lokasi /usr/bin/mv. Gunakan juga fungsi `waitpid`.
2. Fungsi kedua adalah `iteration_files`, yang berfungsi untuk melakukan perulangan dan melist file/folder di dalam direktori. Fungsi ini menggunakan 2 pointer, yakni `char *source` dan `char *destination`.  Di dalam fungsi ini, kita juga akan membuat 2 pointer baru, `*dir` dan `*ent`. Setelahnya, lakukan pengulangan kondisi di mana direktori akan dibuka. Lalu, Ketika direkotri-direktori tersebut dibaca dengan perulangan “while”, lakukan lagi perulangan kondisi yang akan membandingkan setiap string. Berikutnya, buat sebuah pointer `*path` (yang memiliki ukuran 64 \* sizeof(char)). Tambahkan string dari source dan `ent->d_name` ke `path` dengan `strcat`. Lalu, jalankan fungsi `move_files`. Terakhir, tutup direktori.
3. Jalankan fungsi iteration_files sebanyak 3 kali dan sesuai dengan jenis datanya.

#### Kendala
1. Untuk iterasi file pada suatu directory dapat menggunakan library dirent.h dan menggunakan fungsi readdir yang diletakkan pada while tidak sama dengan NULL.

### 1E. Menjalankan program pada nomor 1a hingga 1d otomatis saat 6 jam sebelum ulang tahun stevany.
#### Source Code 
![image](https://user-images.githubusercontent.com/81459084/115846906-93daec80-a44c-11eb-92b2-e000d6af8062.png)

![image](https://user-images.githubusercontent.com/81459084/115846917-963d4680-a44c-11eb-95a7-43a7dcda7b70.png)

#### Cara Pengerjaan 
1.	Dalam soal ini, kita akan membuat sebuah fungsi baru dan sebuah pointer bertipe `char`. Pertama adalah pointernya dulu, yakni `char *get_current_formatted_time`, yang berfungsi untuk memperoleh waktu saat ini. Di dalamnya, masukkan variable `current_time` yang awalnya di set NULL. Lalu, gunakan struct untuk mengumpulkan data waktu saat ini, dimana hasilnya akan dimasukkan ke dalam fungsi `localtime (&current_time)`. Jangan lupa untuk membuat format waktu seperti yang telah diminta pada soal menggunakan `strftime()`.
2.	Lalu, buat fungsi baru bernama  `run_timer` yang berfungsi menjalankan waktu program. Fungsi ini menggunakan pointer `char *target_time`. Pertama, masukkan pointer \*now_time yang ukurannya 64 \* ukuran char. Lalu, lakukan perulangan `while (is_running)`. Di dalam perulangan, samakan `now_time` dengan `get_current_formatted_time` untuk menjalankan waktu hingga waktu target. 
3.	Jalankan fungsi `run_timer` dengan target 6 jam sebelum ultah dimulai.

#### Kendala
1. Memanfaatkan fungsi `time(NULL)` pada library `time.h` untuk melakukan while dan mengecheck jika waktu tujuan dan waktu saat ini sama, maka waktu tujuan telah tercapai dan mulai melakukan eksekusi perintah yang diinginkan.

### 1F. Menzip semua folder ke dalam 1 folder khusus yang telah diberi nama dan menghapus folder lainnya.
#### Source Code
![image](https://user-images.githubusercontent.com/81459084/115847021-b4a34200-a44c-11eb-807c-9e11decc63d3.png)

![image](https://user-images.githubusercontent.com/81459084/115847034-b8cf5f80-a44c-11eb-83fc-d9a0f904982f.png)

![image](https://user-images.githubusercontent.com/81459084/115847042-bb31b980-a44c-11eb-86e9-7021dcb6b85f.png)

![image](https://user-images.githubusercontent.com/81459084/115847054-bd941380-a44c-11eb-8d9a-8f1ee354a635.png)

#### Cara Pengerjaan
1.	Untuk menyelesaikan permasalahan ini, kita akan menggunakan fungsi dan pointer pada nomor 1E dan membuat lagi 2 fungsi baru.
2.	Fungsi pertama adalah `zip_files`, yang berfungsi menzip files. Fungsi ini menggunakan 4 pointer bertipe char, yakni \*path, \*source1, \*source2, dan \*source3. Hal pertama yang dilakukan adalah membuat fork dan disimpan di `child_id`. Lalu, lakukan perulangan “if” dan jalankan eksekusi program zip ini di lokasi zip, yakni /usr/bin/zip. Terakhir, masukkan fungsi waitpid.
3.	Fungsi kedua adalah `delete_files` (menggunakan pointer char \*path) yang bertujuan menghapus file. Susunan pembuatannya mirip dengan fungsi `zip_files`, yakni buat `fork`, buat perulangan “if” dan jalankan program ini di lokasi fungsi menghapus data, yakni /usr/bin/rm. Masukkan juga fungsi `waitpid`.
4.	Lalu, jalankan fungsi `run_timer` dengan waktu target dimodifikasi pada tanggal `9 April jam 22.22 WIB`, yakni waktu ultah stevany.
5.	Setelah itu, jalankan fungsi `delete_files` untuk menghapus semua file dan folder (kecuali folder zip untuk stevany).

#### Kendala
Tidak terdapat kendala untuk bagian ini.

### Hasil Output Soal1
#### Tampilan direktori setelah compile dan run program soal1
![image](https://user-images.githubusercontent.com/16128257/115943589-00043180-a4db-11eb-8e30-aa27097112f7.png)

#### Isi zip stefany folder pertama
![image](https://user-images.githubusercontent.com/16128257/115943611-1ca06980-a4db-11eb-948c-b98d2ded9dd5.png)

#### Isi zip stefany folder kedua
![image](https://user-images.githubusercontent.com/16128257/115943624-2f1aa300-a4db-11eb-8006-6a5436e12970.png)

#### Isi zip stefany folder kedua
![image](https://user-images.githubusercontent.com/16128257/115943635-3cd02880-a4db-11eb-986d-d02c26de605b.png)

#### Output program ketika menunggu hingga ulang tahun stevany tiba
![image](https://user-images.githubusercontent.com/16128257/115943733-f7f8c180-a4db-11eb-8e9e-fc67b8be0533.png)

## Soal2
### Tujuan
Kita diminta untuk membantu Loba untuk memproses file yang diberikan oleh bos Loba dengan mengategorikan foto-foto yang ada dalam file zip tersebut sesuai dengan jenis hewannya. Selain itu, di setiap kategori dari jenis hewan tersebut diminta untuk membuat sebuah file yang bernama 'keterangan.txt' dan isinya berupa nama dan umur dari daftar hewan yang ada pada directory tersebut.

### 2A. Mengextract zip ke dalam folder “/home/[user]/modul2/petshop”. Membedakan file dan folder, kemudian menghapus folder yang tidak dibutuhkan.
#### Source Code
![image](https://user-images.githubusercontent.com/62937814/115519778-b685cd80-a2b3-11eb-9c05-42e4a82772b2.png)

![image](https://user-images.githubusercontent.com/62937814/115519829-c3a2bc80-a2b3-11eb-8988-1a3753b4dcb4.png)

![image](https://user-images.githubusercontent.com/62937814/115519858-ca313400-a2b3-11eb-9000-a6839d397f63.png)

![image](https://user-images.githubusercontent.com/62937814/115524227-1e3e1780-a2b8-11eb-8a21-c1c89cccc67c.png)

![image](https://user-images.githubusercontent.com/62937814/115524807-b50ad400-a2b8-11eb-99cb-53e2b7a011f1.png)

#### Cara Pengerjaan
1. Membuat fungsi `make_dir` yang memiliki parameter `path` dengan tujuan bahwa kita membuat directory dengan nama berupa `path` tersebut. Pada pembuatannya menggunakan `"/bin/mkdir"` yang digunakan untuk membuat directory. 
2. Membuat fungsi `unzip` dengan parameter `(source, destination)` dimana `source` ini menandakan file yang akan kita extract atau unzip dan `destination` merupakan lokasi dimana kita akan meletakkan hasil file yang telah kita extract tersebut. Pada pembuatannya menggunakan `"/bin/unzip"` yang digunakan untuk melakukan unzip pada file tersebut. `"-d"` menandakan bahwa file tersebut akan dimasukkan ke dalam sebuah directory yaitu `destination`.
3. Setelah itu kita membuat fungsi `read_file` yang digunakan untuk membaca setiap file yang telah diextract. File yang kita baca hanyalah pada directory `"./petshop"`. Pada `if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)` digunakan apabila ada file yang bernama `"."` dan `".."` kita melakukan `continue`. Kemudian pada `S_ISDIR(statbuf.st_mode)` digunakan untuk mengecek apabila yang dicek adalah sebuah directory, maka kita memanggil `del_folder` untuk menghapus folder yang tidak dibutuhkan. Pada `else if(length >= 4 && strcmp(ent->d_name + length - 4, ".jpg") == 0)` akan terpenuhi apabila yang dicek merupakan file dan bertipe `.jpg` maka itu merupakan foto yang diminta untuk diproses.

#### Kendala
1. Saat memilih untuk menggunakan exec family, kami memutuskan untuk menggunakan `execl()` karena dirasa paling mudah dan paling cocok untuk digunakan.
2. Saat melakuakan fork, terdapat beberapa percobaan untuk mendapatkan hasil yang diinginkan. Hasilnya kita gunakan kondisi, `if (child_id == 0)` akan melakukan perintah `execl()` yang diinginkan. Disini fungsi child fork tersebut sebagai korban, karena hanya digunakan sekali saja, sehingga process utama dapat tetap berjalan.
3. Saat akan melakukan `del_folder` awalnya kami menggunakan nama folder tersebut satu-satu untuk menghapus folder. Namun akhirnya kami menggunakan `S_ISDIR(statbuf.st_mode)` untuk mengecek apakah itu merupakan folder atau bukan.

### 2B. Membuat directory dalam /petshop/ dengan nama sesuai jenis yang ada pada file foto peliharaan. Contoh : “/petshop/cat”.
#### Source Code
![image](https://user-images.githubusercontent.com/62937814/115526515-50507900-a2ba-11eb-961e-15690f829587.png)

![image](https://user-images.githubusercontent.com/62937814/115526586-62cab280-a2ba-11eb-847d-88c359f529ca.png)

#### Cara Pengerjaan
1. Apabila kondisi memenuhi bahwa yang sedang dicek merupakan file `.jpg` maka akan diproses.
2. Pertama, kita akan menghapus `.jpg` pada file foto agar lebih mudah diproses untuk mengambil data pada nama file foto tersebut. Hal ini menggunakan `namafile[strlen(namafile)-4] = 0`.
3. Kemudian kita akan memisahkan string dari file yang terdapat dua hewan pada satu file. Menggunakan fungsi `strtok` yang merupakan fungsi bawaan dari standard library c yang digunakan untuk memecah string menggunakan delimiter tertentu. Pada kondisi ini kita menggunakan delimiter `"_"` kemudian akan tersimpan nama `hewan` yang merupakan hewan pertama pada nama file tersebut dan `hewan2` yang merupakakan hewan kedua pada nama file tersebut.
4. Setelah kita mendapatkan data `hewan` dan `hewan2` maka kita masuk ke function `split_string` dimana pada function ini akan dilakukan pemisahan string lagi menggunakan `strtok` untuk mendapatkan data `jenis`, `nama`, dan `usia` dari hewan tersebut. Setelah itu kita membuat `path` untuk menyimpan nama path dari directory yang akan dibuat dengan format `./petshop/jenis`. Setelah path didapatkan, maka kita bisa memanggil function `make_dir` yang telah kita buat sebelumnya untuk membuat directory sesuai dengan jenis tersebut.

#### Kendala
1. Saat melakukan pemisahan string menggunakan `strtok` awalnya kami membuat pada satu function yang sama untuk pemisahan `hewan` dan `hewan2` dengan pemisahan `jenis`, `nama`, dan `usia`. Namun hal ini tidak berhasil karena fungsi `strtok` menyimpan sekali yang sama sesuai yang diproses di awal. Akhirnya kami memisahkan proses tersebut pada function yang berbeda.

### 3(C&D). Memindahkan foto ke folder dengan kategori yang sesuai dan di rename dengan nama peliharaan. Contoh: “/petshop/cat/joni.jpg”. Apabila dalam satu foto terdapat lebih dari satu peliharaan maka foto harus di pindah ke masing-masing kategori yang sesuai. Contoh: foto dengan nama “dog;baro;1_cat;joni;2.jpg” dipindah ke folder “/petshop/cat/joni.jpg” dan “/petshop/dog/baro.jpg”.

#### Source Code
![image](https://user-images.githubusercontent.com/62937814/115529673-4b40f900-a2bd-11eb-8d2e-cf78b8f2f235.png)

![image](https://user-images.githubusercontent.com/62937814/115530035-9c50ed00-a2bd-11eb-91c5-c7a69d1b33bf.png)

#### Cara Pengerjaan
1. Pada function `split_string` yang telah kita buat sebelumnya, kita telah menyimpan data `jenis`, `nama`, dan `usia`. Maka kita bisa langsung memanggil function `copy_file` dengan parameter `(original, namafile)` dimana `original` merupakan path asli file tersebut yang berfungsi sebagai _source_ file yang akan dicopy, dan akan di _paste_ dengan path `./petshop/jenis/nama.jpg`. 
2. hal ini juga berlaku dengan file yang memiliki dua hewan dalam satu file karena kita telah memanggil function `split_string` pada keduanya.
3. Setelah dicopy, maka file tersebut bisa dihapus dari directory awalnya dengan menggunakan function `del_file` dimana argumen pada execlnya menggunakan `"/bin/rm"` yang digunakan untuk me-remove file tersebut.

#### Kendala
1. Apabila menggunakan `move file` atau `mv` maka pada file yang memiliki 2 hewan dalam satu file akan lebih susah untuk dimasukkan sesuai kategorinya karena akan berpindah ke hewan ke 2 terlebih dahulu. Oleh karena itu kita menggunakan copy file dan delete file.

### 3E. Di setiap folder buatlah sebuah file "keterangan.txt" yang berisi nama dan umur semua peliharaan dalam folder tersebut.
#### Source Code
![image](https://user-images.githubusercontent.com/62937814/115533310-d243a080-a2c0-11eb-8460-70bcbbf0c60e.png)

#### Cara Pengerjaan
1. Pada function `split_string` yang telah kita buat sebelumnya, kita telah menyimpan data `jenis`, `nama`, dan `usia`. Kemudian kita menyimpan isi dari `keterangan.txt` pada variabel `isi_ket` sesuai format yang diminta. 
2. Kemudian setelah isi file digenerate, maka kita bisa memanggil function `make_ket` yang berfungsi untuk membuat file `keterangan.txt` tersebut dengan salah satu parameternya adalah isi dari file tersebut.
3. Hasil file `keterangan.txt` dari directory cat adalah:
```
nama	: simba
umur	: 4

nama	: luna
umur	: 4

nama	: sus
umur	: 6

nama	: koda
umur	: 11

nama	: oreo
umur	: 7

nama	: chester
umur	: 5

nama	: reggie
umur	: 8

nama	: tilly
umur	: 6

nama	: neko
umur	: 3

nama	: remi
umur	: 8

nama	: ellie
umur	: 3

nama	: chloe
umur	: 4

nama	: atlas
umur	: 0.6

nama	: nala
umur	: 4

nama	: angmry
umur	: 7

nama	: echo
umur	: 7

nama	: ava
umur	: 6

nama	: milo
umur	: 0.5

nama	: tucker
umur	: 3

nama	: jasper
umur	: 10

````

#### Kendala
Tidak terdapat kendala untuk bagian ini

### Hasil Output Soal2
#### Tampilan awal setelah compile dan run soal2
![image](https://user-images.githubusercontent.com/16128257/115943454-41e0a800-a4da-11eb-8ea3-13a7748f893b.png)

#### Hasil membuat direktori petshop
![image](https://user-images.githubusercontent.com/16128257/115943502-7ce2db80-a4da-11eb-8152-2e061315ce53.png)


#### Isi direktori petshop
![image](https://user-images.githubusercontent.com/16128257/115943482-689ede80-a4da-11eb-814b-fbd5102bf4eb.png)

#### Isi direktori salah satu jenis binatang (cat)
![image](https://user-images.githubusercontent.com/16128257/115943511-8e2be800-a4da-11eb-9e78-0d9105b82395.png)

#### Isi keterangan.txt salah satu jenis binatang (cat)
![image](https://user-images.githubusercontent.com/16128257/115943537-aa2f8980-a4da-11eb-9400-9d0cc2acd7fa.png)

## Soal3
### Tujuan
Terdapat seorang yang bernama Ranora, dia disuruh pembimbingnya untuk membuat program .c yang dapat mendownload batch gambar setiap 40 detik. Pada setiap batch tersebut, batch akan mendownload 1 gambar setiap 5 detik hingga 10 kali. Jika batch tersebut berhasil mendownload 10 gambar, maka gambar - gambar tersebut akan dijadikan dalam satu file .zip dengan format nama tertentu. Selanjutnya Ranora diperintahkan untuk membuat suatu executable shell dengan nama Killer.sh yang digunakan untuk menghentikan proses program .c yang dibuat sebelumnya. Namun Killer.sh ini bekerja sesuai dengan argumen saat menjalankan program .c, dan masing - masing argumen tersebut memiliki sifat masing - masing.

### 3A. Membuat sebuah fungsi sebagai timer yang dapat membuat direktori dengan format tertentu setiap 40 detik sekali.

#### Source Code
![image](https://user-images.githubusercontent.com/16128257/114737660-6ff31900-9d71-11eb-8511-49196f9a6e84.png)

![image](https://user-images.githubusercontent.com/16128257/114737781-8bf6ba80-9d71-11eb-9133-bdb7ca7ca688.png)

![image](https://user-images.githubusercontent.com/16128257/114737916-acbf1000-9d71-11eb-9ec7-ccef02e9bff5.png)

![image](https://user-images.githubusercontent.com/16128257/114737856-9f098a80-9d71-11eb-8ee8-e204219600e6.png)

![image](https://user-images.githubusercontent.com/16128257/114738001-bf394980-9d71-11eb-8149-76f4b06124a9.png)


#### Cara Pengerjaan
1. Membuat fungsi untuk mengatur timer yang dapat melakukan suatu perintah setiap 40 detik sekali. Fungsi ini kita beri nama `run_timer(delta_time, mode)` yang dapat dipanggil dengan cara `run_timer(40, mode)`. Untuk mode ada pada soal Nomor 3E.
2. Pada fungsi `run_timer(delta_time, mode)`, kita menggunkan fungsi `time(NULL)` untuk mendapatkan timestamp berupa integer detik saat ini. Kita akan membuat infinite loop dengan `while(is_running)`, dan untuk setiap iterasi kita gunakan fungsi `difftime()` untuk mendapatkan perbedaan waktu. Jika perbedaan waktu lebih atau sama dengan `delta_time` atau `40`, maka kita akan jalankan fungsi `call_timer_update` untuk membuat proses child untuk membuat direktori.
3. Untuk membuat directory, kita akan menggunakan fungsi `execl()`, karena fungsi `execl()` akan mengganti proses ini sesuai dengan perintah pada `execl()`, maka kita harus membuat process children yang digunakan untuk menjalankan `execl()` ini. Untuk itu kita menggunakan `fork()` untuk membuat process child baru. Lalu setelah process child memanggil `execl()`, maka process children akan berhenti, tetapi proses parent tetap berjalan. Fungsi untuk membuat direktori kita beri nama `make_directory(path)`.
4. Direktori yang dibuat sebelumnya mendapatkan argumen path dari fungsi `get_current_formatted_time()` yang mengembalikan sebuah string dengan timestamp format yang diinginkan. fungsi ini memanfaatkan fungsi `time()` dan `localtime()` yang kemudian waktu yang didapat akan diformat menggunakan `strftime()`.

#### Kendala
1. Saat memilih untuk menggunakan exec family, kami memutuskan untuk menggunakan `execl()` karena dirasa paling mudah dan paling cocok untuk digunakan.
2. Saat melakuakan fork, terdapat beberapa percobaan untuk mendapatkan hasil yang diinginkan. Hasilnya kita gunakan kondisi, `if (child_id == 0)` akan melakukan perintah `execl()` yang diinginkan. Disini fungsi child fork tersebut sebagai korban, karena hanya digunakan sekali saja, sehingga process utama dapat tetap berjalan.
3. Untuk menggunakan time di program .c kita menggunakan library `time.h`, dan mencari sumber cara implementasinya di internet.

### 3B. Membuat process yang dapat mendownload 1 gambar setiap 5 detik sebanyak 10 kali. Gambar - gambar ini akan di simpan pada direktori yang telah dibuat sebelumnya dengan nama file dengan format tertentu. 

#### Source Code
![image](https://user-images.githubusercontent.com/16128257/114743585-04ac4580-9d77-11eb-8ea5-b55533ba009c.png)

![image](https://user-images.githubusercontent.com/16128257/114744180-9d42c580-9d77-11eb-95d9-462d68c164ac.png)

![image](https://user-images.githubusercontent.com/16128257/114743840-42a96980-9d77-11eb-9662-e4a66c042f3a.png)

![image](https://user-images.githubusercontent.com/16128257/114743891-4ccb6800-9d77-11eb-9ed2-5b64f3e46c64.png)

#### Cara Pengerjaan
1. Setelah step terakhir pada 3A, kita masih berada pada child process.
2. Kita menggunakan timer yang sama seperti 3A, tetapi diubah pemanggilannya yaitu setiap 5 detik selama 10 kali, fungsi ini kami beri nama `run_timer_download_photos()`.
3. Untuk setiap 5 detik dari timer ini, kita akan download gambar menggunakan fungsi `call_timer_download_photo_update()` yang didalammnya terdapat pembuatan process dengan `fork()`, process yang di forked ini digunakan untuk melakukan download gambar, agak process child saat ini tidak terganggu.
4. Untuk melakukan download gambar, kita manfaatkan fungsi `execl()` dengan membuat fungsi baru `download_image()`. Kita memanfaatkan `wget` untuk mendownload gambar dengan url yang diberikan dan akan disimpan ke direktori sebelumnya, dengan nama file yang didapat dari fungsi `get_current_formatted_time()`.
5. Gambar didownload dari web berikut https://picsum.photos/, berdasarkan dokumentasi web tersebut, kita dapat mendownload gambar dengan ukuran yang kita inginkan. Untuk mendownload gambar persegi dengan ukuran 100x100 px, maka kita akan gunakan url berikut https://picsum.photos/100/100. Ukuran yang lain dapat menyesuaikan.
6. Ukuran gambar didapat dengan cara memanfaatkan fungsi `time(NULL)` sehingga didapat timestamp linux, yang di modulus 1000 dan dijumlah dengan 50. Sehingga minimal adalah 50x50 px dan maximal adalah 1050x1050px.

#### Kendala
1. Karena `char[]` tidak bisa dikembalikan pada suatu fungsi karena bersifal local. Maka untuk mengembalikan string atau char* dari fungsi kita menggunakan `malloc()` yang dapat di `free()` saat string tersebut selesai digunakan untuk membersihkan string tersebut dari memory.
2. Untuk memahami cara kerja https://picsum.photos/, kita membaca dokumentasi sebentar untuk mengetahui cara penggunaanya.

### 3C. Membuat fungsi yang dapat menyimpan suatu file status.txt pada direktori sebelumnya yang berisi pesan “Download Success” yang di-encrypt menggunakan Caesar Cypher 5 Shift. Setelah 10 gambar .jpg dan satu file status.txt berhasil disimpan pada direktori, selanjutnya adalah menyimpan seluruh file pada direktori ini pada suatu file .zip dan menghapus seluruh isi direktori dan direktori itu sendiri.

#### Source Code
![image](https://user-images.githubusercontent.com/16128257/114747171-c022a900-9d7a-11eb-9fa5-37d917b40b19.png)

![image](https://user-images.githubusercontent.com/16128257/114747211-cca70180-9d7a-11eb-9e57-0976d4f9a0ae.png)

![image](https://user-images.githubusercontent.com/16128257/114747253-d4ff3c80-9d7a-11eb-88a5-33d3a1bd6a26.png)

![image](https://user-images.githubusercontent.com/16128257/114747308-e6484900-9d7a-11eb-9d00-54cc355064dd.png)

![image](https://user-images.githubusercontent.com/16128257/114747600-36bfa680-9d7b-11eb-9744-534b0c286e51.png)

#### Cara Pengerjaan
1. Membuat fungsi `caesar_cypher()` yang digunakan untuk membuat string Caesar Cypher dengan cara memodifikasi masing - masing char pada string dengan shift tertentu. Untuk ini kita hanya akan mengubah char yang merupakan alphabet. Setelah itu kita akan mengembalikan string yang telah dimodifikasi ini.
2. Membuat fungsi `make_status_file()` yang digunakan untuk membuat file status.txt dengan isi "Download Success" yang diencrypt dengan Caesar Cypher Shift 5 pada step 1. Fungsi ini memanfaatkan fungsi `fopen()` untuk membuat file status.txt kosong. Lalu file tersebut akan di-write menggunakan fungsi `fprintf()` yang saat selesai kita tutup dengan fungsi `fclose()`.
3. Setelah status.txt dibuat, maka direktori tersebut akan kita buat file zip-nya. Kita buat fungsi `make_zip()` yang memanfaatkan `execl()` sehingga kita harus membuat `fork()` agar child process dapat menjadi korban, sehingga process child saat ini masih tetap dapat berjalan.
4. Fungsi `make_zip()` akan dipanggil oleh fungsi `make_zip_file()` dengan argumen filename dan direktori yang akan di zip. Karena fungsi akan berhenti dan harus berhenti disini, maka kita tidak akan menggunakan `fork()` agar child process ini selesai dan kita akan lanjut ke process utama kembali.

#### Kendala
1. Saat membuat fungsi `caesar_cypher()` kita menggunakan website https://rot13.com/ untuk mengetest kebenaran caesar cypher 5 shift kami.
2. Untuk membuka dan menulis file, kita menggunaan fungsi `fopen()`, `fprintf()` dan `fclose()`. Fungsi ini merupakan cara termudah untuk membuat suatu file text maupun binary. Kita memilih menggunakan fungsi ini dari pada menggunakan `exec()` karena lebih friendly dengan program .c.
3. Untuk membuat file .zip yang dapat menghapus direktori sekaligus, kita menggunakan argumen `-rm`, yang dimana argumen `-r` merupakan fungsi rekursif agar dapat melakukan zip pada suatu direktori, dan `-m` digunakan untuk menghapus folder dan file yang berhasil di zip.

### 3D. Membuat suatu fungsi yang dapat membuat suatu program bash "Killer.sh" yang dapat digunakan untuk melakukan termination pada process utama dan process child yang berjalan dan menghapus dirinya sendiri setelah operasi selesai.

#### Source Code
![image](https://user-images.githubusercontent.com/16128257/114752107-26f69100-9d80-11eb-8710-796d5f0f405e.png)

![image](https://user-images.githubusercontent.com/16128257/114752217-41c90580-9d80-11eb-8d19-41e480ae18e9.png)

#### Cara Pengerjaan
1. Membuat fungsi `make_killer_exec()` yang digunakan untuk membuat file "Killer.sh". Isi dari file ini adalah sebuah perintah `kill [pid]` dengan pid adalah process id dari program utama untuk melakukan terminate pada program utama dan `rm -- "$0"` yang digunakan untuk menghapus file bash sendiri atau "Killer.sh".
2. `[pid]` yang akan ditulis pada file "Killer.sh" didapat dari fungsi `getpid()` pada program utama.
3. Untuk membuat file "Killer.sh" kita memanfatkan fungsi `fopen()`, `fprintf()` dan `fclose()`.
4. Untuk melakukan test, kita jalankan program utama, lalu pada terminal yang berbeda kita jalankan perintah `./Killer.sh` apabila terdapat permission error, tambahkan permission dengan perintah `chmod +x Killer.sh`.
5. Saat "Killer.sh" di eksekusi maka program utama akan berhenti, namum child process masih berjalan.

#### Kendala
1. Untuk menghapus diri sendiri dapat menggunakan `rm Killer.sh` namun kurang elegan, maka kami menggunakan perintah `rm -- "$0"` pada "Killer.sh".

### 3E. Menambahkan suatu argument pada program .c utama dijalankan yang masing - masing argument tersebut akan berpengaruh pada "Killer.sh" yang dieksekusi.

#### Source Code
![image](https://user-images.githubusercontent.com/16128257/114753244-7093ab80-9d81-11eb-8308-b56322d95b14.png)

![image](https://user-images.githubusercontent.com/16128257/114753265-77222300-9d81-11eb-9632-08b7afa843d5.png)

![image](https://user-images.githubusercontent.com/16128257/114753379-98830f00-9d81-11eb-8f80-7d9b3559b756.png)

#### Cara Pengerjaan
1. Melakukan perombakan pada bagian kode yang membutuhkan mode.
2. Menggunakan `argc` dan `argv` untuk mendapatkan mode yang akan digunakan untuk melakuakn terminasi saat "Killer.sh" dieksekusi.
3. Terdapat 2 mode, yaitu `-z` yang akan memberhentikan seluruh process yang ada saat "Killer.sh" dieksekusi. Lalu mode `-x` yang akan memberhentikan process utama saja, sedangkan process child akan tetap melanjutkan tugasnya (mendownload gambar hingga melakukan zip).
4. Pada mode `-z`, untuk melakukan terminate pada semua child, maka kita harus mencatat semua pid pada process child, sehingga kita lakukan append pada "Killer.sh" yang berisi isi pid dari child process. Oleh karena itu kita menambah fungsi `append_killer_exec()` yang digunakan untuk melakukan append pada file "Killer.sh" dengan perintah `kill [pid]`, dengan `[pid]` adalah child process id.
5. Pada mode `-x`, kita tinggal lakukan terminate pada program utama, sehingga semua child process menjadi orphan process.
6. Untuk melakukan test, kita jalankan program utama dengan argument `-z` atau `-x`, lalu pada terminal yang berbeda kita jalankan perintah `./Killer.sh` apabila terdapat permission error, tambahkan permission dengan perintah `chmod +x Killer.sh`.
7. Saat "Killer.sh" di eksekusi maka process akan dihentikan sesuai dengan argument yang diberikan sebelumnya.

#### Kendala
1. Menggunakan argc dan argv sebagai parameter fungsi `main()` untuk mendapatkan argument yang dijalankan pada program utama.
2. Karena pada soal tidak ada keterangan untuk mode tanpa argument, maka kami menggunakan mode `-z` sebagai argument default.

### Hasil Output Soal3
#### Tampilan awal compile dan run program soal3
![image](https://user-images.githubusercontent.com/16128257/115943146-76536480-a4d8-11eb-920d-6346c039985b.png)

#### Hasil membuat direktori, download images dan melakukan zip terhadap direktori tersebut
![image](https://user-images.githubusercontent.com/16128257/115943177-a6026c80-a4d8-11eb-93a5-2d090dba3526.png)

#### Isi lengkap salah satu direktori yang di-zip
![image](https://user-images.githubusercontent.com/16128257/115943196-c03c4a80-a4d8-11eb-8549-a2774578e2fa.png)

#### Isi dari file status.txt
![image](https://user-images.githubusercontent.com/16128257/115943234-ebbf3500-a4d8-11eb-8107-2a1e0f2467d7.png)

#### Isi dari shell Killer.sh tanpa argument dan dengan argument -z
![image](https://user-images.githubusercontent.com/16128257/115943255-0a253080-a4d9-11eb-906f-a6b7d181b1eb.png)

#### Isi dari shell Killer.sh dengan argument -x
![image](https://user-images.githubusercontent.com/16128257/115943300-507a8f80-a4d9-11eb-8566-50e159c875cb.png)

# Referensi
## 1
- https://www.geeksforgeeks.org/exec-family-of-functions-in-c/
- https://stackoverflow.com/questions/41211732/fork-and-waitpid-in-c
- https://www.tutorialspoint.com/c_standard_library/time_h.htm
## 2
- https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
- https://stackoverflow.com/questions/4553012/checking-if-a-file-is-a-directory-or-just-a-file
- https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
## 3
- https://www.youtube.com/watch?v=cex9XrZCU14
- https://www.tutorialspoint.com/c_standard_library/time_h.htm
- https://www.geeksforgeeks.org/time-h-header-file-in-c-with-examples/
- https://stackoverflow.com/questions/8981164/self-deleting-shell-script/8981233
- https://stackoverflow.com/questions/25798977/returning-string-from-c-function
- https://rot13.com/
- https://www.unix.com/shell-programming-and-scripting/169967-zip-files-deleting-originals.html
- https://www.programiz.com/c-programming/c-file-input-output
- https://stackoverflow.com/questions/8981164/self-deleting-shell-script
- https://www.tutorialspoint.com/cprogramming/c_command_line_arguments.htm

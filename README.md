# soal-shift-sisop-modul-2-D02-2021
- Jessica Tasyanita (05111940000043)
- Ahmad Syafiq Aqil Wafi (05111940000089)
- Maximilian H M Lingga (05111940000092)

## Soal - Template (copy ini aja.)
### Tujuan
### 5Z. Mencoba mengirim
#### Source Code
#### Cara Pengerjaan
#### Kendala

## Soal1
- Menunggu Deadline

## Soal2
- Menunggu Deadline

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
#### Cara Pengerjaan
#### Kendala

# Referensi
## SOAL 1
## SOAL 2
## SOAL 3
### 3A
1. some
2. thing
### 3B
1. Alright

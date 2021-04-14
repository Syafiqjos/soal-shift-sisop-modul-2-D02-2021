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

#### Cara Pengerjaan
#### Kendala

### 3D. Some
#### Source Code
#### Cara Pengerjaan
#### Kendala

### 3E. Some
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

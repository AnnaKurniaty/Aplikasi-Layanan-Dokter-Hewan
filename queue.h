/* Program: queue.h
 * Deskripsi: Spesifikasi ADT Queue menggunakan Linked List
 * Nama: Ardhiansyah
 * Tanggal: 23 April 2011
 * Compiler: GCC 4.9.2
 * Update: Muhammad Saiful Islam
 * Tanggal Update: 7 April 2015
 * Tanggal Update 2: 20 Mei 2015
 * Update: Asri Maspupah
 * Tanggal Update: 7 Mei 2021
 */

#ifndef QUEUE_H
#define QUEUE_H


#include "boolean.h"
#define nil NULL
#define Front(Q) (Q).Front 
#define Rear(Q) (Q).Rear 
#define InfoFront(Q) (Q).Front->info 
#define InfoRear(Q) (Q).Rear->info  
#define Info(P) (P)->info  
#define next(P) (P)->next


typedef struct{
	int waktuKedatangan; 
	char nama[255]; //Nama majikan
	char dataPenyakit[10][255]; //Daftar Nama Penyakit 
	char kategoriPenyakit[10]; //Berisi Ringan || Sedang || Berat
	int WaktuPelayanan; //Waktu estimasi Pelayanan
	int WaktuMulai; //Waktu estimasi mulai Pemeriksaan
	int WaktuSelesai; //Waktu selesai Pemeriksaan
	int prioritas;
}data;

/* Definisi elemen dan address */ 
typedef data infotypeQueue; // infotypeQueue nama lain struct participant
typedef struct NodeQueue *addrNQ; // sebuah pointer yang menunjuk ke struct NodeQueue
typedef struct NodeQueue {
    infotypeQueue info; // address Node NBTree
    addrNQ next;
} NodeQueue;
typedef struct {
    addrNQ Front; // tag antrian depan
    addrNQ Rear; // tag antrian belakang
} Queue;


/***** Manajemen memori *****/
/* Mengirimkan address hasil alokasi sebuah elemen dengan info X.
 * Jika alokasi berhasil, modul mengembalikan P; Info(P) = X, Next(P) = NULL.
 * P adalah pointer yang menunjuk ke node Queue sebagai hasil alokasi.
 * Jika alokasi gagal, modul mengembalikan NULL.
 */
addrNQ AlokasiQueue(infotypeQueue X);

/* Melakukan dealokasi elemen P (pointer menunjuk ke alamat node queue).
 * I.S.: P terdefinisi.
 * F.S.: P dikembalikan ke sistem.
 */
void DealokasiQueue(addrNQ P);

/***** Manajemen Queue *****/
/* Membuat sebuah Queue kosong dengan Front(Q) = Nil dan Rear (Q) = Nil 
   I.S. Belum terbentuk Queue 
   F.S. Sudah terbentuk Queue
*/
void CreateQueue(Queue *Q);

/* Mengetahui apakah Queue kosong atau tidak. 
   mengirimkan true, jika Queue Kosong yaitu Front(Q) = Nil dan Rear (Q) = Nil
   Sebaliknya false
*/
boolean IsQueueEmpty(Queue Q);

/* Memasukkan info baru ke dalam Queue dengan aturan FIFO */
/* I.S. Q mungkin kosong atau Q mungkin berisi antrian */ 
/* F.S. info baru (data) menjadi Rear yang baru dengan node Rear yang lama mengaitkan pointernya ke node yang baru */ 
void enQueue(Queue *Q, infotypeQueue data);

/* Proses: Mengambil info pada Front(Q) dan mengeluarkannya dari Queue dengan aturan FIFO */ 
/* I.S. Q mungkin kosong atau Q mungkin berisi antrian */  
/* F.S. info yang diambil = nilai elemen Front pd I.S. */ 
/* Front(Q) menunjuk ke next antrian atau diset menjadi NIll, Q mungkin kosong */ 
void deQueue(Queue *Q, infotypeQueue *data);


/* Mengirimkan banyaknya elemen queue jika Q berisi atrian atau 
   mengirimkan 0 jika Q kosong 
*/ 
int NBElmt(Queue Q); 

boolean waktuTercepat(Queue data, int waktu);

void PrintQueue(Queue data);

void PrintFormat(Queue data);

void printPenyakit(data buff);
#endif // QUEUE_H

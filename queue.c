/*
 *	File          : queue.c
 *	Deskripsi     : Body file dari ADT Queue [Linked List]
*/

#include "queue.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

/***** Manajemen memori *****/
/* Mengirimkan address hasil alokasi sebuah elemen dengan info X.
 * Jika alokasi berhasil, modul mengembalikan P; Info(P) = X, Next(P) = NULL.
 * P adalah pointer yang menunjuk ke node Queue sebagai hasil alokasi.
 * Jika alokasi gagal, modul mengembalikan NULL.
 */
addrNQ AlokasiQueue(infotypeQueue X){
	//Kamus
	NodeQueue *p;
	
	//Algoritma
	p = (addrNQ)malloc(sizeof(NodeQueue));
	if(p != nil){
		Info(p) = X;
		p->next = nil;
		return p;
	}else {
		return nil;
	} 
}

/* Melakukan dealokasi elemen P (pointer menunjuk ke alamat node queue).
 * I.S.: P terdefinisi.
 * F.S.: P dikembalikan ke sistem.
 */
void DealokasiQueue(addrNQ P){
	free(P);
}

/***** Manajemen Queue *****/
/* Membuat sebuah Queue kosong dengan Front(Q) = Nil dan Rear (Q) = Nil 
   I.S. Belum terbentuk Queue 
   F.S. Sudah terbentuk Queue
*/
void CreateQueue(Queue *Q){
	Q->Front = nil; // buat output(tempat keluar)
	Q->Rear = nil;	 // buat input(tempat masuk)
}

/* Mengetahui apakah Queue kosong atau tidak. 
   mengirimkan true, jika Queue Kosong yaitu Front(Q) = Nil dan Rear (Q) = Nil
   Sebaliknya false
*/
boolean IsQueueEmpty(Queue Q){
	return (Front(Q) == nil &&  Rear(Q) == nil);
}

/* Memasukkan info baru ke dalam Queue dengan aturan FIFO */
/* I.S. Q mungkin kosong atau Q mungkin berisi antrian */ 
/* F.S. info baru (data) menjadi Rear yang baru dengan node Rear yang lama mengaitkan pointernya ke node yang baru */ 
void enQueue(Queue *Q, infotypeQueue data){
    NodeQueue *P;
    
    P = AlokasiQueue(data);
    if(IsQueueEmpty(*Q)){
        Q->Front = P;
        Q->Rear = P;
    }else{
        next(Q->Rear) = P;
        Q->Rear = P;
    }
}

/* Proses: Mengambil info pada Front(Q) dan mengeluarkannya dari Queue dengan aturan FIFO */ 
/* I.S. Q mungkin kosong atau Q mungkin berisi antrian */  
/* F.S. info yang diambil = nilai elemen Front pd I.S. */ 
/* Front(Q) menunjuk ke next antrian atau diset menjadi NIll, Q mungkin kosong */ 
void deQueue(Queue *Q, infotypeQueue *data){
	NodeQueue *P;
    
    P = Q->Front;
    if(P!=nil){
        Q->Front = next(P);
        *data = Info(P);
        DealokasiQueue(P);
    }else{
        printf("\n\t\t\t\t\tKesalahan : Queue kosong\n");
    }
    if(Q->Front==nil){
    	Q->Rear=nil;
    }   
}

/* Mengirimkan banyaknya elemen queue jika Q berisi atrian atau 
   mengirimkan 0 jika Q kosong 
*/ 
int NBElmt(Queue Q){
	addrNQ P;
    int i = 0;
    
    P = Front(Q);
    while(P!=nil){
        i++;
        P = next(P);
    }
    return i;
}

void PrintQueue(Queue data){
	//Kamus
	NodeQueue *p;
	int i = 1;
	//Algoritma
	puts("\n\t\t\t\t\t  Data Pendaftar Layanan Dokter Hewan - Queue");
	puts("\t=========================================================================================================");
	puts("\tNo Nama \t Waktu Datang \t Kategori    Penyakit     Wpelayanan  Wpemerikasaan  Wselesai  Prioritas");
	if(!IsQueueEmpty(data)){
		p = data.Front;
		while (p != nil){
			printf("\t%d. %s \t     %d  \t %s       %s  \t   %d    \t   %d  \t     %d  \t     %d\n", i, p->info.nama, p->info.waktuKedatangan, p->info.kategoriPenyakit, p->info.dataPenyakit[0], p->info.WaktuPelayanan, p->info.WaktuMulai, p->info.WaktuSelesai, p->info.prioritas);
			i++;
			p = next(p);
		}
	}
	if(i==1){
		printf("\t\t\t\t\t\t[ Antrian masih kosong ]\n");
	}
	printf("\n\t\t\t\t\t\tPress any key to continue.. ");
	getch();
}

void PrintFormat(Queue data){
	//Kamus
	NodeQueue *p;
	int i = 1;
	//Algoritma
	puts("\n\t\t\t\t\t  Data Pendaftar Layanan Dokter Hewan - Queue");
	puts("\t\t\t\t\t================================================");
	if(!IsQueueEmpty(data)){
		p = data.Front;
		while (p != nil){
			printf("\t\t\t\t\t%d. %s \n", i, p->info.nama);
			printf("\t\t\t\t\tWaktu Datang : %d\n", p->info.waktuKedatangan);
			printf("\t\t\t\t\tKategori : %s\n", p->info.kategoriPenyakit);
			printPenyakit(p->info);
			printf("\t\t\t\t\tWaktu Pelayanan : %d\n", p->info.WaktuPelayanan);
			printf("\t\t\t\t\tWaktu Mulai Pemeriksaan : %d\n", p->info.WaktuMulai);
			printf("\t\t\t\t\tWaktu Selesai : %d\n",  p->info.WaktuSelesai);
			printf("\t\t\t\t\tPrioritas : %d\n\n",  p->info.prioritas);
			i++;
			p = next(p);
		}
	}
	if(i==1){
		printf("\t\t\t\t\t\t   [ Antrian masih kosong ]\n\n");
	}
	printf("\t\t\t\t\tPress any key to continue.. ");
	getch();
}

void printPenyakit(data buff){
	int i;
	printf("\t\t\t\t\tNama Penyakit : ");
	for(i=0; i<10; i++){
		printf("%s", buff.dataPenyakit[i]);	
		if(strcmp(buff.dataPenyakit[i+1],"Kosong")==0){
			break;
		}
		printf(", ");
	}
	printf("\n");
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.c"
#include "queue.h"


void tambahPendaftar(Queue *Q);
void tampilPendaftar(Queue myQueue);
void panggilPendaftar(Queue *myQueue);
void help();
void credit();

void sort(Queue *Q);
void set(Queue *Q);

void tambahPendaftar(Queue *Q){
	//Kamus
	data customer;
	NodeQueue *p;
	
	//Algoritma
	p = Q->Rear;
	//customer.Wselesai = 0;
	//customer.Wmengantri = 0;
	
	//Input data antrian
	printf("Nama         : ");
	fflush(stdin);
	scanf("%s", customer.nama);
	printf("Waktu Datang : ");
	scanf("%d", &customer.waktuKedatangan);
	int i;
	char temp;
	for(i=0; i<10; i++){
		printf("Nama Penyakit %d : ", i+1);
		fflush(stdin);
		scanf("%s", customer.dataPenyakit[i]);
		
		fflush(stdin);
		printf("Apakah ada penyakit lain? (y/n): ");
		scanf("%c", &temp);
		if(temp=='n'||temp=='N'){
			i+=10;
		}
	}
	/*
	//Proses Menghitung Waktu Mengantri dan Estimasi Selesai	
	if(p==nil){
		customer.Wselesai = customer.Wdatang + HitungWaktuCheckIn(customer.jumlahKoper);
		getch();
	}
	if(p!=nil){
		if(p->info.Wselesai > customer.Wdatang){
			customer.Wmengantri = p->info.Wselesai - customer.Wdatang;
			customer.Wselesai = p->info.Wselesai + HitungWaktuCheckIn(customer.jumlahKoper);
		}else{
			customer.Wmengantri = 0;
			customer.Wselesai = customer.Wdatang + HitungWaktuCheckIn(customer.jumlahKoper);
		}
	}
	
	puts("Hasil proses perhitungan");
	printf("Waktu Mengantri  : %d\n", customer.Wmengantri);
	printf("Estimasi Selesai : %d\n", customer.Wselesai);
	*/
	//Memasukkan ke antrian
	enQueue(Q,customer);
	
	//Mengurutkan antrian Berdasarkan Prioritas
	sort(Q);
	
	//Mengisi elemen pendukung
	set(Q);
	
	
	printf("Press any key to continue.. ");
	getch();
}

void tampilPendaftar(Queue Q){
	PrintQueue(Q);
}

void panggilPendaftar(Queue *myQueue){
	
}

void help(){
	
}

void credit(){
	
}


int main(){
	char choice;
	Queue myQueue;
	CreateQueue(&myQueue);
	do{
		system("cls");
		printf("Program Layanan Dokter Hewan\n");
		printf("1. Tambah Pendaftar\n");
		printf("2. Tampilkan Pendaftar\n");
		printf("3. Panggil Pendaftar\n");
		printf("4. Help\n");
		printf("5. Credit\n");
		printf("6. Keluar\n");
		printf("Masukkan Pilihan: ");
		fflush(stdin);
		scanf("%c", &choice);
		if(choice=='1'){
			tambahPendaftar(&myQueue);
		}else if(choice=='2'){
			tampilPendaftar(myQueue);	
		}else if(choice=='3'){
			panggilPendaftar(&myQueue);
		}else if(choice=='4'){
			help();
		}else if(choice=='5'){
			credit();
		}
	}while(choice!='6');
	return 0;
}

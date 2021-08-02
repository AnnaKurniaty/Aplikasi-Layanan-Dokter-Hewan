#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.c"
#include "queue.h"

/*
	ringan : penyakit kulit, luka ringan, bersin
	sedang : cacingan, diare, luka dalam
	berat : gangguan kerongkongan yang mengeluarkan lendir yang berbau busuk, kuning, terkena virus 
*/
void tambahPendaftar(Queue *Q);
void tampilPendaftar(Queue myQueue);
void panggilPendaftar(Queue *myQueue, int *checkpoints );
void help();
void credit();
void set(Queue *Q, int checkpoints);
void sort(Queue *Q);
int HitungWaktuPelayanan(char temp[10][255]);
int HitungPrioritas(char temp[10][255]);
int KlasifikasiKategori(char temp[10][255]);
void header();

/* 
	Deskripsi : Modul untuk menghitung waktu pelayanan yang sudah di set berdasarkan kategori penyakit 
   Autor : Dimas W S
   
*/
int HitungWaktuPelayanan(char temp[10][255]){
	int i;
	int result = 0;
	//Menambahkan 45 menit jika pada daftar penyakit terdapat penyakit dengan kategori berat
	for(i=0; i<10; i++){
		if(strcmp(temp[i],"Kosong")==0){
			break;
		}
		if(strcmp(temp[i],"gangguan kerongkongan")==0){
			result += 45;
		}else if(strcmp(temp[i],"kuning")==0){
			result += 45;
		}else if(strcmp(temp[i],"terkena virus")==0){
			result += 45;
		}	
	}
	
	//Menambahkan 30 menit jika pada daftar penyakit terdapat penyakit dengan kategori sedang
	for(i=0; i<10; i++){
		if(strcmp(temp[i],"Kosong")==0){
			break;
		}
		if(strcmp(temp[i],"cacingan")==0){
			result += 30;
		}else if(strcmp(temp[i],"diare")==0){
			result += 30;
		}else if(strcmp(temp[i],"luka dalam")==0){
			result += 30;
		}
	}
	
	//Menambahkan 15 menit jika pada daftar penyakit terdapat penyakit dengan kategori ringan
	for(i=0; i<10; i++){
		if(strcmp(temp[i],"Kosong")==0){
			break;
		}
		if(strcmp(temp[i],"penyakit kulit")==0){
			result += 15;
		}else if(strcmp(temp[i],"luka ringan")==0){
			result += 15;
		}else if(strcmp(temp[i],"bersin")==0){
			result += 15;
		}
	}
	for(i=0; i<10; i++){
		if(strcmp(temp[i],"Kosong")==0){
			break;
		}
		if(strcmp(temp[i],"gangguan kerongkongan")!=0 && strcmp(temp[i],"kuning")!=0 && strcmp(temp[i],"terkena virus")!=0 && strcmp(temp[i],"cacingan")!=0 && strcmp(temp[i],"diare") !=0 && strcmp(temp[i],"luka dalam") != 0 && strcmp(temp[i],"penyakit kulit") != 0 && strcmp(temp[i],"luka ringan") != 0 &&strcmp(temp[i],"bersin") != 0 ){
			result += 15;
		}	
	}
	
	//Mengembalikan result
	return result;
}


/* 
	Deskripsi : Modul ini berfungsi untuk menghitung poin prioritas pada data pasien sesuai kategori penyakit yaitu, berat, sedang, dan ringan 
	Autor : Hasanah
	
*/

int HitungPrioritas(char temp[10][255]){
	int i;
	int tempSedang = 0;
	int tempRingan = 0;
	//Mengembalikan langsung 4 poin apabila terdapat penyakit dengan kategori berat
	//Jika terdapat penyakit dengan kategori ringan, jumlah penyakit akan disimpan di tempRingan
	//Jika terdapat penyakit dengan kategori sedang, jumlah penyakit akan disimpan di tempSedang
	for(i=0; i<10; i++){
		if(strcmp(temp[i],"gangguan kerongkongan")==0){
			return 4;
		}else if(strcmp(temp[i],"kuning")==0){
			return 4;
		}else if(strcmp(temp[i],"terkena virus")==0){
			return 4;	
		}else if(strcmp(temp[i],"cacingan")==0){
			tempSedang++;
		}else if(strcmp(temp[i],"diare")==0){
			tempSedang++;
		}else if(strcmp(temp[i],"luka dalam")==0){
			tempSedang++;
		}else if(strcmp(temp[i],"penyakit kulit")==0){
			tempRingan++;
		}else if(strcmp(temp[i],"luka ringan")==0){
			tempRingan++;
		}else if(strcmp(temp[i],"bersin")==0){
			tempRingan++;
		}
	}
	//Mengembalikan 3 poin apabila terdapat penyakit dengan kategori sedang dengan jumlah 2 atau lebih
	//Mengembalikan 2 poin apabila terdapat penyakit dengan kategori ringan dengan jumlah 3 atau lebih
	if(tempSedang>=2){
		return 3;
	}else if(tempRingan>=3){
		return 2;
	}
	return 1;
}

/* 
	Deskripsi : Modul untuk menambahkan data pendaftar
    Autor : Dimas W S
    
*/

void tambahPendaftar(Queue *Q){
	//Kamus
	data customer;
	NodeQueue *p;
	int i;
	char temp;
	//Algoritma
	p = Q->Rear;
	
	//Input data antrian
	system("cls");
	printf("\n\t\t\t\t\t    |~|~|~|~QUEENPET~|~|~|~|");
	printf("\n\n\t\t\t\t\t    ~|Masukan Data Antrian|~");
	printf("\n\n\t\t\t\t>>>------------------------------------------<<<\n\n");
	printf("\t\t\t\t\tNama            : ");
	fflush(stdin);
	scanf("%[^\n]c", customer.nama);
	printf("\t\t\t\t\tWaktu Datang    : ");
	scanf("%d", &customer.waktuKedatangan);
	
	//Inisialisasi variabel Data penyakit dengan Kalimat Kosong
	for(i=0; i<10; i++){
		strcpy(customer.dataPenyakit[i],"Kosong");
	}
	
	for(i=0; i<10; i++){
		printf("\t\t\t\t\tNama Penyakit %d : ", i+1);
		fflush(stdin);
		scanf("%[^\n]c", customer.dataPenyakit[i]);
		do{
			fflush(stdin);
			printf("\n\t\t\t\t\tApakah ada penyakit lain? (y/n): ");
			scanf("%c", &temp);
			if(temp=='y'||temp=='n'||temp=='Y'||temp=='N'){
				break;
			}
			puts("\n\t\t\t\t\t   inputan salah!!");
		}while(true);
		if(temp=='n'||temp=='N'){
			i+=10;
		}
	}
	
	//Proses Menghitung Waktu Pelayanan, Waktu Mulai, dan Estimasi Selesai	
	customer.WaktuPelayanan = HitungWaktuPelayanan(customer.dataPenyakit);
	if(p==nil){
		customer.WaktuSelesai = customer.waktuKedatangan + customer.WaktuPelayanan;
		customer.WaktuMulai = customer.waktuKedatangan;
	}
	
	if(p!=nil){
		if(p->info.WaktuSelesai > customer.waktuKedatangan){
			customer.WaktuMulai = p->info.WaktuSelesai;
			customer.WaktuSelesai = p->info.WaktuSelesai + customer.WaktuPelayanan;
		}else{
			customer.WaktuMulai = customer.waktuKedatangan;
			customer.WaktuSelesai = customer.waktuKedatangan + customer.WaktuPelayanan;
		}
	}
	
	//Proses mengisi poin prioritas dan kategori penyakit
	customer.prioritas = HitungPrioritas(customer.dataPenyakit);
	
	if(KlasifikasiKategori(customer.dataPenyakit)==1){
		strcpy(customer.kategoriPenyakit,"Berat"); 
	}else if(KlasifikasiKategori(customer.dataPenyakit)==2){
		strcpy(customer.kategoriPenyakit,"Sedang"); 
	}else{
		strcpy(customer.kategoriPenyakit,"Ringan"); 	
	}
			
	//Memasukkan data ke antrian
	enQueue(Q,customer);
	
	printf("\n\n\t\t\t\t>>>------------------------------------------<<<\n\n");
	printf("\n\t\t\t\t\tPress any key to continue.. ");
	getch();
}

/* Deskripsi : Modul untuk memilih cara untuk menampilkan data pendaftar 
   Autor : Dimas W S
*/

void tampilPendaftar(Queue Q){
	char choice;
	
	do{
		system("cls");
		printf("\n\t\t\t\t\t\t     |~|~|~|~QUEENPET~|~|~|~|");
		printf("\n\n\t\t\t\t\t\t       ~|Tampil Pendaftar|~");
		printf("\n\n\t\t\t\t\t>>>------------------------------------------<<<\n\n");
		puts("\t\t\t\t\t\t      1. Bentuk Tabel");
		puts("\t\t\t\t\t\t      2. Bentuk List");
		puts("\t\t\t\t\t\t      3. Kembali ke Main Menu");
		printf("\n\t\t\t\t\t>>>------------------------------------------<<<\n\n");
		printf("\t\t\t\t\t\t      Masukkan Pilihan: ");
		fflush(stdin);
		scanf("%c", &choice);
		if(choice=='1'){
			PrintQueue(Q);
		}else if(choice=='2'){
			PrintFormat(Q);
		}
	}while(choice!='3');
}

/* Deskripsi : Modul untuk memanggil data pendaftar
   Autor : Anna K
*/

void panggilPendaftar(Queue *myQueue, int *checkpoints){
	//Deklarasi
	data temp;
	temp.prioritas = 6;
	
	//Mengeluarkan antrian
	deQueue(myQueue, &temp);
	if(temp.prioritas>5){
		puts("\t\t\t\t\tPendaftar masih kosong!");
	}else{
		puts("\t\t\t\t\t~~Memanggil Antrian~~");
		printf("\t\t\t\t\tNama : %s\n", temp.nama);
		printPenyakit(temp);
		*checkpoints = temp.WaktuSelesai;
	}
	printf("\n\t\t\t\t\tPress any key to continue.. ");
	getch();
}

/* Deskripsi : Modul untuk menampilkan data help 
   Autor : Anna K
*/

void help(){
	char pilih='0';
	char a='0';
	do{
		system("cls");
		printf("\n\t\t\t\t    ||||~QUEENPET~||||");
		printf("\n\n\t\t\t\t\t  |Help|");
		printf("\n\n\t\t\t\t>>>---------------------<<<\n\n");
		printf("\t\t\t\t1. Aturan Prioritas \n");
		printf("\t\t\t\t2. Daftar Penyakit \n");
		printf("\t\t\t\t3. Exit \n");
		printf("\n\t\t\t\t>>>---------------------<<<\n\n");
		printf("\n Enter Menu : ");
		fflush(stdin);
	    scanf("%c",&pilih);
	    if ( pilih == '1' ){
	    	system("cls");
	    	printf("\n\t\t\t\t    ||||~QUEENPET~||||");
			printf("\n\n\t\t\t\t |Help - Aturan Prioritas|");
			printf("\n\n\t\t\t\t>>>---------------------<<<\n\n");
			printf("\t\t\t\tParameter urutan prioritas \n");
			printf("\t\t\t\tditentukan dengan nilai \n");
			printf("\t\t\t\tsebagai berikut :\n");
			printf("\t\t\t\t1. Memiliki salah satu\n");
			printf("\t\t\t\t   penyakit berat - 4 \n");
			printf("\t\t\t\t2. Memiliki minimal 2 buah\n");
			printf("\t\t\t\t   penyakit sedang - 3\n");
			printf("\t\t\t\t3. Memiliki minimal 3 buah\n");
			printf("\t\t\t\t   penyakit ringan - 2 \n");
			printf("\t\t\t\t4. Waktu kedatangan - 1\n");
			printf("\n type anything to return : ");
			fflush(stdin);
	    	scanf("%c",&a);
			printf("\n\t\t\t\t>>>---------------------<<<\n\n");
		}else if ( pilih == '2' ){
			system("cls");
	    	printf("\n\t\t\t\t    ||||~QUEENPET~||||");
			printf("\n\n\t\t\t\t~|Help - Daftar Penyakit|~");
			printf("\n\n\t\t\t\t>>>---------------------<<<\n\n");
			printf("\t\t\t\t1. Ringan : penyakit kulit,\n");
			printf("\t\t\t\t   luka ringan, bersin\n");
			printf("\t\t\t\t2. Sedang : cacingan, diare, \n");
			printf("\t\t\t\t   luka dalam\n");
			printf("\t\t\t\t3. Berat : gangguan \n");
			printf("\t\t\t\t   kerongkongan yang  \n");
			printf("\t\t\t\t   mengeluarkan lendir yang \n");
			printf("\t\t\t\t   berbau busuk, kuning, \n");
			printf("\t\t\t\t   terkena virus\n");
			printf("\n\t\t\t\t>>>---------------------<<<\n\n");
			printf("\n type anything to return : ");
			fflush(stdin);
	    	scanf("%c",&a);
	    }
	}while(pilih != '3');
}

/* Deskripsi : Modul untuk menampilkan data Credit
   Autor : hasanah
*/

void credit(){
	char kembali='0';
	system("cls");
	do{
		printf("\n\t\t\t\t    ||||~QUEENPET~||||");
		printf("\n\n\t\t\t\t\t~|Credits|~");
		printf("\n\n\t\t\t\t>>>---------------------<<<\n\n");
		printf("\t\t\t\t Anna Kurniaty \n");
		printf("\t\t\t\t Dimas Wisnu Saputro \n");
		printf("\t\t\t\t Hasanah \n\n");
		printf("\t\t\t\t D4 - Teknik Informatika \n");
		printf("\t\t\t\t JTK 2020 \n");
		printf("\n\t\t\t\t>>>---------------------<<<\n\n");
		printf("\n Type 1 if you want to return to the menu : ");
	    scanf("%s",&kembali);
		}
	while(kembali != '1');
}


/* 
	Deskripsi : Modul untuk menentukan kategori suatu pasien
	Autor : Dimas W S
*/

int KlasifikasiKategori(char temp[10][255]){
	int i;
	//Jika ada penyakit dengan kategori berat akan mengembalikan angka 1
	for(i=0; i<10; i++){
		if(strcmp(temp[i],"Kosong")==0){
			break;
		}
		if(strcmp(temp[i],"gangguan kerongkongan")==0){
			return 1;
		}else if(strcmp(temp[i],"kuning")==0){
			return 1;
		}else if(strcmp(temp[i],"terkena virus")==0){
			return 1;
		}	
	}
	
	//Jika ada penyakit dengan kategori sedang akan mengembalikan angka 2
	for(i=0; i<10; i++){
		if(strcmp(temp[i],"Kosong")==0){
			break;
		}
		if(strcmp(temp[i],"cacingan")==0){
			return 2;
		}else if(strcmp(temp[i],"diare")==0){
			return 2;
		}else if(strcmp(temp[i],"luka dalam")==0){
			return 2;
		}
	}
	//Jika tidak ada penyakit dengan kategori berat maupun sedang akan mengembalikan angka 3
	return 3;
}

/* 
	Deskripsi : Modul untuk mengurutkan queue berdasarkan prioritas
	Autor : Dimas W S
*/

void sort(Queue *Q){
	//Kamus Data
	NodeQueue *p, *buff, *first;
	data temp;
	int i;
	
	//Algoritma
	p = Q->Front;
	
	//Jika antrian kosong atau hanya memiliki satu elemen, maka modul sort tidak dijalankan
	if(p==NULL || p->next==NULL){
 		return;
	}
	first = p;//1
	p = p->next;//2
	
	while(p->next!=NULL){
		buff = p->next;//3
		while(buff!=NULL){
			//Jika Waktu Selesai pasien 1 dan 2 lebih dari waktu kedatangan pasien 3, maka bisa terjadi penukaran
			if(p->info.WaktuSelesai > buff->info.waktuKedatangan && first->info.WaktuSelesai > buff->info.waktuKedatangan){
				if(p->info.prioritas < buff->info.prioritas){
					temp = p->info;
					p->info = buff->info;
					buff->info = temp;
				}else if(p->info.prioritas == buff->info.prioritas){
					if(p->info.waktuKedatangan > buff->info.waktuKedatangan){
						temp = p->info;
						p->info = buff->info;
						buff->info = temp;
					}
				}
			}
			buff = buff->next;
		}
		first = first->next;
		p = p->next; 
	}
}

/* 
	Deskripsi : Modul ini berfungsi untuk menghitung waktu mulai pemeriksaan hingga waktu selesai pasien
	Autor : Dimas W S
*/

void set(Queue *Q, int checkpoints){
	//Kamus Data
	NodeQueue *p, *buff;
	data temp;
	
	//Algoritma
	p = Q->Front;
	
	//Jika antrian kosong atau hanya memiliki satu elemen, maka modul set tidak dijalankan
	if(p==NULL || p->next==NULL){
 		return;
	}
	
	//Set Waktu mulai Pemeriksaan dan Waktu Selesai	pada elemen
	if(checkpoints==0){
		p->info.WaktuMulai = p->info.waktuKedatangan;
		p->info.WaktuSelesai = p->info.waktuKedatangan + p->info.WaktuPelayanan;	
	}else{
		if(checkpoints > p->info.waktuKedatangan){
			p->info.WaktuMulai = checkpoints;
			p->info.WaktuSelesai = checkpoints + p->info.WaktuPelayanan;
		}else{
			p->info.WaktuMulai = p->info.waktuKedatangan;
			p->info.WaktuSelesai = p->info.waktuKedatangan + p->info.WaktuPelayanan;
		}	
	}
	buff = p;
	p = p->next;
	while(p!=NULL){
		if(buff->info.WaktuSelesai > p->info.waktuKedatangan){
			p->info.WaktuMulai = buff->info.WaktuSelesai;
			p->info.WaktuSelesai = buff->info.WaktuSelesai + p->info.WaktuPelayanan;
		}else{
			p->info.WaktuMulai = p->info.waktuKedatangan;
			p->info.WaktuSelesai = p->info.waktuKedatangan + p->info.WaktuPelayanan;
		}
		buff = buff->next;
		p = p->next;
	}
}

/* 
	Deskripsi : Modul untuk menampilkan tampilan di main menu
	Autor : Anna K
*/

void header(){
	printf("\n\t\t\t\t__________________________________________");
	printf("\n\t\t\t\t|Selamat Datang pada Layanan Dokter Hewan|");
	printf("\n\t\t\t\t|               QUEENPET                 |");
	printf("\n\t\t\t\t|________________________________________|\n");
}

/* 
	Deskripsi : Modul untuk menjalankan program
	Autor : Hasanah

*/

int main(){
	char choice;
	int checkpoint = 0;
	Queue myQueue;
	CreateQueue(&myQueue);
	do{
		system("cls");
		header();
		printf("\n\t\t\t\t     _________________________________\n");
		printf("\t\t\t\t     |\t\t\t\t     |\n");
		printf("\t\t\t\t     |\tProgram Layanan Dokter Hewan |\n");
		printf("\t\t\t\t     |\t\t\t\t     |\n");
		printf("\t\t\t\t     |\t1. Tambah Pendaftar\t     |\n");
		printf("\t\t\t\t     |\t2. Tampilkan Pendaftar\t     |\n");
		printf("\t\t\t\t     |\t3. Panggil Pendaftar\t     |\n");
		printf("\t\t\t\t     |\t4. Help\t\t\t     |\n");
		printf("\t\t\t\t     |\t5. Credit\t\t     |\n");
		printf("\t\t\t\t     |\t6. Keluar\t\t     |\n");
		printf("\t\t\t\t     |_______________________________|\n");
		printf("\t\t\t\t\tMasukkan Pilihan: ");
		fflush(stdin);
		scanf("%c", &choice);
		if(choice=='1'){
			tambahPendaftar(&myQueue);
		}else if(choice=='2'){
			sort(&myQueue);
			set(&myQueue, checkpoint);
			tampilPendaftar(myQueue);	
		}else if(choice=='3'){
			panggilPendaftar(&myQueue, &checkpoint);
		}else if(choice=='4'){
			help();
		}else if(choice=='5'){
			credit();
		}
	}while(choice!='6');
	return 0;
}

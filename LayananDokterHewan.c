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

int HitungWaktuPelayanan(char temp[10][255]){
	int i;
	for(i=0; i<10; i++){
		if(strcmp(temp[i],"gangguan kerongkongan")==0){
			return 45;
		}else if(strcmp(temp[i],"kuning")==0){
			return 45;
		}else if(strcmp(temp[i],"terkena virus")==0){
			return 45;
		}
	}
	for(i=0; i<10; i++){
		if(strcmp(temp[i],"cacingan")==0){
			return 30;
		}else if(strcmp(temp[i],"diare")==0){
			return 30;
		}else if(strcmp(temp[i],"luka dalam")==0){
			return 30;
		}
	}
	
	return 15;
}

int HitungPrioritas(char temp[10][255]){
	int i;
	int tempSedang = 0;
	int tempRingan = 0;
	
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
	if(tempSedang>=2){
		return 3;
	}else if(tempRingan>=3){
		return 2;
	}
	return 1;
}


void tambahPendaftar(Queue *Q){
	//Kamus
	data customer;
	NodeQueue *p;
	int i;
	char temp;
	//Algoritma
	p = Q->Rear;
	
	//Input data antrian
	printf("Nama         : ");
	fflush(stdin);
	scanf("%[^\n]c", customer.nama);
	printf("Waktu Datang : ");
	scanf("%d", &customer.waktuKedatangan);
	
	for(i=0; i<10; i++){
		strcpy(customer.dataPenyakit[i],"Kosong");
	}
	
	for(i=0; i<10; i++){
		printf("Nama Penyakit %d : ", i+1);
		fflush(stdin);
		scanf("%[^\n]c", customer.dataPenyakit[i]);
		
		fflush(stdin);
		printf("Apakah ada penyakit lain? (y/n): ");
		scanf("%c", &temp);
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
	customer.prioritas = HitungPrioritas(customer.dataPenyakit);
	if(customer.WaktuPelayanan==45){
		strcpy(customer.kategoriPenyakit,"Berat"); 
	}else if(customer.WaktuPelayanan==30){
		strcpy(customer.kategoriPenyakit,"Sedang"); 
	}else{
		strcpy(customer.kategoriPenyakit,"Ringan"); 	
	}
			
	//Memasukkan ke antrian
	enQueue(Q,customer);
	
	printf("Press any key to continue.. ");
	getch();
}

void tampilPendaftar(Queue Q){
	char choice;
	
	do{
		system("cls");
		puts("Tampil Pendaftar");
		puts("1. Bentuk Tabel");
		puts("2. Bentuk List");
		puts("3. Kembali ke Main Menu");
		printf("Masukkan Pilihan: ");
		fflush(stdin);
		scanf("%c", &choice);
		if(choice=='1'){
			PrintQueue(Q);
		}else if(choice=='2'){
			PrintFormat(Q);
		}
	}while(choice!='3');
}

void panggilPendaftar(Queue *myQueue, int *checkpoints){
	data temp;
	temp.prioritas = 6;
	deQueue(myQueue, &temp);
	if(temp.prioritas>5){
		puts("Pendaftar masih kosong!");
	}else{
		puts("~~Memanggil Antrian~~");
		printf("Nama : %s\n", temp.nama);
		printPenyakit(temp);
		*checkpoints = temp.WaktuSelesai;
	}
	printf("\nPress any key to continue.. ");
	getch();
}

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
	    scanf("%s",&pilih);
	    if ( pilih == '1' ){
	    	system("cls");
	    	printf("\n\t\t\t\t    ||||~QUEENPET~||||");
			printf("\n\n\t\t\t\t  |Help - Aturan Prioritas|");
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
	    	scanf("%s",&a);
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
	    	scanf("%s",&a);
	    }
	}while(pilih != '3');
}

void credit(){
	char kembali='0';
	system("cls");
	do{
		printf("\n\t\t\t\t|~|~|~|~TIC TAC TOE~|~|~|~|");
		printf("\n\n\t\t\t\t\t~|Credits|~");
		printf("\n\n\t\t\t\t>>>---------------------<<<\n\n");
		printf("\t\t\t\t Anna Kurniaty \n");
		printf("\t\t\t\t Dimas Wisnu Saputro \n\n");
		printf("\t\t\t\t Hasanah \n\n");
		printf("\t\t\t\t D4 - Teknik Informatika \n");
		printf("\t\t\t\t JTK 2020 \n");
		printf("\n\t\t\t\t>>>---------------------<<<\n\n");
		printf("\n Type 1 if you want to return to the menu : ");
	    scanf("%s",&kembali);
		}
	while(kembali != '1');
}

void sort(Queue *Q){
	//Kamus Data
	NodeQueue *p, *buff;
	data temp;
	int i;
	
	//Algoritma
	p = Q->Front;
	if(p==NULL || p->next==NULL){
 		return;
	}
	p = p->next;
	while(p->next!=NULL){
		buff = p->next;
		while(buff!=NULL){
			if(p->info.WaktuSelesai > buff->info.waktuKedatangan){
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
		p = p->next; 
	}
}

void set(Queue *Q, int checkpoints){
	//Kamus Data
	NodeQueue *p, *buff;
	data temp;
	
	p = Q->Front;
	if(p==NULL || p->next==NULL){
 		return;
	}
	
	//Set Waktu mulai Pemeriksaan dan Waktu Selesai; 	
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


int main(){
	char choice;
	int checkpoint = 0;
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

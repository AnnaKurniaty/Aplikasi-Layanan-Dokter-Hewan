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
void panggilPendaftar(Queue *myQueue);
void help();
void credit();
void set(Queue *Q);
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
		}else if(strcmp(temp[i],"cacingan")==0){
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
	
	//Algoritma
	p = Q->Rear;
	
	//Input data antrian
	printf("Nama         : ");
	fflush(stdin);
	scanf("%[^\n]c", customer.nama);
	printf("Waktu Datang : ");
	scanf("%d", &customer.waktuKedatangan);
	int i;
	char temp;
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
		customer.WaktuMulai = 0;
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
	//Memasukkan ke antrian
	enQueue(Q,customer);
	
	printf("Press any key to continue.. ");
	getch();
}

void tampilPendaftar(Queue Q){
	PrintQueue(Q);
}

void panggilPendaftar(Queue *myQueue){
	
}

void help(){
	help();
}

void credit(){
	credit();
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

void set(Queue *Q){
	
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
			sort(&myQueue);
			set(&myQueue);
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

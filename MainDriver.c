#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "queue.c"
#include "LayananDokterHewan.h"
#include "LayananDokterHewan.c"

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

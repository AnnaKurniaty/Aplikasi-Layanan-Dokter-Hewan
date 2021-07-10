#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void tambahPendaftar(Queue *myQueue){
	
}

void tampilPendaftar(Queue myQueue){
	
}

void panggilPendaftar(Queue *myQueue){
	
}

void about(){
	
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
		printf("4. About\n");
		printf("5. Keluar\n");
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
			about();
		}
	}while(choice!='5');
	return 0;
}

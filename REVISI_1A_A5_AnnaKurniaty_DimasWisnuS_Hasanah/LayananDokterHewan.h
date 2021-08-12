
#ifndef LAYANANDOKTERHEWAN_H
#define LAYANANDOKTERHEWAN_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define KULIT "penyakit kulit"
#define LURING "luka ringan"
#define BERSIN "bersin"
#define CACINGAN "cacingan"
#define DIARE "diare"
#define LUDAM "luka dalam"
#define KERONGKONGAN "gangguan kerongkongan"
#define KUNING "kuning"
#define VIRUS "terkena virus"

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

#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_DATA 100000000

// Struktur data untuk menyimpan informasi barang
typedef struct {
    char nama[50];
    int jumlah;
    int harga;
} Barang;

// Daftar barang
Barang *album;
Barang *merchandise;
int jumlahAlbum = NUM_DATA;
int jumlahMerchandise = NUM_DATA;
unsigned long long totalAlbum = 0;
unsigned long long totalMerchandise = 0;
int i;

void inputData() {
    album = (Barang*)malloc(jumlahAlbum * sizeof(Barang));
    merchandise = (Barang*)malloc(jumlahMerchandise * sizeof(Barang));

    for (i = 0; i < jumlahAlbum; i++) {
        snprintf(album[i].nama, sizeof(album[i].nama), "Album %d", i+1);
        album[i].jumlah = rand() % 100 + 1;
        album[i].harga = rand() % 100000 + 5000;
    }

    for (i = 0; i < jumlahMerchandise; i++) {
        snprintf(merchandise[i].nama, sizeof(merchandise[i].nama), "Merchandise %d", i+1);
        merchandise[i].jumlah = rand() % 100 + 1;
        merchandise[i].harga = rand() % 50000 + 2000;
    }
}


int main() {
	
	srand(time(NULL)); // Inisialisasi seed untuk fungsi rand

    inputData();

    clock_t start = clock();

    // Menghitung total biaya album
    for (i = 0; i < jumlahAlbum; i++) {
        unsigned long long biayaAlbum = (unsigned long long)album[i].jumlah * album[i].harga;
        if (biayaAlbum > 0) {
            totalAlbum += biayaAlbum;
        }
    }

    // Menghitung total biaya merchandise
    for (i = 0; i < jumlahMerchandise; i++) {
        unsigned long long biayaMerchandise = (unsigned long long)merchandise[i].jumlah * merchandise[i].harga;
        if (biayaMerchandise > 0) {
            totalMerchandise += biayaMerchandise;
        }
    }

    clock_t end = clock();
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    // Menampilkan hasil
    printf("Nama Album Terakhir: %s\n", album[jumlahAlbum-1].nama);
    printf("Nama Merchandise Terakhir: %s\n", merchandise[jumlahMerchandise-1].nama);
    printf("Total Biaya Album: Rp%llu\n", totalAlbum);
    printf("Total Biaya Merchandise: Rp%llu\n", totalMerchandise);
    printf("Total Biaya: Rp%llu\n", totalAlbum + totalMerchandise);
    printf("Waktu Eksekusi: %f detik\n", time_taken);

    free(album);
    free(merchandise);

    return 0;
}


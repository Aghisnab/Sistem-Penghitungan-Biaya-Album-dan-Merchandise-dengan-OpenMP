#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define NUM_DATA 1000

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
long long int totalAlbum = 0;
long long int totalMerchandise = 0;
int i;

void inputData() {
    album = (Barang*)malloc(jumlahAlbum * sizeof(Barang));
    merchandise = (Barang*)malloc(jumlahMerchandise * sizeof(Barang));

    #pragma omp parallel for
    for (i = 0; i < jumlahAlbum; i++) {
        snprintf(album[i].nama, sizeof(album[i].nama), "Album %d", i+1);
        album[i].jumlah = rand() % 100 + 1;
        album[i].harga = rand() % 100000 + 5000;
    }

    #pragma omp parallel for
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

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            // Menghitung total biaya album
            long long int localTotalAlbum = 0;
            #pragma omp parallel for reduction(+:localTotalAlbum)
            for (i = 0; i < jumlahAlbum; i++) {
                long long int biaya = (long long int)album[i].jumlah * (long long int)album[i].harga;
                if (biaya < 0) biaya = 0; // Pastikan biaya tidak negatif
                localTotalAlbum += biaya;
            }
            #pragma omp critical
            totalAlbum += localTotalAlbum;
        }

        #pragma omp section
        {
            // Menghitung total biaya merchandise
            long long int localTotalMerchandise = 0;
            #pragma omp parallel for reduction(+:localTotalMerchandise)
            for (i = 0; i < jumlahMerchandise; i++) {
                long long int biaya = (long long int)merchandise[i].jumlah * (long long int)merchandise[i].harga;
                if (biaya < 0) biaya = 0; // Pastikan biaya tidak negatif
                localTotalMerchandise += biaya;
            }
            #pragma omp critical
            totalMerchandise += localTotalMerchandise;
        }
    }

    clock_t end = clock();
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    // Menampilkan hasil
    printf("Nama Album Terakhir: %s\n", album[jumlahAlbum-1].nama);
    printf("Nama Merchandise Terakhir: %s\n", merchandise[jumlahMerchandise-1].nama);
    printf("Total Biaya Album: Rp%lld\n", totalAlbum);
    printf("Total Biaya Merchandise: Rp%lld\n", totalMerchandise);
    printf("Total Biaya: Rp%lld\n", totalAlbum + totalMerchandise);
    printf("Waktu Eksekusi: %f detik\n", time_taken);

    free(album);
    free(merchandise);

    return 0;
}

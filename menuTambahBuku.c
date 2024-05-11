#include <stdio.h>
#include <string.h>

#define MAX_JUDUL 30
#define MAX_PENULIS 25
#define MAX_PENERBIT 20

typedef struct {
    unsigned int id;
    char judul[MAX_JUDUL + 1];
    char penulis[MAX_PENULIS + 1];
    char penerbit[MAX_PENERBIT + 1];
    unsigned int halaman;
    unsigned int tahun;
    unsigned int stok;
} Buku;

int cariID(FILE *file, unsigned int id) {
    Buku buku;
    int found = 0;
    rewind(file);
    while (fscanf(file, "%u \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" %u %u %u\n", &buku.id, buku.judul, buku.penulis, buku.penerbit, &buku.halaman, &buku.tahun, &buku.stok) != EOF) {
        if (buku.id == id) {
            found = 1;
            break;
        }
    }
    return found;
}

int main() {
    char pilihan;
    Buku buku;
    FILE *file = fopen("daftar_buku.txt", "r+");

    do {
        printf("Apakah anda ingin menambahkan buku? (y/n) ");
        scanf(" %c", &pilihan);
        getchar();

        if (pilihan == 'y') {
            printf("\nMasukkan Pilihan [yes/no] : y\n\n");
            printf("// input setiap data\n");
            printf("ID Buku: ");
            scanf("%u", &buku.id);
            getchar();

            if (cariID(file, buku.id)) {
                printf("ID buku telah digunakan: \n\n");
                rewind(file);
                fscanf(file, "%u \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" %u %u %u\n", &buku.id, buku.judul, buku.penulis, buku.penerbit, &buku.halaman, &buku.tahun, &buku.stok);
                printf("ID Buku\t\t: %u\nJudul Buku\t: %s\nPenulis\t\t: %s\nPenerbit\t: %s\nJumlah Halaman\t: %u\nTahun Terbit\t: %u\nStok Buku\t: %u\n\n", buku.id, buku.judul, buku.penulis, buku.penerbit, buku.halaman, buku.tahun, buku.stok);
                printf("(Buku Gagal ditambahkan)\n\n");
            } else {
                printf("Judul Buku: ");
                fgets(buku.judul, MAX_JUDUL + 1, stdin);
                buku.judul[strcspn(buku.judul, "\n")] = '\0';

                printf("Penulis: ");
                fgets(buku.penulis, MAX_PENULIS + 1, stdin);
                buku.penulis[strcspn(buku.penulis, "\n")] = '\0';

                printf("Penerbit: ");
                fgets(buku.penerbit, MAX_PENERBIT + 1, stdin);
                buku.penerbit[strcspn(buku.penerbit, "\n")] = '\0';

                printf("Jumlah Halaman: ");
                scanf("%u", &buku.halaman);
                getchar();

                printf("Tahun Terbit: ");
                scanf("%u", &buku.tahun);
                getchar();

                printf("Stok Buku: ");
                scanf("%u", &buku.stok);
                getchar();

                fprintf(file, "%u \"%s\" \"%s\" \"%s\" %u %u %u\n", buku.id, buku.judul, buku.penulis, buku.penerbit, buku.halaman, buku.tahun, buku.stok);
                printf("\n(Buku Berhasil ditambahkan)\n\n");
            }
        }
    } while (pilihan == 'y');

    fclose(file);
    return 0;
}
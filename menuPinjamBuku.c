#include <stdio.h>
#include <string.h>

struct Buku {
    int id;
    char judul[40];
    char penulis[30];
    char penerbit[20];
    unsigned int jmlHal;
    unsigned int tahun;
    unsigned int stok;
};
//menampilkan daftar buku yang tersedia 
void pinjamBuku(struct Buku *daftarBuku, int id, int jumlahBuku) {
    for (int i = 0; i < jumlahBuku; i++) {
        if (daftarBuku[i].id == id) {
            if (daftarBuku[i].stok > 0)
            
                //mendapatkan id buku dari pengguna
            {
                printf("Buku tersedia. Data buku:\n");
                printf("ID Buku: %d\n", daftarBuku[i].id);
                printf("Judul: %s\n", daftarBuku[i].judul);
                printf("Penulis: %s\n", daftarBuku[i].penulis);
                printf("Penerbit: %s\n", daftarBuku[i].penerbit);
                printf("Jumlah Halaman: %d\n", daftarBuku[i].jmlHal);
                printf("Tahun Terbit: %d\n", daftarBuku[i].tahun);

                //memeriksa ketersediaan buku dan mengurangi jumlah buku
                daftarBuku[i].stok--;
                printf("Apakah anda yakin ingin meminjam buku ini? [y/n] : ");
                char jawaban[5];
                scanf("%s", jawaban);
                if (strcmp(jawaban, "y") == 0) {
                    FILE *file = fopen("namaUser_book.txt", "a");
                    fprintf(file, "ID Buku: %d, Judul: %s, Penulis: %s, Penerbit: %s\n", daftarBuku[i].id, daftarBuku[i].judul, daftarBuku[i].penulis, daftarBuku[i].penerbit);
                    fclose(file);
                    printf("Buku berhasil dipinjam\n");
                }
                printf("Ingin meminjam buku lagi? [y/n] : ");
                char lagi[5];
                scanf("%s", lagi);
                if (strcmp(lagi, "y") == 0) {
                    printf("Masukkan ID Buku yang ingin dipinjam: ");
                    int idBaru;
                    scanf("%d", &idBaru);
                    pinjamBuku(daftarBuku, idBaru, jumlahBuku);
                }
            } else {
                printf("Stok buku yang dipinjam habis\n");
            }
            return;
        }
    }
    printf("Buku tidak ditemukan\n");
}

int main() {
    struct Buku daftarBuku[100]; // asumsi maksimal 100 buku
    // inisialisasi daftar buku dari file teks "daftar_buku.txt"
    int jumlahBuku = 10; // contoh jumlah buku
    char lagi[5] = "y";
    while (strcmp(lagi, "y") == 0) {
        int id;
        printf("Masukkan ID Buku yang ingin dipinjam: ");
        scanf("%d", &id);
        pinjamBuku(daftarBuku, id, jumlahBuku);
        printf("Ingin meminjam buku lagi? [y/n] : ");
        scanf("%s", lagi);
    }
    return 0;
}





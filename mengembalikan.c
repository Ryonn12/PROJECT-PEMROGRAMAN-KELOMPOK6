#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Buku {
  char idBuku[10];
  char judulBuku[100];
  char penulis[50];
  char penerbit[50];
  int jumlahHalaman;
  int tahunTerbit;
} Buku;

void bacaDaftarBuku(Buku *daftarBuku, int *nBuku);
void tampilkanDaftarBukuDipinjam(Buku *daftarBuku, int nBuku);
void kembalikanBuku(Buku *daftarBuku, int *nBuku);
void simpanDaftarBuku(Buku *daftarBuku, int nBuku);

int main() {
  Buku daftarBuku[100];
  int nBuku = 0;

  // Membaca daftar buku dari file teks
  bacaDaftarBuku(daftarBuku, &nBuku);

  // Menampilkan daftar buku yang dipinjam
  tampilkanDaftarBukuDipinjam(daftarBuku, nBuku);

  // Mengembalikan buku
  kembalikanBuku(daftarBuku, &nBuku);

  // Menyimpan daftar buku yang diperbarui ke file teks
  simpanDaftarBuku(daftarBuku, nBuku);

  return 0;
}

void bacaDaftarBuku(Buku *daftarBuku, int *nBuku) {
  // Membuka file teks dalam mode baca
  FILE *fp = fopen("data/daftar buku dipinjam.txt", "r");
  if (fp == NULL) {
    printf("Gagal membuka file daftarBuku.txt\n");
    return;
  }

  // Membaca data buku dari file teks
  while (fscanf(fp, "%s %s %s %s %d %d", daftarBuku[*nBuku].idBuku, daftarBuku[*nBuku].judulBuku, daftarBuku[*nBuku].penulis, daftarBuku[*nBuku].penerbit, &daftarBuku[*nBuku].jumlahHalaman, &daftarBuku[*nBuku].tahunTerbit) != EOF) {
    *nBuku = *nBuku + 1;
  }

  // Menutup file teks
  fclose(fp);
}

void tampilkanDaftarBukuDipinjam(Buku *daftarBuku, int nBuku) {
  if (nBuku == 0) {
    printf("Tidak ada buku yang dipinjam.\n");
    return;
  }

  printf("\nDaftar Buku yang Dipinjam:\n");
  for (int i = 0; i < nBuku; i++) {
    printf("ID Buku: %s\n", daftarBuku[i].idBuku);
    printf("Judul Buku: %s\n", daftarBuku[i].judulBuku);
    printf("Penulis: %s\n", daftarBuku[i].penulis);
    printf("Penerbit: %s\n", daftarBuku[i].penerbit);
    printf("Jumlah Halaman: %d\n", daftarBuku[i].jumlahHalaman);
    printf("Tahun Terbit: %d\n\n", daftarBuku[i].tahunTerbit);
  }
}

void kembalikanBuku(Buku *daftarBuku, int *nBuku) {
  char idBuku[10];

  printf("\nMasukkan ID Buku yang Ingin Dikembalikan: ");
  scanf("%s", idBuku);

  int i = 0;
  for (; i < *nBuku && strcmp(daftarBuku[i].idBuku, idBuku) != 0; i++);

  if (i == *nBuku) {
    printf("ID Buku tidak ditemukan.\n");
    return;
  }

  // Memindahkan data buku yang tersisa
  for (; i < *nBuku - 1; i++) {
    daftarBuku[i] = daftarBuku[i + 1];
  }

  *nBuku = *nBuku - 1;

  printf("Buku dengan ID %s telah dikembalikan.\n", idBuku);
}

void simpanDaftarBuku(Buku *daftarBuku, int nBuku) {
  // Membuka file teks dalam mode tulis, tambahkan "a" untuk append
  FILE *fp = fopen("data/daftar buku dipinjam.txt", "a");
  if (fp == NULL) {
    printf("Gagal membuka file daftarBuku.txt\n");
    return;
  }

  // Menulis data buku ke file teks, ubah menjadi fputs untuk string
  for (int i = 0; i < nBuku; i++) {
    fprintf(fp, "%s %s %s %s %d %d\n", daftarBuku[i].idBuku, daftarBuku[i].judulBuku, daftarBuku[i].penulis, daftarBuku[i].penerbit, daftarBuku[i].jumlahHalaman, daftarBuku[i].tahunTerbit);
  }

  // Menutup file teks
  fclose(fp);
}
void kembalikanBuku(Buku *daftarBuku, int *nBuku) {
  char idBuku[10];
  int pilihan;

  do {
    printf("\nMasukkan ID Buku yang Ingin Dikembalikan: ");
    scanf("%s", idBuku);

    int i = 0;
    for (; i < *nBuku && strcmp(daftarBuku[i].idBuku, idBuku) != 0; i++);

    if (i == *nBuku) {
      printf("ID Buku tidak ditemukan.\n");
      continue;
    }

    printf("\nBuku dengan ID %s ditemukan.\n", idBuku);
    printf("Apakah Anda yakin ingin mengembalikan buku ini? (1: Ya, 0: Tidak): ");
    scanf("%d", &pilihan);

    if (pilihan == 1) {
      // Memindahkan data buku yang tersisa
      for (; i < *nBuku - 1; i++) {
        daftarBuku[i] = daftarBuku[i + 1];
      }

      *nBuku = *nBuku - 1;

      printf("Berhasil mengembalikan buku.\n");
      break; // Keluar dari loop do-while
    } else {
      printf("Pengembalian buku dibatalkan.\n");
    }
  } while (1); // Loop do-while berulang sampai pengguna memilih untuk keluar

  printf("\nIngin mengembalikan buku lagi? (1: Ya, 0: Tidak): ");
  scanf("%d", &pilihan);

  if (pilihan == 1) {
    kembalikanBuku(daftarBuku, nBuku); // Memanggil fungsi kembali untuk mengembalikan buku lain
  } else {
    printf("Terima kasih.\n");
  }
}
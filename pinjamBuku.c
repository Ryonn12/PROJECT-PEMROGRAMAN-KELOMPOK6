#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dataBuku {
  unsigned int id;
  char judul[40];
  char penulis[30];
  char penerbit[20];
  unsigned int jmlHal;
  unsigned int tahun;
  unsigned int stok;
} buku;

void pinjam(void){}

int main(){
    pinjam();
    return 0;
}

  void pinjam(void){}

int pinjamBuku(int userId) {
  
  // 1. Memuat data buku dari file
  struct dataBuku* buku = loadBukuData();
  int jumlahBuku = getJumlahBuku(); // Asumsikan fungsi ini ada di data.c

  // 2. Menampilkan daftar buku yang tersedia
  printf("\nDaftar Buku yang Tersedia:\n");
  for (int i = 0; i < jumlahBuku; i++) {
    if (buku[i].stok> 0) {
      printf("  - ID: %d, Judul: %s\n", buku[i].id, buku[i].judul);
    }
  }

  // 3. Mendapatkan ID buku dari pengguna
  int pinjamID;
  printf("\nMasukkan ID buku yang ingin dipinjam: ");
  scanf("%d", &pinjamID);

  // 4. Memeriksa ketersediaan buku
  int ditemukan = 0;
  for (int i = 0; i < jumlahBuku; i++) {
    if (buku[i].id == pinjamID && buku[i].stok > 0) {
      ditemukan = 1;
      buku[i].stok--; // Mengurangi jumlah yang tersedia
      break;
    }
  }

  // 5. Menangani ketersediaan buku
  if (ditemukan) {
    // Mencatat data peminjaman (panggil fungsi untuk menulis ke peminjaman.txt)
    printf("\nBuku berhasil dipinjam!\n");
    recordPeminjaman(userId, pinjamID); // Asumsikan fungsi ini ada
  } else {
    printf("\nMaaf, buku tidak tersedia atau jumlah stok tidak mencukupi.\n");
  }

  // 6. Membebaskan memori yang dialokasikan untuk buku (jika berlaku)
  free(buku);
  return 0;
}

void recordPeminjaman(int userId, int bukuId) {
  // Membuka peminjaman.txt untuk menambahkan data
  FILE* pinjamFile = fopen("peminjaman.txt", "a");
  if (pinjamFile == NULL) {
    printf("Gagal membuka file peminjaman.txt\n");
    return;
  }

  // Mendapatkan tanggal saat ini (implementasikan logika tanggal)
  char tanggalPinjam[20]; // Placeholder untuk string tanggal (logika untuk mendapatkan tanggal saat ini)
  

  // Menulis data ke file (userId, bukuId, tanggalPinjam)
  fprintf(pinjamFile, "%d %d %s\n", userId, bukuId, tanggalPinjam);

  fclose(pinjamFile);
  printf("Data peminjaman berhasil dicatat.\n");
}


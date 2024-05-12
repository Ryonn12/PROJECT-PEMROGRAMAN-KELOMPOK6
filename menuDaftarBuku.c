#include"header.h"

int menuDaftarBuku(char *fileStream, char *fileStream2, char *fileStream3, char *userName, int role){
    dataBuku buku[N], bukuPinjam[N], record[N];
    int numbOption;

    enum role{ADMIN=0, USER};
    if(role==ADMIN){
        while(1){
            clearScreen();
            pathLoc(" Menu Admin\\Daftar Buku>");
            movePos(0,5);
            printf("   (1) Daftar buku perpustakaan\n");
            printf("   (2) Daftar buku yang sedang dipinjam user\n");
            printf("   (3) Riwayat peminjaman buku\n");
            printf("   (4) Kembali\n\n");
            printf("       Masukkan pilihan : ");
            numbOption = getOptionNumb();
            if(numbOption==1){
                daftarBuku(buku, fileStream, role);   // fungsi menampilkah buku perpustakaan
            } else if(numbOption==2){
                daftarBukuPinjam(bukuPinjam, fileStream2);  // fungsi menampilkan buku yg sedang dipinjam user
            } else if(numbOption==3){
                daftarRecordPinjam(record, fileStream3);    // fungsi menapilkan riwayat semua peminjaman
            } else if(numbOption==4){
                break;
            } else{
                printf("\n      (Input tidak valid, masukkan input ulang)\n\n   ");
                getEnterKey();
            }
        }

    } else if(role==USER){
            daftarBuku(buku, fileStream, 1); // fungsi menampilkan buku perpustakaan
        }


clearScreen();
}

void daftarBuku(dataBuku *buku, char *fileStream, int role){
    clearScreen();
    int jmlData = 0;
    int jmlBuku = 0;
    char *ifp = fileStream;
    jmlData = countData(ifp);       // menghitung data pada file
    
    if(jmlData>N){
        jmlData = N;
    }
    
    loadData(buku, ifp, jmlData);   // inisialisasi data

    for(int i=0; i<jmlData; i++){
        jmlBuku += buku[i].stok; 
    }

    char ch;
    int page = 1;
    int jmlPage = 0;
    int temp = jmlData;
    if(jmlBuku<=N){                         // menghitung jumlah page pada daftar buku
        for (int i = 1; temp > 0; i++){         
            temp -= 20;
            jmlPage++;
        }
    } 
    if(jmlBuku>N){
        for (int i = 1; temp > 0; i++){         
            temp -= 20;
            jmlPage++;
        }
    }
    
    if(jmlData!=0){
        while(1){
            clearScreen();
            hidCurs(1);
            bookTable(role);
            movePos(65,5);
            printf("< P A G E  %d >", page);

            int ordinat=10;
            int batas = page*20;
            for(int i=batas- 20; i<batas; i++){

                textStyle(0);
                if(i%2 == 1){
                    textStyle(2);
                }

                if(i<=8){
                    movePos(3, ordinat);    //cetak nomor 1-9
                    printf("0%d", i+1);     
                } else{
                    movePos(3, ordinat);    //cetak nomor > 9
                    printf("%d", i+1);
                }
                
                // cetak data
                movePos(9, ordinat); printf("%u", buku[i].id);
                movePos(16, ordinat); printf("%s", buku[i].judul);
                movePos(55, ordinat); printf("%s", buku[i].penulis);
                movePos(83, ordinat); printf("%s", buku[i].penerbit);
                movePos(111, ordinat); printf("%u", buku[i].jmlHal);
                movePos(127, ordinat); printf("%u", buku[i].tahun);
                movePos(142, ordinat); printf("%u", buku[i].stok);
                ordinat++;
                if(i==jmlData-1){
                    break;
                }
            }

            textStyle(0);
            movePos(130,31);   
            printf("Jumlah Data : %d", jmlData);
            movePos(130,32);   
            printf("Jumlah Buku : %d", jmlBuku);
            movePos(139,35);
            printf("Page %d/%d", page, jmlPage);

            // navigasi halaman
            movePos(4,31);
            printf("(1) Pindah ke halaman sebelumnya");
            movePos(4,32);
            printf("(2) Pindah ke halaman selanjutnya");
            movePos(4,33);
            printf("(3) Kembali");
            movePos(8,35);
            printf("Masukkan Pilihan [1-3] : ");
            hidCurs(0);
            ch = getchar();
            if(ch == '2'){
                page++;             // pindah halaman ke depan
                if(page>jmlPage){
                    page=jmlPage;
                }
            } 
            if(ch == '1'){
                page--;             // pindah halaman ke belakang
                if(page<1){
                    page=1;
                }
            } 
            if (ch == '3'){
                break;
            }
            clearScreen();
        }
    }else if(jmlData<=0){
        printf("\n\n   (Tidak ditemukan data)\n\n");
        getEnterKey();
    }
    
    ignoreInputBuffer();
    movePos(0,0);
    clearScreen();
}

void daftarBukuPinjam(dataBuku *buku, char *fileStream){
    clearScreen();
    int jmlData=0;
    char *ifp = fileStream;
    jmlData = countData(ifp);   // menghitung data pada file

    if(jmlData>N){
        jmlData = N;
    }
    
    FILE *file = fopen(ifp, "r");
    if (file == NULL){
        printf("   Error reading file...\n");
        getchar();
    }

    char buffer[512];
    int i = 0;
    while (fgets(buffer, sizeof(buffer), file) && i < jmlData) {
        sscanf(buffer, "\"%20[^\"]\" %u \"%49[^\"]\" \"%20[^\"]\"  \"%20[^\"]\" \n", buku[i].userName, &buku[i].id, buku[i].judul, buku[i].tglPinjam, buku[i].tglKembali);
        i++;
    }
    fclose(file);

    char ch;
    int page = 1;
    int jmlPage = 0;
    int temp = jmlData;
    if(jmlData<=N){                         // menghitung jumlah page pada daftar buku
        for (int i = 1; temp > 0; i++){         
            temp -= 20;
            jmlPage++;
        }
    } 
    if(jmlData>N){
        for (int i = 1; temp > 0; i++){         
            temp -= 20;
            jmlPage++;
        }
    }

    if(jmlData!=0){
        while(1){
            clearScreen();
            pathLoc(" Menu Admin\\Daftar Buku\\Daftar buku yang sedang dipinjam user");
            hidCurs(1);
            tabelPeminjaman();
            movePos(65,5);
            printf("< P A G E  %d >", page);

            int ordinat=10;
            int batas = page*20;
            int numb =  (page*20-20)+1;
        
            for(int i=batas-20; i<batas; i++){
            
                    textStyle(0);
                    if(numb%2 == 0){
                        textStyle(2);
                    }
                    if(numb<10){
                        movePos(3, ordinat);    //cetak nomor 1-9
                        printf("0%d", numb);     
                    } else{
                        movePos(3, ordinat);    //cetak nomor > 9
                        printf("%d", numb);
                    }         
                    // cetak data
                    movePos(9, ordinat); printf("%u", buku[i].id);
                    movePos(17, ordinat); printf("%s", buku[i].judul);
                    movePos(65, ordinat); printf("%s", buku[i].userName);
                    movePos(89, ordinat); printf("%s", buku[i].tglPinjam);
                    movePos(122, ordinat); printf("%s", buku[i].tglKembali); 
                    ordinat++;
                    if(i==jmlData-1){
                        break;
                    }
                    numb++;
            }
        
            textStyle(0);
            movePos(130,31);   
            printf("Jumlah Data : %d", jmlData);
            movePos(139,35);
            printf("Page %d/%d", page, jmlPage);

            // navigasi halaman
            movePos(4,31);
            printf("(1) Pindah ke halaman sebelumnya");
            movePos(4,32);
            printf("(2) Pindah ke halaman selanjutnya");
            movePos(4,33);
            printf("(3) Kembali");
            movePos(8,35);
            printf("Masukkan Pilihan [1-3] : ");
            hidCurs(0);
            ch = getchar();
            if(ch == '2'){
                page++;             // pindah halaman ke depan
                if(page>jmlPage){
                    page=jmlPage;
                }
            } 
            if(ch == '1'){
                page--;             // pindah halaman ke belakang
                if(page<1){
                    page=1;
                }
            } 
            if (ch == '3'){
                break;
            }
            clearScreen();
        }
    }else if(jmlData<=0){
        printf("\n\n   (Tidak ditemukan data)\n\n");
        getEnterKey();
    }

    ignoreInputBuffer();
    movePos(0,0);
    clearScreen();
}

void daftarRecordPinjam(dataBuku *buku, char *fileStream){  
    clearScreen();
    int jmlData=0;
    char *ifp = fileStream;
    jmlData = countData(ifp);   // menghitung data pada file

    if(jmlData>N){
        jmlData = N;
    }
    
    FILE *file = fopen(ifp, "r");
    if (file == NULL){
        printf("   Error reading file...\n");
        getchar();
    }

    loadBukuPinjam(buku, ifp, jmlData);

    char ch;
    int page = 1;
    int jmlPage = 0;
    int temp = jmlData;
    if(jmlData<=N){                         // menghitung jumlah page pada daftar buku
        for (int i = 1; temp > 0; i++){         
            temp -= 20;
            jmlPage++;
        }
    } 
    if(jmlData>N){
        for (int i = 1; temp > 0; i++){         
            temp -= 20;
            jmlPage++;
        }
    }
    
    if(jmlData!=0){
        int numb;
        while(1){
            clearScreen();
            hidCurs(1);
            pathLoc(" Menu Admin\\Daftar Buku\\Riwayat Peminjaman Buku");
            tabelPeminjaman();
            movePos(65,5);
            printf("< P A G E  %d >", page);

            int ordinat=10;
            int batas = page*20;
            numb = (batas-20)+1;
            for(int i=batas-20; i<batas; i++){
                    textStyle(0);
                    if(numb%2 == 0){
                        textStyle(2);
                    }

                    if(numb<10){
                        movePos(3, ordinat);    //cetak nomor 1-9
                        printf("0%d", numb);     
                    } else{
                        movePos(3, ordinat);    //cetak nomor > 9
                        printf("%d", numb);
                    }
                    
                    // cetak data
                    movePos(9, ordinat); printf("%u", buku[i].id);
                    movePos(17, ordinat); printf("%s", buku[i].judul);
                    movePos(65, ordinat); printf("%s", buku[i].userName);
                    movePos(89, ordinat); printf("%s", buku[i].tglPinjam);
                    movePos(122, ordinat); printf("%s", buku[i].tglKembali); 
                    ordinat++;
                    if(i==jmlData-1){
                        break;
                }
                numb++;
            }
        
            textStyle(0);
            movePos(130,31);   
            printf("Jumlah Data : %d", jmlData);
            movePos(139,35);
            printf("Page %d/%d", page, jmlPage);

            // navigasi halaman
            movePos(4,31);
            printf("(1) Pindah ke halaman sebelumnya");
            movePos(4,32);
            printf("(2) Pindah ke halaman selanjutnya");
            movePos(4,33);
            printf("(3) Kembali");
            movePos(8,35);
            printf("Masukkan Pilihan [1-3] : ");
            hidCurs(0);
            ch = getchar();
            if(ch == '2'){
                page++;             // pindah halaman ke depan
                if(page>jmlPage){
                    page=jmlPage;
                }
            } 
            if(ch == '1'){
                page--;             // pindah halaman ke belakang
                if(page<1){
                    page=1;
                }
            } 
            if (ch == '3'){
                break;
            }
            clearScreen();
        }
    }else if(jmlData<=0){
        printf("\n\n   (Tidak ditemukan data)\n\n");
        getEnterKey();
    }
    ignoreInputBuffer();
    movePos(0,0);
    clearScreen();
}

void tabelPeminjaman(void){
    
    for(int i=2; i<148;i++){   
        movePos(i, 7); printf("-");
        movePos(i,9); printf("-");
        movePos(i,30); printf("-");
    }

    //garis vertikal
    for(int i=8; i<30; i++){    
        movePos(0,i); printf("|");
        movePos(6,i); printf("|");
        movePos(15,i); printf("|");
        movePos(54,i); printf("|");
        movePos(82,i); printf("|");
        movePos(113,i); printf("|");
        movePos(150,i); printf("|");
    }

    // nama kolom
    int p=8;
    movePos(3, p); printf("NO");
    movePos(7, p); printf("ID Buku");
    movePos(27, p); printf("Judul Buku");
    movePos(64, p); printf("Peminjam");
    movePos(89, p); printf("Tanggal Peminjaman");
    movePos(121, p); printf("Tanggal Pengembalian");

}

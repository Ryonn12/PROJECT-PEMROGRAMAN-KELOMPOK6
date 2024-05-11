#include"header.h"

//menu pilihan untuk meminjam buku
int menuPinjamBuku(char *filestream, char *userName, char *filePinjam){
    dataBuku dBuku[N], bukuPinjam[M];
    char option;
    char dataPinjam[]= "userBook.txt";
    char *ifp = filestream;
    char *ofp = dataPinjam;

    int is_borrow, is_max;
    int jmlData = countData(ifp);
    int jmlBukuPinjam = countData(ofp);
    int maxPinjam = countBukuPinjam(ofp, userName);
    loadData(dBuku, ifp, jmlData);

    int id, is_continue;
    while(1){
        clearScreen();
        pathLoc("  Menu User/Pinjam Buku>");
        menuTitle(1);
        printf("  Apakah anda ingin meminjam buku? [y/n] : ");
        option = getOption();

        if(option == 'y'){

            label_is_continue:
            jmlBukuPinjam = countData(ofp);
            maxPinjam = countBukuPinjam(ofp, userName);
            loadBukuPinjam(bukuPinjam, ofp, jmlBukuPinjam);
            updateData(dBuku, ifp, jmlData, id);
            loadData(dBuku, ifp, jmlData);
            clearScreen();
            pathLoc("  Menu User/Pinjam Buku>");
            menuTitle(1);

            if(maxPinjam<5){ 
                printf("\n   Masukkan ID Buku yang ingin dipinjam : ");
                scanf("%d", &id);
                ignoreInputBuffer();
                int i;
                i = findID(dBuku, id, jmlData);
                        
                if(i != -1){
                    is_borrow = findBookID(bukuPinjam, ofp, jmlBukuPinjam, userName, id);

                    if(is_borrow==id){
                        printf("\n   (Anda sudah meminjam buku ini)\n\n");
                        getEnterKey();
                          
                    }

                    if(is_borrow==0){
                        is_continue = pinjamBuku(dBuku, bukuPinjam, i, userName, ofp);
                        // loadData(dBuku, ifp, jmlData);
                        updateData(dBuku, ifp, jmlData, id);
                        loadData(dBuku, ifp, jmlData);
                        if(is_continue == 1){
                            goto label_is_continue;
                        }
                        else if(is_continue==0){
                            updateData(dBuku, ifp, jmlData, id);
                            loadData(dBuku, ifp, jmlData);
                            break;
                        }
                    }

                } else if(i == -1){
                    printf("\n   (ID buku tidak ditemukan)\n\n");
                    getEnterKey();
                }

            } else if(maxPinjam>=5){
                    printf("  (Anda tidak dapat meminjam lebih dari 5 buku)\n\n");
                    printf("   (Kembalikan beberapa buku terlebih dahulu untuk meminjam lagi)\n\n");
                    getEnterKey();
            }

        } else if(option == 'n'){
            break;

        } else{
            printf("\n   (Input tidak valid! Masukkan input ulang)\n\n");   
            getEnterKey();
        }
    }

}

//menampilkan daftar buku yang tersedia 
int pinjamBuku(dataBuku *daftarBuku, dataBuku *bPinjam, int i, char *username, char *userFileStream) {
   char name[20];
   char *ofp = userFileStream;
   strcpy(name, username);

    while(1){
        
            if (daftarBuku[i].stok > 0)
                //mendapatkan id buku dari pengguna
            {
                label_confirm:
                clearScreen();
                pathLoc("  Menu User\\Pinjam Buku>");
                menuTitle(1);

                printf("  Data buku yang dicari:\n\n");
                printf("   ID Buku\t\t: %d\n", daftarBuku[i].id);
                printf("   Judul\t\t: %s\n", daftarBuku[i].judul);
                printf("   Penulis\t\t: %s\n", daftarBuku[i].penulis);
                printf("   Penerbit\t\t: %s\n", daftarBuku[i].penerbit);
                printf("   Jumlah Halaman\t: %d\n", daftarBuku[i].jmlHal);
                printf("   Tahun Terbit\t\t: %d\n", daftarBuku[i].tahun);
                printf("   Tahun Terbit\t\t: %d\n", daftarBuku[i].stok);

                //memeriksa ketersediaan buku dan mengurangi jumlah buku
                
                printf("\n   Apakah anda yakin ingin meminjam buku ini? [y/n] : ");
                char jawaban = getOption();
                if (jawaban == 'y') {
                    daftarBuku[i].stok--;
                    FILE *file = fopen("userBook.txt", "a");
                    fprintf(file, "\"%s\" %u \"%s\" \"%s\" \"%s\" %u %u %u\n", name, daftarBuku[i].id, daftarBuku[i].judul, daftarBuku[i].penulis, daftarBuku[i].penerbit, daftarBuku[i].jmlHal, daftarBuku[i].tahun, daftarBuku[i].stok);
                    fclose(file);

                    printf("\n   (Buku berhasil dipinjam)\n\n");
                    getEnterKey();

                
                } else if (jawaban == 'n'){
                    printf("\n   (Membatalkan peminjaman)\n\n");
                    getEnterKey(); 
                    break;

                } else{
                    printf("\n   (Input tidak valid! Masukkan input ulang)\n\n");   
                    getEnterKey();
                    goto label_confirm;      
                }
                label_request:
                clearScreen();
                pathLoc("  Menu User/Pinjam Buku>");
                menuTitle(1);
                printf("  Ingin meminjam buku lagi? [y/n] : ");
                char lagi = getOption();
                if (lagi == 'y') {
                    return 1;
                } else if(lagi == 'n'){
                    return 0;
                } else{
                    printf("\n   (Input tidak valid! Masukkan input ulang)\n\n");   
                    getEnterKey();
                    goto label_request;
                }
            } else {
                printf("\n   Stok buku yang dipinjam habis\n");
            
        }
    }
    
}

#include"header.h"

int menuTambahBuku(char *filestream){
    char *ifp = filestream;
    char pilihan;
    char confirm;
    int id, dataAddSucced=0;
    dataBuku buku;
    dataBuku dBuku[N];
    FILE *file = fopen(ifp, "r");
    int jmlData = countData(ifp);

    fclose(file);

    do {
        clearScreen();
        pathLoc("  Menu Admin\\Tambah Buku>");
        menuTitle(1);
        dataAddSucced = 0;
        jmlData = countData(ifp);
        loadData(dBuku, ifp, jmlData);

        //  input pilihan iya atau tidak utk menambahkan buku
        printf("  Apakah anda ingin menambahkan buku? [y/n] : ");       
        pilihan = getOption();

        // pilihan iya utk menambahkan buku
        if (pilihan == 'y') {   
            label_input:
            clearScreen();
            pathLoc("  Menu Admin\\Tambah Buku>");
            menuTitle(1);


            // input data pada buku
            printf("  (Masukkan data buku) \n\n");
            printf("   ID Buku\t  : ");
            buku.id = 0;
            scanf("%u", &buku.id);
            ignoreInputBuffer();
            id = buku.id;            

            // cek digit id
            if((id<100) || (id>=1000)){
                    printf("\n\n   (ID buku hanya terdiri dari 3 digit)\n\n");
                    getEnterKey();
                    goto label_input;
                }
            int i;
            i = findID(dBuku, id, jmlData);     // mencari id buku
            
            // jika id yang dicari ada yang sama dengan id buku lain maka penambahan dibatalkan
            if (i != -1)  {
                printf("\n   ID buku ini telah digunakan pada buku : \n\n");
                printf("   ID Buku\t  : %u\n   Judul Buku\t  : %s\n   Penulis\t  : %s\n   Penerbit\t  : %s\n   Jumlah Halaman : %u\n   Tahun Terbit\t  : %u\n   Stok Buku\t  : %u\n\n", dBuku[i].id, dBuku[i].judul, dBuku[i].penulis, dBuku[i].penerbit, dBuku[i].jmlHal, dBuku[i].tahun, dBuku[i].stok);
                printf("   (Buku gagal ditambahkan)\n\n");
                getEnterKey();

             // jika id tidak ada yang sama dgn buku lain  maka penambahan data dilanjutkan
            } else {
                printf("   Judul Buku\t  : ");
                fgets(buku.judul, sizeof(buku.judul), stdin);
                buku.judul[strcspn(buku.judul, "\n")] = '\0';

                printf("   Penulis\t  : ");
                fgets(buku.penulis, sizeof(buku.penulis), stdin);
                buku.penulis[strcspn(buku.penulis, "\n")] = '\0';

                printf("   Penerbit\t  : ");
                fgets(buku.penerbit, sizeof(buku.penerbit), stdin);
                buku.penerbit[strcspn(buku.penerbit, "\n")] = '\0';

                buku.jmlHal = 0;
                printf("   Jumlah Halaman : ");
                scanf("%d", &buku.jmlHal);
                ignoreInputBuffer();
                  if(buku.jmlHal<=0){
                    dataAddSucced = -1;         // dataAddSucced akan bernilai -1 ketika input data tidak sesuai
                }

                buku.tahun = 0;
                printf("   Tahun Terbit\t  : ");
                scanf("%d", &buku.tahun);
                ignoreInputBuffer();
                  if(buku.tahun<=0){
                    dataAddSucced = -1;
                }
            
                buku.stok = 0;
                printf("   Stok Buku\t  : ");
                scanf("%u", &buku.stok);
                ignoreInputBuffer();
                if(buku.stok<=0){
                    dataAddSucced = -1;
                }

                // konfirmasi ulang utk penambahan data
                if(dataAddSucced == 0){
                    printf("\n\n   Apakah anda yakin ingin menambahkan buku dengan data tersebut? [y/n] : ");
                    confirm = getOption();
                    
                    // jika konfirmasi iya, data buku baru ditambahkan
                    if(confirm == 'y'){
                        fopen(ifp, "a");
                        fprintf(file, "%u \"%s\" \"%s\" \"%s\" %u %u %u\n", buku.id, buku.judul, buku.penulis, buku.penerbit, buku.jmlHal, buku.tahun, buku.stok);
                        fclose(file);
                        dataAddSucced = 1;

                     // jika konfirmasi tidak, data buku baru tidak ditambahkan 
                    } else if(confirm == 'n'){
                        printf("\n\n   (Penambahan data dibatalkan)\n\n");
                        getEnterKey();
                    }

                    // input tidak valid saat konfirmasi ulang
                    else if(confirm == 'x'){
                        printf("\n\n   (Input tidak valid, masukkan data dengan benar)\n\n");
                        getEnterKey();
                    }
                }

            }

        // pilihan tidak untuk menambahkan buku
        } else if(pilihan == 'n'){          
            clearScreen();
            
        // pilihan invalid untuk menambahkan buku    
        } else{            
            printf("\n\n   (Input tidak valid, masukkan input ulang)\n\n");
            getEnterKey();
        }

        if(dataAddSucced == 1){
            printf("\n   (Buku berhasil ditambahkan)\n\n"); // pemberitahuan penambahan data
            getEnterKey();

        } if(dataAddSucced == -1){
            printf("\n   (Buku gagal ditambahkan, perhatikan input bilangan pada data)\n\n"); // pemberitahuan penambahan data
            getEnterKey();
        }
        clearScreen();
    } while (pilihan != 'n');       // while loop berhenti ketika pilihan = 'n' pada input awal

    return 0;
}

#include"header.h"

int menuEditBuku(char *filestream){
    char *ifp = filestream;
    
    int jmlData = countData(ifp);
    dataBuku buku[jmlData];

    FILE *file = fopen(ifp, "r");
    if (file == NULL){
        printf("  Error reading file...\n");
        getchar();
        return 1;
    }

    loadData(buku, ifp, jmlData);


    char option;
    int id_find=1, id_input;
    while(1){
        label_continue:
        clearScreen();
        pathLoc("  Menu Admin\\Ubah Buku>");
        menuTitle(1);
        printf("  Apakan anda ingin melakukan pengeditan? [y/n] : ");
        option = getOption();
        
        if(option == 'y'){
            printf("\n   Masukkan ID yang ingin diubah : ");
            scanf("%d", &id_input);
            ignoreInputBuffer();
            for(int i = 0; i < jmlData; i++){
                if((unsigned int)id_input == buku[i].id){
                    id_find = i;    // id buku ditemukan
                    break;    
                }
                if(i==jmlData-1){
                    printf("   (ID Buku tidak tersedia pada data)\n\n"); //id buku tidak ditemukan
                    getEnterKey();
                    goto label_continue;
                }
            }

            editBook(buku, ifp, id_find);


        } else if(option == 'n'){
            
            break;
        } else{
            printf("\n\n   (Input tidak valid, masukkan input ulang)\n\n");
            getEnterKey();
        }

    }
    clearScreen();

}

int editBook(dataBuku *dBuku, char *filestream, int id_find){
    char *ifp = filestream;

    int jmlData = countData(ifp);
    int option;

    FILE *file = fopen(ifp, "r");
    if (file == NULL){
        printf("   Error reading file...\n");
        getchar();
        return 1;
    }

    loadData(dBuku, ifp, jmlData);

    int numb=0;
    char str[40];
    int id_check;
    int i = id_find;

    label_menu_edit:
    clearScreen();
    pathLoc("   Menu Admin\\Ubah Buku>");
    menuTitle(1);
    movePos(3,6);
 
    printf(" Data buku yang dicari : \n\n");
    printf("   (1) ID Buku        : %u\n", dBuku[i].id);
    printf("   (2) Judul Buku     : %s\n", dBuku[i].judul);
    printf("   (3) Penulis        : %s\n", dBuku[i].penulis);
    printf("   (4) Penerbit       : %s\n", dBuku[i].penerbit);
    printf("   (5) Jumlah Halaman : %u\n", dBuku[i].jmlHal);
    printf("   (6) Tahun Terbit   : %u\n", dBuku[i].tahun);
    printf("   (7) Stok Buku      : %u\n", dBuku[i].stok);
   
    printf("\n   (Pilih nomor untuk mengubah data [1-7] || Masukkan '0' untuk membatalkan perubahan)\n   Input : ");
    scanf("%d", &option);
    ignoreInputBuffer();

    if((option>=1 && option <= 7)){
        printf("   Masukkan perubahan : ");
        switch (option){
            case 1:
                scanf("%u", &id_check);
                ignoreInputBuffer();
                if((id_check<100) || (id_check>=1000)){
                    printf("   (ID buku hanya terdiri dari 3 digit)\n\n");
                    getEnterKey();
                    goto label_menu_edit;        
                }
               
                for(int j=0; j<jmlData; j++){
                        if((checkPrimeKey(dBuku, id_check, jmlData))== 1){
                            printf("   (ID buku sudah digunakan)\n\n");
                            getEnterKey();
                            goto label_menu_edit;    
                        } 
                }
                dBuku[i].id = id_check;
                break;

            case 2:
                scanf("%[^\n]s", str);
                ignoreInputBuffer();
                strncpy(dBuku[i].judul, str, 40);
                break;

            case 3:
                scanf("%[^\n]s", str);
                ignoreInputBuffer();
                strncpy(dBuku[i].penulis, str, 30);
                break;

            case 4:
                scanf("%[^\n]s", str); 
                ignoreInputBuffer();
                strncpy(dBuku[i].penerbit, str, 20);
                break;

            case 5:
                numb = getNumb();
                if(numb == -1){
                    printf("   (Input tidak valid, harap masukkan bilangan integer)\n\n");
                    getEnterKey();
                    goto label_menu_edit;
                }
                dBuku[i].jmlHal = numb;
                
                break;

            case 6:
                numb = getNumb();
                if(numb == -1){
                    printf("   (Input tidak valid, harap masukkan bilangan integer)\n\n");
                    getEnterKey();
                    goto label_menu_edit;
                }
                dBuku[i].tahun = numb;
                break;

            case 7:
                numb = getNumb();
                if(numb == -1){
                    printf("   (Input tidak valid, harap masukkan bilangan integer positif)\n\n");
                    getEnterKey();
                    goto label_menu_edit;
                }
                dBuku[i].stok = numb;
                break;
    
        }

        file = fopen(ifp, "w"); 
        if(!file){
            perror("\n   (Gagal melakukan perubahan)\n\n)");
            getEnterKey();
        }

        for(int j=0; j<jmlData; j++){
            fprintf(file, "%u \"%s\" \"%s\" \"%s\" %u %u %u\n", dBuku[j].id, dBuku[j].judul, dBuku[j].penulis, dBuku[j].penerbit, dBuku[j].jmlHal, dBuku[j].tahun, dBuku[j].stok);
        }
        fclose(file);
        printf("\n   (Data buku berhasil diubah)\n\n");
        getEnterKey();
        

    } else if(option == 0){
        printf("\n   (Membatalkan Perubahan)\n\n");
        getEnterKey();
    } 
    else if(!(option>=1 && option <= 7)){
        printf("\n   (Input tidak valid, masukkan input dengan benar)\n\n");
        getEnterKey();
        goto label_menu_edit;
    }

}
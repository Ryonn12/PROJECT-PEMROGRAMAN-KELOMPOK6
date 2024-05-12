#include"header.h"

int menuKembaliBuku(char *fileData, char *filePinjam, char *userName){
    dataBuku buku[N], bukuPinjam[M];
    char *name = userName;
    int jmlData = countData(fileData);
    int jmlBukuPinjam = countData(filePinjam);
    char option;
    int ID, i;  // i = indeks

    while(1){
        borderBukuPinjam(buku, bukuPinjam, filePinjam, fileData, name);
        printf("   Apakah anda ingin mengembalikan buku? [y/n] : ");
        option = getOption();
        if(option=='y'){

                label_pinjam:
                borderBukuPinjam(buku, bukuPinjam, filePinjam, fileData, name);
                printf("\n   Masukkan ID buku yang akan dikembalikan : ");
                scanf("%d", &ID);
                ignoreInputBuffer();


                ID = findBookID(bukuPinjam, filePinjam, jmlBukuPinjam, userName, ID);
                i = findID(buku, ID, jmlData);
                
                if(ID != 0){
                    label_confirm:
                    borderBukuPinjam(buku, bukuPinjam, filePinjam, fileData, name);
             
                    printf("\n   Apakah anda ingin mengembalikan buku dengan ID %d? [y/n] : ", ID);
                    option = getOption();
                    if(option == 'y'){
                        
                        kembaliBuku(ID, filePinjam, userName);
                        buku[i].stok++;
                        updateData(buku, fileData, jmlData, ID);
                        loadBukuPinjam(bukuPinjam, filePinjam, jmlBukuPinjam);
                        printf("\n\n   (Pengembalian buku berhasil)\n\n");
                        getEnterKey();
                        borderBukuPinjam(buku, bukuPinjam, filePinjam, fileData, name);

                        printf("\n   Ingin mengembalikan buku lagi? [y/n] : ");
                        option = getOption();

                        if (option == 'y') {
                            goto label_pinjam;
                        } else if(option == 'n'){
                            break;
                        } else{
                            printf("\n\n   (Input tidak valid, masukkan input dengan benar)\n\n");
                            getEnterKey();
                        }

                    } else if(option == 'n'){
                        printf("\n\n   (Pengembalian buku dibatalkan)\n\n");
                        getEnterKey();
                    } else{
                        printf("\n\n   (Input tidak valid, masukkan input dengan benar)\n\n");
                        getEnterKey();
                        goto label_confirm;
                    }

                } else if(ID==0){
                    printf("\n\n   (Anda tidak meminjam buku dengan ID tersebut)\n\n");
                    getEnterKey();
                } 
            
        }else if(option=='n'){
            clearScreen();
            return 0;
        }else{
            printf("\n\n   (Input tidak valid, masukkan input dengan benar)\n\n");
            getEnterKey();
        }
    }
    clearScreen();
    return 0;
}

int kembaliBuku(int id_delete, char *filename, char *userNameDel){
    char *ifp = filename;
    FILE *file = fopen(ifp, "r"); 
    if(!file){
        perror("   (Gagal mengembalikan buku\n\n)");
        return -1;
        getEnterKey();
    }

    FILE *tempfile = fopen("tempfile.txt", "w");
    if(!tempfile){
        perror("   (Gagal mengembalikan buku\n\n)");
        getEnterKey();
        fclose(file);
        return -1;
    }

    int jmlData = countData(ifp);
    char buffer[512];
    char userName[20];
    int daftar_id[10];
    int id_buku;

    //Proses penghapusan data dari file
    while(fgets(buffer, sizeof(buffer), file) != NULL){     //Input data dari file ke buffer
        sscanf(buffer, "\"%20[^\"]\" %u",  userName, &id_buku);                     //id_buku hanya menampung angka dari array buffer

        if(strcmp(userName, userNameDel)!=0){     
                fputs(buffer, tempfile);                       
        }    
            
        if(strcmp(userName, userNameDel)==0){     
            if(id_buku != id_delete){
                fputs(buffer, tempfile);                        //tempfile hanya mendapat data dari buffer yang id bukunya berbeda dengan id_delete
            }
        }

    }
    fclose(file);
    fclose(tempfile);

    file = fopen(ifp, "w");
    if(!file){
        perror("   (Gagal mengembalikan buku\n\n)");
        getEnterKey();
        fclose(file);
        fclose(tempfile);
        return -1;
    }

    tempfile = fopen("tempfile.txt", "r");
    if(!tempfile){
        perror("   (Gagal mengembalikan buku\n\n)");
        getEnterKey();
        fclose(tempfile);
        return -1;
    }

    while(fgets(buffer, sizeof(buffer), tempfile) != NULL){     //input data dari tempfile ke buffer
        fputs(buffer, file);                                    //input data dari buffer ke file awal
    }

    fclose(file);
    fclose(tempfile);
    remove("tempfile.txt");                     //tempfile dihapus
}
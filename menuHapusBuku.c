#include"header.h"

int menuHapusBuku(char *filename){
    
    unsigned int id_input;
    char *ifp = filename;     // file data buku yang digunakan

    FILE *file = fopen(ifp, "r");
    if (file == NULL){
        printf("   Error reading file...");
        return 1;
    }

    int jmlData = countData(ifp);   // mneghitung jumlah data

    dataBuku buku[N];

    loadData(buku, ifp, jmlData);

    if(buku[0].id == 0){
        printf("   (Data tidak tersedia)\n\n");  // file data kosong
        getEnterKey();
        return 1;
    }

    char option, option2;
    int id_find;
    
    while (1) {

        label_continue:
        clearScreen();
        pathLoc("  Menu Admin\\Hapus Buku>");
        menuTitle(1);
        printf("  Apakah anda ingin menghapus buku? [y/n] : ");
        
        option = getOption();
        
        if (option == 'y') {
            printf("\n   Masukkan ID buku yang ingin dihapus: ");
            scanf("%u", &id_input);     // input id buku yang dicari
            ignoreInputBuffer();
            id_input = checkID(id_input);   //Jika id_input bernilai -1, maka id tidak valid

            if(id_input != -1){

            // looping mencari id buku terkait
                for(int i = 0; i < jmlData; i++){
                    if((unsigned int)id_input == buku[i].id){
                        id_find = i;    // id buku ditemukan
                        break;
                    }
                    if(i==jmlData-1){
                        printf("\n   (ID Buku tidak ditemukan)\n\n"); 
                        getEnterKey();
                        goto label_continue;    // id buku tidak ditemukan dan kembali ke input awal
                    }
                }       
                    label_confirm:
                    clearScreen();
                    pathLoc("  Menu Admin\\Hapus Buku>");
                    menuTitle(1);
                    // cetak data buku terkait
                    printf("  ID Buku       : %u\n", buku[id_find].id);
                    printf("   Judul Buku    : %s\n", buku[id_find].judul);
                    printf("   Penulis       : %s\n", buku[id_find].penulis);
                    printf("   Penerbit      : %s\n", buku[id_find].penerbit);
                    printf("   Jumlah Hal    : %u\n", buku[id_find].jmlHal);
                    printf("   Tahun Terbit  : %u\n", buku[id_find].tahun);
                    printf("   Stok          : %u\n", buku[id_find].stok);
                    printf("\n");

                    printf("   Apakah anda yakin ingin menghapus buku ini? [y/n]: ");
                    option = getOption();   // input konfirmasi ulang
                    if(option == 'y'){
                        removeBook(id_input, ifp);      // buku berhasil dihapus
                        id_input = 0;
                        buku[id_find].id = 0;
                        goto label_continue;
                    }
                    if(option == 'n'){
                        printf("\n   (Batal menghapus buku)\n\n");   // batal menghapus buku
                        getEnterKey();
                        id_input = 0;
                        goto label_continue;
                    }
                    if((option != 'y') || (option != 'n')){
                        printf("\n   (Input tidak valid! Konfirmasi ulang)\n\n");
                        getEnterKey();
                        goto label_confirm;    // konfirmasi ulang
                    }
            } 
            
        } else if (option == 'n') {   
            break;                               // keluar dari looping awal

        } else{
            printf("\n\n   (Input tidak valid! Masukkan input ulang)\n\n");   
            getEnterKey();        
        }
    }   //akhir looping while
    
}       

void removeBook(int id_delete, char *filename){
    char *ifp = filename;
    FILE *file = fopen(ifp, "r"); 
    if(!file){
        perror("   (Gagal menghapus buku\n\n)");
        getEnterKey();
    }

    FILE *tempfile = fopen("tempfile.txt", "w");
    if(!tempfile){
        perror("   (Gagal menghapus buku\n\n)");
        getEnterKey();
        fclose(file);
    }

    int jmlData = countData(ifp);
    char buffer[1024];
    int daftar_id[jmlData];
    int id_buku;

    //Proses penghapusan data dari file
    while(fgets(buffer, sizeof(buffer), file) != NULL){     //Input data dari file ke buffer
        sscanf(buffer, "%u", &id_buku);                     //id_buku hanya menampung angka dari array buffer
        
        if(id_buku != id_delete){                           
            fputs(buffer, tempfile);                        //tempfile hanya mendapat data dari buffer yang id bukunya berbeda dengan id_delete
        }
    }
      

    fclose(file);
    fclose(tempfile);

    file = fopen(ifp, "w");
    if(!file){
        perror("   (Gagal menghapus buku\n\n)");
        getEnterKey();
        fclose(file);
        fclose(tempfile);
    }

    tempfile = fopen("tempfile.txt", "r");
    if(!tempfile){
        perror("   (Gagal menghapus buku\n\n)");
        getEnterKey();
        fclose(tempfile);
    }

    while(fgets(buffer, sizeof(buffer), tempfile) != NULL){     //input data dari tempfile ke buffer
        fputs(buffer, file);                                    //input data dari buffer ke file awal
    }

    fclose(file);
    fclose(tempfile);
    remove("tempfile.txt");                     //tempfile dihapus
    printf("\n   (Buku berhasil dihapus)\n\n");
    getEnterKey();
}
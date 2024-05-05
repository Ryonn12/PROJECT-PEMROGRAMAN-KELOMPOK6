#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 150

int menuHapusBuku(char *filename);

char getOption(void);
void removeBook(int id_delete, char *filename);
int countData(char *filename);
int checkID(int n);
void ignoreInputBuffer();

typedef struct dataBuku {
    unsigned int id;
    char judul[40];
    char penulis[30];
    char penerbit[20];
    unsigned int jmlHal;
    unsigned int tahun;
    unsigned int stok;
} buku;

int main (){

    menuHapusBuku("daftar_buku1.txt");
    printf("\n(Program selesai)\n");   

    return 0;
}

int menuHapusBuku(char *filename){
    
    unsigned int id_input;
    char *ifp = filename;     // file data buku yang digunakan

    FILE *file = fopen(ifp, "r");
    if (file == NULL){
        printf("Error reading file...");
        return 1;
    }

    int jmlData = countData(ifp);

    buku dataBuku[jmlData];

    file = fopen(ifp, "r");
    if (file == NULL){
        printf("Error reading file...");
        return 1;
    }
    char buffer[1052];
    for (int i = 0; i < jmlData+1; i++) {     // inisialisasi data file ke struct
        fgets(buffer, 1056, file);
        sscanf(buffer, "%u \"%49[^\"]\" \"%29[^\"]\" \"%19[^\"]\" %u %u %u\n", &dataBuku[i].id, dataBuku[i].judul, dataBuku[i].penulis, dataBuku[i].penerbit, &dataBuku[i].jmlHal, &dataBuku[i].tahun, &dataBuku[i].stok);
    }
    fclose(file);

    if(dataBuku[0].id == 0){
        printf("Data tidak tersedia");  // file data kosong
        return 1;
    }

    char option, option2;
    int id_find;
    
    while (1) {
        label_continue:
        printf("Apakah anda ingin menghapus buku? [y/n]: ");
        
        option = getOption();
        
        if (option == 'y') {
            printf("Masukkan ID buku yang ingin dihapus: ");
            scanf("%u", &id_input);     // input id buku yang dicari
            ignoreInputBuffer();
            id_input = checkID(id_input);   //Jika id_input = 1, id tidak ditemukan

            if(id_input != 1){

            // looping mencari id buku terkait
            for(int i = 0; i < jmlData; i++){
                if((unsigned int)id_input == dataBuku[i].id){
                    id_find = i;    // id buku ditemukan
                    break;
                }
                if(i==jmlData-1){
                    printf("(ID Buku tidak ditemukan)\n\n"); 
                    goto label_continue;    // id buku tidak ditemukan dan kembali ke input awal
                }
            }
                    // cetak data buku terkait
                    printf("\nID Buku      : %u\n", dataBuku[id_find].id);
                    printf("Judul Buku    : %s\n", dataBuku[id_find].judul);
                    printf("Penulis       : %s\n", dataBuku[id_find].penulis);
                    printf("Penerbit      : %s\n", dataBuku[id_find].penerbit);
                    printf("Jumlah Hal    : %u\n", dataBuku[id_find].jmlHal);
                    printf("Tahun Terbit  : %u\n", dataBuku[id_find].tahun);
                    printf("Stok          : %u\n", dataBuku[id_find].stok);
                    printf("\n");

                    label_confirm:
                    printf("Apakah anda yakin ingin menghapus buku ini? [y/n]: ");
                    option = getOption();   // input konfirmasi ulang
                    if(option == 'y'){
                        removeBook(id_input, ifp);      // buku berhasil dihapus
                        id_input = 0;
                        dataBuku[id_find].id = 0;
                    }
                    if(option == 'n'){
                        printf("(Batal menghapus buku)\n\n");   // batal menghapus buku
                        id_input = 0;
                    }
                    else if(option == 'x'){
                        printf("(Input tidak valid! Konfirmasi ulang)\n\n"); 
                        goto label_confirm;    // konfirmasi ulang
                    }

            } else if(id_input == 1){
                printf("(ID buku tidak ditemukan, masukkan ID dengan benar!)\n\n");  // id tidak ditemukan ketika input char
                id_input = 0;
            }
            
        } else if (option == 'n') {   
            break;                               // keluar dari looping awal

        } else if(option == 'x'){
            printf("(Input tidak valid! Masukkan input ulang)\n\n");            
        }
    }   //akhir looping while
    
}       

char getOption(void){
    char option, input[30];
    fgets(input, sizeof(input), stdin);
    int length = strlen(input);

    if(length>2){   // invalid
        option = 'x';
    } 
    else if(length==2){
         if( (input[0]=='y') || (input[0]=='Y') ){  // true option
        option = 'y';
        }
        else if ( (input[0]=='n') || (input[0]=='N') ){     // false option
            option = 'n';
        }
        else{   // invalid option
            option = 'x';   
        }
    }
    return option;
}

int checkID(int n){
    if((n>=1000) || (n<100)){
        return 1;              // id tidak ditemukan
    }

    return n;
}

int countData(char *filename){
    int jmlData=1;

    char *ifp = filename;
    FILE *file = fopen(ifp, "r");
    if (file == NULL){
        printf("Error reading file...");
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {      // menghitung jumlah data yang masuk dari file teks
        if (ch == '\n') {
            jmlData++;
        }
    }
    fclose(file);

    return jmlData-1;
}

void ignoreInputBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {   // membersihkan buffer input
        continue;
    }
}

void removeBook(int id_delete, char *filename){
    char *ifp = filename;
    FILE *file = fopen(ifp, "r"); 
    if(!file){
        perror("(Gagal menghapus buku\n\n)");
    }

    FILE *tempfile = fopen("tempfile.txt", "w");
    if(!tempfile){
        perror("(Gagal menghapus buku\n\n)");
        fclose(file);
    }

    int jmlData = countData(ifp);
    char buffer[1024];
    int daftar_id[jmlData];
    int id_buku;

    int i = 0;

    //Proses penghapusan data dari file
    while(fgets(buffer, sizeof(buffer), file) != NULL){     //Input data dari file ke buffer
        sscanf(buffer, "%u", &id_buku);                     //id_buku hanya menampung angka dari array buffer
        
        if(id_buku != id_delete){                           
            fputs(buffer, tempfile);                        //tempfile hanya mendapat data dari buffer yang id bukunya berbeda dengan id_delete
        }
        i++;
    }
      

    fclose(file);
    fclose(tempfile);

    file = fopen(ifp, "w");
    if(!file){
        perror("(Gagal menghapus buku\n\n)");
        fclose(file);
        fclose(tempfile);
    }

    tempfile = fopen("tempfile.txt", "r");
    if(!tempfile){
        perror("(Gagal menghapus buku\n\n)");
        fclose(tempfile);
    }


    while(fgets(buffer, sizeof(buffer), tempfile) != NULL){     //input data dari tempfile ke buffer
        fputs(buffer, file);                                    //input data dari buffer ke file awal
    }

    fclose(file);
    fclose(tempfile);
    remove("tempfile.txt");                     //tempfile dihapus
    printf("(Buku berhasil dihapus)\n\n");
}
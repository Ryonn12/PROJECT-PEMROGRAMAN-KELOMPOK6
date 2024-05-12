#include"header.h"

void adminMenu(void);
void userMenu(void);

int main(int argc, char *argv[]){
    clearScreen();
    if(argc != 2){
        printf("\nArgument inputs are required!\n\nEXAMPLE :\nArgument \t:.\\program \"role\" \n ");
        printf("\nrole \t\t: admin/user\n\n");
        getEnterKey();

        return EXIT_FAILURE;
    }

    char file1[] = "daftar_buku.txt";
    char file2[] = "userBook.txt";
    char file3[] = "recordBook.txt";
    char *fileData = file1;
    char *filePinjam = file2;
    char *fileRecord = file3;

    int roleOption;
    if (strcmp(argv[1], "admin") == 0) {
        roleOption = 0; 
    } else if (strcmp(argv[1], "user") == 0) {
        roleOption = 1;
    } else {
        printf("Tipe akun tidak valid!\n");
        getEnterKey();
        return EXIT_FAILURE;
    }

        char userName[20];
        strcpy(userName, loginMenu(argv[1]));
        char *name = userName;

        loadingScreen();

    enum role{ADMIN, USER};

    int option;
    int is_continue;
    if (roleOption == ADMIN){
        is_continue=1;
        while(is_continue){
            adminMenu();
            greetingText(name);
            printf("Masukkan Pilihan : ");
            option = getOptionNumb();
            switch (option){
                case 1:
                    menuDaftarBuku(fileData, filePinjam, fileRecord, name, roleOption);
                    break;
                case 2:
                    /* fungsi untuk menambahkan data buku baru ke dalam daftar */
                    menuTambahBuku(fileData);
                    break;
                case 3:
                    /* fungsi untuk menghapus buku dari daftar*/;
                    menuHapusBuku(fileData);
                    break;
                case 4:
                    /* Fungsi untuk mengedit buku*/
                    menuEditBuku(fileData);
                    break;
                case 5:
                    is_continue = 0;
                    break;    
                default:
                    break;
            }
            
        }

    } else if(roleOption == USER){
        is_continue=1;
        while(is_continue){
            userMenu();
            greetingText(name);
            printf("Masukkan Pilihan : ");
            option = getOptionNumb();
            switch (option){
                case 1:
                    /* fungsi tampilan isi buku*/
                    menuDaftarBuku(fileData, filePinjam, fileRecord, name, roleOption);
                    break;
                case 2:
                    /* fungsi menampilkan daftar buku yang dipinjam*/
                    menuPinjamBuku(fileData, name, filePinjam, fileRecord);
                    break;
                case 3:
                    /* fungsi mengembalikan buku */
                    menuKembaliBuku(fileData, filePinjam, name);
                    break;
                case 4:
                    is_continue = 0;
                    break;    
                default:
                    break;
            }
            
        }
    }
    
    movePos(66,26);
    hidCurs(1);
    printf("<End Program>\n");
    getchar();
    hidCurs(0);
    clearScreen();

    return 0;
}
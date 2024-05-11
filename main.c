#include"header.h"

int main(int argc, char *argv[]){
    clearScreen();
    if(argc != 2){
        printf("\nArgument inputs are required!\n\nEXAMPLE :\nArgument \t:.\\program \"role\" \n ");
        printf("\nrole \t\t: admin/user\n\n");
        getEnterKey();

        return EXIT_FAILURE;
    }
    
    char file1[20] = "daftar_buku.txt";
    char file2[15] = "userBook.txt";
    char *fileData = file1;
    char *filePinjam = file2;

    char userName[20] = "user1";
    char *name = userName;

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
                    /* fungsi menampilkan buku */
                  
                    break;
                // case 2:
                    /* fungsi menampilkan buku yang sedang dipinjam oleh user*/
                    
                    break;
                case 2:
                    /* fungsi untuk menambahkan data buku baru ke dalam daftar */
                  
                    break;
                case 3:
                    /* fungsi untuk menghapus buku dari daftar*/;
                  
                    break;
                case 4:
                    
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
                   
                    break;
                case 2:
                    /* fungsi menampilkan daftar buku yang dipinjam*/
                    
                    break;
                case 3:
                    /* fungsi mengembalikan buku */
                   
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
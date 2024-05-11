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

void userMenu(){

    clearScreen();
    pathLoc("  Menu User>");
    borderMenu();
    movePos(63,8);
    printf("M E N U  U S E R");
   
    movePos(59,12);
    printf("(1) D A F T A R  B U K U");
    movePos(59,14);
    printf("(2) P I N J A M  B U K U");
    movePos(59,16);
    printf("(3) K E M B A L I K A N  B U K U");
    movePos(59,18);
    printf("(4) K E L U A R");
    
    menuTitle(0);
    movePos(63,24);
  
}

void adminMenu(){
   
    clearScreen();
    pathLoc("  Menu Admin>");
    borderMenu();
    movePos(63,8);
    printf("M E N U  A D M I N");
   
    movePos(59,12);
    printf("(1) D A F T A R  B U K U");
    movePos(59,14);
    printf("(2) T A M B A H  B U K U");
    movePos(59,16);
    printf("(3) H A P U S  B U K U");
    movePos(59,18);
    printf("(4) U B A H  D A T A  B U K U");
    movePos(59,20);
    printf("(5) K E L U A R");
 
 
    menuTitle(0);
    movePos(63,24);
  
}

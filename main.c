    #include<stdio.h>
#include<stdlib.h>

void clear(void);
int userAdmin(void);
int userOption(void);

int loginMenu(char *);

// fungsi user
void daftarBuku();
void pinjamBuku();
void kembaliBuku();

// fungsi admin
void daftarBuku();
void daftarBukuPinjaman();
void tambahBuku();
void hapusBuku(); 

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Input Argumen!\nArgumen Input : admin/user\n ");
        return EXIT_FAILURE;
    }

    int roleOption=0;

//    loginMenu(argv[2]);

    enum role{ADMIN, USER};

    if (roleOption == ADMIN){
        int option;
        int is_continue;
        is_continue=1;
        while(is_continue){
            option = userAdmin();
            switch (option){
                case 1:
                    /* code tampilan isi buku*/
                    break;
                case 2:
                    /* code menampilkan daftar buku yang sedang dipinjam oleh user*/
                    break;
                case 3:
                    /* code untuk menambahkan data buku baru ke dalam daftar */
                    break;
                case 4:
                    /* code untuk menghapus buku dari daftar*/;
                    break;
                case 5:
                    is_continue = 0;
                    break;    
                default:
                    printf("Invalid Input!");
                    is_continue= 0;
                    break;
            }
            
        }

    } else if(roleOption == USER){
        int option;
        int is_continue;
        is_continue=1;
        while(is_continue){
            option = userOption();
            switch (option){
                case 1:
                    /* code tampilan isi buku*/
                    break;
                case 2:
                    /* code menampilkan daftar buku yang dipinjam*/
                    break;
                case 3:
                    /* code pinjam dan kembalikan buku */
                    break;
                case 4:
                    is_continue = 0;
                    break;    
                default:
                    printf("Invalid Input!");
                    is_continue= 0;
                    break;
            }
            
        }
    }
    
    printf("\nEnd Program\n");

    return 0;
}

int userOption(){
    int input;
    clear();
    printf("User Option\n");
    printf("================================\n");
    printf("(1) Tampilkan Daftar Buku\n");
    printf("(2) Tampilkan Daftar Buku yang Dipinjam\n");
    printf("(3) Pinjam dan Kembalikan Buku\n");
    printf("(4) Keluar dari Aplikasi\n");
    printf("\n================================\n");
    printf("Masukkan Pilihan :");
    scanf("%d", &input);
    return input;
}

int userAdmin(){
    int input;
    clear();
    printf("User Admin\n");
    printf("================================\n");
    printf("(1) Tampilkan Daftar Buku\n");
    printf("(2) Tampilkan Buku yang Dipinjam User\n");
    printf("(3) Tambahkan Buku\n");
    printf("(4) Hapus Buku\n");
    printf("(5) Keluar dari Aplikasi\n");
    printf("\n================================\n");
    printf("Masukkan Pilihan :");
    scanf("%d", &input);
    return input;
}

void clear(void){
    printf("\033[2J");
}
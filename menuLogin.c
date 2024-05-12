#include "header.h"

//Prototipe fungsi untuk membuat akun baru

// Fungsi untuk login
const char* loginMenu(char *account_type) {
    char username[50];
    char password[50];
    char filename[20];
    FILE *file;
    int is_admin = strcmp(account_type, "admin") == 0 ? 1 : 0;

    sprintf(filename, "akun_%s.txt", account_type);

    // percabagan khusus utk user, jika admin langsung ke sesi login
    if (!is_admin && strcmp(account_type, "user") == 0) {
        char choice;
        label_is_account:
        clearScreen();
        printf("\n\n   Apakah Anda ingin membuat akun baru? [y/n]: ");      // menawarkan buat akun atau login akun pada user
        choice = getOption();
        if (choice == 'y') {
            registerUser(); // Panggil fungsi untuk membuat akun baru

        } else if(choice == 'n'){

        } 
        else{
            printf("\n\n   (Input tidak valid, masukkan input dengan benar)\n\n");
            getEnterKey();
            goto label_is_account;
        }
    }

    // Buka file sesuai dengan tipe akun
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Gagal membuka file akun.\n");
        exit(1);
    }

    // Meminta input username dan password
    printf("\n\n   Masukkan username : ");
    scanf("%[^\n]", username);
    ignoreInputBuffer();
    printf("\n   Masukkan password : ");
    strcpy(password, inputSafetyPassword(password));

    // Mencocokkan username dan password dengan data yang ada di file
    char file_username[50];
    char file_password[50];
    while (fscanf(file, "%s %s", file_username, file_password) != EOF) {
        if (strcmp(file_username, username) == 0 && strcmp(file_password, password) == 0) {
            printf("\n\n   Login berhasil!\n\n");
            getEnterKey();
            fclose(file);
            char *userNameOutput = username;
            return userNameOutput;
        }
    }

    // Jika username tidak ditemukan atau password salah
    printf("\n\n   Username tidak ditemukan atau password salah.\n   Silahkan login ulang.\n\n");
    getEnterKey();
    clearScreen();

    fclose(file);

    exit(EXIT_FAILURE);
}

// Fungsi untuk membuat akun baru
void registerUser() {
    char username[21]; // Karena username maksimal 20 char
    char password[13]; // Karena password maksimal 12 char
    FILE *file;

    while (1) {
        clearScreen();

        // Meminta input username
        printf("\n\n   Masukkan username (maksimal 20 karakter)\t: ");
        scanf("%20s", username);
        ignoreInputBuffer();

        // Memeriksa apakah username sudah digunakan
        file = fopen("akun_user.txt", "r");
        if (file == NULL) {
            printf("Error: Gagal membuka file akun.\n");
            exit(1);
        }
        char file_username[21];
        while (fscanf(file, "%20s %*s", file_username) != EOF) {
            if (strcmp(username, file_username) == 0) {
                printf("\n\n   Username telah digunakan. Silakan pilih username lain\n\n");
                getEnterKey();
                fclose(file);
                break;
            }
        }
        fclose(file);
        if (strcmp(username, file_username) != 0) // Jika username belum digunakan
            break;
    }

    // Meminta input password yang sesuai
    while (1) {
        printf("\n   Masukkan password (antara 8 - 12 karakter)\t: ");
        scanf("%12s", password);
        ignoreInputBuffer();
        if (strlen(password) < 8 || strlen(password) > 12) {
            printf("\n\n   Password harus terdiri dari 8 - 12 karakter\n\n");
            getEnterKey();
        } else {
            break;
        }
    }

    // Buka file akun user untuk menulis akun baru
    file = fopen("akun_user.txt", "a");
    if (file == NULL) {
        printf("Error: Gagal membuka file akun.\n");
        exit(1);
    }

    // Tulis username dan password baru ke file
    fprintf(file, "%s %s\n", username, password);
    printf("\n\n   Akun berhasil dibuat!\n\n");
    getEnterKey();
    fclose(file);
    clearScreen();
}

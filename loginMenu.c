#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Prototipe fungsi untuk membuat akun baru
void registerUser();

// Fungsi untuk login
int loginMenu(char *account_type) {
    char username[50];
    char password[50];
    char filename[20];
    FILE *file;
    int is_admin = strcmp(account_type, "admin") == 0 ? 1 : 0;

    // Buka file sesuai dengan tipe akun
    sprintf(filename, "akun_%s.txt", account_type);
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Gagal membuka file akun.\n");
        exit(1);
    }

    // Meminta input username dan password
    printf("Masukkan username: ");
    scanf("%s", username);
    printf("Masukkan password: ");
    scanf("%s", password);

    // Mencocokkan username dan password dengan data yang ada di file
    char file_username[50];
    char file_password[50];
    while (fscanf(file, "%s %s", file_username, file_password) != EOF) {
        if (strcmp(file_username, username) == 0 && strcmp(file_password, password) == 0) {
            printf("Login berhasil!\n");
            fclose(file);
            return is_admin ? 0 : 1;
        }
    }

    // Jika username tidak ditemukan atau password salah
    printf("Username tidak ditemukan atau password salah.\n");

    // Jika tipe akun adalah "user" dan pengguna belum memiliki akun, tawarkan untuk membuat akun baru
    if (!is_admin && strcmp(account_type, "user") == 0) {
        char choice;
        printf("Apakah Anda ingin membuat akun baru? [y/n]: ");
        scanf(" %c", &choice);
        if (choice == 'y' || choice == 'Y') {
            fclose(file);
            // Panggil fungsi untuk membuat akun baru
            registerUser();
            // Rekursi untuk mencoba login lagi setelah membuat akun baru
            return loginMenu(account_type);
        }
    }

    fclose(file);
    return -1;
}

// Fungsi untuk membuat akun baru
void registerUser() {
    char username[21]; // Karena username maksimal 20 char
    char password[13]; // Karena password maksimal 12 char
    FILE *file;

    while (1) {
        // Meminta input username
        printf("Masukkan username (maksimal 20 karakter): ");
        scanf("%20s", username);

        // Memeriksa apakah username sudah digunakan
        file = fopen("akun_user.txt", "r");
        if (file == NULL) {
            printf("Error: Gagal membuka file akun.\n");
            exit(1);
        }
        char file_username[21];
        while (fscanf(file, "%20s %*s", file_username) != EOF) {
            if (strcmp(username, file_username) == 0) {
                printf("Username telah digunakan. Silakan pilih username lain.\n");
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
        printf("Masukkan password (antara 8 - 12 karakter): ");
        scanf("%12s", password);
        if (strlen(password) < 8 || strlen(password) > 12) {
            printf("Password harus terdiri dari 8 - 12 karakter.\n");
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
    printf("Akun berhasil dibuat!\n");
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Input Argumen!\nArgumen Input : admin/user\n ");
        return EXIT_FAILURE;
    }

    int roleOption;
    if (strcmp(argv[1], "admin") == 0) {
        roleOption = 1;
    } else if (strcmp(argv[1], "user") == 0) {
        roleOption = 2;
    } else {
        printf("Tipe akun tidak valid!\n");
        return EXIT_FAILURE;
    }

    // Login sesuai dengan tipe akun yang diberikan
    int result = loginMenu(argv[1]);
    if (result != -1) {
        printf("Login berhasil sebagai %s.\n", roleOption == 1 ? "admin" : "user");
    }

    return 0;
}
#ifdef _WIN32 // Jika di lingkungan Windows, gunakan Sleep() dari windows.h
#include <windows.h>
#include <conio.h>
#define getch _getch // Ganti getch() dengan _getch() untuk kompatibilitas
#elif defined(__APPLE__) || defined(__MACH__) // Definisikan fungsi getch() untuk lingkungan macOS
#include <ncurses.h>
#else // Definisikan fungsi getch() untuk lingkungan Linux
#include <ncurses.h>
#include <unistd.h>
#endif
        
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<conio.h>
#define N 150
#define M 5

typedef struct dataBuku {
    unsigned int id;
    char userName[20];
    char judul[40];
    char penulis[30];
    char penerbit[20];
    unsigned int jmlHal;
    unsigned int tahun;
    unsigned int stok;
} dataBuku;

void adminMenu(void);
void userMenu(void);

int menuDaftarBuku(char *filestream);
void bookTable(int role);

// Fungsi menu pilihan admin


//Fungsi menu pilihan user
int menuPinjamBuku(char *filestream, char *userName, char *filePinjam);


//Fungsi UI
void clearScreen();
void ignoreInputBuffer();
void menuTitle(int pos);
void pathLoc(char *path);
void textStyle(int mode);
void movePos(int x, int y);
void hidCurs(int ON);
void getEnterKey();
void borderMenu(void);
void greetingText(char *userName);
void loadingScreen(void);
void delay(float sec);  
void borderBukuPinjam(dataBuku *buku, dataBuku *bukuPinjam, char *filestream1, char *filestream2, char *userName);
void bookTable(int role);

//Fungsi Input
char getOption(void);
int getOptionNumb(void);
int getNumb(void);
void ignoreInputBuffer();
int checkNumb(int numb);

//Fungsi operasi data
int countData(char *filename);
void loadData(dataBuku *dBuku, char *filestream, int dataSize);
void loadBukuPinjam(dataBuku *dBuku, char *filestream, int dataSize);
void updateData(dataBuku *dBuku, char *filestream, int dataSize, int id);
void printData(dataBuku *dBuku, char *filestream, int dataSize);
void printBukuPinjam(dataBuku *buku, dataBuku *bukuPinjam, char *filePinjam, char *fileData, char *userName);
int checkPrimeKey(dataBuku *dBuku, int id, int dataSize);
int checkID(int n);
int findID(dataBuku *dbuku, int id_input, int dataSize);
int checkBookKey(dataBuku *dBuku, int id, int dataSize);
int findBookID(dataBuku *bukuPinjam, char*filestream, int dataSize, char*userName, int ID);
int countBukuPinjam(char *filename, char *userName);

// Fungsi tambahan
void removeBook(int id_delete, char *filename);
int pinjamBuku(dataBuku *daftarBuku, dataBuku *bukuPinjam, int id, char *username, char *userFileStream);
void borderBukuPinjam(dataBuku *buku, dataBuku *bukuPinjam, char *filestream1, char *filestream2, char *userName);
void printBukuPinjam(dataBuku *buku, dataBuku *bukuPinjam, char *filePinjam, char *fileData, char *userName);
int kembaliBuku(int id_delete, char *filename, char *userNameDel);
int findBookID(dataBuku *loadBukuPinjam, char*filestream, int dataSize, char*userName, int ID);
int pinjamBuku(dataBuku *daftarBuku, dataBuku *bPinjam, int i, char *username, char *userFileStream);
void registerUser(void);


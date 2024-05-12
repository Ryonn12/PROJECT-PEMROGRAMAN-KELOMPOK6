#ifdef _WIN32 
#include <windows.h>
#include <conio.h>
#define getch _getch
#elif defined(__APPLE__) || defined(__MACH__) 
#include <ncurses.h>
#else 
#include <ncurses.h>
#include <unistd.h>
#endif
        
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
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
    char tglPinjam[25];
    char tglKembali[25];
} dataBuku;

const char* loginMenu(char *account_type);
void registerUser(void);
char* inputSafetyPassword(char regPassword[]);

// Fungsi menu pilihan admin
int menuDaftarBuku(char *fileStream1, char *fileStream2, char *fileStream3, char *userName, int role);
int menuTambahBuku(char *fileStream);
int menuHapusBuku(char *filename);
int menuEditBuku(char *fileStream);

//Fungsi menu pilihan user
int menuPinjamBuku(char *filestream, char *userName, char *filePinjam, char *recordFile);
int menuKembaliBuku(char *fileData, char *filePinjam, char *userName);

// Fungsi operasi data
int countData(char *filename);
void loadData(dataBuku *dBuku, char *fileStream, int dataSize);
void loadBukuPinjam(dataBuku *dBuku, char *fileStream, int dataSize);
void printData(dataBuku *dBuku, char *fileStream, int dataSize);
int checkPrimeKey(dataBuku *dBuku, int id, int dataSize);
int checkBookKey(dataBuku *dBuku, int id, int dataSize);
int checkID(int n);
int findID(dataBuku *dbuku, int id_input, int dataSize);
void updateData(dataBuku *dBuku, char *fileStream, int dataSize, int id);
int cariID(FILE *file, unsigned int id);
int findBookID(dataBuku *bukuPinjam, char*fileStream, int dataSize, char*userName, int ID);
int countBukuPinjam(char *filename, char *userName);
void recTime(char *tglPinjam, char *tglKembali, size_t bufferSize);

//Fungsi UI
void clearScreen();
void ignoreInputBuffer();
void menuTitle(int pos);
void pathLoc(char *path);
void textStyle(int mode);
void movePos(int x, int y);
void hidCurs(int ON);
void getEnterKey();
void bookTable(int role);
void tabelPeminjaman(void);
void borderMenu(void);
void greetingText(char *userName);
void loadingScreen(void);
void delay(float sec);  


//Fungsi Input
char getOption(void);
int getOptionNumb(void);
int getNumb(void);
void ignoreInputBuffer();
int checkNumb(int numb);

void updateRecFile(char *userName, char *tgl);
void daftarRecordUser(dataBuku *buku, char *fileStream, char *userName);
void daftarRecordPinjam(dataBuku *buku, char *fileStream);
void daftarBukuPinjam(dataBuku *buku, char *fileStream);
void daftarBuku(dataBuku *buku,char *fileStream, int role);
int editBook(dataBuku *dBuku, char *fileStream, int id_find);
void removeBook(int id_delete, char *filename);
int pinjamBuku(dataBuku *daftarBuku, dataBuku *bPinjam, int i, char *username, char *filePinjam, char *recordFile);
void tabelBukuPinjam(dataBuku *buku, dataBuku *bukuPinjam, char *fileStream1, char *fileStream2, char *userName);
void printBukuPinjam(dataBuku *buku, dataBuku *bukuPinjam, char *filePinjam, char *fileData, char *userName);
int kembaliBuku(int id_delete, char *filename, char *userNameDel);
int findBookID(dataBuku *loadBukuPinjam, char*fileStream, int dataSize, char*userName, int ID);

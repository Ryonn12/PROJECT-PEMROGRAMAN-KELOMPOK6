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


// Fungsi operasi data


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

//Fungsi Input
char getOption(void);
int getOptionNumb(void);
int getNumb(void);
void ignoreInputBuffer();
int checkNumb(int numb);

//Fungsi operasi data
int countData(char *filename);
void loadData(dataBuku *dBuku, char *filestream, int dataSize);
#include"header.h"

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


// Fungsi operasi data
void updateData(dataBuku *dBuku, char *filestream, int dataSize, int id){
    char *ifp = filestream;

    FILE *file = fopen(ifp, "w"); 
        if(!file){
            perror("   (Gagal melakukan update data)\n\n)");
            printf("   <Tekan Enter untuk lanjut>");
            getchar();
        }

        // update data dari struct ke dalam file
        for(int i=0; i<dataSize; i++){
                fprintf(file, "%u \"%s\" \"%s\" \"%s\" %u %u %u\n", dBuku[i].id, dBuku[i].judul, dBuku[i].penulis, dBuku[i].penerbit, dBuku[i].jmlHal, dBuku[i].tahun, dBuku[i].stok);
        }
        fclose(file);
        
}
int countData(char *filename){
    int jmlData=1;

    char *ifp = filename;
    FILE *file = fopen(ifp, "r");

    char ch;
    while ((ch = fgetc(file)) != EOF) {      // menghitung jumlah data yang masuk dari file teks
        if (ch == '\n') {
            jmlData++;
        }
    }
    fclose(file);

    return jmlData-1;
}
void loadData(dataBuku *dBuku, char *filestream, int dataSize){
    char *ifp = filestream;
    FILE *file = fopen(ifp, "r");
  
    char buffer[512];
    for (int i = 0; i < dataSize; i++) {     // inisialisasi data file ke struct
        fgets(buffer, 512, file);
        sscanf(buffer, "%u \"%49[^\"]\" \"%29[^\"]\" \"%19[^\"]\" %u %u %u\n", &dBuku[i].id, dBuku[i].judul, dBuku[i].penulis, dBuku[i].penerbit, &dBuku[i].jmlHal, &dBuku[i].tahun, &dBuku[i].stok);
    }
    fclose(file);

}
void loadBukuPinjam(dataBuku *dBuku, char *filestream, int dataSize){
    char *ifp = filestream;
    FILE *file = fopen(ifp, "r");

    char buffer[512];
    for (int i = 0; i < dataSize; i++) {     // inisialisasi data file ke struct
        fgets(buffer, 512, file);
        sscanf(buffer, "\"%20[^\"]\" %u \"%49[^\"]\" \"%20[^\"]\"  \"%20[^\"]\" \n", dBuku[i].userName, &dBuku[i].id, dBuku[i].judul, dBuku[i].tglPinjam, dBuku[i].tglKembali);
    }
    fclose(file);

}
void printData(dataBuku *dBuku, char *filestream, int dataSize){

    for(int i=0; i<dataSize; i++){
        printf("%u   %-40s %-30s %-25s %u   %u   %u\n", dBuku[i].id, dBuku[i].judul, dBuku[i].penulis, dBuku[i].penerbit, dBuku[i].jmlHal, dBuku[i].tahun, dBuku[i].stok);
    }
}
void printBukuPinjam(dataBuku *buku, dataBuku *bukuPinjam, char *filePinjam, char *fileData, char *userName) {
    char tempFile[] = "tempFile.txt";
    char *tfp = tempFile;
    char *name = userName;
     int jmlBukuPinjam = countData(filePinjam);

    movePos(54, 6);
    printf("D A F T A R  B U K U  P I N J A M A N");

    movePos(0, 11);
    int numb=1;
    for(int i = 0; i < jmlBukuPinjam; i++){
        if(strcmp(bukuPinjam[i].userName, name) == 0){
            printf("  0%-4u %-6u %-66s %-37s %-37s \n", numb, bukuPinjam[i].id, bukuPinjam[i].judul, bukuPinjam[i].tglPinjam, bukuPinjam[i].tglKembali);
            numb++;
        }
    }
    textStyle(0);
}
int checkPrimeKey(dataBuku *dBuku, int id, int dataSize){
    for(int i=0; i<dataSize; i++){             
        if(id == dBuku[i].id){
            return 1;               // return id ketika id buku ditemukan
        }
    }
    return 0;       //return 0 ketika id tidak ditemukan 
}
int checkID(int n){
    if((n>=1000) || (n<100)){
        return 1;              // return 1 ketika id tidak ditemukan
    }                          // hanya berlaku pada module menuHapusBuku

    return n;
}
int findID(dataBuku *dbuku, int id_input, int dataSize){
    int id_find;
    for(int i = 0; i < dataSize; i++){
        if((unsigned int)id_input == dbuku[i].id){
        id_find = i;    // id buku ditemukan dan mengembalikan indeks buku
        return id_find;
        }
    }
    return -1;  // return -1 ketika id tidak ditemukan
}
int checkBookKey(dataBuku *dBuku, int id, int dataSize){
    for(int i=0; i<dataSize; i++){             
        if(id == dBuku[i].id){
            return 1;               // return id ketika id buku ditemukan
        }
    }
    return 0;       //return 0 ketika id tidak ditemukan 
}
int findBookID(dataBuku *bukuPinjam, char*filestream, int dataSize, char*userName, int ID){
    
    for(int i=0; i<dataSize; i++){ 
        if(strcmp(bukuPinjam[i].userName, userName)==0){
                if(ID==bukuPinjam[i].id){
                    return ID;      // return id jika sama
                }
        }
        
        
    }
    return 0;       //return 0 ketika id tidak ditemukan 
}
int countBukuPinjam(char *filename, char *userName) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return -1;
    }
    char line[512]; 
    int count = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, userName) != NULL) {
            count++;
        }
    }
    fclose(file);
    return count;
}
void recTime(char *tglPinjam, char *tglKembali, size_t bufferSize){
    struct tm *timeVal;
    time_t currentTime, futureTime;
    
    currentTime = time(NULL);
    timeVal = localtime(&currentTime);
    strftime(tglPinjam, bufferSize, "%Y-%m-%d %H:%M:%S", timeVal);

    futureTime = currentTime + (14*24*60*60);
    
    timeVal = localtime(&futureTime);
    strftime(tglKembali, bufferSize, "%Y-%m-%d %H:%M:%S", timeVal);
}

//Fungsi UI
void clearScreen(){
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
void menuTitle(int pos){
    if(pos==0){
        movePos(0,30);
        for(int i=0; i<148; i++){
            printf("=");
        }

        movePos(63,32);
        printf("SISTEM PERPUSTAKAAN");
        
        movePos(58,33);
        printf("PROJECT-PEMROGRAMAN-KELOMPOK6");

        movePos(0,37);
        for(int i=0; i<148; i++){
            printf("=");
        }
        movePos(63,24);
    }
    if(pos==1){
        movePos(0,30);
        for(int i=0; i<148; i++){
            printf("=");
        }

        movePos(63,32);
        printf("SISTEM PERPUSTAKAAN");
        
        movePos(58,33);
        printf("PROJECT-PEMROGRAMAN-KELOMPOK6");

        movePos(0,37);
        for(int i=0; i<148; i++){
            printf("=");
        }
        movePos(2,6);
    }

}
void pathLoc(char *path){
    for(int i=0; i<148; i++){
        printf("=");
    }
    printf("\n");
    printf("%s", path);
    printf("\n");
    for(int i=0; i<148; i++){
        printf("=");
    }
    printf("\n\n\n");    
} 
void textStyle(int mode){
    printf("\033[%dm", mode);
}
void movePos(int x, int y){
    printf("\033[%d;%dH", y, x);
}
void hidCurs(int ON){
    if (ON==1){
        printf("\e[?25l"); // Menyembunyikan kursor
    } if(ON==0){
        printf("\e[?25h"); // Menampilkan kembali kursor
    }
}
void bookTable(int role){

    clearScreen();
    if(role == 0){
        pathLoc("  Menu Admin\\Daftar Buku\\ Buku Perpustakaan");
    } else if(role == 1){
        pathLoc("  Menu User\\Daftar Buku\\ Buku Perpustakaan");
    }
    
     //garis horizontal
    for(int i=2; i<148;i++){   
        movePos(i, 7);
        printf("-");
        movePos(i,9);
        printf("-");
        movePos(i,30);
        printf("-");
    }

    //garis vertikal
    for(int i=8; i<30; i++){    
        movePos(0,i);
        printf("|");
        movePos(6,i);
        printf("|");
        movePos(15,i);
        printf("|");
        movePos(54,i);
        printf("|");
        movePos(82,i);
        printf("|");
        movePos(104,i);
        printf("|");
        movePos(121,i);
        printf("|");
        movePos(136,i);
        printf("|");
        movePos(150,i);
        printf("|");
    }

    // nama kolom
    int p=8;
    movePos(3, p);          
    printf("NO");
    movePos(7, p);
    printf("ID Buku");
    movePos(27, p);
    printf("Judul Buku");
    movePos(61, p);
    printf("Penulis");
    movePos(90, p);
    printf("Penerbit");
    movePos(106, p);
    printf("Jumlah Halaman");
    movePos(123, p);
    printf("Tahun Terbit");
    movePos(138, p);
    printf("Stok Buku");
}
void borderMenu(void){

    // garis vertikal
    for(int i=8; i<22; i++){
        movePos(47,i);
        printf("|");
        movePos(97,i);
        printf("|");
    }

    // garis horizontal
    for(int i=48; i<=96; i++){
        movePos(i,7);
        printf("-");
        movePos(i,10);
        printf("-");
        movePos(i,22);
        printf("-");
    }
}
void tabelBukuPinjam(dataBuku *buku, dataBuku *bukuPinjam, char *filestream1, char *filestream2, char *userName){
    int jmlBukuPinjam = countData(filestream1);
    int jmlData = countData(filestream2);
    loadBukuPinjam(bukuPinjam, filestream1, jmlBukuPinjam);
    loadData(buku, filestream2, jmlData);

    clearScreen();
    pathLoc("  Menu User\\Kembalikan Buku");
    // menuTitle(1);
    printBukuPinjam(buku, bukuPinjam, filestream1, filestream2, userName);

    movePos(3,9);
    printf("NO");
    movePos(7,9);
    printf("ID Buku");
    movePos(37,9);
    printf("Judul Buku");
    movePos(83,9);
    printf("Tanggal Peminjaman");
    movePos(120,9);
    printf("Tanggal Pengembalian");

    for(int i=2; i<147; i++){
        movePos(i,8); printf("-");
        movePos(i,10); printf("-");
        movePos(i,8); printf("-");
        movePos(i,20); printf("-");
    }

    for(int i=9; i<20; i++){
        movePos(0,i); printf("|");
        movePos(6,i); printf("|");
        movePos(14,i); printf("|");
        movePos(73,i); printf("|");
        movePos(110,i); printf("|");
        movePos(147,i); printf("|");
    }

    movePos(0,23);
}
void getEnterKey(){
    hidCurs(1);
    printf("   <Tekan enter untuk lanjut>");
    ignoreInputBuffer();
    clearScreen();
    hidCurs(0);
}
void greetingText(char *userName){
    movePos(4,5);
    textStyle(1);
    printf("Welcome, %s ", userName);
    movePos(63,24);
    textStyle(0);
}
void loadingScreen(void){
#ifdef _WIN32
    clearScreen();
    hidCurs(1);
    movePos(60,15);
    printf("L "); delay(0.09); printf("O "); delay(0.09); printf("G "); delay(0.09); printf("I "); delay(0.09); printf("N "); delay(0.09);
    printf("  S "); delay(0.09); printf("U "); delay(0.09); printf("C "); delay(0.09); printf("C "); delay(0.09); printf("E "); delay(0.09); printf("S "); delay(0.09); printf("S ");
    delay(0.09);system("cls");delay(0.09);movePos(55,15);
    printf("  S "); delay(0.09); printf("T "); delay(0.09); printf("A "); delay(0.09); printf("R "); delay(0.09); printf("T "); delay(0.09); printf("I "); delay(0.09); printf("N "); printf("G "); delay(0.09);
    printf("  P "); delay(0.09);printf("R "); delay(0.09);printf("O "); delay(0.09);printf("G "); delay(0.09);printf("R "); delay(0.09);printf("A "); delay(0.09);printf("M "); delay(0.09);

    int is_delay=0;
    label_delay:
    movePos(88,15);
    double time=0.05;
    for(int i=0; i<3; i++){
        delay(time);
        printf(" .");
        time += time+0.075;
    }
    movePos(89,15);
    delay(0.1);
    printf("       ");
    delay(0.999);
    if(is_delay<2){
        movePos(15,90);
        is_delay++;
        goto label_delay;
    }
    delay(0.09);
    hidCurs(0);
#endif
}
void delay(float sec) {
    #ifdef _WIN32 // Jika di lingkungan Windows, gunakan Sleep() dari windows.h
        Sleep(sec * 1000); // Sleep() membutuhkan argumen dalam milidetik
    #else // Jika di lingkungan UNIX (macOS, Linux, dll), gunakan sleep() dari unistd.h
        #ifdef __APPLE__ // Jika di lingkungan macOS, gunakan usleep()
        usleep(sec * 1000000); // usleep() membutuhkan argumen dalam mikrodetik
        #else // Jika di lingkungan Linux dan lainnya, gunakan sleep()
        sleep(sec); // sleep() membutuhkan argumen dalam detik
        #endif
#endif
}   


// Fungsi input
char* inputSafetyPassword(char regPassword[]) {
#ifdef _WIN32  
    int i = 0;
    while(1) {
        regPassword[i] = getch();
        if(regPassword[i] == '\r') {
            regPassword[i] = '\0';
            break;
        } else if (regPassword[i] == 8 && i > 0) {
            printf("\b \b");
            i--;
        } else {
            printf("*");
            i++;
        }
    }
    if(strlen(regPassword) >= 8 && strlen(regPassword) <= 12) {
        return regPassword; // Mengembalikan string konstan "success"
    } else {
        return "fail"; // Mengembalikan string konstan "fail"
    }
#else
    char buffer[13];
    scanf("%[^\n]", regPassword);
    ignoreInputBuffer();
     if(strlen(regPassword) >= 8 && strlen(regPassword) <= 12) {
        return regPassword; // Mengembalikan string konstan "success"
    } else {
        return "fail"; // Mengembalikan string konstan "fail"
    }
#endif
}
void ignoreInputBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {   // membersihkan buffer input
        continue;
    }
}
int checkNumb(int numb){
    if((numb>1000000) || (numb<0)){
        return -1;
    } else{
        return numb;
    }
}
int getOptionNumb(void){
    int option;
    char input[30];
    fgets(input, sizeof(input), stdin);
    int length = strlen(input);
    
    if(length>2){   // invalid
        option = -1;
    } 

    else if(length==2){
        if( (input[0]=='1')){  
        option = 1;
        }
        else if ( (input[0]=='2') ){    
            option = 2;
        }
        else if((input[0]=='3')){   
            option = 3;   
        }
         else if((input[0]=='4')){   
            option = 4;   
        }
         else if((input[0]=='5')){   
            option = 5;   
        }
         else if((input[0]=='6')){   
            option = 6;   
        }
         else if((input[0]=='7')){   
            option = 7;   
        }
         else if((input[0]=='8')){   
            option = 8;   
        }
         else if((input[0]=='9')){   
            option = 9;   
        }
         else if((input[0]=='0')){   
            option = 0;   
        } else{
            option = -1;
        }
    }
    return option;
}
int getNumb(void){
#ifdef _WIN32
    char buffer[10]; 
    int numb;
    fgets(buffer, strlen(buffer),stdin);
        if (sscanf(buffer, "%d", &numb) == 1) {  
            if(numb > 999){
                ignoreInputBuffer();
            }
            return numb;
        } else {      
            return -1; 
        }
#else
    int numb;
    scanf("%d", &numb);
    return numb;
#endif
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
        else{   
            option = 'x';   
        }
    }
    return option;
}
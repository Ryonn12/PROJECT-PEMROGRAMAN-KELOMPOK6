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
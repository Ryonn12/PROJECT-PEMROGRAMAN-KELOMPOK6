#include"header.h"

int menuDaftarBuku(char *filestream){
    clearScreen();
    int jmlData = 0;
    int jmlBuku = 0;

    char *ifp = filestream;
    jmlData = countData(ifp);

    if(jmlData>N){
        jmlData = N;
    }

    dataBuku buku[N]; // Menggunakan array dari struct buku

    loadData(buku, ifp, jmlData);       // mengisi nilai struct dari file

    for(int i=0; i<jmlData; i++){
        jmlBuku += buku[i].stok;    // menghitung jumlah seluruh buku
    }

    char ch;
    int page = 1;
    int jmlPage = 0;
    int temp = jmlData;
    if(jmlData<=N){                         // menghitung jumlah page pada daftar buku
        for (int i = 1; temp > 0; i++){         
            temp -= 20;
            jmlPage++;
        }
    } 
    if(jmlData>N){
        for (int i = 1; temp > 0; i++){         
            temp -= 20;
            jmlPage++;
        }
    }
 
    while(1){
        hidCurs(1);
        bookTable(1 );
        movePos(65,5);
        printf("< P A G E  %d >", page);

        int ordinat=10;
        int batas = page*20;
        for(int i=batas- 20; i<batas; i++){

            textStyle(0);
            if(i%2 == 1){
                textStyle(2);
            }
            if(i<=8){
                movePos(3, ordinat);    //cetak nomor 1-9
                printf("0%d", i+1);     
            } else{
                movePos(3, ordinat);    //cetak nomor > 9
                printf("%d", i+1);
            }        

            // cetak data 
            movePos(9, ordinat); printf("%u", buku[i].id);
            movePos(16, ordinat); printf("%s", buku[i].judul);
            movePos(55, ordinat); printf("%s", buku[i].penulis);
            movePos(83, ordinat); printf("%s", buku[i].penerbit);
            movePos(111, ordinat); printf("%u", buku[i].jmlHal);
            movePos(127, ordinat); printf("%u", buku[i].tahun);
            movePos(142, ordinat); printf("%u", buku[i].stok);
            ordinat++;
            if(i==jmlData-1){
                break;
            }
        }

        textStyle(0);
        movePos(130,31);   
        printf("Jumlah Data : %d", jmlData);
        movePos(130,32);   
        printf("Jumlah Buku : %d", jmlBuku);
        movePos(139,35);
        printf("Page %d/%d", page, jmlPage);

        // navigasi halaman
        movePos(4,31);
        printf("(1) Pindah ke halaman sebelumnya");
        movePos(4,32);
        printf("(2) Pindah ke halaman selanjutnya");
        movePos(4,33);
        printf("(3) Kembali");
        movePos(8,35);
        printf("Masukkan Pilihan [1-3] : ");
        hidCurs(0);
        ch = getchar();
        if(ch == '2'){
            page++;             // pindah halaman ke depan
            if(page>jmlPage){
                page=jmlPage;
            }
        } 
        if(ch == '1'){
            page--;             // pindah halaman ke belakang
            if(page<1){
                page=1;
            }
        } 
        if (ch == '3'){
            break;
        }
        clearScreen();
    }
    
    getchar();
    movePos(0,0);
    clearScreen();
}
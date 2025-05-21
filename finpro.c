#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

void welcome()
{
    int i; // deklarasi variabel integer
    printf("!--- Harap Fullscreen lalu tekan ENTER untuk memulai aplikasi ---!");
    getchar();     // memanggil function getchar
    system("CLS"); // Membersihkan layar
    Sleep(800);    // menjeda program selama 0.8 detik
    system("color B0");
    printf("\n\n\n\n\n\n\n");
    char a[] = {"\t\t\t\t\t\t\t\t=====================================\n"
                "\t\t\t\t\t\t\t\t|---- Selamat Datang Di Aplikasi ---|\n"
                "\t\t\t\t\t\t\t\t| Machine for sustainable production|\n"
                "\t\t\t\t\t\t\t\t|---------- Kelompok Julia ---------|\n"
                "\t\t\t\t\t\t\t\t|------- Pemrograman Dasar 01 ------|\n"
                "\t\t\t\t\t\t\t\t=====================================\n\n"};
    for (i = 0; a[i] != a[283]; i++)
    {
        printf("%c", a[i]);
        Sleep(5);
    }
    printf("\t\t\t\t\t\t\t\t\t\tLoading... \n\n");
    Beep(659, 400);
    Sleep(1000); // menjeda program selama 1 detik
    for (i = 1; i <= 172; i++)
    {
        printf("%c", 223); // 233 adalah kode KARAKTER beta di dalam ASCII2
        if (i == 60 || i == 100)
            Sleep(500); // menjeda program selama 0.5 detik
        Sleep(12);
    }
    Sleep(1600);   // menjeda program selama 1.6 detik
    system("CLS"); // Membersihkan layar
}

int main(){
    welcome();
}

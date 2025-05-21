#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


//define variabel tetap
#define JamKerjaPerHari 8
#define JamPerHari 24
#define HariPerTahun 365

//tipe data tambahan
typedef struct{
    char dataNama[30];
    float dataListrikKwH, dataEmisiMwH, dataProduksi, dataHargaMesin;
} KlasifikasiMesin;

//enum 

//function kalkulasi utama
float KalkulasiHematEnergi(); //ini output nilainya aja
float KalkulasiEmisiKarbon(); 
float KalkulasiKeuntunganProduksi(KlasifikasiMesin mesinSample, KlasifikasiMesin normMesin, int tahun);
//ini cari banyak produksi per rupiah, produksi dari laju kali total jam

//function tambahan
int GantiMesinPerTahun(int ovrHeating, int tahun);
//call by reference
void SortMesinTerbaik(float score[], KlasifikasiMesin objek[]);
void Swap(float* a, float* b);

//Fungsi User Interface input
void welcome();

int main(){
    welcome();

    //input berapa mesin
    printf("\n\n\n\n\n\n\n");
    printf("\t\t\t\t\t\t\t\t================== Mulai Simulasi ===================\n");
    int totalMesin;
    
    printf("\t\t\t\t\t\t\t\tTotal mesin yang ingin disimulasikan :");
    scanf("%d", &totalMesin);
    //input data tahun, listrik (kwh), emisi (mwh), produksi (item/jam), harga mesin(rupiah). bikin loop nah cari nilai terbesar setiap kategori, jadiin untuk variabel normalisasi
    KlasifikasiMesin nMesin = {0};
    KlasifikasiMesin *mesin = malloc(totalMesin * sizeof(KlasifikasiMesin));

    //nanti tambah printf
    for (int i = 0; i < totalMesin; i++){
        printf("\n\t\t\t\t\t\t\t\tData Mesin ke-%d ", i+1);
        printf("\n\t\t\t\t\t\t\t\tNama Mesin ke-%d: ", i+1);
        getchar();//membersihkan newline sisa input sebelumnya
        scanf(" %[^\n]", mesin[i].dataNama);

        printf("\t\t\t\t\t\t\t\tBesar listrik yang digunakan (KwH): ");
        scanf("%f", &mesin[i].dataListrikKwH);
        //cari data normanisasi
        nMesin.dataListrikKwH = (mesin[i].dataListrikKwH > nMesin.dataListrikKwH) ? mesin[i].dataListrikKwH : nMesin.dataListrikKwH;

        printf("\t\t\t\t\t\t\t\tTotal emisi karbon per jam (MwH): ");
        scanf("%f", &mesin[i].dataEmisiMwH);
        //cari data normanisasi
        nMesin.dataEmisiMwH = (mesin[i].dataEmisiMwH > nMesin.dataEmisiMwH) ? mesin[i].dataEmisiMwH : nMesin.dataEmisiMwH;

        printf("\t\t\t\t\t\t\t\tTotal mesin memproduksi per jam (Kg): ");
        scanf("%f", &mesin[i].dataProduksi); 
        //cari data normanisasi
        nMesin.dataProduksi = (mesin[i].dataProduksi > nMesin.dataProduksi) ? mesin[i].dataProduksi : nMesin.dataProduksi;

        printf("\t\t\t\t\t\t\t\tHarga mesin (Juta): ");
        scanf("%f", &mesin[i].dataHargaMesin);
        nMesin.dataHargaMesin = (mesin[i].dataHargaMesin > nMesin.dataHargaMesin) ? mesin[i].dataHargaMesin: nMesin.dataHargaMesin;

        printf("\n");
    }

    //berapa tahun mesin perlu dipake
    int tahun;
    printf("\t\t\t\t\t\t\t\tTarget tahun mesin digunakan: ");
    scanf("%d", &tahun);
    
    //kalkulasi score dan simulasi tiap mesin
    float scoreAkhir[totalMesin];
    for (int i = 0; i < totalMesin ; i++){
        //panggil fungsi hemat energi 
        float scoreHE = 30 * KalkulasiHematEnergi(/*masukin per mesin*/) / KalkulasiHematEnergi(/*parameter normalisasi*/);
        //panggil fungsi emisi karbon
        float scoreEM = 25 * KalkulasiEmisiKarbon(/*masukin per mesin*/) / KalkulasiHematEnergi(/*parameter normalisasi*/);
        //panggil fungsi keuntungan
        float scoreKU = 25 * KalkulasiKeuntunganProduksi(mesin[i], nMesin, tahun) / KalkulasiKeuntunganProduksi(nMesin, nMesin, tahun);
        //score akhir efektivitas 
        scoreAkhir[i] = scoreEM + scoreHE + scoreKU;
    }
    
    //urutin mesin yang paling efektif
    SortMesinTerbaik(scoreAkhir, mesin);
    
    //print out urutan

    //end
    free(mesin);
    return 0;
}

//isi function
//serangkaian function produksi
int GantiMesinPerTahun(int ovrHeating, int tahun){
    int gantiMesin = 0;
    return gantiMesin;
}

float KalkulasiKeuntunganProduksi(KlasifikasiMesin mesinSample, KlasifikasiMesin normMesin, int tahun){
    //cari persamaan overHeat
    float OvhTime = 0.3 * (mesinSample.dataListrikKwH / normMesin.dataListrikKwH) + 0.3 * (mesinSample.dataEmisiMwH / normMesin.dataEmisiMwH) + 0.4 * (mesinSample.dataProduksi / normMesin.dataProduksi);

    //cari berapa kali ganti mesin selama periodo tahun
    int gantiMesin = GantiMesinPerTahun (OvhTime, tahun);

    //cuma buat error handle pas di run, krn nilai blm di assign
    float scoreKeuntungan = 0;
    return scoreKeuntungan;
}

float KalkulasiHematEnergi(){

}

float KalkulasiEmisiKarbon(){

}

void SortMesinTerbaik(float score[], KlasifikasiMesin objek[]){

}

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


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
typedef enum {
    GOOD = 5500, WARNING = 6150, DANGER = 9200, FATAL = 11050
} StatusMesin;

//function kalkulasi utama
float KalkulasiHematEnergi(KlasifikasiMesin mesinSample, KlasifikasiMesin normMesin); //ini output nilainya aja
float KalkulasiEmisiKarbon(KlasifikasiMesin mesinSample, KlasifikasiMesin normMesin); 
float KalkulasiKeuntunganProduksi(KlasifikasiMesin mesinSample, KlasifikasiMesin normMesin, int tahun);
//ini cari banyak produksi per rupiah, produksi dari laju kali total jam

//function tambahan
int GantiMesinPerTahun(float ovrHeating, int tahun);
//call by reference
void SwapObjek(KlasifikasiMesin* a, KlasifikasiMesin* b);
void Swap(float* a, float* b);
void SortMesinTerbaik(float score[], KlasifikasiMesin objek[], int totalMesin);

//Fungsi User Interface input
void welcome();
void printDataMesin(KlasifikasiMesin *mesin, float score[], int totalMesin) {
    printf("=============================================================================================================================\n");
    printf("| No | Nama Mesin                 | Listrik (kWh) | Emisi (MWh) | Produksi (item/jam) | Harga Mesin (Juta) | Skor Akhir     |\n");
    printf("=============================================================================================================================\n");

    for (int i = 0; i < totalMesin; i++) {
        printf("| %-2d | %-25s | %-13.2f | %-11.2f | %-19.2f | %-17.2f | %-14.4f |\n",
               i + 1,
               mesin[i].dataNama,
               mesin[i].dataListrikKwH,
               mesin[i].dataEmisiMwH,
               mesin[i].dataProduksi,
               mesin[i].dataHargaMesin,
               score[i]);
    }

    printf("===========================================================================================================================\n");
}


int main(){
    welcome();

    //input berapa mesin
    printf("\n\n\n\n\n\n\n");
    printf("\t\t\t\t\t\t\t\t================== Mulai Simulasi ===================\n");
    int totalMesin;
    
    printf("\t\t\t\t\t\t\t\tTotal mesin yang ingin disimulasikan :");
    scanf("%d", &totalMesin);

    int i = 0, j = 0, k = 0, z = 0;
    KlasifikasiMesin *mesin = malloc(totalMesin * sizeof(KlasifikasiMesin));
    char lanjutInput;

    //input data tahun, listrik (kwh), emisi (mwh), produksi (item/jam), harga mesin(rupiah). bikin loop nah cari nilai terbesar setiap kategori, jadiin untuk variabel normalisasi
    KlasifikasiMesin nMesin = {0};
    KlasifikasiMesin nMesinProduksi = {0};
    do
    {
        //deklarasi arrray 
        float *semuaEfisiensi = malloc((totalMesin+1) * sizeof(float));
        float *scoreAkhir = malloc(totalMesin * sizeof(float));

        //bikinin error handling per input
        for ( ; i < totalMesin; i++){
            printf("\n\t\t\t\t\t\t\t\tData Mesin ke-%d ", i+1);
            printf("\n\t\t\t\t\t\t\t\tNama Mesin ke-%d: ", i+1);
            getchar();//membersihkan newline sisa input sebelumnya
            scanf(" %[^\n]", mesin[i].dataNama);

            //contoh error handling
            int inpStatus;
            do
            {
                printf("\t\t\t\t\t\t\t\tBesar listrik yang digunakan (KwH): ");
                inpStatus = scanf("%f", &mesin[i].dataListrikKwH);
                if (inpStatus != 1){
                    /* bikinin printf input gavalid */
                    while (getchar() != '\n');}
                
            } while (inpStatus != 1);

            //cari data normanisasi
            nMesin.dataListrikKwH = (mesin[i].dataListrikKwH > nMesin.dataListrikKwH) ? mesin[i].dataListrikKwH : nMesin.dataListrikKwH;
            nMesinProduksi.dataListrikKwH = (mesin[i].dataListrikKwH < nMesinProduksi.dataListrikKwH) ? mesin[i].dataListrikKwH : nMesinProduksi.dataListrikKwH;

            printf("\t\t\t\t\t\t\t\tTotal emisi karbon per jam (MwH): ");
            scanf("%f", &mesin[i].dataEmisiMwH);
            //cari data normanisasi
            nMesin.dataEmisiMwH = (mesin[i].dataEmisiMwH > nMesin.dataEmisiMwH) ? mesin[i].dataEmisiMwH : nMesin.dataEmisiMwH;
            nMesinProduksi.dataEmisiMwH = (mesin[i].dataEmisiMwH < nMesinProduksi.dataEmisiMwH) ? mesin[i].dataEmisiMwH : nMesinProduksi.dataEmisiMwH;

            printf("\t\t\t\t\t\t\t\tTotal mesin memproduksi per jam (Kg): ");
            scanf("%f", &mesin[i].dataProduksi); 
            //cari data normanisasi
            nMesin.dataProduksi = (mesin[i].dataProduksi > nMesin.dataProduksi) ? mesin[i].dataProduksi : nMesin.dataProduksi;
            nMesinProduksi.dataProduksi = (mesin[i].dataProduksi > nMesinProduksi.dataProduksi) ? mesin[i].dataProduksi : nMesinProduksi.dataProduksi;

            printf("\t\t\t\t\t\t\t\tHarga mesin (Juta): ");
            scanf("%f", &mesin[i].dataHargaMesin);
            nMesin.dataHargaMesin = (mesin[i].dataHargaMesin > nMesin.dataHargaMesin) ? mesin[i].dataHargaMesin: nMesin.dataHargaMesin;
            nMesinProduksi.dataHargaMesin = (mesin[i].dataHargaMesin < nMesinProduksi.dataHargaMesin) ? mesin[i].dataHargaMesin : nMesinProduksi.dataHargaMesin;

            printf("\n");

        }

        //berapa tahun mesin perlu dipake
        int tahun;
        printf("\t\t\t\t\t\t\t\tTarget tahun mesin digunakan: ");
        scanf("%d", &tahun);

        //cari efesiensi mesin maksimum
        float efisiensiMaks = 0;

        for (j=0 ; j <= totalMesin; j++) {
            if (j == totalMesin){
                semuaEfisiensi[j] = KalkulasiKeuntunganProduksi(nMesinProduksi, nMesin, tahun);}
            else{semuaEfisiensi[j] = KalkulasiKeuntunganProduksi(mesin[j], nMesin, tahun);}
            if (semuaEfisiensi[j] > efisiensiMaks) {
                efisiensiMaks = semuaEfisiensi[j];
            }
        }

        //kalkulasi score dan simulasi tiap mesin
        for (k = 0 ; k < totalMesin ; k++){
            //panggil fungsi hemat energi 
            float scoreHE = 30 * KalkulasiHematEnergi(mesin[k], nMesin);
            //panggil fungsi emisi karbon
            float scoreEM = 25 * KalkulasiEmisiKarbon(mesin[k], nMesin);
            //panggil fungsi keuntungan
            float scoreKU = 45 * (1 - semuaEfisiensi[k] / efisiensiMaks);
            //score akhir efektivitas 
            scoreAkhir[k] = scoreEM + scoreHE + scoreKU;
        }

        //urutin mesin yang paling efektif
	    SortMesinTerbaik(scoreAkhir, mesin, totalMesin);

        //print out urutan
        system("CLS"); // Membersihkan layar
        printDataMesin(mesin, scoreAkhir, totalMesin);

        // apakah tambah mesin lagi
        printf("\nTambah mesin lagi? (y/n) : ");
        scanf(" %c", &lanjutInput);  // Spasi sebelum %c untuk skip newline

        // apakah nambah mesin
       if (lanjutInput == 'Y' || lanjutInput == 'y') {
            int tambahan;
            printf("Tambah berapa mesin yang ingin disimulasikan : ");
            scanf("%d", &tambahan);

            // Alokasi memori sementara
            KlasifikasiMesin *temp = realloc(mesin, (totalMesin + tambahan) * sizeof(KlasifikasiMesin));
            free(scoreAkhir);
            free(semuaEfisiensi);

            if (temp == NULL) {
                printf("❌ Gagal menambah memori! Program dihentikan.\n");
                exit(1);
            }
        
            // Jika berhasil, update pointer utama
            mesin = temp;
        
            system("CLS"); // Membersihkan layar
            printf("\t\t\t\t\t\t\t\t================== Mulai Simulasi ===================\n");
            totalMesin += tambahan; // update jumlah total mesin
        }


    } while (lanjutInput == 'Y' || lanjutInput == 'y'); 
    
    //end
    free(mesin);

    return 0;
}

//isi function
//serangkaian function produksi
int GantiMesinPerTahun(float ovrHeating, int tahun){
    float ovhValue = ovrHeating;
    int gantiMesin = 0;
    float statusPoin = 0;

    for (int i = 0; i < tahun; i++){
        for (int j = 0; j < HariPerTahun ; j++){
            statusPoin += ovhValue * JamKerjaPerHari; //jadi status poin nambah sesuai kecepatan overheating
            statusPoin -= (1 - ovhValue) * (24 - JamKerjaPerHari); // pendinginan saat jam istirahat
            //saat mencapai FATAL, mesin diganti
            if (statusPoin >= FATAL){
                statusPoin = 0; //restart 
                ovhValue = ovrHeating; //kembali ke nilai defaulft mesin
                gantiMesin++;
            }
            //laju naik saat mencapai kondisi tertentu
            else if (statusPoin >= DANGER){ovhValue *= 1.7;}
            else if (statusPoin >= WARNING){ovhValue *= 1.15;}
        }
        
    }
    return gantiMesin;
}

float KalkulasiKeuntunganProduksi(KlasifikasiMesin mesinSample, KlasifikasiMesin normMesin, int tahun){
    //cari persamaan overHeat
    float OvhTime = 0.3 * (mesinSample.dataListrikKwH / normMesin.dataListrikKwH) + 0.3 * (mesinSample.dataEmisiMwH / normMesin.dataEmisiMwH) + 0.4 * (mesinSample.dataProduksi / normMesin.dataProduksi);

    //cari berapa kali ganti mesin selama periode tahun
    int gantiMesin = GantiMesinPerTahun(OvhTime, tahun);
    float totalCost = (1 + gantiMesin) * mesinSample.dataHargaMesin;

    float scoreKeuntungan = mesinSample.dataProduksi / totalCost;

    return scoreKeuntungan;
}

float KalkulasiHematEnergi(KlasifikasiMesin mesinSample, KlasifikasiMesin normMesin){
	// semakin kecil listrik yang digunakan, maka akan semakin hemat
	if (mesinSample.dataListrikKwH <= 0 || normMesin.dataListrikKwH <= 0){
		return 0;
	}else {
		float kalkuHE;
		kalkuHE = 1 - (mesinSample.dataListrikKwH / normMesin.dataListrikKwH); 
		return kalkuHE;
	}

}

float KalkulasiEmisiKarbon(KlasifikasiMesin mesinSample, KlasifikasiMesin normMesin){
	// semakin kecil emisi yang dihasilkan  maka akan semakin ramah lingkungan
	if (mesinSample.dataEmisiMwH <= 0 || normMesin.dataEmisiMwH <= 0){
		return 0;
	}else {
		float kalkuEM;
		kalkuEM = 1 - (mesinSample.dataEmisiMwH / normMesin.dataEmisiMwH);
		return kalkuEM;
	}
}

//sort score mesin
void SwapObjek(KlasifikasiMesin* a, KlasifikasiMesin* b) {
    KlasifikasiMesin temp = *a;
    *a = *b;
    *b = temp;
}

void Swap(float* a, float* b) {
    float temp = *a;
    *a = *b;
    *b = temp;
}

void SortMesinTerbaik(float score[], KlasifikasiMesin objek[], int totalMesin) {
    for (int i = 0; i < totalMesin - 1; i++) {
        for (int j = 0; j < totalMesin - i - 1; j++) {
            if (score[j] < score[j + 1]) {
                Swap(&score[j], &score[j + 1]);
                SwapObjek(&objek[j], &objek[j + 1]);
            }
        }
    }
}

//UI inout
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
    for (i = 1; i <= 190; i++)
    {
        printf("%c", 223); // 233 adalah kode KARAKTER beta di dalam ASCII2
        if (i == 60 || i == 100)
            Sleep(500); // menjeda program selama 0.5 detik
        Sleep(12);
    }
    Sleep(1600);   // menjeda program selama 1.6 detik
    system("CLS"); // Membersihkan layar
}
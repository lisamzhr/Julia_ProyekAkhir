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
float KalkulasiHematEnergi(); //ini output nilainya aja
float KalkulasiEmisiKarbon(); 
float KalkulasiKeuntunganProduksi(KlasifikasiMesin mesinSample, KlasifikasiMesin normMesin, int tahun);
//ini cari banyak produksi per rupiah, produksi dari laju kali total jam

//function tambahan
int GantiMesinPerTahun(float ovrHeating, int tahun);
//call by reference
void SortMesinTerbaik(float score[], KlasifikasiMesin objek[]);
void Swap(float* a, float* b);


int main(){
    //input berapa mesin
    int totalMesin;
    //nanti tambah printf
    scanf("%d", &totalMesin);
    //input data tahun, listrik (kwh), emisi (mwh), produksi (item/jam), harga mesin(rupiah). bikin loop nah cari nilai terbesar setiap kategori, jadiin untuk variabel normalisasi
    KlasifikasiMesin nMesin = {0};
    KlasifikasiMesin *mesin = malloc(totalMesin * sizeof(KlasifikasiMesin));

    //nanti tambah printf
    for (int i = 0; i < totalMesin; i++){
        scanf(" %[^\n]", mesin[i].dataNama);
        scanf("%f", &mesin[i].dataListrikKwH);
        //cari data normanisasi
        nMesin.dataListrikKwH = (mesin[i].dataListrikKwH > nMesin.dataListrikKwH) ? mesin[i].dataListrikKwH : nMesin.dataListrikKwH;
        scanf("%f", &mesin[i].dataEmisiMwH);
        //cari data normanisasi
        nMesin.dataEmisiMwH = (mesin[i].dataEmisiMwH > nMesin.dataEmisiMwH) ? mesin[i].dataEmisiMwH : nMesin.dataEmisiMwH;
        scanf("%f", &mesin[i].dataProduksi); 
        //cari data normanisasi
        nMesin.dataProduksi = (mesin[i].dataProduksi > nMesin.dataProduksi) ? mesin[i].dataProduksi : nMesin.dataProduksi;
        scanf("%f", &mesin[i].dataHargaMesin);
        nMesin.dataHargaMesin = (mesin[i].dataHargaMesin > nMesin.dataHargaMesin) ? mesin[i].dataHargaMesin: nMesin.dataHargaMesin;
    }

    //berapa tahun mesin perlu dipake
    int tahun;
    scanf("%d", &tahun);

    //cari efesiensi mesin maksimum
    float efisiensiMaks = 0;
    float semuaEfisiensi[totalMesin];

    for (int i = 0; i < totalMesin; i++) {
        semuaEfisiensi[i] = KalkulasiKeuntunganProduksi(mesin[i], nMesin, tahun);
        if (semuaEfisiensi[i] > efisiensiMaks) {
            efisiensiMaks = semuaEfisiensi[i];
        }
    }

    //kalkulasi score dan simulasi tiap mesin
    float scoreAkhir[totalMesin];
    for (int i = 0; i < totalMesin ; i++){
        //panggil fungsi hemat energi 
        float scoreHE = 30 * KalkulasiHematEnergi(/*masukin per mesin*/) / KalkulasiHematEnergi(/*parameter normalisasi*/);
        //panggil fungsi emisi karbon
        float scoreEM = 25 * KalkulasiEmisiKarbon(/*masukin per mesin*/) / KalkulasiEmisiKarbon(/*parameter normalisasi*/);
        //panggil fungsi keuntungan
        float scoreKU = 45 * (semuaEfisiensi[i] / efisiensiMaks);
        printf(" score KU  %f \n", scoreKU);
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
    printf("%d ", gantiMesin);
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

float KalkulasiHematEnergi(){

}

float KalkulasiEmisiKarbon(){

}

void SortMesinTerbaik(float score[], KlasifikasiMesin objek[]){

}


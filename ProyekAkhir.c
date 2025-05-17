#include <stdio.h>

typedef struct{
    char dataNama[30];
    int dataTahun;
    float dataListrikKwH, dataEmisiMwH, dataProduksi, dataHargaMesin;
} KlasifikasiMesin;


float KalkulasiHematEnergi(); //ini output nilainya aja
float KalkulasiEmisiKarbon();
float KalkulasiKeuntunganProduksi();

//function tambahan
//call by reference
void SortMesinTerbaik(float score[], KlasifikasiMesin objek[]);
void Swap(float* a, float* b);

int main(){
    //input berapa mesin
    int totalMesin;
    scanf("%d", totalMesin);
    //input data tahun, listrik (kwh), emisi (mwh), produksi (item/jam), harga mesin(rupiah). bikin loop nah cari nilai terbesar setiap kategori, jadiin untuk variabel normalisasi
    float NormDataListrikKwH, NormDataEmisiMwH, NormDataProduksi, NormDataHargaMesin;
    KlasifikasiMesin mesin[totalMesin];

    //kalkulasi score tiap mesin
    float scoreAkhir[totalMesin];
    for (int i = 0; i < totalMesin ; i++){
        //panggil fungsi hemat energi 
        float scoreHE = 30 * KalkulasiHematEnergi(/*masukin per mesin*/) / KalkulasiHematEnergi(/*parameter normalisasi*/);
        //panggil fungsi emisi karbon
        float scoreEM = 25 * KalkulasiEmisiKarbon(/*masukin per mesin*/) / KalkulasiHematEnergi(/*parameter normalisasi*/);
        //panggil fungsi keuntungan
        float scoreKU = 25 * KalkulasiKeuntunganProduksi(/*masukin per mesin*/) / KalkulasiKeuntunganProduksi(/*parameter normalisasi*/);
        //score akhir efektivitas 
        scoreAkhir[i] = scoreEM + scoreHE + scoreKU;
    }
    
    //urutin mesin yang paling efektif
    SortMesinTerbaik(scoreAkhir, mesin);
    
    //print out urutan
}
#include <stdio.h>
#include <stdlib.h>

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
float KalkulasiHematEnergi(KlasifikasiMesin mesinSample, KlasifikasiMesin normMesin); //ini output nilainya aja
float KalkulasiEmisiKarbon(KlasifikasiMesin mesinSample, KlasifikasiMesin normMesin); 
float KalkulasiKeuntunganProduksi(KlasifikasiMesin mesinSample, KlasifikasiMesin normMesin, int tahun);
//ini cari banyak produksi per rupiah, produksi dari laju kali total jam

//function tambahan
int GantiMesinPerTahun(int ovrHeating, int tahun);
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
    
    //kalkulasi score dan simulasi tiap mesin
    float scoreAkhir[totalMesin];
    for (int i = 0; i < totalMesin ; i++){
        //panggil fungsi hemat energi 
        float scoreHE = 30 * KalkulasiHematEnergi(mesin[i], nMesin);
        //panggil fungsi emisi karbon
        float scoreEM = 25 * KalkulasiEmisiKarbon(mesin[i], nMesin);
        //panggil fungsi keuntungan
        float scoreKU = 45 * KalkulasiKeuntunganProduksi(mesin[i], nMesin, tahun) / KalkulasiKeuntunganProduksi(nMesin, nMesin, tahun);
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

float KalkulasiHematEnergi(KlasifikasiMesin mesinSample, KlasifikasiMesin normMesin){
	// semakin kecil listrik yang digunakan, maka akan semakin hemat
	if (mesinSample.dataListrikKwH <= 0 || normMesin.dataListrikKwH <= 0){
		return 0;
	}else {
		float kalkuHE;
		kalkuHE =  mesinSample.dataListrikKwH / normMesin.dataListrikKwH; 
		return kalkuHE;
	}

}

float KalkulasiEmisiKarbon(KlasifikasiMesin mesinSample, KlasifikasiMesin normMesin){
	// semakin kecil emisi yang dihasilkan  maka akan semakin ramah lingkungan
	if (mesinSample.dataEmisiMwH <= 0 || normMesin.dataEmisiMwH <+ 0){
		return 0;
	}else {
		float kalkuEM;
		kalkuEM = mesinSample.dataEmisiMwH / normMesin.dataEmisiMwH;
		return kalkuEM;
	}

}

void SortMesinTerbaik(float score[], KlasifikasiMesin objek[]){

}


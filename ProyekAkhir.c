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

typedef enum {
    KWH_PER_UNIT,
    MWH_PER_1000_UNIT
} JenisSatuan;

//union efisiensi energi
typedef union {
    float KWHperUnit;      
    float MWhperUnit;  
} EfisiensiEnergi;

//struct ramah lingkungan
typedef struct {
    EfisiensiEnergi efisiensi;
    int ramahLingkungan;  
} EvaluasiLingkungan;

//function kalkulasi utama
//untuk menghitung score hemat energi berdasarkan listrik dari setiap mesin, dibuat oleh putri ayu
float KalkulasiHematEnergi(KlasifikasiMesin mesinSample, KlasifikasiMesin normMesin); 

//untuk menghitung score ramah lingkungan dari setiap mesin, dibuat oleh putri ayu
float KalkulasiEmisiKarbon(KlasifikasiMesin mesinSample, KlasifikasiMesin normMesin); 

//untuk mengitung score keuntungan produksi dari mesin yang digunakan, dibuat khalisa
float KalkulasiKeuntunganProduksi(KlasifikasiMesin mesinSample, KlasifikasiMesin normMesin, int tahun);

//untuk mengitung berapa kali mesin harus diganti dalam periode tahun yang ditentukan, dibuat khalisa
int GantiMesinPerTahun(float ovrHeating, int tahun);

// untuk memastikan bahwa urutan skor tetap sinkron dengan urutan data mesin ketika diurutkan. dibuat ariq
void SwapObjek(KlasifikasiMesin* a, KlasifikasiMesin* b);

//  untuk membantu mengurutkan array skor tanpa kehilangan keterkaitan urutan dengan data mesinnya. dibuat ariq
void Swap(float* a, float* b);

// untuk mengurutkan mesin berdasarkan skor efektivitas. semakin tinggi skor, semakin baik posisi mesin. dibuat ariq
void SortMesinTerbaik(float score[], KlasifikasiMesin objek[], int totalMesin);

//untuk menghitung berapa kali ganti mesin dalam x tahun di mana x ditentukan oleh user, dibuat putay
void FrekuensiGantiMesin (KlasifikasiMesin* mesin, int totalMesin, KlasifikasiMesin normMesin);

//untuk menghitung berapa lama untuk mendapatkan keuntungan, dibuat putay
void hitungBEP(KlasifikasiMesin mesin);

// untuk untuk tes dampak kondisi lingkungan ekstrem. suhu tinggi/rendah, kelembaban tinggi, dan tekanan rendah. dibuat ariq
void SimulasiLingkunganEkstrem(KlasifikasiMesin* mesin, int totalMesin);

//untuk mengevaluasi apakah mesin tersebut ramah lingkungan atau tidak, dibuat lisa 
EvaluasiLingkungan EvaluasiRamahLingkungan(KlasifikasiMesin mesin, float standarEfisiensi, JenisSatuan jenis);

//Fungsi User Interface awal aplikasi dimulai, dibuat oleh syifa naila
void welcome(); 

// fungsi untuk user interface hasil data, dibuat o;eh syifa naila
void printDataMesin(KlasifikasiMesin *mesin, float score[], int totalMesin);

int main(){
    welcome();

    //input berapa mesin
    printf("\n\n\n\n\n\n\n");
    printf("\t\t\t\t\t\t\t\t================== Mulai Simulasi ===================\n");
    int totalMesin;
    
    printf("\t\t\t\t\t\t\t\tTotal mesin yang ingin disimulasikan :");
    scanf("%d", &totalMesin);

    int i = 0, j = 0, k = 0;
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
            do{
                printf("\t\t\t\t\t\t\t\tBesar listrik yang digunakan (KwH): ");
                inpStatus = scanf("%f", &mesin[i].dataListrikKwH);
                if (inpStatus != 1){
                    printf("\t\t\t\t\t\t\t\tInput tidak valid!\n");
                    while (getchar() != '\n');}
                
            } while (inpStatus != 1);

            //cari data normanisasi
            nMesin.dataListrikKwH = (mesin[i].dataListrikKwH > nMesin.dataListrikKwH) ? mesin[i].dataListrikKwH : nMesin.dataListrikKwH;
            nMesinProduksi.dataListrikKwH = (mesin[i].dataListrikKwH < nMesinProduksi.dataListrikKwH) ? mesin[i].dataListrikKwH : nMesinProduksi.dataListrikKwH;

            do{
                printf("\t\t\t\t\t\t\t\tTotal emisi karbon per jam (MwH): ");
                inpStatus = scanf("%f", &mesin[i].dataEmisiMwH);
                if (inpStatus != 1){
                    printf("\t\t\t\t\t\t\t\tInput tidak valid!\n");
                    while (getchar() != '\n');}
                
            } while (inpStatus != 1);

            //cari data normanisasi
            nMesin.dataEmisiMwH = (mesin[i].dataEmisiMwH > nMesin.dataEmisiMwH) ? mesin[i].dataEmisiMwH : nMesin.dataEmisiMwH;
            nMesinProduksi.dataEmisiMwH = (mesin[i].dataEmisiMwH < nMesinProduksi.dataEmisiMwH) ? mesin[i].dataEmisiMwH : nMesinProduksi.dataEmisiMwH;

            do{
                printf("\t\t\t\t\t\t\t\tTotal mesin memproduksi per jam (Kg): ");
                inpStatus = scanf("%f", &mesin[i].dataProduksi); 
                if (inpStatus != 1){
                    printf("\t\t\t\t\t\t\t\tInput tidak valid!\n");
                    while (getchar() != '\n');}
                
            } while (inpStatus != 1);

            //cari data normanisasi
            nMesin.dataProduksi = (mesin[i].dataProduksi > nMesin.dataProduksi) ? mesin[i].dataProduksi : nMesin.dataProduksi;
            nMesinProduksi.dataProduksi = (mesin[i].dataProduksi > nMesinProduksi.dataProduksi) ? mesin[i].dataProduksi : nMesinProduksi.dataProduksi;

            do{
                printf("\t\t\t\t\t\t\t\tHarga mesin (Juta): ");
                inpStatus = scanf("%f", &mesin[i].dataHargaMesin);
                if (inpStatus != 1){
                    printf("\t\t\t\t\t\t\t\tInput tidak valid!\n");
                    while (getchar() != '\n');}
                
            } while (inpStatus != 1);
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
        do
        {
            printf("\nTambah mesin lagi? (y/n) : ");
            scanf(" %c", &lanjutInput);  // Spasi sebelum %c untuk skip newline
        } while (lanjutInput != 'y' && lanjutInput != 'Y' && lanjutInput != 'n' && lanjutInput != 'N');

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
                printf("Gagal menambah memori! Program dihentikan.\n");
                exit(1);
            }
        
            // Jika berhasil, update pointer utama
            mesin = temp;
        
            system("CLS"); // Membersihkan layar
            printf("\t\t\t\t\t\t\t\t================== Mulai Simulasi ===================\n");
            totalMesin += tambahan; // update jumlah total mesin
        }


    } while (lanjutInput == 'Y' || lanjutInput == 'y'); 

    // menawarkan fitur tambahan pada user
    int fiturTambahan;
    int exit = 1;
    system("CLS"); // Membersihkan layar

    do
    {
        printf("\nApakah Anda ingin menggunakan fitur tambahan?\n");
        printf("0 = Tidak\n1 = Ganti Mesin\n2 = Break Even Point (BEP)\n3 = Simulasi Lingkungan Ekstrem \n4 = Evaluasi Ramah Lingkungan \nPilihan Anda: ");
        scanf("%d", &fiturTambahan);
        
        // Jalankan fitur sesuai pilihan user
        switch (fiturTambahan) {
            case 0:
                printf("Tidak menggunakan fitur tambahan.\n");
                exit = 0;
                break;

            case 1:
                // Panggil fungsi frekuensi ganti mesin
                FrekuensiGantiMesin(mesin, totalMesin, nMesin);
                break;
            case 2:
                // Panggil fungsi BEP untuk tiap mesin
                for (int i = 0; i < totalMesin; i++) {
                    printf("\nMesin: %s\n", mesin[i].dataNama);
                    hitungBEP(mesin[i]);
                }
                break;
            case 3:
                //fitur simulasi
                SimulasiLingkunganEkstrem(mesin, totalMesin);
                break;
            case 4:
                //fitur carbon evaluasi ramah lingkungan
                for (int i = 0; i < totalMesin; i++) {
                    EvaluasiRamahLingkungan(mesin[i], 0.35, KWH_PER_UNIT);
                    EvaluasiRamahLingkungan(mesin[i], 0.45, MWH_PER_1000_UNIT);
                }
                break;
            default:
                printf("Pilihan tidak valid.\n");
                break;
        }

    } while (exit != 0);
    
    //end
    free(mesin);
    return 0;
}

int GantiMesinPerTahun(float ovrHeating, int tahun){
    float ovhValue = ovrHeating;
    int gantiMesin = 0;
    float statusPoin = 0;

    for (int i = 0; i < tahun; i++){
        for (int j = 0; j < HariPerTahun ; j++){
            statusPoin += ovhValue * JamKerjaPerHari; //jadi status poin nambah sesuai kecepatan overheating
            statusPoin -= (1 - ovhValue) * (24 - JamKerjaPerHari); // pendinginan saat jam istirahat
            //batasi statusPoin minimal 0
            if (statusPoin < 0) {statusPoin = 0;}
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

EvaluasiLingkungan EvaluasiRamahLingkungan(KlasifikasiMesin mesin, float standarEfisiensi, JenisSatuan jenis) {
    EvaluasiLingkungan hasil;

    printf("Mesin %s\n", mesin.dataNama);

    if (jenis == KWH_PER_UNIT) {
        hasil.efisiensi.KWHperUnit = mesin.dataListrikKwH / mesin.dataProduksi;
        printf("Efisiensi: %.3f kWh/unit\n", hasil.efisiensi.KWHperUnit);

        if (hasil.efisiensi.KWHperUnit <= standarEfisiensi) {
            hasil.ramahLingkungan = 1;
            printf("Status: Mesin RAMAH LINGKUNGAN (berdasarkan kWh/unit)\n");
        } else {
            hasil.ramahLingkungan = 0;
            printf("Status: Mesin TIDAK RAMAH LINGKUNGAN (berdasarkan kWh/unit)\n");
        }

    } else if (jenis == MWH_PER_1000_UNIT) {
        float MWHperUnit = mesin.dataEmisiMwH / mesin.dataProduksi;
        hasil.efisiensi.MWhperUnit = MWHperUnit / 1000.0 * 1000; // konversi jadi MWh/1000 unit
        printf("Efisiensi: %.3f MWh/1000unit\n", hasil.efisiensi.MWhperUnit);

        if (hasil.efisiensi.MWhperUnit <= standarEfisiensi) {
            hasil.ramahLingkungan = 1;
            printf("Status: Mesin RAMAH LINGKUNGAN (berdasarkan MWh/1000unit)\n");
        } else {
            hasil.ramahLingkungan = 0;
            printf("Status: Mesin TIDAK RAMAH LINGKUNGAN (berdasarkan MWh/1000unit)\n");
        }
    }

    return hasil;
}

void SimulasiLingkunganEkstrem(KlasifikasiMesin* mesin, int totalMesin) {
    float suhu, kelembaban, tekanan;

    printf("\n=== SIMULASI KONDISI LINGKUNGAN EKSTREM (Tambahan) ===\n");
    printf("Masukkan suhu lingkungan (°C): ");
    scanf("%f", &suhu);
    printf("Masukkan kelembaban (%%): ");
    scanf("%f", &kelembaban);
    printf("Masukkan tekanan udara (atm): ");
    scanf("%f", &tekanan);
    printf("-----------------------------------------------------------\n");

    for (int i = 0; i < totalMesin; i++) {
        float efisiensiAwal = 100.0f * mesin[i].dataProduksi / mesin[i].dataListrikKwH;
        float efisiensi = efisiensiAwal;
        float emisi = mesin[i].dataEmisiMwH * 1000 / mesin[i].dataProduksi; // gr CO2 per unit

        // Dampak lingkungan terhadap efisiensi
        if (suhu > 40) efisiensi -= efisiensiAwal * 0.10f;
        else if (suhu < 10) efisiensi -= efisiensiAwal * 0.05f;

        if (kelembaban > 80) efisiensi -= efisiensiAwal * 0.05f;
        if (tekanan < 0.9) efisiensi -= efisiensiAwal * 0.07f;

        // Dampak lingkungan terhadap emisi
        if (suhu > 40) emisi *= 1.05f;
        if (kelembaban > 80) emisi *= 1.05f;
        if (tekanan < 0.9) emisi *= 1.05f;

        // Buat peringatan
        char peringatan[150] = "";
        if (suhu > 40) strcat(peringatan, "Suhu tinggi, ");
        if (suhu < 10) strcat(peringatan, "Suhu rendah, ");
        if (kelembaban > 80) strcat(peringatan, "Kelembaban tinggi, ");
        if (tekanan < 0.9) strcat(peringatan, "Tekanan rendah, ");
        if (strlen(peringatan) > 0)
            peringatan[strlen(peringatan) - 2] = '\0'; 

        // Tampilkan hasil
        printf("Mesin %d: %s\n", i + 1, mesin[i].dataNama);
        printf("  Efisiensi awal                : %.2f%%\n", efisiensiAwal);
        printf("  Efisiensi setelah penyesuaian: %.2f%%\n", efisiensi);
        printf("  Produksi                      : %.0f unit\n", mesin[i].dataProduksi);
        printf("  Emisi meningkat menjadi       : %.2f gr CO2/unit\n", emisi);
        if (strlen(peringatan) > 0)
            printf("  Peringatan                    : %s ? Risiko performa buruk.\n", peringatan);
        else
            printf("  Peringatan                    : Tidak ada.\n");
        printf("-----------------------------------------------------------\n");
    }
}

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

void FrekuensiGantiMesin (KlasifikasiMesin* mesin, int totalMesin, KlasifikasiMesin normMesin){
    int tahun;
    printf("\n\n================= CEK FREKUENSI PENGGANTIAN MESIN =================\n");
    printf("Masukkan berapa tahun mesin akan digunakan untuk analisis pergantian: ");
    scanf("%d",  &tahun);
    printf("-------------------------------------------------------------------\n");
    for (int i = 0; i < totalMesin; i++){
        float OvhTime = 0.3 * (mesin[i].dataListrikKwH / normMesin.dataListrikKwH) + 0.3 * (mesin[i].dataEmisiMwH / normMesin.dataEmisiMwH) + 0.4 * (mesin[i].dataProduksi / normMesin.dataProduksi);
        
        int totalGanti = GantiMesinPerTahun(OvhTime, tahun);
         printf("Mesin %-25s perlu diganti sebanyak: %d kali dalam %d tahun\n", mesin[i].dataNama, totalGanti, tahun);
    }
    printf("===================================================================\n\n");
}

void hitungBEP(KlasifikasiMesin mesin) {
    double hargaJual, biayaListrik;

    printf("=== HITUNG BREAK EVEN POINT (BEP) ===\n");
    printf("Masukkan harga jual per item (dalam Rupiah): ");
    scanf("%lf", &hargaJual);

    printf("Masukkan biaya listrik per kWh (dalam Rupiah): ");
    scanf("%lf", &biayaListrik);

    // Konversi biaya awal dari juta ke rupiah
    double biayaAwalRupiah = mesin.dataHargaMesin * 1000000;

    // Hitung biaya listrik per item berdasarkan efisiensi energi
    double biayaListrikPerItem = (mesin.dataListrikKwH / mesin.dataProduksi) * biayaListrik;

    // Hitung laba bersih per item
    double labaPerItem = hargaJual - biayaListrikPerItem;

    // Hitung total laba per tahun
    double kapasitasProduksiPerTahun = mesin.dataProduksi * JamKerjaPerHari * HariPerTahun;
    double labaPerTahun = labaPerItem * kapasitasProduksiPerTahun;

    // Hitung tahun BEP
    double totalLaba = 0;
    int tahun = 0;

    if (labaPerTahun <= 0) {
        printf("Tidak dapat menghitung BEP karena laba per tahun <= 0.\n");
    } else {
        while (totalLaba < biayaAwalRupiah) {
            tahun++;
            totalLaba += labaPerTahun;
        }

        printf("BEP tercapai dalam %d tahun.\n", tahun);
    }

    printf("======================================\n\n");
}

void welcome(){
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
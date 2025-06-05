
**IndustriLogic** adalah program simulasi interaktif yang membantu pengguna memilih mesin produksi paling efisien dan berkelanjutan berdasarkan konsumsi listrik, emisi karbon, tingkat produksi, dan harga. Pengguna dapat memasukkan data mesin, menentukan jangka waktu penggunaan, dan mengevaluasi performa mesin dari aspek efisiensi, biaya, serta keberlanjutan. Fitur tambahan mencakup perhitungan frekuensi penggantian mesin, Break Even Point (BEP), simulasi dalam kondisi ekstrem, dan evaluasi tingkat keramahan lingkungan. Program ini turut mendukung pencapaian SDG 9 dengan mendorong industri yang inovatif, inklusif, dan berkelanjutan.

### Khalisa Zahra Maulana
- Menyusun struktur awal program.
- Menyediakan logika input awal, error handling, dan validasi variabel.
- Membuat fungsi:
  - `KalkulasiKeuntunganProduksi()` untuk menghitung keuntungan berdasarkan produksi dan ketahanan mesin.
  - `GantiMesinPerTahun()` untuk memperhitungkan kerusakan akibat overheat.
  - `EvaluasiRamahLingkungan()` untuk mengevaluasi apakah mesin termasuk ramah lingkungan dari sisi konsumsi dan emisi.
- Melakukan merge seluruh fitur, debug, dan uji stabilitas semua fungsi.

---

### Muhammad Ariq Haqi
- Menyusun flowchart program utama.
- Mengembangkan sistem pemeringkatan dan pengurutan mesin terbaik.
- Membuat fungsi:
  - `Swap()`, `SwapObjek()` untuk mempermudah sorting.
  - `SortMesinTerbaik()` untuk menyusun mesin berdasarkan skor terbaik.
  - `SimulasiLingkunganEkstrem()` untuk melihat ketahanan mesin dalam kondisi ekstrem.

---

### Putri Ayu Pembayun M
- Membuat perhitungan efisiensi energi dan emisi karbon:
  - `KalkulasiHematEnergi()` dan `KalkulasiEmisiKarbon()`.
- Menyusun logika:
  - `FrekuensiGantiMesin()` untuk memperkirakan berapa kali mesin perlu diganti dalam jangka waktu tertentu.
  - `hitungBEP()` untuk menghitung kapan modal kembali (Break Even Point).

---

### Syifa Naila Maulidya
- Menyusun flowchart bagian sub-program dan alur UI.
- Membuat fungsi UI:
  - `welcome()` sebagai pembuka program.
  - `printDataMesin()` untuk menampilkan hasil simulasi dalam bentuk tabel.

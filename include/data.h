#ifndef DATA_H
#define DATA_H

// Kapasitas array tetap sesuai ketentuan
const int MAX_DATA = 100;

// Struct pendukung (struct di dalam struct / nested struct)
struct CatatanRiwayat {
    char tanggal[15];
    char keterangan[30];
};

// Struct utama
struct Tanaman {
    char kode[10];
    char nama[30];
    char jenis[20];
    int interval;
    char tglSiram[15];
    char kondisi[20];
    int totalRiwayat;
    CatatanRiwayat riwayat[5]; // Struct bersarang
};

// Variabel global untuk data
extern Tanaman dataTanaman[MAX_DATA];
extern int jumlahData;

#endif
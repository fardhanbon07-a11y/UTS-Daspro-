#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "data.h"
#include "fungsi.h"

using namespace std;

// Tampilan Menu Utama
void menuUtama() {
    cout << "\n====================================\n";
    cout << "   PROGRAM PENCATATAN TANAMAN KOS\n";
    cout << "====================================\n";
    cout << "1. Tambah Tanaman\n";
    cout << "2. Lihat Semua Tanaman\n";
    cout << "3. Cari Tanaman\n";
    cout << "4. Catat Perawatan (Siram)\n";
    cout << "5. Urutkan Data\n";
    cout << "6. Ubah Data Tanaman\n";
    cout << "7. Hapus Data Tanaman\n";
    cout << "8. Statistik\n";
    cout << "9. Info Memori\n";
    cout << "0. Keluar\n";
    cout << "====================================\n";
    cout << "Pilihan Anda: ";
}

// Fungsi baca file teks + penanganan baris rusak/error (syarat file I/O)
void bacaFile(const char* namaFile) {
    ifstream file(namaFile);
    if (!file.is_open()) {
        cout << "Belum ada file data, mulai dengan data kosong.\n";
        return;
    }

    char baris[256];
    int berhasil = 0;

    while (file.getline(baris, sizeof(baris))) {
        // Kalau baris kosong, lewati
        if (strlen(baris) == 0) continue;

        char k[10], n[30], j[20], tgl[15], kon[20];
        int iv;

        // Memecah string dengan sscanf (cara klasik pemula)
        int hasilScan = sscanf(baris, "%[^|]|%[^|]|%[^|]|%d|%[^|]|s", k, n, j, &iv, tgl, kon);
        
        // Validasi baris error / tidak lengkap (minimal 3 baris error diabaikan agar tidak crash)
        if (hasilScan < 5 || iv <= 0 || jumlahData >= MAX_DATA) {
            continue; 
        }

        strcpy(dataTanaman[jumlahData].kode, k);
        strcpy(dataTanaman[jumlahData].nama, n);
        strcpy(dataTanaman[jumlahData].jenis, j);
        dataTanaman[jumlahData].interval = iv;
        strcpy(dataTanaman[jumlahData].tglSiram, tgl);
        strcpy(dataTanaman[jumlahData].kondisi, "Sehat");
        dataTanaman[jumlahData].totalRiwayat = 0;

        jumlahData++;
        berhasil++;
    }

    file.close();
    cout << "Berhasil memuat " << berhasil << " data dari file.\n";
}

// Fungsi simpan data ke file teks
void simpanFile(const char* namaFile) {
    ofstream file(namaFile);
    if (!file.is_open()) return;

    for (int i = 0; i < jumlahData; i++) {
        file << dataTanaman[i].kode << "|"
             << dataTanaman[i].nama << "|"
             << dataTanaman[i].jenis << "|"
             << dataTanaman[i].interval << "|"
             << dataTanaman[i].tglSiram << "|"
             << dataTanaman[i].kondisi << "\n";
    }
    file.close();
}

// 1. Tambah Data
void tambahData() {
    if (jumlahData >= MAX_DATA) {
        cout << "Maaf, data sudah penuh!\n";
        return;
    }

    Tanaman t;
    cout << "\n--- TAMBAH TANAMAN BARU ---\n";
    cout << "Masukkan Kode: ";
    cin >> t.kode;

    // Cek kode kembar
    for (int i = 0; i < jumlahData; i++) {
        if (strcmp(dataTanaman[i].kode, t.kode) == 0) {
            cout << "Kode sudah terdaftar!\n";
            return;
        }
    }

    cin.ignore();
    cout << "Masukkan Nama Tanaman: ";
    cin.getline(t.nama, sizeof(t.nama));
    cout << "Masukkan Jenis Tanaman: ";
    cin.getline(t.jenis, sizeof(t.jenis));
    cout << "Interval Siram (hari): ";
    cin >> t.interval;

    if (t.interval <= 0) {
        cout << "Interval harus angka lebih dari 0!\n";
        return;
    }

    cout << "Tanggal Terakhir Siram (YYYY-MM-DD): ";
    cin >> t.tglSiram;
    strcpy(t.kondisi, "Sehat");
    t.totalRiwayat = 0;

    dataTanaman[jumlahData] = t;
    jumlahData++;
    cout << "Data berhasil ditambah!\n";
}

// 2. Tampilkan Data (Format Tabel)
void tampilData() {
    cout << "\n-------------------------------------------------------------\n";
    cout << left << setw(8) << "KODE" 
         << setw(18) << "NAMA" 
         << setw(15) << "JENIS" 
         << setw(10) << "SIRAM" 
         << setw(12) << "TGL TERAKHIR" << "\n";
    cout << "-------------------------------------------------------------\n";

    if (jumlahData == 0) {
        cout << "Belum ada data tanaman.\n";
    } else {
        for (int i = 0; i < jumlahData; i++) {
            cout << left << setw(8) << dataTanaman[i].kode
                 << setw(18) << dataTanaman[i].nama
                 << setw(15) << dataTanaman[i].jenis
                 << setw(10) << dataTanaman[i].interval
                 << setw(12) << dataTanaman[i].tglSiram << "\n";
        }
    }
    cout << "-------------------------------------------------------------\n";
}

// 3. Cari Data
void cariData() {
    if (jumlahData == 0) {
        cout << "Data masih kosong.\n";
        return;
    }
    char cari[30];
    cout << "Masukkan nama/kode yang dicari: ";
    cin >> cari;

    bool ketemu = false;
    for (int i = 0; i < jumlahData; i++) {
        if (strstr(dataTanaman[i].nama, cari) != NULL || strstr(dataTanaman[i].kode, cari) != NULL) {
            cout << "Ketemu -> Kode: " << dataTanaman[i].kode << ", Nama: " << dataTanaman[i].nama << "\n";
            ketemu = true;
        }
    }
    if (!ketemu) cout << "Tanaman tidak ditemukan.\n";
}

// 4. Catat Perawatan
void catatSiram() {
    char kd[10];
    cout << "Masukkan kode tanaman yang disiram: ";
    cin >> kd;

    int idx = -1;
    for (int i = 0; i < jumlahData; i++) {
        if (strcmp(dataTanaman[i].kode, kd) == 0) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        cout << "Kode tidak ditemukan!\n";
        return;
    }

    cout << "Masukkan tanggal siram hari ini (YYYY-MM-DD): ";
    cin >> dataTanaman[idx].tglSiram;
    dataTanaman[idx].totalRiwayat++;
    cout << "Perawatan berhasil dicatat!\n";
}

// 5. Urutkan Data (Bubble Sort)
void urutkanData() {
    if (jumlahData < 2) return;
    
    // Sorting pakai cara manual bubble sort
    for (int i = 0; i < jumlahData - 1; i++) {
        for (int j = 0; j < jumlahData - i - 1; j++) {
            if (strcmp(dataTanaman[j].nama, dataTanaman[j+1].nama) > 0) {
                Tanaman temp = dataTanaman[j];
                dataTanaman[j] = dataTanaman[j+1];
                dataTanaman[j+1] = temp;
            }
        }
    }
    cout << "Data berhasil diurutkan berdasarkan nama (A-Z).\n";
}

// 6. Ubah Data
void ubahData() {
    char kd[10];
    cout << "Masukkan kode tanaman yang mau diubah: ";
    cin >> kd;

    for (int i = 0; i < jumlahData; i++) {
        if (strcmp(dataTanaman[i].kode, kd) == 0) {
            cin.ignore();
            cout << "Nama baru: ";
            cin.getline(dataTanaman[i].nama, sizeof(dataTanaman[i].nama));
            cout << "Interval baru: ";
            cin >> dataTanaman[i].interval;
            cout << "Data berhasil diubah!\n";
            return;
        }
    }
    cout << "Kode tidak ditemukan.\n";
}

// 7. Hapus Data
void hapusData() {
    char kd[10];
    cout << "Masukkan kode tanaman yang mau dihapus: ";
    cin >> kd;

    int idx = -1;
    for (int i = 0; i < jumlahData; i++) {
        if (strcmp(dataTanaman[i].kode, kd) == 0) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        cout << "Data tidak ditemukan.\n";
        return;
    }

    // Geser array ke kiri
    for (int i = idx; i < jumlahData - 1; i++) {
        dataTanaman[i] = dataTanaman[i+1];
    }
    jumlahData--;
    cout << "Data berhasil dihapus!\n";
}

// 8. Statistik
void statistikData() {
    if (jumlahData == 0) {
        cout << "Belum ada data untuk dihitung.\n";
        return;
    }
    int totalInterval = 0;
    for (int i = 0; i < jumlahData; i++) {
        totalInterval += dataTanaman[i].interval;
    }
    cout << "\n--- STATISTIK PERAWATAN ---\n";
    cout << "Total jenis tanaman : " << jumlahData << "\n";
    cout << "Rata-rata interval  : " << (float)totalInterval / jumlahData << " hari\n";
}

// 9. Info Memori (Syarat A5)
void infoMemori() {
    cout << "\n--- INFORMASI MEMORI PROGRAM ---\n";
    cout << "Ukuran 1 struct Tanaman : " << sizeof(Tanaman) << " byte\n";
    cout << "Total memori array      : " << sizeof(dataTanaman) << " byte\n";
    cout << "Slot terpakai           : " << jumlahData << " dari " << MAX_DATA << " kapasitas\n";
}
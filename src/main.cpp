#include <iostream>
#include "data.h"
#include "fungsi.h"

using namespace std;

// Inisialisasi variabel global
Tanaman dataTanaman[MAX_DATA];
int jumlahData = 0;

int main() {
    // Memuat data dari file teks saat awal jalan
    bacaFile("data_tanaman.txt");

    int pilihan;
    do {
        menuUtama();
        if (!(cin >> pilihan)) {
            cout << "Input harus angka!\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (pilihan) {
            case 1: tambahData(); break;
            case 2: tampilData(); break;
            case 3: cariData(); break;
            case 4: catatSiram(); break;
            case 5: urutkanData(); break;
            case 6: ubahData(); break;
            case 7: hapusData(); break;
            case 8: statistikData(); break;
            case 9: infoMemori(); break;
            case 0:
                simpanFile("data_tanaman.txt");
                cout << "Keluar program. Data tersimpan.\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 0);

    return 0;
}
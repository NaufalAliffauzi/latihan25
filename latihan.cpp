#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

// 3. Struct dan array
struct Mahasiswa {
    string nama;
    string nim;
    int umur;
    float ipk;
};

// Fungsi untuk menampilkan data mahasiswa
void tampilkanData(Mahasiswa mhs[], int jumlah) {
    cout << "\nData Mahasiswa:\n";
    cout << "-----------------------------------------\n";
    cout << "No.  NIM\tNama\t\tUmur\tIPK\n";
    cout << "-----------------------------------------\n";
    for (int i = 0; i < jumlah; i++) {
        cout << i+1 << ".  " << mhs[i].nim << "\t" << mhs[i].nama << "\t\t" 
             << mhs[i].umur << "\t" << mhs[i].ipk << endl;
    }
}

// 4. Fungsi searching - sequential search
int cariMahasiswa(Mahasiswa mhs[], int jumlah, string nimCari) {
    for (int i = 0; i < jumlah; i++) {
        if (mhs[i].nim == nimCari) {
            return i;
        }
    }
    return -1;
}

// 4. Fungsi sorting - berdasarkan IPK (descending)
void urutkanBerdasarkanIPK(Mahasiswa mhs[], int jumlah) {
    sort(mhs, mhs + jumlah, [](Mahasiswa a, Mahasiswa b) {
        return a.ipk > b.ipk;
    });
}

int main() {
    const int MAX_MAHASISWA = 100;
    Mahasiswa dataMahasiswa[MAX_MAHASISWA];
    int jumlahMahasiswa = 0;
    string filename = "data_mahasiswa.txt";

    // 1. Pembacaan data dari file
    ifstream fileInput(filename);
    if (fileInput.is_open()) {
        cout << "Membaca data dari file..." << endl;
        while (!fileInput.eof() && jumlahMahasiswa < MAX_MAHASISWA) {
            fileInput >> dataMahasiswa[jumlahMahasiswa].nim 
                     >> dataMahasiswa[jumlahMahasiswa].nama 
                     >> dataMahasiswa[jumlahMahasiswa].umur 
                     >> dataMahasiswa[jumlahMahasiswa].ipk;
            if (!dataMahasiswa[jumlahMahasiswa].nim.empty()) {
                jumlahMahasiswa++;
            }
        }
        fileInput.close();
        cout << "Data berhasil dibaca. Jumlah mahasiswa: " << jumlahMahasiswa << endl;
    } else {
        cout << "File tidak ditemukan. Membuat data baru." << endl;
    }

    // Menu utama
    int pilihan;
    do {
        cout << "\nMenu:\n";
        cout << "1. Tambah Data Mahasiswa\n";
        cout << "2. Tampilkan Semua Data\n";
        cout << "3. Cari Mahasiswa berdasarkan NIM\n";
        cout << "4. Urutkan Berdasarkan IPK (Tertinggi)\n";
        cout << "5. Simpan Data ke File\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                if (jumlahMahasiswa < MAX_MAHASISWA) {
                    cout << "\nMasukkan data mahasiswa baru:\n";
                    cout << "NIM: "; cin >> dataMahasiswa[jumlahMahasiswa].nim;
                    cout << "Nama: "; cin >> dataMahasiswa[jumlahMahasiswa].nama;
                    cout << "Umur: "; cin >> dataMahasiswa[jumlahMahasiswa].umur;
                    cout << "IPK: "; cin >> dataMahasiswa[jumlahMahasiswa].ipk;
                    jumlahMahasiswa++;
                    cout << "Data berhasil ditambahkan.\n";
                } else {
                    cout << "Kapasitas data penuh!\n";
                }
                break;
            }
            case 2:
                tampilkanData(dataMahasiswa, jumlahMahasiswa);
                break;
            case 3: {
                string nimCari;
                cout << "Masukkan NIM yang dicari: ";
                cin >> nimCari;
                int posisi = cariMahasiswa(dataMahasiswa, jumlahMahasiswa, nimCari);
                if (posisi != -1) {
                    cout << "\nData ditemukan:\n";
                    cout << "NIM: " << dataMahasiswa[posisi].nim << endl;
                    cout << "Nama: " << dataMahasiswa[posisi].nama << endl;
                    cout << "Umur: " << dataMahasiswa[posisi].umur << endl;
                    cout << "IPK: " << dataMahasiswa[posisi].ipk << endl;
                } else {
                    cout << "Data tidak ditemukan.\n";
                }
                break;
            }
            case 4:
                urutkanBerdasarkanIPK(dataMahasiswa, jumlahMahasiswa);
                cout << "Data telah diurutkan berdasarkan IPK tertinggi.\n";
                tampilkanData(dataMahasiswa, jumlahMahasiswa);
                break;
            case 5:
                // 2. Menyimpan data ke file
                ofstream fileOutput(filename);
                for (int i = 0; i < jumlahMahasiswa; i++) {
                    fileOutput << dataMahasiswa[i].nim << " " 
                              << dataMahasiswa[i].nama << " " 
                              << dataMahasiswa[i].umur << " " 
                              << dataMahasiswa[i].ipk;
                    if (i < jumlahMahasiswa - 1) {
                        fileOutput << endl;
                    }
                }
                fileOutput.close();
                cout << "Data berhasil disimpan ke file.\n";
                break;
        }
    } while (pilihan != 0);

    return 0;
}
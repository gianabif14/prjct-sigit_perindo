#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

typedef struct
{
    int nik;
    string nama;
    string tgl_lahir_asli;
    string tgl_lahir;
    string profesi;
    char status;
    string pass;
} pengguna;

typedef struct
{
    int pemilik;
    string label;
    string alamat;
    string tgl_beli;
    int luas;
    char bangunan;
} data1;

typedef struct
{
    int pemilik;
    string nopol;
    string tgl_beli;
    string merk;
    string tipe;
    int cc;
    int thn_perakitan;
    string no_rangka;
} data2;

typedef struct
{
    int pemilik;
    int id_tanah;
    string tgl_bayar;
    int pajak_tanah;
    int pajak_bangunan;
    int denda;
} data3;

typedef struct
{
    int pemilik;
    int id_kendaraan;
    string nopol;
    string tgl_bayar;
    int pajak_kendaraan;
    int denda;
} data4;

pengguna user[1000];
data1 data_pbb[1000];
data2 data_kendaraan[1000];
data3 data_pajak_pbb[1000];
data4 data_pajak_kendaraan[1000];

int id_terdaftar = 0;
int id_sedang_login = -1;
int id_tanah = 0;
int id_kendaraan = 0;

void print_cantik(string header);
void ubah_format_tglLhr(string tgl_lhr_asli, string *tgl_lhr);
void buat_pass(int id);
void kata_kata();
void main_menu();
void pbb();
void kendaraan();
void identitas();
void laporan_pbb();
void laporan_kendaraan();
int baca_data_pbb();
int baca_data_pajak_kendaraan();
int hitung_denda(int pajak, int selisih_hari);
int nik_masuk_id_berapa(int nik);
int tanah_id_berapa(string alamat);
int kendaraan_id_berapa(string no_pol);
int cek_selisih_tanggal(string tgl_beli, string tgl_bayar);
bool cek_nik_belum_dipakai(int nik_baru);
bool cek_ketentuan_pass(string pass_baru, int pjg_char);
bool cek_berhasil_login_atau_tidak(int nik, string pass);
bool cek_kesesuaian_nik_dan_tglLhr(int nik, string tgl_lhr);
void simpan_sertifikat_tanah();
void baca_sertifikat_tanah();
void simpan_data_kendaraan();
void baca_data_kendaraan();
void simpan_data_user();
void baca_data_user();

int main(){
    baca_data_user(); // baca user dari file
    baca_sertifikat_tanah();
    baca_data_kendaraan();

    int pilih_menu, nik_baru, auth_nik, id;
    string pass_baru, auth_pass, auth_pass2, auth_tgl;
    bool menu_awal = 1;
    char yakin;
    do{
        print_cantik("Sistem Digital Perpajakan Negeri Indo");
        cout << "Menu Awal:\n1. Registrasi\n2. Login\n3. Lupa Password\n0. Keluar Sistem" << endl;
        cout << "Pilih Menu: ";
        cin >> pilih_menu;
        switch (pilih_menu)
        {
        case 1:
            print_cantik("Registrasi Akun");
            cout << "Masukkan NIK: ";
            cin >> nik_baru;
            if (cek_nik_belum_dipakai(nik_baru)){
                user[id_terdaftar].nik = nik_baru;
                cin.ignore();
                cout << "Nama Lengkap: "; getline(cin, user[id_terdaftar].nama);
                cout << "Tanggal Lahir (dd-mm-yyyy): "; getline(cin, user[id_terdaftar].tgl_lahir_asli);
                ubah_format_tglLhr(user[id_terdaftar].tgl_lahir_asli, &user[id_terdaftar].tgl_lahir);
                cout << "Profesi: ";
                getline(cin, user[id_terdaftar].profesi);
                cout << "Status Perkawinan (Y/T): "; cin >> user[id_terdaftar].status;
                system("pause");
                system("cls");
                cin.ignore();
                buat_pass(id_terdaftar);
                id_terdaftar++;
                simpan_data_user();
            } else{
                cout << "NIK Sudah Terdaftar" << endl;
            }
            system("pause");
            break;
        
        case 2:
            print_cantik("Login");
            cout << "Masukkan NIK: "; 
            cin >> auth_nik;
            cout << "Masukkan Password: "; 
            cin.ignore(); 
            getline(cin, auth_pass);
            if(cek_berhasil_login_atau_tidak(auth_nik, auth_pass)){
                cout << endl << "Login Berhasil." << endl;
                id_sedang_login = nik_masuk_id_berapa(auth_nik);
                system("pause");
                main_menu();
            }else{
                cout << endl << "NIK/Password Salah. Login Gagal!" << endl;
                system("pause");
            }
            break;

        case 3:
            print_cantik("Lupa Password");
            cout << "Masukkan NIK: "; cin >> auth_nik;
            cout << "Masukkan Tanggal Lahir (dd-mm-yyyy): "; cin >> auth_tgl;
            id = nik_masuk_id_berapa(auth_nik);
            if (id == -1)
            {
                cout << "NIK tidak ditemukan" << endl;
            }else{
                if(cek_kesesuaian_nik_dan_tglLhr(auth_nik, auth_tgl)){
                    cin.ignore();
                    buat_pass(id);
                }else{
                    cout << "NIK dan tanggal lahir tidak sesuai" << endl;
                }
            }
            simpan_data_user();
            system("pause");
            break;
        
        case 0:
            print_cantik("Keluar Sistem");
            cout << "Apakah anda yakin akan keluar dari sistem (Y/N): ";
            cin >> yakin;
            (yakin == 'Y' || yakin == 'y') ? menu_awal = 0 : menu_awal = 1;
            break;
        
        default:
            print_cantik("Input Salah");
            system("pause");
            break;
        }
    } while(menu_awal);
    kata_kata();
    system("pause");
}

void simpan_sertifikat_tanah() {
    ofstream tulis("data_sertifikat_tanah.txt");
    for (int i = 0; i < id_tanah; i++) {
        tulis << data_pbb[i].pemilik << '|'
              << data_pbb[i].label << '|'
              << data_pbb[i].alamat << '|'
              << data_pbb[i].tgl_beli << '|'
              << data_pbb[i].luas << '|'
              << data_pbb[i].bangunan << endl;
    }
    tulis.close();
}

void baca_sertifikat_tanah() {
    ifstream baca("data_sertifikat_tanah.txt");
    string line, pemilik, label, alamat, tgl_beli, luas, bangunan;
    id_tanah = 0;
    while (getline(baca, line) && id_tanah < 1000) {
        stringstream ss(line);
        getline(ss, pemilik, '|');
        getline(ss, label, '|');
        getline(ss, alamat, '|');
        getline(ss, tgl_beli, '|');
        getline(ss, luas, '|');
        getline(ss, bangunan);
        data_pbb[id_tanah].pemilik = stoi(pemilik);
        data_pbb[id_tanah].label = label;
        data_pbb[id_tanah].alamat = alamat;
        data_pbb[id_tanah].tgl_beli = tgl_beli;
        data_pbb[id_tanah].luas = stoi(luas);
        data_pbb[id_tanah].bangunan = bangunan[0];
        id_tanah++;
    }
    baca.close();
}

void simpan_data_kendaraan() {
    ofstream tulis("data_kendaraan.txt");
    for (int i = 0; i < id_kendaraan; i++) {
        tulis << data_kendaraan[i].pemilik << '|'
              << data_kendaraan[i].nopol << '|'
              << data_kendaraan[i].tgl_beli << '|'
              << data_kendaraan[i].merk << '|'
              << data_kendaraan[i].tipe << '|'
              << data_kendaraan[i].cc << '|'
              << data_kendaraan[i].thn_perakitan << '|'
              << data_kendaraan[i].no_rangka << endl;
    }
    tulis.close();
}

void baca_data_kendaraan() {
    ifstream baca("data_kendaraan.txt");
    string line, pemilik, nopol, tgl_beli, merk, tipe, cc, thn_perakitan, no_rangka;
    id_kendaraan = 0;
    while (getline(baca, line) && id_kendaraan < 1000) {
        stringstream ss(line);
        getline(ss, pemilik, '|');
        getline(ss, nopol, '|');
        getline(ss, tgl_beli, '|');
        getline(ss, merk, '|');
        getline(ss, tipe, '|');
        getline(ss, cc, '|');
        getline(ss, thn_perakitan, '|');
        getline(ss, no_rangka);
        data_kendaraan[id_kendaraan].pemilik = stoi(pemilik);
        data_kendaraan[id_kendaraan].nopol = nopol;
        data_kendaraan[id_kendaraan].tgl_beli = tgl_beli;
        data_kendaraan[id_kendaraan].merk = merk;
        data_kendaraan[id_kendaraan].tipe = tipe;
        data_kendaraan[id_kendaraan].cc = stoi(cc);
        data_kendaraan[id_kendaraan].thn_perakitan = stoi(thn_perakitan);
        data_kendaraan[id_kendaraan].no_rangka = no_rangka;
        id_kendaraan++;
    }
    baca.close();
}

int baca_data_pbb() {
    ifstream baca("data_pbb.txt");
    string line, pemilik, id_tanah, tgl_bayar, pajak_tanah, pajak_bangunan, denda;
    int banyak_data = 0;
    while (getline(baca, line) && banyak_data < 1000) {
        stringstream ss(line);
        getline(ss, pemilik, '|');
        getline(ss, id_tanah, '|');
        getline(ss, tgl_bayar, '|');
        getline(ss, pajak_tanah, '|');
        getline(ss, pajak_bangunan, '|');
        getline(ss, denda);
        data_pajak_pbb[banyak_data].pemilik = stoi(pemilik);
        data_pajak_pbb[banyak_data].id_tanah = stoi(id_tanah);
        data_pajak_pbb[banyak_data].tgl_bayar = tgl_bayar;
        data_pajak_pbb[banyak_data].pajak_tanah = stoi(pajak_tanah);
        data_pajak_pbb[banyak_data].pajak_bangunan = stoi(pajak_bangunan);
        data_pajak_pbb[banyak_data].denda = stoi(denda);
        banyak_data++;
    }
    baca.close();
    return banyak_data;
}

int baca_data_pajak_kendaraan() {
    ifstream baca("data_pajak_kendaraan.txt");
    string line, pemilik, id_kendaraan, nopol, tgl_bayar, pajak_kendaraan, denda;
    int banyak_data = 0;
    while (getline(baca, line) && banyak_data < 1000) {
        stringstream ss(line);
        getline(ss, pemilik, '|');
        getline(ss, id_kendaraan, '|');
        getline(ss, nopol, '|');
        getline(ss, tgl_bayar, '|');
        getline(ss, pajak_kendaraan, '|');
        getline(ss, denda);
        data_pajak_kendaraan[banyak_data].pemilik = stoi(pemilik);
        data_pajak_kendaraan[banyak_data].id_kendaraan = stoi(id_kendaraan);
        data_pajak_kendaraan[banyak_data].nopol = nopol;
        data_pajak_kendaraan[banyak_data].tgl_bayar = tgl_bayar;
        data_pajak_kendaraan[banyak_data].pajak_kendaraan = stoi(pajak_kendaraan);
        data_pajak_kendaraan[banyak_data].denda = stoi(denda);
        banyak_data++;
    }
    baca.close();
    return banyak_data;
}

void laporan_pbb(){
    ofstream tulis("laporan_pajak_pbb.txt", ios::trunc);
    data3 temp;
    int banyak_data = baca_data_pbb();
    bool swapped;
    if (banyak_data == 0) {
        cout << "Tidak ada data pajak PBB yang tersedia." << endl;
        return;
    }
    for (int i = 0; i < banyak_data - 1; i++)
    {
        swapped = false;
        for (int j = 0; j < banyak_data - 1 - i; j++)
        {
            int total_pajak_j = data_pajak_pbb[j].pajak_tanah + data_pajak_pbb[j].pajak_bangunan + data_pajak_pbb[j].denda;
            int total_pajak_j1 = data_pajak_pbb[j + 1].pajak_tanah + data_pajak_pbb[j + 1].pajak_bangunan + data_pajak_pbb[j + 1].denda;
            if (total_pajak_j < total_pajak_j1)
            {
                temp = data_pajak_pbb[j];
                data_pajak_pbb[j] = data_pajak_pbb[j + 1];
                data_pajak_pbb[j + 1] = temp;
                swapped = true;
            }  
        }
        if (!swapped) break;
    }
    tulis << "Laporan Pajak PBB (Urut Berdasarkan Besaran Biaya Pajak)\n";
    tulis << "--------------------------------------------------------\n";
    for (int i = 0; i < banyak_data; i++)
    {
        if(data_pajak_pbb[i].pemilik == id_sedang_login || id_sedang_login == -1) {
            tulis << "ID Tanah: " << data_pajak_pbb[i].id_tanah << endl;
            tulis << "Label Tanah: " << data_pbb[data_pajak_pbb[i].id_tanah].label << endl;
            tulis << "Tanggal Bayar: " << data_pajak_pbb[i].tgl_bayar << endl;
            tulis << "Pajak Tanah: Rp. " << data_pajak_pbb[i].pajak_tanah << endl;
            tulis << "Pajak Bangunan: Rp. " << data_pajak_pbb[i].pajak_bangunan << endl;
            tulis << "Denda: Rp. " << data_pajak_pbb[i].denda << endl;
            tulis << "Total Pajak: Rp. " << (data_pajak_pbb[i].pajak_tanah + data_pajak_pbb[i].pajak_bangunan + data_pajak_pbb[i].denda) << endl;
            tulis << "--------------------------------------------------------\n";
        }
    }
    tulis << "Laporan Selesai.\n";
    cout << "Laporan Pajak PBB telah disimpan ke file 'laporan_pajak_pbb.txt'." << endl;
    tulis.close();
}

void laporan_kendaraan(){
    ofstream tulis("laporan_pajak_kendaraan.txt", ios::trunc);
    int banyak_data = baca_data_pajak_kendaraan();
    data4 temp;
    bool swapped;
    if (banyak_data == 0) {
        cout << "Tidak ada data pajak kendaraan yang tersedia." << endl;
        return;
    }
    for (int i = 0; i < banyak_data - 1; i++)
    {
        swapped = false;
        for (int j = 0; j < banyak_data - 1 - i; j++)
        {
            int total_pajak_j = data_pajak_kendaraan[j].pajak_kendaraan + data_pajak_kendaraan[j].denda;
            int total_pajak_j1 = data_pajak_kendaraan[j + 1].pajak_kendaraan + data_pajak_kendaraan[j + 1].denda;
            if (total_pajak_j < total_pajak_j1)
            {
                temp = data_pajak_kendaraan[j];
                data_pajak_kendaraan[j] = data_pajak_kendaraan[j + 1];
                data_pajak_kendaraan[j + 1] = temp;
                swapped = true;
            }  
        }
        if (!swapped) break;
    }
    tulis << "Laporan Pajak Kendaraan (Urut Berdasarkan Besaran Biaya Pajak)\n";
    tulis << "--------------------------------------------------------\n";
    for (int i = 0; i < banyak_data; i++)
    {
        if( data_pajak_kendaraan[i].pemilik == id_sedang_login || id_sedang_login == -1) {
            tulis << "ID Kendaraan: " << data_pajak_kendaraan[i].id_kendaraan << endl;
            tulis << "No. Polisi: " << data_pajak_kendaraan[i].nopol << endl;
            tulis << "Tanggal Bayar: " << data_pajak_kendaraan[i].tgl_bayar << endl;
            tulis << "Pajak Kendaraan: Rp. " << data_pajak_kendaraan[i].pajak_kendaraan << endl;
            tulis << "Denda: Rp. " << data_pajak_kendaraan[i].denda << endl;
            tulis << "Total Pajak: Rp. " << (data_pajak_kendaraan[i].pajak_kendaraan + data_pajak_kendaraan[i].denda) << endl;
            tulis << "--------------------------------------------------------\n";
        }
    }
    tulis << "Laporan Selesai.\n";
    cout << "Laporan Pajak Kendaraan telah disimpan ke file 'laporan_pajak_kendaraan.txt'." << endl;
    tulis.close();
}

void print_cantik(string header){
    int pjg_char= header.size()+4;
    system("cls");
    for (int i = 0; i < pjg_char; i++)
    {
        cout << '=';
    }
    cout << endl << "  " << header << endl;
    for (int i = 0; i < pjg_char; i++)
    {
        cout << '=';
    }
    cout << endl;
};

void main_menu(){
    int pilih_menu;
    char yakin='n';
    do{
        system("cls");
        print_cantik("Menu Utama");
        cout << "1. Bayar pajak PBB" << endl;
        cout << "2. Bayar pajak Kendaraan" << endl;
        cout << "3. Identitas Pribadi" << endl;
        cout << "0. Keluar Sistem (Log Out)" << endl;
        cout << "Pilih Menu: ";
        cin >> pilih_menu;
        switch (pilih_menu)
        {
        case 1:
            pbb();
            break;

        case 2:
            kendaraan();
            break;

        case 3:
            identitas();
            break;

        case 0:
            print_cantik("Keluar Sistem");
            cout << "Apakah anda yakin akan logout dari sistem (Y/N): ";
            cin >> yakin;
            break;
        
        default:
            print_cantik("Menu Tidak Valid.");
            break;
        }
        if (pilih_menu != 0) system("pause");
    }while(yakin != 'Y' && yakin != 'y');
};

void pbb(){
    int pilih_menu, auth_nik, id_pemilikLama, id_tanah_dicari, id_tanah_dipilih;
    int id_tanah_dimiliki[1000], banyak_tanah = 0, pilih_data_diubah, banyak_data_pbb = 0;
    string auth_alamat;
    char yakin1, yakin_balik, status;
    bool ketemu;
    do{
        ofstream tulis("data_pbb.txt", ios::app);
        print_cantik("Menu Pajak Bumi dan Bangunan");
        cout << "1. Tambah Sertifikat Tanah" << endl;
        cout << "2. Bayar Pajak (PBB)" << endl;
        cout << "3. Balik Nama Pemilik Tanah" << endl;
        cout << "4. Cek Status Pajak" << endl;
        cout << "5. Ubah Data Sertifikat" << endl;
        cout << "6. Unduh Laporan Pajak" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilih Menu: "; 
        cin >> pilih_menu;
        switch (pilih_menu){
            case 1:
                print_cantik("Tambah Sertifikat Tanah");
                data_pbb[id_tanah].pemilik = id_sedang_login;
                cin.ignore();
                cout << "Label Tanah (cth: Rumah, Sawah): ";
                getline(cin, data_pbb[id_tanah].label);
                cout << "Alamat (cth: Jl. Babarsari No.2): ";
                getline(cin, data_pbb[id_tanah].alamat);
                cout << "Tanggal Pembelian (dd-mm-yyyy): ";
                cin >> data_pbb[id_tanah].tgl_beli;
                cout << "Luas Tanah dlm m^2 (cth: 210): ";
                cin >> data_pbb[id_tanah].luas;
                cout << "Dalam Tanah tsb, apakah terdapat bangunan? (Y/N): ";
                cin >> data_pbb[id_tanah].bangunan;
                system("pause");
                system("cls");
                cout << "Data Sertifikat Tanah Berhasil Disimpan." << endl;
                id_tanah++;
                simpan_sertifikat_tanah();
                break;

            case 2:
                print_cantik("Bayar Pajak (PBB)");
                banyak_tanah = 0;
                for (int i = 0; i < id_tanah; i++)
                {
                    if (data_pbb[i].pemilik == id_sedang_login)
                    {
                        id_tanah_dimiliki[banyak_tanah] = i;
                        banyak_tanah++;
                    }
                }
                if (banyak_tanah == 0) cout << "Anda belum memiliki sertifikat tanah terdaftar." << endl;
                else{
                    string tanggal_bayar;
                    cout << "List tanah yang anda miliki:" << endl;
                    for (int i = 0; i < banyak_tanah; i++)
                    {
                        cout << "ID: \"" << id_tanah_dimiliki[i] << "\". " << data_pbb[id_tanah_dimiliki[i]].label << " - " << data_pbb[id_tanah_dimiliki[i]].alamat << endl;
                    }
                    cout << endl << "Pilih ID Tanah (tanpa petik dua (\" \")): ";
                    cin >> id_tanah_dipilih;
                    bool ketemu = 0;
                    for (int i = 0; i < banyak_tanah; i++)
                    {
                        if (id_tanah_dipilih == id_tanah_dimiliki[i])
                        {
                            ketemu = 1;
                            break;
                        }
                    }
                    
                    if (id_tanah_dipilih < 0 || id_tanah_dipilih >= id_tanah || ketemu == 0) {
                        cout << "ID Tanah tidak valid." << endl;
                        break;
                    }
                    cout << "Tanggal Pembayaran (dd-mm-yyyy): ";
                    cin >> tanggal_bayar;

                    system("pause");
                    system("cls");

                    cout << "+------------------------------------+" << endl;
                    cout << "| Pembayaran Pajak Bumi dan Bangunan |" << endl;
                    cout << "+------------------------------------+" << endl;
                    cout << "Label Tanah: " << data_pbb[id_tanah_dipilih].label << endl;
                    cout << "Alamat     : " << data_pbb[id_tanah_dipilih].alamat << endl;
                    cout << "Luas Tanah : " << data_pbb[id_tanah_dipilih].luas << " m^2" << endl;
                    cout << "Status Tanah: ";
                    (data_pbb[id_tanah_dipilih].bangunan == 'Y') ? cout << "Ada Bangunan" << endl : cout << "Tidak Ada Bangunan" << endl;
                    cout << "-------------------------------------" << endl;

                    int pajak;
                    int pajak_bangunan = 0;
                    int denda = 0;
                    int idx_sudah_pernahBayar = -1;
                    int selisih_tanggal = 0;
                    banyak_data_pbb = baca_data_pbb();
                    pajak = data_pbb[id_tanah_dipilih].luas * 1000; // pajak tanah Rp. 1000 per m^2
                    if (data_pbb[id_tanah_dipilih].bangunan == 'Y')
                    {
                        pajak_bangunan = data_pbb[id_tanah_dipilih].luas * 500; // pajak bangunan Rp. 500 per m^2
                    }
                    for (int i = 0; i < banyak_data_pbb; i++)
                    {
                        if (data_pajak_pbb[i].id_tanah == id_tanah_dipilih && data_pajak_pbb[i].pemilik == id_sedang_login)
                        {
                            idx_sudah_pernahBayar = i;
                        }
                    }
                    if (idx_sudah_pernahBayar != -1)
                    {
                        selisih_tanggal = cek_selisih_tanggal(data_pajak_pbb[idx_sudah_pernahBayar].tgl_bayar, tanggal_bayar);
                        if (selisih_tanggal > 365)
                        {
                            denda = hitung_denda((pajak + pajak_bangunan), (selisih_tanggal - 365)); // denda 10% dari total pajak
                        }else{
                            denda = 0; // tidak ada denda jika bayar tepat waktu
                        }
                        
                    }else{
                        selisih_tanggal = cek_selisih_tanggal(data_pbb[id_tanah_dipilih].tgl_beli, tanggal_bayar);
                        if (selisih_tanggal > 365)
                        {
                            denda = hitung_denda((pajak + pajak_bangunan), (selisih_tanggal - 365)); // denda 10% dari total pajak
                        }else{
                            denda = 0; // tidak ada denda jika bayar tepat waktu
                        }
                    }
                    
                    char yakin_bayar = 'N';
                    if(selisih_tanggal >= 358){
                        cout << "Pajak Tanah: Rp. " << pajak << endl;
                        cout << "Pajak Bangunan: Rp. " << pajak_bangunan << endl;
                        cout << "Denda: Rp. " << denda << endl;
                        cout << "Total Pajak yang harus dibayar: Rp. " << pajak + pajak_bangunan + denda << endl;
                        cout << "Apakah Anda yakin akan membayar pajak PBB (Y/N): ";
                        cin >> yakin_bayar;
                        cin.ignore();
                        if (yakin_bayar == 'Y' || yakin_bayar == 'y')
                        {
                            cout << "Pembayaran Pajak Berhasil." << endl;
                            cout << "Terimakasih telah membayar pajak PBB." << endl;

                            // simpan data pembayaran ke file
                            tulis << data_pbb[id_tanah_dipilih].pemilik << '|'; // pemilik
                            tulis << id_tanah_dipilih << '|'; // id_tanah
                            tulis << tanggal_bayar << '|'; // tgl_bayar
                            tulis << pajak << '|'; // pajak_tanah
                            tulis << pajak_bangunan << '|'; // pajak_bangunan
                            tulis << denda << endl; // denda
                        }else{
                            cout << "Pembayaran Pajak Dibatalkan." << endl;
                        }
                    }else{
                        cout << "Tanggal pembayaran tidak valid." << endl;
                        cout << "Pembayaran Pajak Dibatalkan." << endl;
                    }
                }
                break;

            case 3:
                print_cantik("Balik Nama Pemilik Tanah");
                cout << "Pada menu ini anda memerlukan identitas berupa: " << endl;
                cout << "1. NIK Pemilik Tanah Sebelumnya" << endl;
                cout << "2. Alamat Tanah yang akan dibalik nama" << endl;
                cout << "Apakah Anda yakin akan melakukan balik nama sertifikat tanah (Y/N): ";
                cin >> yakin_balik;
                if (yakin_balik != 'Y' && yakin_balik != 'y')
                {
                    cout << "Proses Balik Nama Dibatalkan." << endl;
                }else{
                    system("cls");
                    ketemu = 0;
                    print_cantik("Input Data");
                    cout << "NIK Pemilik Tanah Sebelumnya: ";
                    cin >> auth_nik;
                    cout << "Alamat Tanah yang akan dibalik nama: ";
                    cin.ignore();
                    getline(cin, auth_alamat);

                    id_pemilikLama = nik_masuk_id_berapa(auth_nik);
                    if (id_pemilikLama != -1)
                    {
                        system("cls");
                        id_tanah_dicari = tanah_id_berapa(auth_alamat);
                        if (id_tanah_dicari != -1 && id_pemilikLama == data_pbb[id_tanah_dicari].pemilik)
                        {
                            ketemu = 1;
                            cout << "Data Berhasil ditemukan!" << endl;
                            cout << "Pemilik     : " << user[id_pemilikLama].nama << endl;
                            cout << "Label Tanah : " << data_pbb[id_tanah_dicari].label << endl;
                            cout << "Alamat      : " << data_pbb[id_tanah_dicari].alamat << endl;
                            cout << "Luas Tanah  : " << data_pbb[id_tanah_dicari].luas << endl;
                            cout << "Status Tanah: ";
                            (data_pbb[id_tanah_dicari].bangunan == 'Y') ? cout << "Ada Bangunan" << endl << endl: cout << "Tidak Ada Bangunan" << endl << endl;
                            cout << "Data berhasil diubah nama." << endl;
                            data_pbb[id_tanah_dicari].pemilik = id_sedang_login;
                            simpan_sertifikat_tanah();
                        }
                    }
                    if(id_pemilikLama == -1 || ketemu == 0){
                        cout << "Sertifikat Tanah tidak ditemukan atau data tidak sesuai." << endl; 
                        cout << "Gagal Melakukan balik nama." << endl;
                    }
                }
                break;

            case 4:
                print_cantik("Cek Status Pajak");
                banyak_data_pbb = baca_data_pbb();
                if (banyak_data_pbb == 0)
                {
                    cout << "Anda belum pernah membayar pajak PBB." << endl;
                }else
                {
                    cout << "List Sertifikat Tanah yang anda miliki:" << endl;
                    for (int i = 0; i < id_tanah; i++)
                    {
                        if (data_pbb[i].pemilik == id_sedang_login)
                        {
                            cout << "ID: \"" << i << "\". " << data_pbb[i].label << " - " << data_pbb[i].alamat << endl;
                        }
                    }
                    cout << endl << "Pilih ID Tanah (tanpa petik dua (\" \")): ";
                    cin >> id_tanah_dipilih;
                    bool ketemu = 0;
                    for (int i = 0; i < banyak_tanah; i++)
                    {
                        if (id_tanah_dipilih == id_tanah_dimiliki[i])
                        {
                            ketemu = 1;
                            break;
                        }
                    }
                    if (id_tanah_dipilih < 0 || id_tanah_dipilih >= id_tanah || ketemu == 0) {
                        cout << "ID Tanah tidak valid." << endl;
                        break;
                    }
                    system("pause");
                    system("cls");
                    cout << "Anda memilih ID Tanah: \"" << id_tanah_dipilih << "\". " << data_pbb[id_tanah_dipilih].label << " - " << data_pbb[id_tanah_dipilih].alamat << endl;
                    cout << "Data Pajak yang telah dibayar:" << endl;
                    for (int i = 0; i < banyak_data_pbb; i++)
                    {
                        if (data_pajak_pbb[i].id_tanah == id_tanah_dipilih && data_pajak_pbb[i].pemilik == id_sedang_login)
                        {
                            cout << "Tanggal Bayar: " << data_pajak_pbb[i].tgl_bayar 
                                 << ", Pajak Tanah: Rp. " << data_pajak_pbb[i].pajak_tanah 
                                 << ", Pajak Bangunan: Rp. " << data_pajak_pbb[i].pajak_bangunan 
                                 << ", Denda: Rp. " << data_pajak_pbb[i].denda 
                                 << endl << endl;
                        }
                    }
                }
                break;

            case 5:
                print_cantik("Ubah Data Sertifikat");
                banyak_tanah = 0;
                for (int i = 0; i < id_tanah; i++)
                {
                    if (data_pbb[i].pemilik == id_sedang_login)
                    {
                        id_tanah_dimiliki[banyak_tanah] = i;
                        banyak_tanah++;
                    }
                }
                if (banyak_tanah == 0) cout << "Anda belum memiliki sertifikat tanah terdaftar." << endl;
                else{
                    cout << "List tanah yang anda miliki:" << endl;
                    for (int i = 0; i < banyak_tanah; i++)
                    {
                        cout << "ID: \"" << id_tanah_dimiliki[i] << "\". " << data_pbb[id_tanah_dimiliki[i]].label << " - " << data_pbb[id_tanah_dimiliki[i]].alamat << endl;
                    }
                    cout << endl << "Pilih ID Tanah (tanpa petik dua (\" \")): ";
                    cin >> id_tanah_dipilih;
                    bool ketemu = 0;
                    for (int i = 0; i < banyak_tanah; i++)
                    {
                        if (id_tanah_dipilih == id_tanah_dimiliki[i])
                        {
                            ketemu = 1;
                            break;
                        }
                    }
                    if (id_tanah_dipilih < 0 || id_tanah_dipilih >= id_tanah || ketemu == 0) {
                        cout << "ID Tanah tidak valid." << endl;
                        break;
                    }
                    system("pause");
                    system("cls");
                    cout << "Anda memilih ID Tanah: \"" << id_tanah_dipilih << "\". " << data_pbb[id_tanah_dipilih].label << " - " << data_pbb[id_tanah_dipilih].alamat << endl;
                    cout << "Data yang akan diubah:" << endl;
                    cout << "1. Label Tanah" << endl;
                    cout << "2. Status Tanah (Ada/Tidak Ada Bangunan)" << endl;
                    cout << "Pilih Data yang akan diubah (1/2): ";
                    cin >> pilih_data_diubah;
                    if(pilih_data_diubah == 1){
                        cin.ignore();
                        cout << "Label Tanah Baru: ";
                        getline(cin, data_pbb[id_tanah_dipilih].label);
                        cout << "Label Tanah Berhasil Diubah." << endl;
                    }else if(pilih_data_diubah == 2){
                        cout << "Status Tanah Baru (Y/N): ";
                        cin >> status;
                        if (status == 'Y' || status == 'y' || status == 'N' || status == 'n'){
                            data_pbb[id_tanah_dipilih].bangunan = status;
                            cout << "Status Tanah Berhasil Diubah." << endl;
                        }else{
                            cout << "Status Tanah tidak valid." << endl;
                        }
                    }else{
                        cout << "Pilihan tidak valid." << endl;
                    }
                }
                simpan_sertifikat_tanah();
                break;

            case 6:
                print_cantik("Unduh Laporan Pajak");
                cout << "Laporan Pajak PBB akan diunduh ke file 'laporan_pajak_pbb.txt'." << endl;
                system("pause");
                system("cls");
                laporan_pbb();
                cout << "Laporan Pajak PBB berhasil diunduh." << endl;
                break;

            case 0:
                print_cantik("Keluar");
                cout << "Apakah anda yakin akan keluar dari sistem Pembayaran PBB (Y/N): ";
                cin >> yakin1;
                break;
            
            default:
                print_cantik("Menu Tidak Valid.");
                break;
            }
            tulis.close();
            if (pilih_menu != 0) system("pause");
    }while(yakin1 != 'Y' && yakin1 != 'y');
};

void kendaraan(){
    int pilih_menu, id_pemilikLama, auth_nik, id_kendaraan_dicari, banyak_data_pajakKendaraan = 0;
    int banyak_kendaraan = 0, id_kendaraan_dimiliki[1000], id_kendaraan_dipilih;
    char yakin2, yakin_balik;
    bool ketemu;
    string auth_nopol, auth_noRangka;
    do{
        ofstream tulis("data_pajak_kendaraan.txt", ios::app);
        print_cantik("Menu Pajak Kendaraan");
        cout << "1. Tambah Kendaraan" << endl;
        cout << "2. Bayar Pajak (Kendaraan)" << endl;
        cout << "3. Balik Nama Pemilik Kendaraan" << endl;
        cout << "4. Cek Status Pajak" << endl;
        cout << "5. Unduh Laporan Pajak" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilih Menu: "; 
        cin >> pilih_menu;
        switch (pilih_menu){
            case 1:
                print_cantik("Tambah Kendaraan");
                data_kendaraan[id_kendaraan].pemilik = id_sedang_login;
                cin.ignore();
                cout << "No. Polisi (cth: AB 1234 XX): ";
                getline(cin, data_kendaraan[id_kendaraan].nopol);
                cout << "Tanggal Pembelian (dd-mm-yyyy): ";
                cin >> data_kendaraan[id_kendaraan].tgl_beli;
                cin.ignore();
                cout << "Merk (cth: Honda): ";
                getline(cin, data_kendaraan[id_kendaraan].merk);
                cout << "Tipe (cth: Beat): ";
                getline(cin, data_kendaraan[id_kendaraan].tipe);
                cout << "Isi Silinder dlm CC (cth: 150): ";
                cin >> data_kendaraan[id_kendaraan].cc;
                cout << "Tahun Perakitan (cth: 2020): ";
                cin >> data_kendaraan[id_kendaraan].thn_perakitan;
                cin.ignore();
                cout << "Nomor Rangka (cth: MH1234567890): ";
                getline(cin, data_kendaraan[id_kendaraan].no_rangka);
                system("pause");
                system("cls");
                cout << "Data Kendaraan Berhasil Disimpan." << endl;
                id_kendaraan++;
                simpan_data_kendaraan();
                break;

            case 2:
                print_cantik("Bayar Pajak Kendaraan");
                banyak_kendaraan = 0;
                for (int i = 0; i < id_kendaraan; i++)
                {
                    if (data_kendaraan[i].pemilik == id_sedang_login)
                    {
                        id_kendaraan_dimiliki[banyak_kendaraan] = i;
                        banyak_kendaraan++;
                    }
                }
                if (banyak_kendaraan == 0) cout << "Anda belum memiliki kendaraan terdaftar." << endl;
                else{
                    string tanggal_bayar;
                    cout << "List kendaraan yang anda miliki:" << endl;
                    for (int i = 0; i < banyak_kendaraan; i++)
                    {
                        cout << "ID: \"" << id_kendaraan_dimiliki[i] << "\". " << data_kendaraan[id_kendaraan_dimiliki[i]].nopol << endl;
                    }
                    cout << endl << "Pilih ID Kendaraan (tanpa petik dua (\" \")): ";
                    cin >> id_kendaraan_dipilih;
                    bool ketemu = 0;
                    for (int i = 0; i < banyak_kendaraan; i++)
                    {
                        if (id_kendaraan_dipilih == id_kendaraan_dimiliki[i])
                        {
                            ketemu = 1;
                            break;
                        }
                    }
                    if (id_kendaraan_dipilih < 0 || id_kendaraan_dipilih >= id_kendaraan || ketemu == 0) {
                        cout << "ID Kendaraan tidak valid." << endl;
                        break;
                    }
                    cout << "Tanggal Pembayaran (dd-mm-yyyy): ";
                    cin >> tanggal_bayar;

                    system("pause");
                    system("cls");

                    cout << "+----------------------------+" << endl;
                    cout << "| Pembayaran Pajak Kendaraan |" << endl;
                    cout << "+----------------------------+" << endl;
                    cout << "No. Polisi: " << data_kendaraan[id_kendaraan_dipilih].nopol << endl;
                    cout << "Merk      : " << data_kendaraan[id_kendaraan_dipilih].merk << endl;
                    cout << "Tipe      : " << data_kendaraan[id_kendaraan_dipilih].tipe << endl;
                    cout << "Isi Silinder: " << data_kendaraan[id_kendaraan_dipilih].cc << " CC" << endl;
                    cout << "Tahun Perakitan: " << data_kendaraan[id_kendaraan_dipilih].thn_perakitan << endl;
                    cout << "Nomor Rangka: " << data_kendaraan[id_kendaraan_dipilih].no_rangka << endl;
                    cout << "-------------------------------------" << endl;

                    int pajak;
                    int denda = 0;
                    int idx_sudah_pernahBayar = -1;
                    int selisih_tanggal = 0;
                    banyak_data_pajakKendaraan = baca_data_pajak_kendaraan();
                    pajak = data_kendaraan[id_kendaraan_dipilih].cc * 100; // pajak kendaraan Rp. 100 per CC
                    for (int i = 0; i < banyak_data_pajakKendaraan; i++)
                    {
                        if (data_pajak_kendaraan[i].id_kendaraan == id_kendaraan_dipilih && data_pajak_kendaraan[i].pemilik == id_sedang_login)
                        {
                            idx_sudah_pernahBayar = i;
                        }
                    }
                    if (idx_sudah_pernahBayar != -1)
                    {
                        selisih_tanggal = cek_selisih_tanggal(data_pajak_kendaraan[idx_sudah_pernahBayar].tgl_bayar, tanggal_bayar);
                        if (selisih_tanggal > 365)
                        {
                            denda = hitung_denda(pajak, (selisih_tanggal - 365)); // denda 10% dari total pajak
                        }else{
                            denda = 0; // tidak ada denda jika bayar tepat waktu
                        }
                        
                    }else{
                        selisih_tanggal = cek_selisih_tanggal(data_kendaraan[id_kendaraan_dipilih].tgl_beli, tanggal_bayar);
                        if (selisih_tanggal > 365)
                        {
                            denda = hitung_denda(pajak, (selisih_tanggal - 365)); // denda 10% dari total pajak
                        }else{
                            denda = 0; // tidak ada denda jika bayar tepat waktu
                        }
                    }
                    
                    char yakin_bayar = 'N';
                    if (selisih_tanggal >= 358)
                    {
                        cout << "Pajak Kendaraan: Rp. " << pajak << endl;
                        cout << "Denda: " << denda << endl;
                        cout << "Total Pajak yang harus dibayar: Rp. " << pajak + denda << endl;
                        cout << "Apakah Anda yakin akan membayar pajak Kendaraan (Y/N): ";
                        cin >> yakin_bayar;
                        cin.ignore();
                        if (yakin_bayar == 'Y' || yakin_bayar == 'y')
                        {
                            cout << "Pembayaran Pajak Berhasil." << endl;
                            cout << "Terimakasih telah membayar pajak Kendaraan." << endl;

                            // simpan data pembayaran ke file
                            tulis << data_kendaraan[id_kendaraan_dipilih].pemilik << '|'; // pemilik
                            tulis << id_kendaraan_dipilih << '|'; // id_kendaraan
                            tulis << data_kendaraan[id_kendaraan_dipilih].nopol << '|'; // nopol
                            tulis << tanggal_bayar << '|'; // tgl_bayar
                            tulis << pajak << '|'; // pajak_kendaraan
                            tulis << denda << endl; // denda
                        }else{
                            cout << "Pembayaran Pajak Dibatalkan." << endl;
                        }
                    } else{
                        cout << "Anda belum bisa membayar pajak kendaraan, karena belum masuk waktu pembayaran pajak." << endl;
                    }
                }
                break;

            case 3:
                print_cantik("Balik Nama Pemilik Kendaraan");
                cout << "Pada menu ini anda memerlukan identitas berupa: " << endl;
                cout << "1. NIK Pemilik Kendaraan Sebelumnya" << endl;
                cout << "2. No Polisi kendaraan yang akan dibalik nama" << endl;
                cout << "3. No Rangka kendaraan yang akan dibalik nama" << endl;
                cout << "Apakah Anda yakin akan melakukan balik nama kepemilikan kendaraan (Y/N): ";
                cin >> yakin_balik;
                if (yakin_balik != 'Y' && yakin_balik != 'y')
                {
                    cout << "Proses Balik Nama Dibatalkan." << endl;
                }else{
                    system("cls");
                    ketemu = 0;
                    print_cantik("Input Data");
                    cout << "NIK Pemilik Kendaraan Sebelumnya: ";
                    cin >> auth_nik;
                    cin.ignore();
                    cout << "Nomor Polisi (cth: AB 1234 XX): ";
                    getline(cin, auth_nopol);
                    cout << "Nomor Rangka (cth: MH1234567890): ";
                    getline(cin, auth_noRangka);
                    id_pemilikLama = nik_masuk_id_berapa(auth_nik);
                    if (id_pemilikLama != -1)
                    {
                        system("cls");
                        id_kendaraan_dicari = kendaraan_id_berapa(auth_nopol);
                        if (id_kendaraan_dicari != -1 && id_pemilikLama == data_kendaraan[id_kendaraan_dicari].pemilik)
                        {
                            if (auth_noRangka == data_kendaraan[id_kendaraan_dicari].no_rangka)
                            {
                                ketemu = 1;
                                cout << "Data Berhasil ditemukan!" << endl;
                                cout << "Pemilik        : " << user[id_pemilikLama].nama << endl;
                                cout << "Nomor Polisi   : " << data_kendaraan[id_kendaraan_dicari].nopol << endl;
                                cout << "Merk           : " << data_kendaraan[id_kendaraan_dicari].merk << endl;
                                cout << "Isi Silinder   : " << data_kendaraan[id_kendaraan_dicari].cc << " CC" << endl;
                                cout << "Tahun Perakitan: " << data_kendaraan[id_kendaraan_dicari].thn_perakitan << endl;
                                cout << "No Rangka      : " << data_kendaraan[id_kendaraan_dicari].no_rangka << endl << endl;
                                cout << "Data berhasil diubah nama." << endl;
                                data_kendaraan[id_kendaraan_dicari].pemilik = id_sedang_login;
                                simpan_data_kendaraan();
                            }
                        }
                    }
                    if(ketemu == 0){
                        cout << "Kendaraan tidak ditemukan atau data tidak sesuai." << endl; 
                        cout << "Gagal Melakukan balik nama." << endl;
                    }
                }
                
                break;

            case 4:
                print_cantik("Cek Status Pajak");
                banyak_kendaraan = baca_data_pajak_kendaraan();
                if (banyak_kendaraan == 0)
                {
                    cout << "Anda belum pernah membayar pajak kendaraan." << endl;
                }else{
                    cout << "List Kendaraan yang anda miliki:" << endl;
                    int a = 0;
                    for (int i = 0; i < banyak_kendaraan; i++)
                    {
                        if (data_kendaraan[i].pemilik == id_sedang_login)
                        {
                            cout << "ID: \"" << i << "\". " << data_kendaraan[i].nopol << " - " << data_kendaraan[i].merk << " " << data_kendaraan[i].tipe << endl;
                            id_kendaraan_dimiliki[a] = i;
                            a++;
                        }
                    }
                    cout << endl << "Pilih ID Kendaraan (tanpa petik dua (\" \")): ";
                    cin >> id_kendaraan_dipilih;
                    bool ketemu = 0;
                    for (int i = 0; i < a; i++)
                    {
                        if (id_kendaraan_dipilih == id_kendaraan_dimiliki[i])
                        {
                            ketemu = 1;
                            break;
                        }
                    }
                    if (id_kendaraan_dipilih < 0 || id_kendaraan_dipilih >= id_kendaraan || ketemu == 0) {
                        cout << "ID Kendaraan tidak valid." << endl;
                        break;
                    }
                    system("pause");
                    system("cls");
                    cout << "Anda memilih ID Kendaraan: \"" << id_kendaraan_dipilih << "\". " << data_kendaraan[id_kendaraan_dipilih].nopol << endl;
                    cout << "Data Pajak yang telah dibayar:" << endl;
                    for (int i = 0; i < banyak_kendaraan; i++)
                    {
                        if (data_pajak_kendaraan[i].id_kendaraan == id_kendaraan_dipilih && data_pajak_kendaraan[i].pemilik == id_sedang_login)
                        {
                            cout << "Tanggal Bayar: " << data_pajak_kendaraan[i].tgl_bayar 
                                 << ", Pajak Kendaraan: Rp. " << data_pajak_kendaraan[i].pajak_kendaraan 
                                 << ", Denda: Rp. " << data_pajak_kendaraan[i].denda 
                                 << endl << endl;
                        }
                    }
                }
                break;

            case 5:
                print_cantik("Unduh Laporan Pajak");
                cout << "Laporan Pajak Kendaraan akan diunduh ke file 'laporan_pajak_kendaraan.txt'." << endl;
                system("pause");
                system("cls");
                laporan_kendaraan();
                cout << "Laporan Pajak Kendaraan berhasil diunduh." << endl;
                break;

            case 0:
                print_cantik("Keluar");
                cout << "Apakah anda yakin akan keluar dari sistem Pembayaran Pajak Kendaraan (Y/N): ";
                cin >> yakin2;
                break;
            
            default:
                print_cantik("Menu Tidak Valid.");
                break;
            }
            tulis.close();
            if (pilih_menu != 0) system("pause");
    }while(yakin2 != 'Y' && yakin2 != 'y');
};

void identitas(){
    print_cantik("Identitas Pribadi");
    cout << "Nama Lengkap     : " << user[id_sedang_login].nama << endl;
    cout << "Tanggal Lahir    : " << user[id_sedang_login].tgl_lahir << endl;
    cout << "Profesi          : " << user[id_sedang_login].profesi << endl;
    cout << "Status Perkawinan: ";
    (user[id_sedang_login].status == 'Y') ? cout << "Kawin\n" : cout << "Belum Kawin\n";
};

void simpan_data_user() {
    ofstream tulis("data_user.txt");
    for (int i = 0; i < id_terdaftar; i++) {
        tulis << user[i].nik << '|'
              << user[i].nama << '|'
              << user[i].tgl_lahir_asli << '|'
              << user[i].tgl_lahir << '|'
              << user[i].profesi << '|'
              << user[i].status << '|'
              << user[i].pass << endl;
    }
    tulis.close();
}

void baca_data_user() {
    ifstream baca("data_user.txt");
    string line, nik, nama, tgl_lahir_asli, tgl_lahir, profesi, status, pass;
    id_terdaftar = 0;
    while (getline(baca, line) && id_terdaftar < 1000) {
        stringstream ss(line);
        getline(ss, nik, '|');
        getline(ss, nama, '|');
        getline(ss, tgl_lahir_asli, '|');
        getline(ss, tgl_lahir, '|');
        getline(ss, profesi, '|');
        getline(ss, status, '|');
        getline(ss, pass);
        user[id_terdaftar].nik = stoi(nik);
        user[id_terdaftar].nama = nama;
        user[id_terdaftar].tgl_lahir_asli = tgl_lahir_asli;
        user[id_terdaftar].tgl_lahir = tgl_lahir;
        user[id_terdaftar].profesi = profesi;
        user[id_terdaftar].status = status[0];
        user[id_terdaftar].pass = pass;
        id_terdaftar++;
    }
    baca.close();
}

int hitung_denda(int pajak, int selisih_hari){
    if(selisih_hari == 0){
        return 0;
    }else{
        return hitung_denda(pajak, selisih_hari - 1) + (pajak * 0.01); // denda 0.01 dari total pajak per hari keterlambatan
    }
};

int cek_selisih_tanggal(string tgl_beli, string tgl_bayar){
    // dd-mm-yyyy
    // 0123456789
    int d1 = stoi(tgl_beli.substr(0, 2));
    int m1 = stoi(tgl_beli.substr(3, 2));
    int y1 = stoi(tgl_beli.substr(6, 4));

    int d2 = stoi(tgl_bayar.substr(0, 2));
    int m2 = stoi(tgl_bayar.substr(3, 2));
    int y2 = stoi(tgl_bayar.substr(6, 4));

    return (y2 - y1) * 365 + (m2 - m1) * 30 + (d2 - d1);
};

void ubah_format_tglLhr(string tgl_lhr_asli, string *tgl_lhr){
    // dd-mm-yyyy
    // 0123456789
    string x, y, z;
    int yInt;

    x = tgl_lhr_asli.substr(0, 2);          // tanggal
    yInt = stoi(tgl_lhr_asli.substr(3, 2)); // bulan

    if (yInt == 1) y = "Januari";
    else if (yInt == 2) y = "Februari";
    else if (yInt == 3) y = "Maret";
    else if (yInt == 4) y = "April";
    else if (yInt == 5) y = "Mei";
    else if (yInt == 6) y = "Juni";
    else if (yInt == 7) y = "Juli";
    else if (yInt == 8) y = "Agustus";
    else if (yInt == 9) y = "September";
    else if (yInt == 10) y = "Oktober";
    else if (yInt == 11) y = "November";
    else if (yInt == 12) y = "Desember";
    else y = "Bulan Tidak Valid";

    z = tgl_lhr_asli.substr(6, 4); // tahun
    *tgl_lhr = x + ' ' + y + ' ' + z;
};

void buat_pass(int id){
    string pass_baru, konfir_pass;
    int pjg_char;
    bool kondisi_pass = 0;
    do{
        system("cls");
        cout << "Buatlah password dengan ketentuan:\n1. Minimal panjang 8 Karakter\n2. Mengandung minimal 1 Uppercase\n3. Mengandung minimal 1 Lowercase\n4. Mengandung minimal 1 Angka\n5. Mengandung minimal 1 Simbol" << endl << endl;
        cout << "Password Baru: ";
        getline(cin, pass_baru);
        cout << "Konfirmasi Password Baru: ";
        getline(cin, konfir_pass);
        if (pass_baru != konfir_pass)
        {
            cout << "Konfirmasi Password tidak sesuai." << endl;
            system("pause");
        }else{
            pjg_char = pass_baru.length();
            kondisi_pass = cek_ketentuan_pass(pass_baru, pjg_char);
            if(kondisi_pass == true){
                user[id].pass = pass_baru;
                cout << endl << "Registrasi Berhasil." << endl;
            }else{
                cout << endl << "Password tidak sesuai ketentuan." << endl;
                cout << "Silahkan Buat Ulang Password." << endl;
                system("pause");
            }
        }
    }while(!kondisi_pass);
};

bool cek_nik_belum_dipakai(int nik_baru){
    bool ans = 1;
    for (int i = 0; i < id_terdaftar; i++)
    {
        if (nik_baru == user[i].nik)
        {
            ans = 0;
            break;
        }
    }
    return ans;
};

bool cek_ketentuan_pass(string pass_baru, int pjg_char){
    bool upper = 0, lower = 0, angka = 0, simbol = 0;
    char huruf;
    for (int i = 0; i < pjg_char; i++)
    {
        huruf = pass_baru[i];
        if (huruf >= '0' && huruf <= '9') angka = 1;
        else if(huruf >= 'A' && huruf <= 'Z') upper = 1;
        else if(huruf >= 'a' && huruf <= 'z') lower = 1;
        else simbol = 1;
    }
    return (angka == 1 && upper == 1 && lower == 1 && simbol == 1 && pjg_char >= 8) ? 1 : 0;
};

bool cek_berhasil_login_atau_tidak(int nik, string pass){
    int id = nik_masuk_id_berapa(nik);
    if (id == -1) return 0;
    return (pass == user[id].pass);
};

bool cek_kesesuaian_nik_dan_tglLhr(int nik, string tgl_lhr){
    int id = nik_masuk_id_berapa(nik);
    if (id == -1) return 0;
    return (tgl_lhr == user[id].tgl_lahir_asli);
}

int nik_masuk_id_berapa(int nik){
    int ans = -1;
    for (int i = 0; i < id_terdaftar; i++)
    {
        if (nik == user[i].nik)
        {
            ans = i;
            break;
        }
    } 
    return ans;
};

int tanah_id_berapa(string alamat){
    for (int i = 0; i < id_tanah; i++)
    {
        if (alamat == data_pbb[i].alamat)
        {
            return i;
        }
    }
    return -1;
}

int kendaraan_id_berapa(string no_pol){
    for (int i = 0; i < id_kendaraan; i++)
    {
        if (no_pol == data_kendaraan[i].nopol)
        {
            return i;
        }
    }
    return -1;
}

void kata_kata(){
    system("cls");
    cout << "Terimakasih sudah rajin dalam membayar pajak." << endl;
    cout << "++==========================================++" << endl;
    cout << "|| PAJAK DIGUNAKAN UNTUK KEPENTINGAN RAKYAT ||" << endl;
    cout << "|| BUKAN UNTUK MEMPERKAYA DIRI PARA PEJABAT ||" << endl;
    cout << "++==========================================++" << endl;
};
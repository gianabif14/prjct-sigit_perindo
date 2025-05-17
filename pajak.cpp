#include <iostream>
using namespace std;

typedef struct
{
    int nik;
    string nama;
    string tgl_lahir;
    string profesi;
    char status;
    string pass;
} pengguna;

pengguna user[1000];

void print_cantik(string header);
void ubah_format_tglLhr(string *tglLahir);
void buat_pass(int id);
void kata_kata();
void main_menu();
void pph();
void pbb();
void kendaraan();
void identitas();
int nik_masuk_id_berapa(int nik);
int id_terdaftar=0;
int id_sedang_login = -1;
bool cek_nik_terdaftar(int nik_baru);
bool cek_ketentuan_pass(string pass_baru, int pjg_char);
bool cek_berhasil_login_atau_tidak(int nik, string pass);
bool cek_kesesuaian_nik_dan_tglLhr(int nik, string tgl_lhr);

//sementara untuk integrasi cmd linux
void cls(){
    system("clear");
}
void pause(){
    cout << "Press any key to continue...";
    cin.ignore();
    cin.get();
}

int main()
{
    
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
            cin.ignore();
            if (cek_nik_terdaftar(nik_baru)){
                user[id_terdaftar].nik = nik_baru;
                cout << "Nama Lengkap: "; getline(cin, user[id_terdaftar].nama);
                cout << "Tanggal Lahir (dd-mm-yyyy): "; cin >> user[id_terdaftar].tgl_lahir;
                ubah_format_tglLhr(&user[id_terdaftar].tgl_lahir);
                cout << "Profesi: ";
                cin.ignore();
                getline(cin, user[id_terdaftar].profesi);
                cout << "Status Perkawinan (Y/T): "; cin >> user[id_terdaftar].status;
                pause();
                cls();
                buat_pass(id_terdaftar);
                id_terdaftar++;
            } else{
                cout << "NIK Sudah Terdaftar" << endl;
            }
            pause();
            break;
        
        case 2:
            print_cantik("Login");
            cout << "Masukkan NIK: "; cin >> auth_nik;
            cout << "Masukkan Password: "; cin >> auth_pass;
            cout << "Konfirmasi Password: "; cin >> auth_pass2;
            if (auth_pass == auth_pass2)
            {
                if(cek_berhasil_login_atau_tidak(auth_nik, auth_pass)){
                    cout << endl << "Login Berhasil." << endl;
                    id_sedang_login = nik_masuk_id_berapa(auth_nik);
                    pause();
                    main_menu();
                }else{
                    cout << endl << "NIK/Password Salah. Login Gagal!" << endl;
                }
            }else{
                cout << endl << "Konfirmasi Password Tidak Sesuai!" << endl;
            }
            pause();
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
            pause();
            break;
        
        case 0:
            print_cantik("Keluar Sistem");
            cout << "Apakah anda yakin akan keluar dari sistem (Y/N): ";
            cin >> yakin;
            (yakin == 'Y' || yakin == 'y') ? menu_awal = 0 : menu_awal = 1;
            break;
        
        default:
            print_cantik("Input Salah");
            pause();
            break;
        }
    } while(menu_awal);
    kata_kata();
}

void print_cantik(string header){
    int pjg_char= header.size()+4;
    cls();
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
        cls();
        print_cantik("Menu Utama");
        cout << endl << "1. Bayar pajak Penghasilan\n2. Bayar pajak PBB\n3. Bayar pajak Kendaraan\n4. Identitas Pribadi\n0. Keluar Sistem (Log Out)" << endl;
        cout << "Pilih Menu: ";
        cin >> pilih_menu;
        switch (pilih_menu)
        {
        case 1:
            pph();
            break;

        case 2:
            pbb();
            break;

        case 3:
            kendaraan();
            break;

        case 4:
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
        if (pilih_menu != 0) pause();
    }while(yakin != 'Y' && yakin != 'y');
};

void pph(){
    print_cantik("Menu Pajak Penghasilan");
};

void pbb(){
    print_cantik("Menu Pajak Bumi dan Bangunan");
};

void kendaraan(){
    print_cantik("Menu Pajak Kendaraan");
};

void identitas(){
    print_cantik("Identitas Pribadi");
    cout << "Nama Lengkap     : " << user[id_sedang_login].nama << endl;
    cout << "Tanggal Lahir    : " << user[id_sedang_login].tgl_lahir << endl;
    cout << "Profesi          : " << user[id_sedang_login].profesi << endl;
    cout << "Status Perkawinan: ";
    (user[id_sedang_login].status == 'Y') ? cout << "Kawin\n" : cout << "Belum Kawin\n";
};

void ubah_format_tglLhr(string *tglLahir){
    // dd-mm-yyyy
    // 0123456789
    string x, y, z;
    int yInt;

    x = tglLahir->substr(0, 2);          // tanggal
    yInt = stoi(tglLahir->substr(3, 2)); // bulan

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

    z = tglLahir->substr(6, 4); // tahun
    *tglLahir = x + ' ' + y + ' ' + z;
};

void buat_pass(int id){
    cin.ignore();
    string pass_baru;
    int pjg_char;
    bool kondisi_pass = 0;
    do{
        cout << "Buatlah password dengan ketentuan:\n1. Minimal panjang 8 Karakter\n2. Mengandung minimal 1 Uppercase\n3. Mengandung minimal 1 Lowercase\n4. Mengandung minimal 1 Angka\n5. Mengandung minimal 1 Simbol" << endl << endl;
        cout << "Password Baru: ";
        getline(cin, pass_baru);
        pjg_char = pass_baru.length();
        kondisi_pass = cek_ketentuan_pass(pass_baru, pjg_char);
        if(kondisi_pass == true){
            user[id].pass = pass_baru;
            cout << endl << "Registrasi Berhasil." << endl;
        }else{
            cout << endl << "Password tidak sesuai ketentuan." << endl;
            cout << "Silahkan Buat Ulang Password." << endl;
            pause();
            cls();
        }
    }while(!kondisi_pass);
};

bool cek_nik_terdaftar(int nik_baru){
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
    if (id == -1)
    {
        return 0;
    }
    ubah_format_tglLhr(&tgl_lhr);
    return (tgl_lhr == user[id].tgl_lahir);
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

void kata_kata(){
    cls();
    cout << "Terimakasih sudah rajin dalam membayar pajak." << endl;
    cout << "++==========================================++" << endl;
    cout << "|| PAJAK DIGUNAKAN UNTUK KEPENTINGAN RAKYAT ||" << endl;
    cout << "|| BUKAN UNTUK MEMPERKAYA DIRI PARA PEJABAT ||" << endl;
    cout << "++==========================================++" << endl;
};
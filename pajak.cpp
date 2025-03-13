#include <iostream>
using namespace std;

typedef struct
{
    int nik;
    string nama;
    string tgl_lahir;
    string profesi;
    string status;
    string pass;
} data;

data user[1000];

void print_cantik(string header);
bool cek_nik(int nik_baru);
bool daftar_pass(string pass_baru, int pjg_char);
int id_terdaftar=0;

int main()
{
    
    int pilih_menu, nik_baru, pjg_char;
    string pass_baru;
    bool menu_awal = 1;
    char yakin;
    do{
        print_cantik("Sistem Digital Perpajakan Negeri Indo");
        cout << "Menu Awal:\n1. Registrasi\n2. Login\n0. Keluar Sistem" << endl;
        cout << "Pilih Menu: ";
        cin >> pilih_menu;
        switch (pilih_menu)
        {
        case 1:
            print_cantik("Registrasi Akun");
            cout << "Masukkan NIK: ";
            cin >> nik_baru;
            if (cek_nik(nik_baru) == 1){
                user[id_terdaftar].nik = nik_baru;
                cout << "Nama Lengkap: "; cin >> user[id_terdaftar].nama;
                cout << "Tanggal Lahir (dd-mm-yyyy): "; cin >> user[id_terdaftar].tgl_lahir;
                cout << "Profesi: "; cin >> user[id_terdaftar].profesi;
                cout << "Status Perkawinan (Y/T): "; cin >> user[id_terdaftar].status;
                system("pause");
                system("cls");
                cout << "Buatlah password dengan ketentuan:\n1. Minimal panjang 8 Karakter\n2. Mengandung minimal 1 Uppercase\n3. Mengandung minimal 1 Lowercase\n4. Mengandung minimal 1 Angka" << endl << endl;
                cout << "Password Baru: ";
                cin >> pass_baru;
                pjg_char = pass_baru.length();
                if((daftar_pass(pass_baru, pjg_char)==1) && pjg_char >= 8){
                    cout << "Registrasi Berhasil." << endl;
                }else{
                    cout << "Password tidak sesuai ketentuan." << endl;
                    user[id_terdaftar].nik = -1;
                }
            } else{
                cout << "NIK Sudah Terdaftar" << endl;
            }
            system("pause");
            break;
        
        case 2:
            print_cantik("Login Akun");
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
}

void print_cantik(string header){
    system("cls");
    for (int i = 0; i < header.size()+4; i++)
    {
        cout << '=';
    }
    cout << endl << "  " << header << endl;
    for (int i = 0; i < header.size()+4; i++)
    {
        cout << '=';
    }
    cout << endl;
};

bool cek_nik(int nik_baru){
    bool ans = 1;
    for (int i = 0; i <= id_terdaftar; i++)
    {
        if (nik_baru == user[i].nik)
        {
            ans = 0;
            break;
        }
    }
    return ans;
};

bool daftar_pass(string pass_baru, int pjg_char){
    bool upper = 0, lower = 0, angka = 0, simbol = 0;
    char huruf;
    for (int i = 0; i < pjg_char; i++)
    {
        huruf = pass_baru[i];
        if (huruf >= 48 && huruf <= 57) angka = 1;
        else if(huruf >= 65 && huruf <= 90) upper = 1;
        else if(huruf >= 97 && huruf <= 122) lower = 1;
        else simbol = 1;
    }
    return (angka == 1 && upper == 1 && lower == 1 && simbol == 1) ? 1 : 0;
};
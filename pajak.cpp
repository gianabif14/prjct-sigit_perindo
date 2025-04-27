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
void buat_pass(int id);
bool cek_nik_terdaftar(int nik_baru);
bool daftar_pass(string pass_baru, int pjg_char);
bool login(int nik, string pass);
bool lupa_pass(int nik, string tgl_lhr);
int cek_nik(int nik);
int id_terdaftar=0;

int main()
{
    
    int pilih_menu, nik_baru, pjg_char, auth_nik;
    string pass_baru, auth_pass, auth_pass2, auth_tgl;
    bool menu_awal = 1, kondisi_pass = 0;
    char yakin;
    do{
        system("cls");
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
            if (cek_nik_terdaftar(nik_baru) == 1){
                user[id_terdaftar].nik = nik_baru;
                cin.ignore();
                cout << "Nama Lengkap: "; getline(cin, user[id_terdaftar].nama);
                cout << "Tanggal Lahir (dd-mm-yyyy): "; cin >> user[id_terdaftar].tgl_lahir;
                cout << "Profesi: "; cin >> user[id_terdaftar].profesi;
                cout << "Status Perkawinan (Y/T): "; cin >> user[id_terdaftar].status;
                system("pause");
                system("cls");
                buat_pass(id_terdaftar);
                id_terdaftar++;
            } else{
                cout << "NIK Sudah Terdaftar" << endl;
            }
            system("pause");
            break;
        
        case 2:
            print_cantik("Login Akun");
            cout << "Masukkan NIK: "; cin >> auth_nik;
            cout << "Masukkan Password: "; cin >> auth_pass;
            cout << "Konfirmasi Password: "; cin >> auth_pass2;
            if (auth_pass == auth_pass2)
            {
                if(login(auth_nik, auth_pass)){
                    cout << endl << "Login Berhasil." << endl;
                }else{
                    cout << endl << "NIK/Password Salah. Login Gagal!" << endl;
                }
            }else{
                cout << endl << "Konfirmasi Password Tidak Sesuai!" << endl;
            }
            system("pause");
            break;

        case 3:
            print_cantik("Lupa Password");
            cout << "Masukkan NIK: "; cin >> auth_nik;
            cout << "Masukkan Tanggal Lahir (dd-mm-yyyy): "; cin >> auth_tgl;
            if (cek_nik(auth_nik) == -1)
            {
                cout << "NIK tidak ditemukan" << endl;
            }else{
                if(lupa_pass(auth_nik, auth_tgl)){
                    buat_pass(cek_nik(auth_nik));
                }else{
                    cout << "NIK dan tanggal lahir tidak sesuai" << endl;
                }
            }
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

void buat_pass(int id){
    string pass_baru;
    int pjg_char;
    bool kondisi_pass = 0;
    do{
        cout << "Buatlah password dengan ketentuan:\n1. Minimal panjang 8 Karakter\n2. Mengandung minimal 1 Uppercase\n3. Mengandung minimal 1 Lowercase\n4. Mengandung minimal 1 Angka\n5. Mengandung minimal 1 Simbol" << endl << endl;
        cout << "Password Baru: ";
        cin.ignore();
        getline(cin, pass_baru);
        pjg_char = pass_baru.length();
        kondisi_pass = daftar_pass(pass_baru, pjg_char);
        if(kondisi_pass){
            user[id].pass = pass_baru;
            cout << endl << "Registrasi Berhasil." << endl;
        }else{
            cout << endl << "Password tidak sesuai ketentuan." << endl;
            cout << "Silahkan Buat Ulang Password." << endl;
            system("pause");
            system("cls");
        }
    }while(!kondisi_pass);
}

bool cek_nik_terdaftar(int nik_baru){
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
    return (angka == 1 && upper == 1 && lower == 1 && simbol == 1 && pjg_char >= 8) ? 1 : 0;
};

bool login(int nik, string pass){
    int id = -1;
    id = cek_nik(nik);
    return (pass == user[id].pass) ? 1 : 0;
};

bool lupa_pass(int nik, string tgl_lhr){
    int id = -1;
    id = cek_nik(nik);
    if (id == -1)
    {
        return 0;
    }else{
        return (tgl_lhr == user[id].tgl_lahir) ? 1 : 0;
    }
};

int cek_nik(int nik){
    int ans = -1;
    for (int i = 0; i <= id_terdaftar; i++)
    {
        if (nik == user[i].nik)
        {
            ans = i;
            break;
        }
    } 
    return ans;
}
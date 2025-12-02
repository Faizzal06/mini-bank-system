#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string username;
int balance;

bool isAvailable(string username)
{
    ifstream db("users.txt");
    string u, p, b;
    bool isFound = false;

    while (db >> u >> p >> b)
    {
        if (username == u)
        {
            isFound = true;
            break;
        }
    }
    db.close();
    return isFound;
}

void substractBalance(string user, int value)
{
    ifstream in("users.txt");
    ofstream out("temp.txt");

    string u, p;
    int b;

    while (in >> u >> p >> b)
    {
        if (u == user)
        {
            b -= value;
            balance -= value;
        }
        out << u << " " << p << " " << b << endl;
    }

    in.close();
    out.close();

    remove("users.txt");
    rename("temp.txt", "users.txt");
}

void addBalance(string user, int value)
{
    ifstream in("users.txt");
    ofstream out("temp.txt");

    string u, p;
    int b;

    while (in >> u >> p >> b)
    {
        if (u == user)
        {
            b += value;
            balance += value;
        }
        out << u << " " << p << " " << b << endl;
    }

    in.close();
    out.close();

    remove("users.txt");
    rename("temp.txt", "users.txt");
}

void transfer()
{
    string receiver;
    int jumlah;
    cout << "Masukan username penerima : ";
    cin >> receiver;
    if (isAvailable(receiver))
    {
        cout << "Masukan Jumlah : ";
        cin >> jumlah;
        if (jumlah <= balance)
        {
            substractBalance(username, jumlah);
            addBalance(receiver, jumlah);
            cout << "saldo anda sekarang : " << balance << endl;
            system("pause");
        }
        else
        {
            cout << "saldo anda kurang!, silahkan coba lagi\n";
            system("pause");
        }
    }
    else
    {
        cout << "Username tidak ditemukan!, silahkan coba lagi\n";
        system("pause");
    }
}

void withdraw()
{
    int value;
    cout << "----------------------------------\n";
    cout << "             Withdraw             \n";
    cout << "----------------------------------\n";
    cout << "Masukan jumlah uang yang ingin anda tarik : ";
    cin >> value;
    if (value <= balance)
    {
        substractBalance(username, value);
        cout << "----------------------------------\n";
        cout << "Saldo anda sekarang : " << balance << endl;
        system("pause");
    }
    else
    {
        cout << "Saldo anda tidak cukup, silahkan deposit terlebih dahulu!\n";
        system("pause");
    }
}
void deposit()
{
    int value;
    cout << "----------------------------------\n";
    cout << "              Deposit             \n";
    cout << "----------------------------------\n";
    cout << "Masukan jumlah uang yang ingin anda depositkan : ";
    cin >> value;
    addBalance(username, value);
    cout << "----------------------------------\n";
    cout << "Saldo anda sekarang : " << balance << endl;
    system("pause");
}

void userDetail()
{
    cout << "----------------------------------\n";
    cout << "Username :" << username << endl;
    cout << "Saldo :" << balance << endl;
    cout << "----------------------------------\n";
}

void menu()
{
    int pilihan;
    userDetail();
    cout << "0. Exit\n1. Deposit\n2. Withdraw\n3. Transfer\n";
    cout << "Pilih (1-3) : ";
    cin >> pilihan;
    switch (pilihan)
    {
    case 0:
        cout << "Exit...\n";
        break;
    case 1:
        deposit();
        break;
    case 2:
        withdraw();
        break;
    case 3:
        transfer();
        break;

    default:
        cout << "Pilihan tidak valid\n";
        break;
    }
    if (pilihan != 0)
    {
        menu();
    }
}

void login()
{
    string inUsername, inPassword, dbUsername, dbPassword;
    int dbBalance;
    bool isFound = false;
    cout << "----------------------------------\n";
    cout << "           Login / Masuk          \n";
    cout << "----------------------------------\n";
    cout << "Masukan username : ";
    cin >> inUsername;
    cout << "Masukan Password : ";
    cin >> inPassword;

    ifstream db("users.txt");
    while (db >> dbUsername >> dbPassword >> dbBalance)
    {
        if (dbUsername == inUsername && dbPassword == inPassword)
        {
            username = dbUsername;
            balance = dbBalance;
            isFound = true;
            cout << "----------Login Berhasil----------\n";
            system("pause");
            break;
        }
    }
    db.close();
    if (!isFound)
    {
        cout << "Username atau Password salah!, silahkan coba lagi\n";
        system("pause");
        login();
    }
    menu();
}

void Register()
{
    string inUsername, inPassword;
    cout << "----------------------------------\n";
    cout << "      Register / Pendaftaran      \n";
    cout << "----------------------------------\n";
    cout << "Masukan username : ";
    cin >> inUsername;
    cout << "Masukan Password : ";
    cin >> inPassword;
    balance = 0;

    ofstream db("users.txt", ios::app);
    if (!isAvailable(inUsername))
    {
        db << inUsername << " " << inPassword << " " << balance << endl;
        cout << "-------Registrasi Berhasil--------\n";
        db.close();
        login();
    }
    else
    {
        cout << "username sudah dipakai, silahkan ganti!\n";
        Register();
    }
}

void welcome()
{
    int pilihan;
    cout << "----------------------------------\n";
    cout << "  Selamat Datang di Bank YAGATAW  \n";
    cout << "----------------------------------\n";
    cout << "1. Login\n";
    cout << "2. Register\n";
    cout << "pilih (1/2) : ";
    cin >> pilihan;
    switch (pilihan)
    {
    case 1:
        login();
        break;
    case 2:
        Register();
        break;
    default:
        cout << "Pilihan tidak valid";
    }
}

int main()
{
    welcome();
    return 0;
}
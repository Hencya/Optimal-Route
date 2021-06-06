#include <iostream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

string arrNama[26];
char arrKode[26];

//untuk mencari kode
bool searchKode(char arrKode[],char kode){
    int i,len;
    i = 0;
    len = sizeof(arrKode)/sizeof(arrKode[0]);
    while (i < len){
        if (kode == arrKode[i]) {
            return true;
        }
        i++;
    }
    return false;
}

//Jumlah Baris dan Kolom dibatasi jumlah alfabet yang ada
const int Baris = 26;
const int Kolom = 26;
int Lintasan[Baris][Kolom];
bool Node[Baris];

//prosedur untuk mengisi lintasan
void IsiLintasan(int isi){
    for(int i = 0; i < Baris; i++) {
		for(int j = 0; j < Kolom; j++) {
			Lintasan[i][j] = isi;
		}
	}
}

/* -'A' karena itu merupakan array yang berindex 0 dan
tidak digunakan saat penghitungan jarak antar lintasan*/
void TambahLintasan(char L1, char L2,int Jarak){
    Lintasan[L1-'A'][L2-'A'] = Jarak;
    Lintasan[L2-'A'][L1-'A'] = Jarak;
    Node[L1-'A'] = true;
    Node[L2-'A'] = true;
}

//prosedur TSP
void TSP_BruteForce(int Lintasan[Baris][Kolom], int Mulai) {
	vector<int> V;
	vector<int> ans;
    int JarakMinimal = INT_MAX;

    /*Semua node selain node awal dimasukkan ke vector V
    karena node awal selalu berada di awal dan akhir Lintasan*/
    for(int i = 0;i < Baris;i++){
        if(Node[i] && i != Mulai){
            V.push_back(i);
        }
    }

	do {
		bool found = true;
        int JarakSekarang = 0;
        int temp = Mulai;
        for (int i = 0; i < V.size() && found; i++){
            if(Lintasan[temp][V[i]] != -1){
                JarakSekarang += Lintasan[temp][V[i]];
                temp = V[i];
            }else{
                found = false;
            }
        }
		if(Lintasan[temp][Mulai] != -1 && found){
		    JarakSekarang += Lintasan[temp][Mulai];
		    if(JarakMinimal > JarakSekarang){
                JarakMinimal = JarakSekarang;
                ans = V;
		    }
		}
	} while (next_permutation(V.begin(), V.end()));

    cout<<"Nama Tempat Lintasan Optimal : "<< arrNama[Mulai] <<" ";
    for(auto i : ans){
        cout<< arrNama[i] <<" ";
    }
    cout<< arrNama[Mulai] << endl;

    cout<<"Kode Tempat Lintasan Optimal : "<< char(Mulai+'A') <<" ";
    for(auto i : ans){
        cout<< char(i+'A')<<" ";
    }
    cout<< char(Mulai+'A') << endl;
	cout << "Jarak : " << JarakMinimal << " Satuan Jarak";
}

int main(){
    IsiLintasan(-1);
    cout << "Traveling Salesman Problem menggunakan metode Brute Force"<< endl;
    cout << "=========================================================="<< endl;
    cout << endl;

    cout << "Masukkan Jumlah Tempat pariwisata : ";
    int JumlahNode;
    cin >> JumlahNode;

    cout << "Masukkan Jumlah Rute dari Tempat pariwisata : ";
    int JumlahEdge;
    cin >> JumlahEdge;

    int jarak = 0;
    char N1, N2;
    string namaKota1,namaKota2;
    cout << endl;
    cout << "|------------------------------------------------------|" << endl;
    cout << "|                       CONTOH                         |" << endl;
    cout << "|------------------------------------------------------|" << endl;
    cout << "|Nama tempat 1 |   Nama tempat 2 | Jarak antara Tempat |" << endl;
    cout << "|--------------|-----------------|---------------------|" << endl;
    cout << "|Borobudur     |   Prambanan     |         10          |" << endl;
    cout << "|------------------------------------------------------|" << endl;
    cout << endl;
    cout << "Silahkan Masukkan Rute  " << endl;
    for(int i=0; i<= JumlahEdge-1; i++){
        cout << "Rute "<< i+1 << " : ";
        cin >> namaKota1 >> namaKota2  >> jarak;
        cout << "Kode Kota "<< i+1 << " : ";
        cin >> N1 >> N2;
        if (searchKode(arrKode,N1) == false)   {
            arrNama[N1-'A'] = namaKota1;
            arrKode[N1-'A'] = N1;
        }
        if (searchKode(arrKode,N2) == false){
            arrNama[N2-'A'] = namaKota2;
            arrKode[N2-'A'] = N2;
        }
        TambahLintasan(N1,N2,jarak);
    }
    char NodeAwal;
    string nama;
    cout << "Masukkan Nama Tempat Pariwisata Awal : ";
    cin >> nama;
    cout << "Masukkan Kode Tempat Pariwisata Awal : ";
    cin >> NodeAwal;
    cout << endl;
    if (searchKode(arrKode,NodeAwal) == false){
        cout << "NAMA TEMPAT DAN KODE YANG ANDA MASUKAN TIDAK ADA ";
    }else {
        TSP_BruteForce(Lintasan, NodeAwal-'A');
    }
    return 0;
}

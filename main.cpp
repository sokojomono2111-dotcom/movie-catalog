#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct Movie {
    string nazva;
    string zanr;
    int rik;
    int reiting;
};

vector<Movie> bazu_filmov;

void save() {
    ofstream out("movies.txt");
    for (int i = 0; i < bazu_filmov.size(); i++) {
        out << bazu_filmov[i].nazva << endl;
        out << bazu_filmov[i].zanr << endl;
        out << bazu_filmov[i].rik << endl;
        out << bazu_filmov[i].reiting << endl;
    }
    out.close();
}

void load() {
    ifstream in("movies.txt");
    if (!in.is_open()) return;
    Movie m;
    while (getline(in, m.nazva)) {
        getline(in, m.zanr);
        in >> m.rik;
        in >> m.reiting;
        in.ignore();
        bazu_filmov.push_back(m);
    }
    in.close();
}

int main() {
    system("chcp 65001 > nul");
    load();

    int vybir = 99;
    while (vybir != 0) {
        cout << "\n=== KATALOG FILMOV ===" << endl;
        cout << "1. Dodaty film" << endl;
        cout << "2. Pokazaty vsi" << endl;
        cout << "3. Poshuk za nazvoyu" << endl;
        cout << "0. Vyhid" << endl;
        cout << "Vash vybir: ";
        
        if (!(cin >> vybir)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Pomyłka! Vvedit tsilu chyslo.\n";
            continue;
        }

        if (vybir == 1) {
            Movie m;
            cout << "Vvedit nazvu: ";
            cin.ignore();
            getline(cin, m.nazva);
            cout << "Vvedit zanr: ";
            getline(cin, m.zanr);
            cout << "Vvedit rik: ";
            cin >> m.rik;
            cout << "Vvedit reiting: ";
            cin >> m.reiting;
            
            cin.ignore(10000, '\n');

            bazu_filmov.push_back(m);
            save();
            cout << "Uspishno dodano!\n";
        }
        else if (vybir == 2) {
            if (bazu_filmov.size() == 0) {
                cout << "\nSpysok filmiv pustyj! Dodat spochatku film.\n";
            } else {
                cout << "\n--- SPYSOK FILMOV ---" << endl;
                for (int i = 0; i < bazu_filmov.size(); i++) {
                    cout << i + 1 << ". " << bazu_filmov[i].nazva << " | " << bazu_filmov[i].zanr << " | " << bazu_filmov[i].rik << " rik | " << bazu_filmov[i].reiting << "/10" << endl;
                }
            }
        }
        else if (vybir == 3) {
            string shukamy;
            cout << "Vvedit nazvu dlya poshuku: ";
            cin.ignore();
            getline(cin, shukamy);

            bool znajshovsya = false;
            for (int i = 0; i < bazu_filmov.size(); i++) {
                if (bazu_filmov[i].nazva == shukamy) {
                    cout << "Znajdeno! Film: " << bazu_filmov[i].nazva << " (" << bazu_filmov[i].rik << "), zanr: " << bazu_filmov[i].zanr << endl;
                    znajshovsya = true;
                }
            }
            if (znajshovsya == false) {
                cout << "Nichoho ne znajshlo...\n";
            }
        }
    }

    return 0;
}
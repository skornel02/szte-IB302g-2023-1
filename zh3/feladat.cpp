#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

// Amelyik reszt szeretned tesztelni, az ne legyen komment
#ifndef TEST_BIRO
#define FELADAT_1
#define FELADAT_2
#define FELADAT_3
#define FELADAT_4
#define FELADAT_5
#define FELADAT_6
#endif

// region ------------------------------- 1. FELADAT -------------------------------
#ifdef FELADAT_1
#ifndef BIRO_TESTER_FELJEGYZES
struct Uticel {
    string nev; // uticel neve
    float tavolsag; // celpont tavolsaga m-ben

    bool operator < (const Uticel& m) const {
        return this->nev < m.nev;
    }
};
#endif

int eselyes_celpontok(set<Uticel>& feljegyzesek) {
    return std::count_if(feljegyzesek.begin(), feljegyzesek.end(), [](const Uticel& uticel) {
       return uticel.tavolsag < 1000;
    });
}
#endif
// endregion

// region ------------------------------- 2. FELADAT -------------------------------
#ifdef FELADAT_2
string celpont_valasztas(const vector<string>& szavazatok) {
    map<string, unsigned> szavazatokossz;

    for (auto& szavazat : szavazatok) {
        if (szavazatokossz.find(szavazat) == szavazatokossz.end()) {
            szavazatokossz[szavazat] = 0;
        }
        szavazatokossz[szavazat]++;
    }

    return std::max_element(szavazatokossz.begin(), szavazatokossz.end(), [](const pair<string, unsigned>& a, const pair<string, unsigned>& b) {
        return a.second < b.second;
    })->first;
}
#endif
// endregion

// region ------------------------------- 3. FELADAT -------------------------------
#ifdef FELADAT_3
#ifndef BIRO_TESTER_KATONA
struct Turazo {
    string nev;
    int fonok_intelligencia;
};
#endif

void visszamennek_dolgozni(vector<Turazo>& turazok, int atlagos_intelligencia) {
    turazok.erase(
            std::remove_if(turazok.begin(), turazok.end(), [&atlagos_intelligencia](const Turazo& turazo) {
                return turazo.fonok_intelligencia < atlagos_intelligencia;
            }),
            turazok.end()
    );
}
#endif
// endregion

// region ------------------------------- 4. FELADAT -------------------------------
#ifdef FELADAT_4
bool elhagyatott_helyek(const map<string, unsigned>& allatmennyisegek) {
    return std::find_if(allatmennyisegek.begin(), allatmennyisegek.end(), [](const pair<string, unsigned >& entry) {
        return entry.second == 0;
    }) != allatmennyisegek.end();
}
#endif
// endregion

// region ------------------------------- 5. FELADAT -------------------------------
#ifdef FELADAT_5
vector<string> egyedi_helyek(const vector<string>& meglatogatott_helyek) {
    vector<string> egyedi;

    for(auto& hely : meglatogatott_helyek) {
        if (std::find(egyedi.begin(), egyedi.end(), hely) == egyedi.end()) {
            egyedi.push_back(hely);
        }
    }

    return egyedi;
}
#endif
// endregion

// region ------------------------------- 6. FELADAT -------------------------------
#ifdef FELADAT_6
struct Foto {
    string nev; // ember neve
    string hely; // hely neve, amit lefotoz
};

vector<string> fotozas(Foto* fotok, unsigned darab) {
    map<string, unsigned> fotosok;

    for (int i = 0; i < darab; ++i) {
        auto foto = fotok[i];
        if (fotosok.find(foto.nev) == fotosok.end()) {
            fotosok[foto.nev] = 0;
        }
        fotosok[foto.nev]++;
    }

    vector<string> fotosokNeve;
    for (auto& entry : fotosok) {
        fotosokNeve.push_back(entry.first);
    }

    std::sort(fotosokNeve.begin(), fotosokNeve.end(), [&fotosok](const string& a, const string& b) {
        return fotosok[a] > fotosok[b];
    });

    return fotosokNeve;
}
#endif
// endregion

// region --------------------------- TESZTELO METODUSOK ---------------------------
#ifndef TEST_BIRO
#ifdef FELADAT_1
void test_feladat1() {
    cout << "1. feladat: eselyes_celpontok" << endl;

    // [INFO] A teszteset itt modosithato!
    set<Uticel> halmaz = {
            {"Ezust pagoda", 4121},
            {"Varazsto", 532},
            {"Idokapu", 1001}
    };

    cout << "elvart: " << "1" << endl;
    cout << "kapott: " << eselyes_celpontok(halmaz) << endl;
    cout << endl;
}
#endif

#ifdef FELADAT_2
void test_feladat2() {
    cout << "2. feladat: celpont_valasztas" << endl;

    // [INFO] A teszteset itt modosithato!
    vector<string> s2 = {
            "Ezust Pagoda", "Varazsto", "Idokapu", "Ezust Pagoda", "Varazsto", "Ezust Pagoda"
    };

    cout << "elvart: " << "Ezust Pagoda" << endl;
    cout << "kapott: " << celpont_valasztas(s2) << endl;

    vector<string> s3 = {
            "Ezust pagoda", "Orokos tavak", "Orokos tavak", "Idokapu", "Tundervolgy",
            "Ezust pagoda", "Ezust pagoda", "Kristalybarlangok"
    };
    cout << "elvart: " << "Ezust Pagoda" << endl;
    cout << "kapott: " << celpont_valasztas(s3) << endl;

    cout << endl;
}
#endif

#ifdef FELADAT_3
void test_feladat3() {
    cout << "3. feladat: visszamennek_dolgozni" << endl;

    // [INFO] A teszteset itt modosithato!
    Turazo k1 = {"Denes", 92};
    Turazo k2 = {"Anna", 111};
    Turazo k3 = {"Peter", 122};

    vector<Turazo> katonak {k1, k2, k3};
    int atlag_iq = 99;

    visszamennek_dolgozni(katonak, atlag_iq);

    cout << "elvart: " << "Anna Peter" << endl;
    cout << "kapott: ";
    for (const Turazo& katona: katonak) {
        cout << katona.nev << " ";
    }

    cout << endl << endl;
}
#endif

#ifdef FELADAT_4
void test_feladat4() {
    cout << "4. feladat: elhagyatott_helyek" << endl;

    // [INFO] A teszteset itt modosithato!
    map<string, unsigned> kontinensek = {
            {"Ezust pagoda", 4},
            {"Lombkorona setany", 6},
            {"Gyuruerdo", 0},
    };

    cout << "elvart: " << "1" << endl;
    cout << "kapott: " << elhagyatott_helyek(kontinensek) << endl;

    cout << endl;
}
#endif

#ifdef FELADAT_5
void test_feladat5() {
    cout << "5. feladat: egyedi_helyek" << endl;

    // [INFO] A teszteset itt modosithato!
    const vector<string> varosok = {
            "EzustPagoda", "EzustPagoda", "Leleksetany", "EzustPagoda", "Feny-erdo", "Aranyret", "Pipacsmezo"
    };

    vector<string> kapott = egyedi_helyek(varosok);
    sort(kapott.begin(), kapott.end());

    cout << "elvart: " << "Aranyret EzustPagoda Feny-erdo Leleksetany Pipacsmezo" << endl;
    cout << "kapott: ";
    for (const string& hely: kapott) {
        cout << hely << " ";
    }

    cout << endl << endl;
}
#endif

#ifdef FELADAT_6
void test_feladat6() {
    cout << "6. feladat: fotozas" << endl;

    // [INFO] A teszteset itt modosithato!
    Foto zsakmazsolasok[] = {
            {"Eszter", "Legi dzsungel"},
            {"Attila", "ezust pagoda"},
            {"Bence", "Legi dzsungel"},
            {"Eszter", "harsona-harangok"},
            {"Attila", "kristalyto"},
            {"Attila", "kristalybarlangok"}
    };

    unsigned meret = 6;

    vector<string> kapott = fotozas(zsakmazsolasok, meret);

    cout << "elvart: " << "Attila Eszter Bence" << endl;
    cout << "kapott: ";
    for (const string& nev: kapott) {
        cout << nev << " ";
    }

    cout << endl;
}
#endif
#endif
// endregion

// region ---------------------------------- MAIN ----------------------------------
#ifndef TEST_BIRO
int main() {
#ifdef FELADAT_1
    test_feladat1();
#endif

#ifdef FELADAT_2
    test_feladat2();
#endif

#ifdef FELADAT_3
    test_feladat3();
#endif

#ifdef FELADAT_4
    test_feladat4();
#endif

#ifdef FELADAT_5
    test_feladat5();
#endif

#ifdef FELADAT_6
    test_feladat6();
#endif

    return 0;
}
#endif
// endregion

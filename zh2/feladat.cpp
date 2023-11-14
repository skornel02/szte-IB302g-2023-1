#include <iostream>
#include <string>
#include <exception>

using namespace std;

class Pok {
    string fajta;
    unsigned meret;
    float veszelyesseg;

public:
    Pok(): fajta(""), meret(0), veszelyesseg(0) {}

    Pok(const string& fajta, unsigned int meret, float veszelyesseg):
            fajta(fajta), meret(meret), veszelyesseg(veszelyesseg > 1 ? 1 : (veszelyesseg < 0 ? 0 : veszelyesseg)) {}

    float get_veszelyesseg() const {
        return veszelyesseg;
    }
};

class KincsMarElrabolva : public exception {
    string uzenet;

public:
    KincsMarElrabolva(const string &uzenet) : uzenet("A " + uzenet + "-bol a kincset mar elraboltak.") {}

    const char *what() const noexcept override {
        return uzenet.c_str();
    }
};

class OsiTemplom {
    string nev;
    string kincs;
    Pok* pokok;
protected:
    unsigned max_pokok;
    unsigned curr_pokok;

public:
    OsiTemplom(const string &nev, const string &kincs, unsigned int maxPokok) : nev(nev), kincs(kincs),
                                                                                max_pokok(maxPokok), curr_pokok(0) {

        pokok = new Pok[max_pokok];
    }

    OsiTemplom(const OsiTemplom& m) {
        nev = m.nev;
        kincs = m.kincs;
        max_pokok = m.max_pokok;
        curr_pokok = m.curr_pokok;

        pokok = new Pok[max_pokok];

        for (int i = 0; i < curr_pokok; ++i) {
            pokok[i] = m.pokok[i];
        }
    }

    virtual ~OsiTemplom() {
        delete[] pokok;
    }

    const string &templom_neve() const {
        return nev;
    }

    const string &templom_kincse() const {
        return kincs;
    }

    virtual OsiTemplom& operator+=(const Pok& pok) {
        if (curr_pokok >= max_pokok) {
            Pok* uj_pokok = new Pok[max_pokok * 2];

            for (int i = 0; i < max_pokok; ++i) {
                uj_pokok[i] = pokok[i];
            }

            delete[] pokok;
            pokok = uj_pokok;
            max_pokok = max_pokok * 2;
        }

        pokok[curr_pokok++] = pok;

        return *this;
    }

    OsiTemplom& operator=(const OsiTemplom& m) {
        if (this == &m) {
            return *this;
        }

        nev = m.nev;
        kincs = m.kincs;
        max_pokok = m.max_pokok;
        curr_pokok = m.curr_pokok;

        delete[] pokok;
        pokok = new Pok[max_pokok];

        for (int i = 0; i < curr_pokok; ++i) {
            pokok[i] = m.pokok[i];
        }

        return *this;
    }

    virtual OsiTemplom& operator<<(const string& uj_kincs) {
        if (kincs.empty()) {
            kincs = uj_kincs;
        } else {
            kincs += ", " + uj_kincs;
        }

        return *this;
    }

    OsiTemplom& operator>>(string* tolvaj) {
        if (kincs.empty()) {
            throw KincsMarElrabolva(nev);
        }

        *tolvaj = kincs;
        kincs = "";

        return *this;
    }
};

class LezartTemplom : public OsiTemplom {
    string lezaras;

public:
    LezartTemplom(const string &nev, unsigned int maxPokok, const string &lezaras) : OsiTemplom(
            nev, "", maxPokok), lezaras(lezaras) {}

    const string &lezarva() const {
        return lezaras;
    }

    OsiTemplom &operator<<(const string &uj_kincs) override {
        return *this;
    }

    OsiTemplom &operator+=(const Pok &pok) override {
        if (curr_pokok >= max_pokok) {
            return *this;
        }

        return OsiTemplom::operator+=(pok);
    }
};

Pok** vedosereg_kivalogatas(const float* bunbanda_erosseg, Pok** pokok)
{
    float osszErosseg = 0;
    unsigned bandaTagokSzama = 0;
    for (; bunbanda_erosseg[bandaTagokSzama] != 0; ++bandaTagokSzama) {
        osszErosseg += bunbanda_erosseg[bandaTagokSzama];
    }
    float atlagErosseg = bandaTagokSzama == 0 ? 0 : (osszErosseg / bandaTagokSzama);

    Pok** vedok = new Pok*[100];
    unsigned vedopokok = 0;

    for (int i = 0; pokok[i] != nullptr; i++) {
        if (pokok[i]->get_veszelyesseg() > atlagErosseg) {
            vedok[vedopokok++] = pokok[i];
        }
    }
    vedok[vedopokok] = nullptr;

    if (vedopokok < bandaTagokSzama) {
        return nullptr;
    }

    return vedok;
}

int main()
{
    Pok p1("Fekete ozvegy" , 34 , 0.25 ) ; // a v e s z e l y e s s e g e 0 . 2 5 l e s z
    Pok p2( "Tarantula" , 41 , 1.35 ) ; // a v e s z e l y e s s e g 1= n e l nagyobb , e z e r t 1 l e s z
    Pok p3( "Buvarpok" , 24 , -1.21 ) ;

    KincsMarElrabolva elrabolva("Sajt");
    cout << elrabolva.what();

    OsiTemplom templom("Templom", "" , 3);
    cout << templom.templom_kincse() << endl;
    templom << "aranytaller";
    cout << templom.templom_kincse() << endl;
    templom << "ezustlada";
    cout << templom.templom_kincse() << endl;
    templom << "medal" << "nyaklanc";
    cout << templom.templom_kincse() << endl;

    templom += p1;
    templom += p2;
    templom += p3;
    templom += p1;
}

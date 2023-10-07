#include <iostream>


class Kolonia;
bool veganE(const Kolonia& kolonia);

class Telepes {
    /**
     * A telepes neve
     */
    std::string nev;
    /**
     * Születés bolgyó
     */
    std::string szul_bolygo;
    /**
     * Jelenlegi bolgyó
     */
    mutable std::string bolygo;
    /**
     * Workefficency
     */
    unsigned ero;

    /**
     * abcedf
     */
    bool vegan;

public:
    Telepes(const std::string &nev, const std::string &szulBolygo, const std::string &bolygo, unsigned int ero, bool vegan)
        : nev(nev), szul_bolygo(szulBolygo), bolygo(bolygo), ero(ero), vegan(vegan) {

    }

    Telepes() : Telepes("", "", "", 1, false) {

    }

    Telepes(const std::string &nev, const std::string &bolygo, unsigned int ero = 1, bool vegan = false)
        : Telepes(nev, bolygo, bolygo, ero, vegan) {

    }

    const std::string &get_nev() const {
        return nev;
    }
    void set_nev(const std::string &nev) {
        Telepes::nev = nev;
    }
    const std::string &get_szul_bolygo() const {
        return szul_bolygo;
    }
    void set_szul_bolygo(const std::string &szulBolygo) {
        szul_bolygo = szulBolygo;
    }
    const std::string &get_bolygo() const {
        return bolygo;
    }
    void set_bolygo(const std::string &bolygo) const {
        Telepes::bolygo = bolygo;
    }
    unsigned int get_ero() const {
        return ero;
    }
    void set_ero(unsigned int ero) {
        Telepes::ero = ero;
    }

    bool is_vegan() const {
        return vegan;
    }

    void set_vegan(bool vegan) {
        Telepes::vegan = vegan;
    }

    bool kivandorlo() const {
        if (szul_bolygo.length() != bolygo.length())
            return true;

        for (int i = 0; i < szul_bolygo.length(); ++i) {
            if (tolower(szul_bolygo[i]) != tolower(bolygo[i]))
                return true;
        }

        return false;
    }

    void dolgozik(std::string& munka) const {
        for (int i = 0; i < ero; ++i) {
            if (munka.length() == 0)
                break;

            auto firstMelo = munka.find_first_of(';');
            if (firstMelo == std::string::npos) {
                munka = "";
                break;
            }

            munka = munka.substr(firstMelo + 1);
        }
    }

    bool operator==(const Telepes& telepes) const {
        Telepes t("", bolygo, telepes.bolygo, 0, false);
        Telepes t2("", szul_bolygo, telepes.szul_bolygo, 0, false);

        return nev == telepes.nev
               && ero == telepes.ero
               && !t.kivandorlo()
               && !t2.kivandorlo()
               && vegan == telepes.vegan;
    }
};

class Kolonia {
    std::string nev;
    std::string bolygo;
    unsigned letszam;
    Telepes lakok[25];
public:
    Kolonia(const std::string &nev, const std::string &bolygo) : nev(nev), bolygo(bolygo), letszam(0) {}

    Kolonia(): Kolonia("", "") {}

public:
    void set_nev(const std::string &nev) {
        Kolonia::nev = nev;
    }

    const std::string &get_nev() const {
        return nev;
    }

    const std::string &get_bolygo() const {
        return bolygo;
    }

    void set_bolygo(const std::string &bolygo) {
        Kolonia::bolygo = bolygo;
    }

    unsigned int get_letszam() const {
        return letszam;
    }

    const Telepes *get_lakok() const {
        return lakok;
    }

    void operator+=(const Telepes& telepes) {
        if (letszam >= 25) {
            std::cerr << "A kolonia megtelt" << std::endl;
            return;
        }

        if (veganE(*this) && !telepes.is_vegan()) {
            std::cerr << "A kolonia vegan" << std::endl;
            return;
        }

        telepes.set_bolygo(bolygo);
        lakok[letszam++] = telepes;
    }

    void operator+=(const Kolonia& kolonia) {
        // lustasag
        Telepes t("", bolygo, kolonia.bolygo, 0, false);
        if (t.kivandorlo()) {
            std::cerr << "Hiba az egyesitesben: bolygo" << std::endl;
            return;
        }
        if (letszam + kolonia.letszam > 25) {
            std::cerr << "Hiba az egyesitesben: meret" << std::endl;
            return;
        }

        for (int i = 0; i < kolonia.letszam ; i++) {
            lakok[letszam++] = kolonia.get_lakok()[i];
        }
    }

    Kolonia operator-(const Telepes& telepes) const {
        int matchIndex = -1;

        for (int i = 0; i < letszam; ++i) {
            if (lakok[i] == telepes) {
                matchIndex = i;
                break;
            }
        }
        if (matchIndex == -1) {
            return *this;
        }

        Kolonia uj(nev, bolygo);

        for (int i = 0; i < letszam; ++i) {
            if (i != matchIndex) {
                uj += lakok[i];
            }
        }

        return uj;
    }
};

bool veganE(const Kolonia& kolonia) {
    int vegan = 0;
    for (int i = 0; i < kolonia.get_letszam() ; i++) {
        if (kolonia.get_lakok()[i].is_vegan()) {
            vegan++;
        }
    }
    return vegan > kolonia.get_letszam() / 2;
}

int main() {
    Kolonia k;
    Telepes t;

    k += t;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
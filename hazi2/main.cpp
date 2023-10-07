#include <iostream>

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
    std::string bolygo;
    /**
     * Workefficency
     */
    unsigned ero;

public:
    Telepes(const std::string &nev, const std::string &szulBolygo, const std::string &bolygo, unsigned int ero)
        : nev(nev), szul_bolygo(szulBolygo), bolygo(bolygo), ero(ero) {

    }

    Telepes() : Telepes("", "", "", 1) {

    }

    Telepes(const std::string &nev, const std::string &bolygo, unsigned int ero = 1)
        : Telepes(nev, bolygo, bolygo, ero) {

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
    void set_bolygo(const std::string &bolygo) {
        Telepes::bolygo = bolygo;
    }
    unsigned int get_ero() const {
        return ero;
    }
    void set_ero(unsigned int ero) {
        Telepes::ero = ero;
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
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

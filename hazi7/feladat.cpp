#include <iostream>

typedef struct Etel {
    std::string nev;
    int hutes;

    Etel(const std::string &nev = "", int hutes = 0) : nev(nev), hutes(hutes) {}

    std::string print() const {
        return "nev:" + nev + ",hofok:" + std::to_string(hutes);
    }
} Etel;

class Hiba : public std::exception {
    std::string msg;

public:
    Hiba() : msg("Hiba tortent") {}

    const char *what() const noexcept override {
        return msg.c_str();
    }
};

class Megromlik : public Hiba {
    std::string msg;

public:
    Megromlik(const Etel& etel) {
        msg = "A " + etel.nev + " tarolasahoz legalabb " + std::to_string(etel.hutes) + " fok kell";
    }

    const char *what() const noexcept override {
        return msg.c_str();
    }
};

class Megtelt : public Hiba {
    std::string msg;

public:
    Megtelt(const std::string& etel) {
        msg = "Nem sikerult letarolni a " + etel + "-t";
    }

    const char *what() const noexcept override {
        return msg.c_str();
    }
};

class Hutoegyseg {
    int hofok;
    Etel tartalom[10];
    unsigned db;

public:
    Hutoegyseg(std::string hofok_str) : db(0) {
        try {
            hofok = std::stoi(hofok_str);
        } catch (...) {
            hofok = -1;
        }
    }

    int get_hofok() const {
        return hofok;
    }
    const Etel *get_tartalom() const {
        return tartalom;
    }

    Hutoegyseg& operator += (const Etel& etel) {
        if (etel.hutes < hofok) {
            throw Megromlik(etel);
        }
        if (db == 10) {
            throw Megtelt(etel.nev);
        }

        tartalom[db++] = etel;

        return *this;
    }

    void print() const {
        if (db == 0) {
            throw Hiba();
        }

        for (int i = 0; i < db; ++i) {
            std::cout << tartalom[i].print() << std::endl;
        }
    }
};

bool feltolt(Hutoegyseg& h, Etel etelek[], unsigned etelszam) {
    try {
        for (int i = 0; i < etelszam; ++i) {
            h += etelek[i];
        }
        return true;
    } catch (Hiba& hiba) {
        return false;
    }
}

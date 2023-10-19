#include <iostream>

class Etel {
    std::string neve;
    std::string leiras;
    int ara;

public:
    Etel(): neve("amint kesz megtudod"), leiras("ami sikerul"), ara(0) {}

    Etel(const std::string &neve, const std::string &leiras, int ara) : neve(neve), leiras(leiras), ara(ara) {}

    virtual const std::string get_nev() const {
        return neve;
    }

    const std::string &get_leiras() const {
        return leiras;
    }

    virtual operator unsigned() const {
        return ara;
    }
};

class Menu: public Etel {
    Etel etelek[3];

public:
    Menu(): Etel() {}

    Menu(const std::string &neve, const std::string &leiras)
        : Etel(neve, leiras, 0) {}

    Menu(const std::string &neve, const std::string &leiras, const Etel& etel1, const Etel& etel2, const Etel& etel3)
        : Etel(neve, leiras, 0) {
        etelek[0] = etel1;
        etelek[1] = etel2;
        etelek[2] = etel3;
    }

    const std::string get_nev() const override {
        return "Menu: " + Etel::get_nev();
    }

    operator unsigned() const override {
        return (unsigned) ((etelek[0] + etelek[1] + etelek[2]) * 0.9);
    }

    const Etel& operator[](unsigned i) const {
        if (i >= 3) {
            throw std::exception();
        }
        return etelek[i];
    }
};

class Vendeglo {
    Etel etelek[7];

public:
    Vendeglo() {}

    Vendeglo( const Etel etelek[7]) {
        for (int i = 0 ; i < 7 ; i++) {
            this->etelek[i] = etelek[i];
        }
    }

    virtual Etel& operator[](size_t i) {
        if (i >= 7) {
            throw std::exception();
        }
        return etelek[i];
    }
};

class Gyorsetterem: public Vendeglo {
    Menu menuk[3];

public:
    Gyorsetterem(): Vendeglo() {}

    Gyorsetterem(const Menu menuk[3]): Vendeglo() {
        for (int i = 0 ; i < 3 ; i++) {
            this->menuk[i] = menuk[i];
        }
    }

    Gyorsetterem(const Etel etelek[7]) : Vendeglo(etelek) {}

    Gyorsetterem(const Etel etelek[7], const Menu menuk[3]) : Vendeglo(etelek) {
        for (int i = 0 ; i < 3 ; i++) {
            this->menuk[i] = menuk[i];
        }
    }

    Menu& operator[](size_t i) override {
        if (i >= 3) {
            throw std::exception();
        }
        return menuk[i];
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

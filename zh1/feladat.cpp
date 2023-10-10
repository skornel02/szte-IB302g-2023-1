#include <iostream>

class Vulkaforrazo {
private:
    std::string nev;
    std::string kepesseg;

public:
    Vulkaforrazo(const std::string &nev, const std::string &kepesseg) : nev(nev), kepesseg(kepesseg) {}

    Vulkaforrazo(): Vulkaforrazo("Magmamarok", "teleportalas") {}

    const std::string &get_nev() const {
        return nev;
    }

    void set_nev(const std::string &nev) {
        Vulkaforrazo::nev = nev;
    }

    const std::string &get_kepesseg() const {
        return kepesseg;
    }

    void set_kepesseg(const std::string &kepesseg) {
        Vulkaforrazo::kepesseg = kepesseg;
    }

    operator std::string() const {
        return nev + " egy vulkaforrazo, akinek specialis kepessege: " + kepesseg;
    }

    Vulkaforrazo& operator!() {
        kepesseg = "";
        return *this;
    }
};

class Vulkan {
protected:
    int meret;
    Vulkaforrazo vulkaforrazok[4];
    unsigned vulkaforrazo_szam;

public:
    explicit Vulkan(int meret) : meret(meret < 5 ? 5 : meret), vulkaforrazo_szam(0) {}

    int get_meret() const {
        return meret;
    }

    const Vulkaforrazo *get_vulkaforrazok() const {
        return vulkaforrazok;
    }

    unsigned int get_vulkaforrazo_szam() const {
        return vulkaforrazo_szam;
    }

    Vulkan& operator++() {
        meret++;
        return *this;
    }

    Vulkan& operator+=(const Vulkaforrazo& vulkaforrazo) {
        if (vulkaforrazo_szam >= 4) {
            return *this;
        }

        for (int i = 0; i < vulkaforrazo_szam; ++i) {
            if (vulkaforrazok[i].get_nev() == vulkaforrazo.get_nev()) {
                return *this;
            }
        }

        vulkaforrazok[vulkaforrazo_szam++] = vulkaforrazo;
        return *this;
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
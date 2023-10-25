#include <iostream>
#include <utility>

class Kutya {
    std::string nev;
    unsigned int kor;

public:
    // A Clion már MSc szinten fejleszt (helyettem)!
    Kutya(std::string nev, unsigned int kor) : nev(std::move(nev)), kor(kor) {
        std::cout << "Kutya letrehozva" << std::endl;
    }

    const std::string &get_nev() const {
        return nev;
    }
    unsigned int get_kor() const {
        return kor;
    }

    virtual std::string pedigre() const {
        return "nev:" + nev + ", kor:" + std::to_string(kor) + " ev";
    }

    virtual std::string* terel(const std::string tomb[], unsigned &length) const {
        if (tomb == nullptr || length == 0) {
            length = 0;
            return nullptr;
        }

        std::string* result = new std::string[length];
        for (unsigned int i = 0; i < length; ++i) {
            result[i] = tomb[i];
        }
        return result;
    }
};

class BorderCollie final : public Kutya {
    unsigned telero;

public:
    BorderCollie(const std::string &nev, unsigned int kor, unsigned int telero) : Kutya(nev, kor), telero(telero) {}

    unsigned int get_terelo_kapacitas() const {
        return telero;
    }

    std::string pedigre() const override {
        return Kutya::pedigre() + ", faj:border collie, terelo kapacitas:" + std::to_string(telero) + " db birka";
    }

    std::string *terel(const std::string *tomb, unsigned int &length) const override {
        auto terelt = Kutya::terel(tomb, length);
        if (terelt == nullptr) {
            return nullptr;
        }

        unsigned toSephard = std::min(length, telero);
        for (int i = 0; i < toSephard; ++i) {
            if (!terelt[i].empty())
            {
                continue;
            }

            for (int j = i; j < length; ++j) {
                if (terelt[j].empty())
                {
                    continue;
                }

                terelt[i] = terelt[j];
                terelt[j] = "";
                break;
            }
        }

        unsigned lastNonEmptyIndex = 0;
        for (int i = 0; i < length; ++i) {
            if (!terelt[i].empty()) {
                lastNonEmptyIndex = i;
            }
        }
        length = lastNonEmptyIndex + 1;

        return terelt;
    }
};

void print(const Kutya &kutya) {
    std::cout << kutya.pedigre() << std::endl;
}

int main(){
    BorderCollie bc("Jess", 12, 3);

    std::string nyaj[] = {"" , " F r i c i " , " J ul c s a " , "" , "Gyuri " , "Margit " } ;
    unsigned int length = 6;

    std::string* terelt = bc.terel(nyaj, length);
    for (int i = 0; i < length; ++i) {
        std::cout << terelt[i] << std::endl;
    }
    std::cout << length << std::endl;
    delete [] terelt;

    length = 6;
    const Kutya& bc_ref = bc;
    std::string* terelt2 = bc_ref.terel(nyaj, length);
    for (int i = 0; i < length; ++i) {
        std::cout << terelt2[i] << std::endl;
    }
    std::cout << length << std::endl;
    delete [] terelt2;
}
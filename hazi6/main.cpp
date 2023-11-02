#include <iostream>

class VilagitoDisz {
    unsigned fenyesseg;
    bool bekapcsolva;

public:
    VilagitoDisz(unsigned int fenyesseg = 0) : fenyesseg(fenyesseg) {}


    unsigned int get_fenyesseg() const {
        if (!bekapcsolva) {
            return 0;
        }
        return fenyesseg;
    }
    bool is_bekapcsolva() const {
        return bekapcsolva;
    }

    VilagitoDisz& operator --() {
        bekapcsolva = false;
        return *this;
    }

    VilagitoDisz& operator ++(){
        bekapcsolva = true;
        return *this;
    }
};

class KisKaracsonyfa {
    std::string fa_tipus;
    VilagitoDisz* csucs_disz;

public:
    KisKaracsonyfa(const std::string &faTipus = "luc") : fa_tipus(faTipus), csucs_disz(nullptr) {}

    KisKaracsonyfa(const KisKaracsonyfa& m) {
        fa_tipus = m.fa_tipus;

        if (csucs_disz != nullptr) {
            delete csucs_disz;
            csucs_disz = nullptr;
        }

        if (m.csucs_disz != nullptr) {
            csucs_disz = new VilagitoDisz(*m.csucs_disz);
        }
    }

    ~KisKaracsonyfa() {
        if (csucs_disz != nullptr)
        {
            delete csucs_disz;
        }
    }

    const std::string &get_fa_tipus() const {
        return fa_tipus;
    }
    VilagitoDisz *get_csucs_disz() const {
        return csucs_disz;
    }

    void disz_felhelyezese(VilagitoDisz& disz) {
        if (csucs_disz != nullptr) {
            delete csucs_disz;
        }

        csucs_disz = new VilagitoDisz(disz);
    }

    void bekapcsol() const {
        if (csucs_disz != nullptr) {
            ++(*csucs_disz);
        }
    }

    void kikapcsol() const {
        if (csucs_disz != nullptr) {
            --(*csucs_disz);
        }
    }

    unsigned get_fenyesseg() const {
        if (csucs_disz != nullptr) {
            return csucs_disz->get_fenyesseg();
        }

        return 0;
    }

    KisKaracsonyfa& operator=(const KisKaracsonyfa& m) {
        if (this == &m) {
            return *this;
        }

        fa_tipus = m.fa_tipus;

        if (csucs_disz != nullptr) {
            delete csucs_disz;
            csucs_disz = nullptr;
        }

        if (m.csucs_disz != nullptr) {
            csucs_disz = new VilagitoDisz(*m.csucs_disz);
        }

        return *this;
    }
};

class NagyKaracsonyfa {
    unsigned max_diszek;
    unsigned jelenlegi_diszek;
    VilagitoDisz* diszek;

public:
    NagyKaracsonyfa(unsigned max_diszek) : max_diszek(max_diszek), jelenlegi_diszek(0) {
        diszek = new VilagitoDisz[max_diszek];
    }

    NagyKaracsonyfa(const NagyKaracsonyfa& m) {
        max_diszek = m.max_diszek;
        jelenlegi_diszek = m.jelenlegi_diszek;

        diszek = new VilagitoDisz[max_diszek];
        for (int i = 0; i < jelenlegi_diszek; ++i) {
            diszek[i] = m.diszek[i];
        }
    }

    ~NagyKaracsonyfa() {
        delete[] diszek;
    }

    const VilagitoDisz *get_diszek() const {
        return diszek;
    }

    void disz_felhelyezese(const VilagitoDisz& disz) {
        if (jelenlegi_diszek < max_diszek) {
            diszek[jelenlegi_diszek++] = disz;
        }
    }

    void bekapcsol() const {
        for (int i = 0; i < jelenlegi_diszek; ++i) {
            ++(diszek[i]);
        }
    }

    void kikapcsol() const {
        for (int i = 0; i < jelenlegi_diszek; ++i) {
            --(diszek[i]);
        }
    }

    unsigned get_fenyesseg() const {
        unsigned fenyesseg = 0;
        for (int i = 0; i < jelenlegi_diszek; ++i) {
            fenyesseg += diszek[i].get_fenyesseg();
        }
        return fenyesseg;
    }

    NagyKaracsonyfa& operator=(const NagyKaracsonyfa& m) {
        if (this == &m) {
            return *this;
        }

        max_diszek = m.max_diszek;
        jelenlegi_diszek = m.jelenlegi_diszek;

        delete[] diszek;

        diszek = new VilagitoDisz[max_diszek];
        for (int i = 0; i < jelenlegi_diszek; ++i) {
            diszek[i] = m.diszek[i];
        }

        return *this;
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

#ifndef TEST_BIRO
  //#define OSZTALY_SET
//  #define MAX_LETSZAM
  //#define TOROL
  #define JEGY_SUM
#endif // TEST_BIRO

class Osztaly {
  char kod;
  unsigned evfolyam, letszam;
  

public:
  Osztaly(char kod, unsigned evfolyam, unsigned letszam) : 
    kod(kod), evfolyam(evfolyam),
    letszam(letszam) { }

  char get_kod() const {
    return kod;
  }
  
  unsigned get_evfolyam() const {
    return evfolyam;
  }

  unsigned get_letszam() const {
    return letszam;
  }
  
  friend ostream& operator<<(ostream& os, const Osztaly& t) {
    return os << t.evfolyam << "/" << t.kod << " (" << t.letszam << "fo)"; 
  }

    bool operator < (const Osztaly& other) const {
    if (evfolyam == other.evfolyam)
      return kod < other.kod;
    return evfolyam < other.evfolyam;
  }
  
};



#ifdef OSZTALY_SET

// Osztaly halmazba pakolása
set<Osztaly> osztaly_set(const vector<Osztaly>& osztalyok) {
  set<Osztaly> osztalySet;
  for (const auto& osztaly : osztalyok) {
    if (!osztalySet.insert(osztaly).second) {
      throw runtime_error("Duplicate class found");
    }
  }
  return osztalySet;
}

#ifndef TEST_BIRO
void test_osztaly_set() {
  cout << endl << " --- test_osztaly_set ---" << endl << endl;
  
  vector<Osztaly> osztalyok;
  osztalyok.push_back(Osztaly('c',10, 32));
  osztalyok.push_back(Osztaly('a',3, 28));
  osztalyok.push_back(Osztaly('a',4, 20));
  osztalyok.push_back(Osztaly('b',4, 22));

  set<Osztaly> iskola = osztaly_set(osztalyok);
  for(auto oszt : iskola){
    cout << oszt << endl;
  }
  osztalyok.push_back(Osztaly('a',4, 21));
  try{
    set<Osztaly> iskola2 = osztaly_set(osztalyok);
  }catch(const exception& ex){
    cout << "Kivetel elkapva" << endl;
  }

  //kimenet
  //3/a (28fo)
  //4/a (20fo)
  //4/b (22fo)
  //10/c (32fo)
  //Kivetel elkapva
}
#endif // TEST_BIRO
#endif // OSZTALY_SET



#ifdef MAX_LETSZAM

// Max létszámok
void max_letszam(const vector<Osztaly>& osztalyok, map<unsigned, unsigned>& maxLetszamMap) {
  for (const auto& osztaly : osztalyok) {
    if (maxLetszamMap.find(osztaly.get_evfolyam()) == maxLetszamMap.end()
          || maxLetszamMap[osztaly.get_evfolyam()] < osztaly.get_letszam()) {
      maxLetszamMap[osztaly.get_evfolyam()] = osztaly.get_letszam();
    }
  }

  for (int i = 1; i <= 12; ++i) {
      if (maxLetszamMap.find(i) == maxLetszamMap.end()) {
          maxLetszamMap[i] = 0;
      }
  }
}

#ifndef TEST_BIRO
void test_max_letszam() {
  cout << endl << " --- test_max_letszam ---" << endl << endl;
  
  vector<Osztaly> osztalyok;
  osztalyok.push_back(Osztaly('c',10, 32));
  osztalyok.push_back(Osztaly('a',3, 28));
  osztalyok.push_back(Osztaly('a',4, 20));
  osztalyok.push_back(Osztaly('b',4, 22));
  osztalyok.push_back(Osztaly('a',1, 18));
  osztalyok.push_back(Osztaly('d',1, 50));
  osztalyok.push_back(Osztaly('a',10, 33));

  map<unsigned, unsigned> letszamok;
  max_letszam(osztalyok, letszamok);

  for(const auto& p : letszamok){
    cout << p.first << ". : " << p.second << endl;
  }

  // kimenet
  //1. : 50
  //2. : 0
  //3. : 28
  //4. : 22
  //5. : 0
  //6. : 0
  //7. : 0
  //8. : 0
  //9. : 0
  //10. : 33
  //11. : 0
  //12. : 0
}
#endif // TEST_BIRO
#endif // MAX_LETSZAM


#ifdef TOROL

void torol(vector<Osztaly>& osztalyok) {
  osztalyok.erase(remove_if(osztalyok.begin(), osztalyok.end(), 
                            [](const Osztaly& o) { return o.get_letszam() < 10; }), 
                  osztalyok.end());
}

#ifndef TEST_BIRO
void test_torol() {
  cout << endl << " --- torol ---" << endl << endl;
  
  vector<Osztaly> osztalyok;
  osztalyok.push_back(Osztaly('c',10, 1));
  osztalyok.push_back(Osztaly('a',3, 12));
  osztalyok.push_back(Osztaly('a',4, 3));
  osztalyok.push_back(Osztaly('b',4, 123));
  osztalyok.push_back(Osztaly('a',1, 8));
  osztalyok.push_back(Osztaly('d',1, 9));
  osztalyok.push_back(Osztaly('a',10, 13));

  torol(osztalyok);

  for(const Osztaly& o : osztalyok){
    cout << o << endl;
  }

  // kimenet
  //3/a (12fo)
  //4/b (123fo)
  //10/a (13fo)

}
#endif // TEST_BIRO
#endif // TOROL


struct Diak{
  std::string nev;
  float atlag;
};

#ifdef JEGY_SUM

// Jegy szum
long jegy_sum(const vector<Diak>& diakok, float atlag) {
  return count_if(diakok.begin(), diakok.end(), [&atlag](const Diak& d) { return d.atlag > atlag; });
}


#ifndef TEST_BIRO
void test_jegy_sum() {
  cout << endl << " --- jegy_sum ---" << endl << endl;

  vector<Diak> diakok{{"Nagy Alfonz", 1.3},
                      {"Berkesi Lajos", 4.8},
                      {"Kiss Emerencina", 2.2},
                      {"Szabo Lujza", 3.3},
                      {"Eperjesi Gizella", 2.9},
                      {"Szanto-Toth Arabella", 4.1},
                      {"Kak Ilona", 4.9}};

  cout << "Negyesnel jobb tanulok szama:" << jegy_sum(diakok, 4.f) << endl;
  cout << "Kettesnel jobb tanulok szama:" << jegy_sum(diakok, 2.f) << endl;

  // kimenet
  //Negyesnel jobb tanulok szama:3
  //Kettesnel jobb tanulok szama:6

}
#endif // TEST_BIRO
#endif // JEGY_SUM

#ifndef TEST_BIRO
int main() {
#ifdef OSZTALY_SET
  test_osztaly_set();
#endif

#ifdef MAX_LETSZAM
  test_max_letszam();
#endif

#ifdef TOROL
  test_torol();
#endif

#ifdef JEGY_SUM
  test_jegy_sum();
#endif
}
#endif

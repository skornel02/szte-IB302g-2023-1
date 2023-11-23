#include <vector>
#include <algorithm>
#include <set>
#include <map>

#include <iostream>

// Amelyik reszt szeretned tesztelni, azt kommentezd ki!
#ifndef TEST_BIRO
#define VECTOR_INCREMENT
#define COUNT_IF_WRAPPER
#define SET_TASK
#define DEGREE_MAP
#define SORT_PARTIAL
#endif

#ifdef VECTOR_INCREMENT
void vector_increment(std::vector<int> &v, int limit) {
    int avg = 0;
    for (const int& i : v) {
        avg += i;
    }
    avg /= v.size();

    for (int& i : v) {
        if (i > limit) {
            i += avg;
        }
    }
}
#endif

#ifdef COUNT_IF_WRAPPER
unsigned count_if_wrapper( const std::vector<int> & v, int limit ) {
    return std::count_if( v.begin(), v.end(), [limit]( int i ) { return (i * 2) > limit; } );
}
#endif

#ifdef SET_TASK

// EZT EGESZITSD KI HA KELL!
class Label {
    std::string text;
public:
    Label( const std::string& str ) : text( str ) {}
    const std::string& get_text() const { return text; }

    bool operator<( const Label& rhs ) const {
        return text.length() < rhs.text.length();
    }
};

void descending_set_print( std::set<Label> & s ) {
    std::for_each(s.rbegin(), s.rend(), [](const Label& label) {
        std::cout << label.get_text() << std::endl;
    });
}
#endif

#ifdef SORT_PARTIAL
void sort_partial( std::vector<int> & v, int search ) {
    std::sort( ++std::find( v.begin(), v.end(), search ), v.end());
}
#endif

#ifdef DEGREE_MAP
std::map<unsigned, unsigned> calculate_degree( const std::map<unsigned, unsigned>& graph ) {
    std::map<unsigned, unsigned> result;
    for(auto &pair : graph) {
        if (result.find(pair.first) == result.end() && pair.first != 0) {
            result[pair.first] = 0;
        }
        if (pair.second != 0) {
            if (result.find(pair.second) == result.end()) {
                result[pair.second] = 0;
            }
            result[pair.second]++;
        }
    }
    return result;
}
#endif

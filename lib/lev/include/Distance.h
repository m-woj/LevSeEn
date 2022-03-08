#pragma once
#include <string>


#include "SizeT.h"


namespace Levenshtein {

template<typename SizeT>
class Distance {
public:
//  Konstruktor tworzący warunki do porównywania słów o podanych długościach
    Distance(const SizeT& patternLength, const SizeT &wordLength);

//  Ustala koszty edycji dla niestatycznych funkcji składowych
    void setEditCosts(SizeT deletionCost, SizeT insertionCost, SizeT swapCost);

//  Zwraca odległość Levenshteina, dla wzorca i słowa o ustalonej w konstruktorze długości
    SizeT getDistance(const std::string& pattern, const std::string& word);

//  Zwraca odległość edycji po samodzielnym sprawdzeniu długości wzorca i słowa
    static SizeT getEditDistance(const std::string& first, const std::string& second);

//  Zwraca odległość Levenshteina po samodzielnym sprawdzeniu długości wzorca i słowa
    static SizeT getDistance(const std::string& first, const std::string& second,
                             SizeT deletionCost, SizeT insertionCost, SizeT swapCost);

protected:
    static inline SizeT min(SizeT a, SizeT b, SizeT c);
    ~Distance();

    SizeT patternLength;
    SizeT wordLength;
    SizeT tableSize;

    SizeT* top;
    SizeT* bot;

    SizeT deletionCost = 1;
    SizeT insertionCost = 1;
    SizeT swapCost = 1;
};

#ifdef UINT8_SizeT
template class Distance<uint8_t>;
#endif

#ifdef UINT16_SizeT
template class Distance<uint16_t>;
#endif

#ifdef UINT32_SizeT
template class Distance<uint32_t>;
#endif

#ifdef UINT64_SizeT
template class Distance<uint64_t>;
#endif

}
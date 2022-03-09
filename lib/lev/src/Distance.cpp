#include "Distance.h"

//#define DRAW
//#define MEMORY_DEBUG

#if defined DRAW || defined MEMORY_DEBUG
    #include <iostream>
#endif


using namespace std;
using namespace Levenshtein;


//Public - static
template<typename SizeT>
SizeT Distance<SizeT>::getEditDistance(const string &pattern, const string &word) {
    return Distance<SizeT>::getDistance(pattern, word, 1, 1, 1);
}


template<typename SizeT>
SizeT Distance<SizeT>::getDistance(const string &pattern, const string &word,
                                   SizeT deletionCost, SizeT insertionCost, SizeT swapCost) {
    return Distance<SizeT>(pattern.size(), word.size(), deletionCost, insertionCost, swapCost).
            getDistance(pattern, word);
}


//Public
//Constructors
template<typename SizeT>
Distance<SizeT>::Distance(const SizeT& patternLength, const SizeT &wordLength) {
    this->patternLength = patternLength;
    this->wordLength = wordLength;
    this->tableSize = patternLength + 1; // +1 na słowo puste

    this->top = new SizeT[tableSize];
    this->bot = new SizeT[tableSize];

    #ifdef MEMORY_DEBUG
        cout << "KONSTRUKTOR " << this << endl;
        cout << top << " | ";
        cout << bot << endl;
    #endif
}


template<typename SizeT>
Distance<SizeT>::Distance(const SizeT& patternLength, const SizeT &wordLength,
                          SizeT deletionCost, SizeT insertionCost, SizeT swapCost) :
                          Distance<SizeT>::Distance(patternLength, wordLength) {
    this->setEditCosts(deletionCost, insertionCost, swapCost);
}


template<typename SizeT>
Distance<SizeT>::Distance(const Distance<SizeT>& other) :
    Distance(other.patternLength, other.wordLength,
             other.deletionCost, other.insertionCost, other.swapCost) {
}


template<typename SizeT>
Distance<SizeT>::Distance(Distance<SizeT>&& other) noexcept {
    this->patternLength = other.patternLength;
    this->wordLength = other.wordLength;
    this->tableSize = other.tableSize;
    this->deletionCost = other.deletionCost;
    this->insertionCost = other.insertionCost;
    this->swapCost = other.swapCost;

    std::swap(this->top, other.top);
    std::swap(this->bot, other.bot);

    other.~Distance();
}


//Methods
template<typename SizeT>
void Distance<SizeT>::setEditCosts(SizeT deletionCost, SizeT insertionCost, SizeT swapCost) {
    this->deletionCost = deletionCost;
    this->insertionCost = insertionCost;
    this->swapCost = swapCost;
}


template<typename SizeT>
SizeT Distance<SizeT>::getDistance(const string &pattern, const string &word) {
    SizeT delFullCost;
    SizeT insFullCost;
    SizeT swpFullCost;
    SizeT result;

    #ifdef DRAW
    cout << "   # ";
    for(auto ch: pattern) {
        cout << ch << " ";
    }
    cout << endl;
    cout << "#| ";
    #endif

    for (SizeT i = 0; i < tableSize; i++)
    {
        top[i] = i * deletionCost;

        #ifdef DRAW
            cout << (int)i << " ";
        #endif
    }

    #ifdef DRAW
        cout << endl;
    #endif

    for (size_t i = 0; i < wordLength; i++)
    {
        bot[0] = (i + 1) * insertionCost;

    #ifdef DRAW
        cout << word.at(i) << "| " << (int)bot[0] << " ";
    #endif

        for (SizeT j = 0; j < patternLength; j++)
        {
            insFullCost = top[j + 1] + insertionCost;
            delFullCost = bot[j] + deletionCost;
            swpFullCost = top[j];
            if (pattern.at(j) != word.at(i))
                swpFullCost += swapCost;

            bot[j + 1] = min(delFullCost, insFullCost, swpFullCost);

            #ifdef DRAW
                cout << (int)bot[j + 1] << " ";
            #endif
        }

        #ifdef DRAW
            cout << endl;
        #endif

        swap(top, bot);
    }

    #ifdef DRAW
        cout << endl;
    #endif

    result = top[patternLength];
    return result;
}


template<typename SizeT>
Distance<SizeT>::~Distance() {
    #ifdef MEMORY_DEBUG
        cout << "DESTRUKTOR " << this << endl;
        cout << top << " | ";
        cout << bot << endl << endl;
    #endif

    delete[] top;
    top = nullptr;

    delete[] bot;
    bot = nullptr;
}


//Protected - static
template<typename SizeT>
inline SizeT Distance<SizeT>::min(SizeT a, SizeT b, SizeT c) {
    auto x = (a < b) ? a : b;
    return (c < x) ? c : x;
}

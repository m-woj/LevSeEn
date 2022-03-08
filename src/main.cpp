#define TEST false

#if TEST
#include "tests.cpp"
#endif

#include <iostream>
#include "string"
#include "Distance.h"


using namespace std;
using namespace Levenshtein;


int main(int argc, char const *argv[])
{
    string pattern = "egg";
    string word = "megg";

    auto lev = Distance<uint8_t>::getEditDistance(pattern, word);
    cout << (int)lev;

//    auto test = Test("/home/mateusz/Pulpit/navarro.txt");
//    string pattern = "The method was based on a little general version of";
//    test.search(pattern);

//    auto lev = Levenshtein<uint8_t>();
//    auto pattern2 = "22Fhh321";
//    string word = "22Fehh321123123312312";
//    auto out = lev.lookFor(pattern2, word, 4);
//
//    for(auto o : *out) {
//        auto subword = word.substr(o.index, o.length);
//        cout << o.index << ": \"" << subword << "\" D=" << (int)o.distance;
//    }

    return 0;
}
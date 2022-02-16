#include "Levenshtein.hpp"


using namespace std;


struct SearchData {
    const string &pattern;
    const string &text;
    const size_t patternLength;
};


struct ThreadData {
    const SearchData& data;
    const size_t firstIndex;
    const size_t lastIndex;
    vector<size_t>* const output;
};


void normalSearch(SearchData &data, vector<size_t>* output) {
    for (auto i = 0; i < output->size(); i++) {
        output->at(i) = Levenshtein::getDistance(data.pattern,
                                                   data.text.substr(i, i + data.patternLength),
                                                   data.patternLength,
                                                   data.patternLength);
    }
}


void threadSearch(ThreadData tData) {
    auto data = tData.data;
    for (auto i = tData.firstIndex; i < tData.lastIndex; i++) {
        tData.output->at(i) = Levenshtein::getDistance(data.pattern,
                                                       data.text.substr(i, i + data.patternLength),
                                                       data.patternLength,
                                                       data.patternLength);
    }
}


void concurrentSearch(const SearchData &commonData, vector<size_t>* output) {
    const auto threadsNum = thread::hardware_concurrency();
    const auto lastThreadIndex = threadsNum - 1;
    const auto iterPerThread = output->size() / threadsNum;

    vector<thread> pool(threadsNum);

    size_t firstIndex = 0;
    auto lastIndex = iterPerThread;
    //Wątki
    for (int i=0; i < lastThreadIndex; i++) {
        ThreadData threadData = {commonData, firstIndex, lastIndex, output};
        pool.at(i) = thread(threadSearch, threadData);
        firstIndex += iterPerThread;
        lastIndex += iterPerThread;
    }

    //Ostatni wątek iteruje do końca (output->size())
    ThreadData threadData = {commonData, firstIndex, output->size(), output};
    pool.at(lastThreadIndex) = thread (threadSearch, threadData);

    for (auto &&t : pool)
        t.join();
}


vector<size_t>* Levenshtein::search(const string &pattern, const string &text) {
    auto patternLength = pattern.size();
    auto textLength = text.size();
    auto lastIndex = textLength - patternLength;
    auto complexity = (patternLength^2 * textLength);

    SearchData data {pattern, text, patternLength};
    auto output = new vector<size_t> (lastIndex);

    if (complexity > Levenshtein::multithreadingStart)
        concurrentSearch(data, output);
    else
        normalSearch(data, output);

    return output;
}
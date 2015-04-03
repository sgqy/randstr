#pragma once


struct argstore
{
    int length;
    int seed;

    wchar_t* rangeTable;
    int tableLength;

    FILE* outFile;

    argstore() :
        length(0),
        seed(0),
        rangeTable(0),
        tableLength(0),
        outFile(0)
    {};

    ~argstore() { if (rangeTable != 0) delete[] rangeTable; }

    void setSeed(const wchar_t*);
    void setLength(const wchar_t*);
    void setOutput(const wchar_t*);
    void setRange(const wchar_t*);
    void init();
};

inline void argstore::init()
{
    setSeed(0);
    setLength(0);
    setOutput(0);
    setRange(0);
}

inline void argstore::setSeed(const wchar_t* num)
{
    if (num == 0)
    {
        LARGE_INTEGER li = { 0 };
        QueryPerformanceCounter(&li);
        seed = li.LowPart;
    }
    else
    {
        seed = wcstol(num, 0, 10);
    }
    srand(seed);
}

inline void argstore::setLength(const wchar_t* num)
{
    if (num == 0)
        length = 32;
    else
        length = wcstol(num, 0, 10);
}

inline void argstore::setOutput(const wchar_t* name)
{
    if (name == 0)
        outFile = stdout;
    else
    {
        outFile = _wfopen(name, L"w+");
        if (outFile == 0)
            outFile = stdout;
    }
}

inline void argstore::setRange(const wchar_t* raw)
{
    std::list<wchar_t> rangeList;

    // set fallback
    if (raw == 0)
        raw = L"!~";

    int rawLen = wcslen(raw);
    rawLen /= 2;
    rawLen *= 2; // should be pairs, discard other

    // make list easier
    for (int i = 0; i < rawLen; i += 2)
    {
        for (auto s = raw[i]; s <= raw[i + 1]; ++s)
            rangeList.push_back(s);
    }

    // when reset, delete existing memory
    if (rangeTable != 0)
        delete[] rangeTable;

    // set new table array
    rangeTable = new wchar_t[tableLength = rangeList.size()];

    int index = 0;
    for (auto s : rangeList)
    {
        rangeTable[index++] = s;
    }
}

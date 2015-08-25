
#pragma once

extern std::default_random_engine rgen;

class argstore
{
    int outLen;
    int seed;

    FILE* outFile;

    std::set<wchar_t> range;

    void _push(const wchar_t, const wchar_t);
    void _numPush(const wchar_t*, const int);
public:
    argstore() :
        outLen(0),
        seed(0),
        outFile(0)
    {};

    ~argstore() {
        if (outFile != 0 && outFile != stdout) fclose(outFile);
    }

    void setSeed(const wchar_t*);
    void setOutLen(const wchar_t*);
    void setOutput(const wchar_t*);
    void setRange(const wchar_t*);

    auto& getRange() const { return range; }
    auto getOutput() const { return outFile; }
    auto getOutLen() const { return outLen; }

};

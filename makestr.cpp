
#include "stdafx.h"
#include "argstore.h"
#include "makestr.h"

std::default_random_engine rgen;

void makestr(argstore & arg)
{
    _setmode(_fileno(arg.getOutput()), _O_U16TEXT);

    // copy the range table for random access
    auto rangeSet = arg.getRange();
    int tbLen = 0;
    wchar_t* table = new wchar_t[tbLen = rangeSet.size()];

    int index = 0;
    for (auto s : rangeSet)
    {
        table[index++] = s;
    }

    // use the table to generate string
    int outLen = arg.getOutLen();
    int bufLen = outLen > MAX_PRINT_COUNT ? MAX_PRINT_COUNT : outLen;
    wchar_t* buff = new wchar_t[bufLen];

    std::uniform_int_distribution<int> dis(0, tbLen - 1);

    for (int i = 0; i < outLen; /**/)
    {
        int used = 0;
        for (; used < bufLen &&  i < outLen; ++used, ++i)
        {     
            buff[used] = table[dis(rgen)];
        }
        fwrite(buff, sizeof(wchar_t), used, arg.getOutput());

        if (arg.getOutput() == stdout)
        {
            wprintf(L"\n");

            // printing to screen has a max count
            break;
        }
    }
    delete[] buff;
}

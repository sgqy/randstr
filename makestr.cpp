
#include "stdafx.h"
#include "argstore.h"
#include "makestr.h"

std::default_random_engine rgen;

void makestr(argstore & arg)
{
    if (printMode == 'a') { _setmode(_fileno(arg.getOutput()), _O_TEXT); }
    else { _setmode(_fileno(arg.getOutput()), _O_U16TEXT); }

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
        for (; used < bufLen && i < outLen; ++used, ++i)
        {
            buff[used] = table[dis(rgen)];
        }

        if (printMode == 'a')
        {
            int cnt = WideCharToMultiByte(0, 0, buff, used, 0, 0, 0, 0);
            char* abuff = new char[cnt];
            WideCharToMultiByte(0, 0, buff, used, abuff, cnt, 0, 0);
            fwrite(abuff, sizeof(char), cnt, arg.getOutput());
        }
        else { fwrite(buff, sizeof(wchar_t), used, arg.getOutput()); }

        if (arg.getOutput() == stdout)
        {
            if (printMode == 'a') { printf("\n"); }
            else { wprintf(L"\n"); }

            // printing to screen has a max count
            break;
        }
    }
    delete[] buff;
}

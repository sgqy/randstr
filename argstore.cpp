
#include "stdafx.h"
#include "argstore.h"

void argstore::_numPush(const wchar_t* str, const int radix)
{
    wchar_t* cpy = new wchar_t[wcslen(str) + 1];

    // filt the raw input
    const wchar_t* table = L"0123456789abcdefABCDEF";

    for (int i = 0; i <= wcslen(str); ++i)
    {
        cpy[i] = str[i];
        int flag = 0;
        if (radix == 16)
        {
            for (int j = 0; j < wcslen(table); ++j)
                if (cpy[i] == table[j]) flag = 1;
        }
        else
        {
            for (int j = 0; j < 10; ++j)
                if (cpy[i] == table[j]) flag = 1;
        }
        if (flag == 0 && cpy[i] != 0) cpy[i] = L' ';
    }

    // cut the blank tail
    for (int i = wcslen(cpy); i >= 0; --i)
    {
        if (cpy[i] != L' ' && cpy[i] != 0)
        {
            cpy[i + 1] = 0;
            break;
        }
    }

    // convert to binary number
    wchar_t* end = cpy;
    while (end < cpy + wcslen(cpy))
    {
        int lhs = wcstol(end, &end, radix);
        int rhs = wcstol(end, &end, radix);

        _push(lhs, rhs);
    }

    delete[] cpy;
}

void argstore::setRange(const wchar_t* raw)
{
    if (raw == 0 || wcslen(raw) < 2)
    {
        _push(L'!', L'~');
        return;
    }

    if (raw[0] == L'\\' && raw[1] == L'c')
    {
        for (int i = 2; i < wcslen(raw); ++i)
            _push(raw[i], raw[i]);
    }
    else if (raw[0] == L'\\' && raw[1] == L'd')
    {
        _numPush(raw + 2, 10);
    }
    else if (raw[0] == L'\\' && raw[1] == L'x')
    {
        _numPush(raw + 2, 16);
    }
    else
    {
        wchar_t bare[200] = { 0 };
        for (int i = 0, j = 0; i < 200 && j < wcslen(raw); ++i, ++j)
        {
            if (L'\\' == (bare[i] = raw[j]) && L'\\' == raw[j + 1]) ++j;
        }

        int len = wcslen(bare) / 2;
        len *= 2;
        for (int i = 0; i < len; i += 2)
        {
            _push(bare[i], bare[i + 1]);
        }
    }

    // last fallback
    if (range.size() == 0) setRange(0);
}

void argstore::_push(const wchar_t lhs, const wchar_t rhs)
{
    for (wchar_t i = lhs; i <= rhs; ++i)
        range.insert(i);
}

void argstore::setSeed(const wchar_t* num)
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
    rgen.seed(seed);
}

void argstore::setOutLen(const wchar_t* num)
{
    if (num == 0)
        outLen = 32;
    else
        outLen = wcstol(num, 0, 10);
}

void argstore::setOutput(const wchar_t* name)
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


#include "stdafx.h"
#include "argstore.h"
#include "makestr.h"


void makestr(argstore & arg)
{
    _setmode(_fileno(arg.outFile), _O_U16TEXT);

    int buffLength = arg.length > 2048 ? 2048 : arg.length;
    wchar_t* buff = new wchar_t[buffLength];

    for (int i = 0; i < arg.length; /**/)
    {
        int used = 0;
        for (; used < buffLength &&  i < arg.length; ++used, ++i)
        {
            buff[used] = arg.mapping((rand() + rand()) & 0xFFFF); // RAND_MAX == 0x7FFF
        }
        fwrite(buff, sizeof(wchar_t), used, arg.outFile);
        if (arg.outFile == stdout)
        {
            wprintf(L"\n");
            break;
        }
    }
    delete[] buff;
}

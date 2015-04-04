// randstr.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "argstore.h"
#include "makestr.h"

void phelp()
{
    wprintf(
        L"\nUsage: randstr [options <optarg>]"
        L"\n    -r  Set char range       (!-~)."
        L"\n    -l  Set print length (32-2048)."
        L"\n    -o  Set output file   (STDOUT)."
        L"\n    -s  Set random seed (CPU Tick)."
        L"\n    -h  Print this help."
        L"\n"
        L"\nLength over 2048 only prints to a file."
        L"\nRange setting: -r 09azAZ for 0-9, a-z and A-Z."
        L"\n"
        );
    exit(0);
}


int wmain(int argc, wchar_t** argv)
{
    _setmode(_fileno(stdout), _O_U16TEXT);


    //if (argc == 1) phelp();

    argstore argparser;
    opterr = 0;

    argparser.init(); // no argument

    // now catch any argument
    int opt = 0;
    while (~(opt = getopt_w(argc, argv, L"s:l:o:r:h?")))
    {
        switch (opt)
        {
        case L's':
            argparser.setSeed(optarg_w);
            break;
        case L'l':
            argparser.setLength(optarg_w);
            break;
        case L'o':
            argparser.setOutput(optarg_w);
            break;
        case L'r':
            argparser.setRange(optarg_w);
            break;
        default:
            phelp();
        }
    }

    // do it
    makestr(argparser);


	return 0;
}

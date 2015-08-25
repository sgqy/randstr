
#include "stdafx.h"
#include "argstore.h"
#include "makestr.h"

void phelp()
{
    wprintf(
        L"\nUsage: randstr [options <optarg>]"
        L"\n    -r  Set char range       (!-~)."
        L"\n    -l  Set print length (32-%d)."
        L"\n    -o  Set output file   (STDOUT)."
        L"\n    -s  Set random seed (CPU Tick)."
        L"\n    -a  Print as ANSI."
        L"\n    -h  Print this help."
        L"\n"
        L"\nLength over 2048 only prints to a file."
        L"\nCommand line supports unicode."
        L"\nThe output file do not have unicode BOM."
        L"\n"
        L"\nRange setting:"
        L"\n    -r 05ezAM       : 0-5 & e-z & A-M."
        L"\n    -r dp\\\\Z        : d-p & \\-Z."
        L"\n    -r \\cTest       : T & e & s & t."
        L"\n    -r \\d0,35,76,89 : 0-35 & 76-89."
        L"\n    -r \\x0,A,2e,37  : 0x00-0x0A & 0x2E-0x37."
        L"\n", MAX_PRINT_COUNT
        );
    exit(0);
}

char printMode = 'u';

int wmain(int argc, wchar_t** argv)
{
    _setmode(_fileno(stdout), _O_U16TEXT);

    wchar_t* argSeed = 0;
    wchar_t* argLength = 0;
    wchar_t* argOutput = 0;
    wchar_t* argRange = 0;

    int opt = opterr = 0;
    while (~(opt = getopt_w(argc, argv, L"as:l:o:r:h?")))
    {
        switch (opt)
        {
        case L's':
            argSeed = optarg_w;
            break;
        case L'l':
            argLength = optarg_w;
            break;
        case L'o':
            argOutput = optarg_w;
            break;
        case L'r':
            argRange = optarg_w;
            break;
        case L'a':
            printMode = 'a';
            break;
        default:
            phelp();
        }
    }

    argstore argparser;

    argparser.setSeed(argSeed);
    argparser.setOutLen(argLength);
    argparser.setOutput(argOutput);
    argparser.setRange(argRange);


    // do it
    makestr(argparser);


	return 0;
}

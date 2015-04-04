
Usage: randstr [options <optarg>]
    -r  Set char range       (!-~).
    -l  Set print length (32-2048).
    -o  Set output file   (STDOUT).
    -s  Set random seed (CPU Tick).
    -h  Print this help.

Length over 2048 only prints to a file.
Command line supports unicode.
The output file do not have unicode BOM.

Range setting:
    -r 05ezAM       : 0-5 & e-z & A-M.
    -r dp\\Z        : d-p & \-Z.
    -r \cTest       : T & e & s & t.
    -r \d0,35,76,89 : 0-35 & 76-89.
    -r \x0,A,2e,37  : 0x00-0x0A & 0x2E-0x37.

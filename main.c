#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CHAR_TO_UPPER(ch)   ((ch >= 'a' && ch <= 'z')?(ch-0x20):ch)

//#define _Debug 1

int main(int argc, char* argv[])
{
    char ch;			//option letter
    char cksum[256];		//
    char *ret_hex = (char *) malloc(256);
    char *ret_ascii = (char *) malloc(256);
    int cmd=1;			//
    //command option
    if(argc <2)
    	PrintHelp(argv[0]);	//

    while ((ch = getopt(argc, argv, "t:r:d:s:p:h?")) != -1)
    {
        switch (ch)
        {
        case 'x':
            Ascii2Hex(optarg, ret_hex);
        strcpy(cksum, optarg);
        cmd=0;
    #ifdef Debug
        printf("x: %s\n", cksum);
        printf("ret_hex: %s\n", ret_hex);
    #endif
            break;
        case 'a':
            Hex2Ascii(optarg, ret_ascii);
        strcpy(cksum, optarg);
        cmd=1;
    #ifdef Debug
//        printf("a: %s\n", optarg);
        printf("ret_ascii: %s\n", ret_ascii);
    #endif
            break;
    case 'c':
    #ifdef Debug
        printf("cmd: %d\n", cmd);
        printf("cksum: %s\n", cksum);
    #endif
        checksum(cksum, cmd);
        break;
        case '?':
    case 'h':
        default:
        PrintHelp(argv[0]);
            exit(0);
            break;
        }
    }

//    Ascii2Hex(argv[1]);
//    Hex2Ascii(argv[1]);
    return 1;
}

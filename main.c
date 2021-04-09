#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CHAR_TO_UPPER(ch)   ((ch >= 'a' && ch <= 'z')?(ch-0x20):ch)

void PrintHelp(char *prog);

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

    while ((ch = getopt(argc, argv, "t:b:d:p:s:rh?")) != -1)
    {
        switch (ch)
        {
        case 't':	// send data 
            cmd=0;
    	#ifdef Debug
            printf("x: %s\n", cksum);
            printf("ret_hex: %s\n", ret_hex);
    	#endif
            break;
        case 'r':	// receive data
            cmd=1;
    	#ifdef Debug
//          printf("a: %s\n", optarg);
            printf("ret_ascii: %s\n", ret_ascii);
    	#endif
            break;
    	case 'b':	// baudrate 
    	#ifdef Debug
    	
	#endif
            break;
    	case 'd':	// data bits
    	#ifdef Debug
    	
	#endif
            break;
    	case 'p':	// parity bits
    	#ifdef Debug
    	
	#endif
            break;
    	case 's':	// stop bits
    	#ifdef Debug
    	
	#endif
            break;
        case '?':	// help information
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


/****************************************************
  * @help
  * @par param[in]
  * @retval: Null
  * @retval: print help information
****************************************************/
void PrintHelp(char* prog)
{
    printf("%s usage.\n", prog);
    printf("eg:\n");
    printf("%s -t abcdef\n", prog);
    printf("-t: ascii, default: abcdef, Send data\n");
    printf("-r: Receive data\n");
    printf("-b: set baudrate\n");
    printf("-d: set data bits\n");
    printf("-p: set parity btis.\n");
    printf("-s: set stop bits.\n");
    printf("-?: show help information\n");
    printf("-h: show help information\n");
}



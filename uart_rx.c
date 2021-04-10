#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/select.h>

int uart_rx(int argc, char **argv)
{
    int tty_fd =-1;		//tty device node
    int rv =-1;			//
    char r_buf[128];		//uart receive buffer
    struct termios options;	//uart attribute
    fd_set rset;		//


    tty_fd =open("/dev/ttyUSB0", O_RDWR|O_NOCTTY|O_NDELAY);  	//OPEN TTY DEVICE
    if(tty_fd <0)
    {
	printf("open tty device failed: %s\n", strerror(errno));
	close(tty_fd);
	exit(0);
    }
    printf("open devices sucessful!\n");

    memset(&options, 0, sizeof(options));	// initial tty options

    rv = tcgetattr(tty_fd, &options);		//get tty attribute
    if (rv != 0)
    {
	printf("tcgetattr() failed:%s\n", strerror(errno));
	close(tty_fd);
	exit(0);
    }

    options.c_cflag|=(CLOCAL|CREAD);	//CREAD: Enable uart receiver
    					//CLOCAL: ignore moderm control
    //set tty databits 
    options.c_cflag &=~CSIZE;		//initial tty databits
    options.c_cflag |=CS8;		//set tty databits=8
    //set tty parity
    options.c_cflag &= ~PARENB;		//disable parity
    
    //set tty baudrate
    cfsetispeed(&options, B115200);	//set input baud=115200
    cfsetospeed(&options, B115200);	//set output baud=115200

    //set stopbits
    options.c_cflag &= ~CSTOPB;		//set stopbits =1

    //set timeout
    options.c_cc[VTIME] =0;		//timeout =0
    options.c_cc[VMIN] =0;		//uart rx min bytes =0

    tcflush(tty_fd, TCIFLUSH);		//

    if((tcsetattr(tty_fd, TCSANOW, &options)) !=0)
    {
	printf("tcsetattr failed:%s\n", strerror(errno));
	close(tty_fd);
	exit(0);
    }

    while(1)
    {
	FD_ZERO(&rset);
	FD_SET(tty_fd, &rset);
	rv = select(tty_fd+1, &rset, NULL, NULL, NULL);
	
	if(rv <0)
	{
	    printf("select() failed: %s\n", strerror(errno));
	    close(tty_fd);
	    exit(0);
	}
	if(rv ==0)
	{
	    printf("select() time out!\n");
	    close(tty_fd);
	    exit(0);
	}

	memset(r_buf, 0, sizeof(r_buf));
	rv = read(tty_fd, r_buf, sizeof(r_buf));
	
	if(rv <0)
	{
	    printf("Read() error:%s\n", strerror(errno));
	    close(tty_fd);
	    exit(0);
	}
	
	printf("Read from tty: %s\n", r_buf);
    }


}


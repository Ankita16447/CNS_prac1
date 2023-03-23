// write a c program to communicate two machines using RS232C protocol

#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<bios.h>     //for bioscom

#define SETTINGS (_COM_9600 | _COM_CHR8 | _COM_NOPARITY |_COM_STOP1)
    /* baud rate = 9600, 8 data bits, no parity bit, 1 stop bit */
    void main(void)
    {
        unsigned i,out,status;int port;
        clrscr();
        printf("Select Port(Enter '0' for COM1 and '1' for COM2):");
        scanf("%d",&port);
        printf("Press ESC to exit");

        extcolor(YELLOW);
        cprintf("\n\rData Received:");

        bios_serialcom(_COM_INIT,port,SETTINGS);
        for(;;)
        {
            status=_bios_serialcom(_COM_STATUS,port,0);
            if (status & 512)printf("\n\t\a Overrun Error");
            if (status & 1024)printf("\n\t\a Parity Error");
            if (status & 2048)printf("\n\t\a Framing Error");
            if(status & (512|1024|2048)) /* if an error */

            break;
            if(status & 256)  /* if data ready */
            {
                if((out=_bios_serialcom(_COM_RECEIVE,port,0) & 255)!=0)
                {
                    putch(out);
                }

                if(kbhit()) /* if a keystroke is currently available */
                {
                    in=getch(); /* get a character without echoing onto the screen */
                    if(in==27) /* if ESC */
                    
                        break;
                        _bios_serialcom(_COM_SEND,port,in);
                    
                }
            }
        }
    }
    

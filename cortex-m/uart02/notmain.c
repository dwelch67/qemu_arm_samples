
void PUT32 ( unsigned int, unsigned int );
unsigned int GETPC ( void );
//#define UART0BASE 0x101f1000
#define UART0BASE 0x10009000

void uart_send ( unsigned int c )
{
    PUT32(UART0BASE+0x00,c);
}
void hexstrings ( unsigned int d )
{
    //unsigned int ra;
    unsigned int rb;
    unsigned int rc;

    rb=32;
    while(1)
    {
        rb-=4;
        rc=(d>>rb)&0xF;
        if(rc>9) rc+=0x37; else rc+=0x30;
        uart_send(rc);
        if(rb==0) break;
    }
    uart_send(0x20);
}
void hexstring ( unsigned int d )
{
    hexstrings(d);
    uart_send(0x0D);
    uart_send(0x0A);
}

int notmain ( void )
{    /* 0x10009000 UART0.  */

    unsigned int rx;
    for(rx=0;rx<8;rx++)
    {
        PUT32(UART0BASE+0x00,0x30+(rx&7));
    }
    uart_send(0x0D);
    uart_send(0x0A);
    hexstring(GETPC());
    return(0);
}

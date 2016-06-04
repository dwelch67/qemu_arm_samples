
//-------------------------------------------------------------------
//-------------------------------------------------------------------
void PUT32 ( unsigned int, unsigned int );
unsigned int GET32 ( unsigned int );
unsigned int GET8 ( unsigned int );
unsigned int GETPC ( void );

#define UART_BASE 0x101F1000
#define UARTDR    (UART_BASE+0x000)

//-------------------------------------------------------------------
static void uart_send ( unsigned int x )
{
    PUT32(UARTDR,x);
}
//-------------------------------------------------------------------
static void uart_init(void)
{
}
//-------------------------------------------------------------------
static void hexstrings ( unsigned int d )
{
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
//-------------------------------------------------------------------
static void hexstring ( unsigned int d )
{
    hexstrings(d);
    uart_send(0x0D);
    uart_send(0x0A);
}
//-------------------------------------------------------------------
int notmain ( void )
{
    unsigned int ra;

    uart_init();
    hexstring(0x12345678);
    hexstring(GETPC());
    for(ra=0;ra<0x200;ra+=4)
    {
        hexstrings(ra); hexstring(GET32(ra));
    }
    for(ra=0xFE0;ra<0x1000;ra+=4)
    {
        hexstrings(UART_BASE+ra); hexstring(GET32(UART_BASE+ra));
    }
    hexstring(0x12345678);
    return(0);
}
//-------------------------------------------------------------------
//-------------------------------------------------------------------

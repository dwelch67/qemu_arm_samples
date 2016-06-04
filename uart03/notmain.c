
//-------------------------------------------------------------------
//-------------------------------------------------------------------
void PUT32 ( unsigned int, unsigned int );
unsigned int GET32 ( unsigned int );
unsigned int GET8 ( unsigned int );
unsigned int GETPC ( void );

#define UART_BASE 0x101F1000
#define UARTDR    (UART_BASE+0x000)
#define UARTFR    (UART_BASE+0x018)

//-------------------------------------------------------------------
static void uart_send ( unsigned int x )
{
    while(1)
    {
        if(GET32(UARTFR)&(1<<7)) break;
    }
    PUT32(UARTDR,x);
}
//-------------------------------------------------------------------
static unsigned int uart_recv ( void )
{
    while(1)
    {
        if(GET32(UARTFR)&(1<<6)) break;
    }
    return(GET32(UARTDR));
}
//-------------------------------------------------------------------
static void uart_init(void)
{
    GET32(UARTDR);
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
    unsigned int rb;

    uart_init();
    PUT32(UARTDR,0x55);
    ra=GET32(UARTFR);
    hexstring(ra);
    ra=GET32(UARTDR);
    rb=GET32(UARTFR);
    hexstrings(ra); hexstring(rb);

    while(1)
    {
        ra=uart_recv();
        if(ra==0x0D) uart_send(0x0A);
        uart_send(ra);
    }

    return(0);
}
//-------------------------------------------------------------------
//-------------------------------------------------------------------
